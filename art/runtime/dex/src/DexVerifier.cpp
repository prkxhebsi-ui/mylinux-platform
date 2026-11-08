#include <mylinux/art/dex/DexVerifier.h>

#include <cstring>
#include <limits>

namespace art {
namespace dex {

namespace {

constexpr uint32_t kHeaderSize = 112;
constexpr uint32_t kEndianConstant = 0x12345678U;

uint32_t ReadU32(const uint8_t* p) {
    return static_cast<uint32_t>(p[0]) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

bool SupportedVersion(const uint8_t* magic) {
    if (std::memcmp(magic, "dex\n", 4) != 0)
        return false;

    if (magic[7] != 0)
        return false;

    const char* version =
        reinterpret_cast<const char*>(magic + 4);

    return std::strcmp(version, "035") == 0 ||
           std::strcmp(version, "037") == 0 ||
           std::strcmp(version, "038") == 0 ||
           std::strcmp(version, "039") == 0 ||
           std::strcmp(version, "040") == 0 ||
           std::strcmp(version, "041") == 0;
}

bool RangeFits(
    uint32_t offset,
    uint32_t count,
    uint32_t item_size,
    uint32_t file_size
) {
    if (count == 0)
        return offset == 0;

    if (offset == 0 || item_size == 0)
        return false;

    const uint64_t end =
        static_cast<uint64_t>(offset) +
        static_cast<uint64_t>(count) * item_size;

    return end <= file_size;
}

} // namespace

bool DexVerifier::ValidateSection(
    const DexSection& section,
    uint32_t file_size,
    const char* name
) {
    if (section.count == 0) {
        if (section.offset != 0) {
            error_ = std::string(name) +
                     ": offset must be zero when count is zero";
            return false;
        }

        return true;
    }

    if (section.offset < kHeaderSize) {
        error_ = std::string(name) +
                 ": section overlaps DEX header";
        return false;
    }

    if ((section.offset & 3U) != 0) {
        error_ = std::string(name) +
                 ": section offset is not 4-byte aligned";
        return false;
    }

    if (!RangeFits(
            section.offset,
            section.count,
            section.item_size,
            file_size)) {
        error_ = std::string(name) +
                 ": section extends beyond DEX file";
        return false;
    }

    return true;
}

bool DexVerifier::VerifyHeader(
    const uint8_t* data,
    size_t available_size,
    DexHeaderInfo* output
) {
    error_.clear();

    if (data == nullptr || output == nullptr) {
        error_ = "null input or output";
        return false;
    }

    if (available_size < kHeaderSize) {
        error_ = "truncated DEX header";
        return false;
    }

    if (!SupportedVersion(data)) {
        error_ = "invalid or unsupported standard DEX version";
        return false;
    }

    DexHeaderInfo h{};

    std::memcpy(h.version, data + 4, 3);
    h.version[3] = '\0';

    h.checksum = ReadU32(data + 8);
    h.file_size = ReadU32(data + 32);
    h.header_size = ReadU32(data + 36);
    h.endian_tag = ReadU32(data + 40);

    h.link_size = ReadU32(data + 44);
    h.link_offset = ReadU32(data + 48);
    h.map_offset = ReadU32(data + 52);

    h.strings = {
        ReadU32(data + 56), ReadU32(data + 60), 4
    };

    h.types = {
        ReadU32(data + 64), ReadU32(data + 68), 4
    };

    h.prototypes = {
        ReadU32(data + 72), ReadU32(data + 76), 12
    };

    h.fields = {
        ReadU32(data + 80), ReadU32(data + 84), 8
    };

    h.methods = {
        ReadU32(data + 88), ReadU32(data + 92), 8
    };

    h.classes = {
        ReadU32(data + 96), ReadU32(data + 100), 32
    };

    h.data_size = ReadU32(data + 104);
    h.data_offset = ReadU32(data + 108);

    if (h.header_size != kHeaderSize) {
        error_ = "invalid DEX header size";
        return false;
    }

    if (h.file_size < kHeaderSize ||
        h.file_size > available_size) {
        error_ = "invalid DEX file size";
        return false;
    }

    if (h.endian_tag != kEndianConstant) {
        error_ = "unsupported DEX byte order";
        return false;
    }

    if ((h.link_size == 0) != (h.link_offset == 0)) {
        error_ = "inconsistent link section";
        return false;
    }

    if (h.link_size != 0) {
        if (h.link_offset < kHeaderSize ||
            static_cast<uint64_t>(h.link_offset) +
                h.link_size > h.file_size) {
            error_ = "link section extends beyond DEX file";
            return false;
        }
    }

    if (h.map_offset != 0) {
        if (h.map_offset < kHeaderSize ||
            (h.map_offset & 3U) != 0 ||
            h.map_offset > h.file_size - 4) {
            error_ = "invalid map section offset";
            return false;
        }
    }

    if ((h.data_size == 0) != (h.data_offset == 0)) {
        error_ = "inconsistent data section";
        return false;
    }

    if (h.data_size != 0) {
        if (h.data_offset < kHeaderSize ||
            (h.data_offset & 3U) != 0 ||
            static_cast<uint64_t>(h.data_offset) +
                h.data_size > h.file_size) {
            error_ = "data section extends beyond DEX file";
            return false;
        }
    }

    if (!ValidateSection(h.strings, h.file_size, "strings") ||
        !ValidateSection(h.types, h.file_size, "types") ||
        !ValidateSection(h.prototypes, h.file_size, "prototypes") ||
        !ValidateSection(h.fields, h.file_size, "fields") ||
        !ValidateSection(h.methods, h.file_size, "methods") ||
        !ValidateSection(h.classes, h.file_size, "classes")) {
        return false;
    }

    *output = h;
    return true;
}

const std::string& DexVerifier::GetError() const {
    return error_;
}

} // namespace dex
} // namespace art
