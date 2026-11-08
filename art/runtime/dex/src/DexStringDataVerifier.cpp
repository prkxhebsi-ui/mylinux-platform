#include <mylinux/art/dex/DexStringDataVerifier.h>

namespace art {
namespace dex {

namespace {

constexpr uint32_t kHeaderSize = 112;

uint32_t ReadU32(const uint8_t* p) {
    return static_cast<uint32_t>(p[0]) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

bool ReadUleb128(
    const uint8_t* data,
    uint32_t limit,
    uint32_t* offset,
    uint32_t* value
) {
    if (data == nullptr || offset == nullptr || value == nullptr)
        return false;

    uint32_t result = 0;

    for (unsigned int i = 0; i < 5; ++i) {
        if (*offset >= limit)
            return false;

        const uint8_t byte = data[(*offset)++];

        // A uint32_t ULEB128 value has only four usable bits
        // in its fifth byte.
        if (i == 4 && (byte & 0xF0U) != 0)
            return false;

        result |= static_cast<uint32_t>(byte & 0x7FU) << (i * 7);

        if ((byte & 0x80U) == 0) {
            *value = result;
            return true;
        }
    }

    return false;
}

bool ValidateModifiedUtf8(
    const uint8_t* data,
    uint32_t begin,
    uint32_t end,
    uint32_t expected_utf16_units
) {
    uint32_t offset = begin;
    uint32_t utf16_units = 0;

    while (offset < end) {
        const uint8_t first = data[offset];

        if (first == 0) {
            return utf16_units == expected_utf16_units &&
                   offset + 1 == end;
        }

        if (first <= 0x7F) {
            ++offset;
            ++utf16_units;
            continue;
        }

        if (first >= 0xC0 && first <= 0xDF) {
            if (offset + 1 >= end)
                return false;

            const uint8_t second = data[offset + 1];

            if ((second & 0xC0U) != 0x80U)
                return false;

            const uint32_t value =
                (static_cast<uint32_t>(first & 0x1FU) << 6) |
                static_cast<uint32_t>(second & 0x3FU);

            // Modified UTF-8 permits C0 80 for U+0000.
            // Other two-byte sequences must not be overlong.
            if (value == 0) {
                if (first != 0xC0 || second != 0x80)
                    return false;
            } else if (value < 0x80) {
                return false;
            }

            offset += 2;
            ++utf16_units;
            continue;
        }

        if (first >= 0xE0 && first <= 0xEF) {
            if (offset + 2 >= end)
                return false;

            const uint8_t second = data[offset + 1];
            const uint8_t third = data[offset + 2];

            if ((second & 0xC0U) != 0x80U ||
                (third & 0xC0U) != 0x80U) {
                return false;
            }

            const uint32_t value =
                (static_cast<uint32_t>(first & 0x0FU) << 12) |
                (static_cast<uint32_t>(second & 0x3FU) << 6) |
                static_cast<uint32_t>(third & 0x3FU);

            if (value < 0x800)
                return false;

            // DEX Modified UTF-8 represents UTF-16 code units.
            // Surrogate code units are therefore accepted here.
            offset += 3;
            ++utf16_units;
            continue;
        }

        // Four-byte UTF-8 sequences are not valid Modified UTF-8.
        return false;
    }

    return false;
}

} // namespace

bool DexStringDataVerifier::VerifyString(
    const uint8_t* data,
    uint32_t file_size,
    uint32_t offset,
    uint32_t string_index
) {
    if (offset >= file_size) {
        error_ = "string[" + std::to_string(string_index) +
                 "]: offset outside DEX file";
        return false;
    }

    uint32_t cursor = offset;
    uint32_t expected_length = 0;

    if (!ReadUleb128(data, file_size, &cursor, &expected_length)) {
        error_ = "string[" + std::to_string(string_index) +
                 "]: invalid ULEB128 length";
        return false;
    }

    const uint32_t string_begin = cursor;

    while (cursor < file_size && data[cursor] != 0)
        ++cursor;

    if (cursor >= file_size) {
        error_ = "string[" + std::to_string(string_index) +
                 "]: missing null terminator";
        return false;
    }

    // Include the null terminator in the bounded validation range.
    const uint32_t string_end = cursor + 1;

    if (!ValidateModifiedUtf8(
            data,
            string_begin,
            string_end,
            expected_length)) {
        error_ = "string[" + std::to_string(string_index) +
                 "]: invalid Modified UTF-8 or UTF-16 length";
        return false;
    }

    return true;
}

bool DexStringDataVerifier::Verify(
    const uint8_t* data,
    size_t available_size,
    const DexHeaderInfo& header,
    uint32_t* verified_count
) {
    error_.clear();

    if (verified_count != nullptr)
        *verified_count = 0;

    if (data == nullptr) {
        error_ = "null DEX data";
        return false;
    }

    if (header.file_size < kHeaderSize ||
        header.file_size > available_size) {
        error_ = "invalid DEX file size";
        return false;
    }

    if (header.data_size == 0 ||
        header.data_offset < kHeaderSize ||
        static_cast<uint64_t>(header.data_offset) +
            header.data_size > header.file_size) {
        error_ = "invalid DEX data section";
        return false;
    }

    if (header.strings.count == 0) {
        if (header.strings.offset != 0) {
            error_ = "empty string table has nonzero offset";
            return false;
        }

        return true;
    }

    if (header.strings.offset < kHeaderSize ||
        (header.strings.offset & 3U) != 0) {
        error_ = "invalid string ID table offset";
        return false;
    }

    const uint64_t ids_end =
        static_cast<uint64_t>(header.strings.offset) +
        static_cast<uint64_t>(header.strings.count) * 4ULL;

    if (ids_end > header.file_size) {
        error_ = "string ID table extends beyond DEX file";
        return false;
    }

    const uint32_t data_begin = header.data_offset;
    const uint32_t data_end = header.data_offset + header.data_size;

    for (uint32_t i = 0; i < header.strings.count; ++i) {
        const uint32_t id_offset =
            header.strings.offset + i * 4U;

        const uint32_t string_offset =
            ReadU32(data + id_offset);

        if (string_offset < data_begin ||
            string_offset >= data_end) {
            error_ = "string[" + std::to_string(i) +
                     "]: string data offset outside data section";
            return false;
        }

        if (!VerifyString(
                data,
                data_end,
                string_offset,
                i)) {
            return false;
        }

        if (verified_count != nullptr)
            ++(*verified_count);
    }

    return true;
}

const std::string& DexStringDataVerifier::GetError() const {
    return error_;
}

} // namespace dex
} // namespace art
