#include <mylinux/art/dex/DexMapVerifier.h>

#include <algorithm>
#include <cstring>
#include <vector>

namespace art {
namespace dex {

namespace {

constexpr uint32_t kHeaderSize = 112;
constexpr uint32_t kMapItemSize = 12;

uint16_t ReadU16(const uint8_t* p) {
    return static_cast<uint16_t>(p[0]) |
           (static_cast<uint16_t>(p[1]) << 8);
}

uint32_t ReadU32(const uint8_t* p) {
    return static_cast<uint32_t>(p[0]) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

struct MapEntry {
    uint16_t type;
    uint16_t unused;
    uint32_t count;
    uint32_t offset;
};

struct Range {
    uint64_t begin;
    uint64_t end;
    uint16_t type;
};

bool IsKnownType(uint16_t type) {
    switch (type) {
        case 0x0000: // header_item
        case 0x0001: // string_id_item
        case 0x0002: // type_id_item
        case 0x0003: // proto_id_item
        case 0x0004: // field_id_item
        case 0x0005: // method_id_item
        case 0x0006: // class_def_item
        case 0x0007: // call_site_id_item
        case 0x0008: // method_handle_item
        case 0x1000: // map_list
        case 0x1001: // type_list
        case 0x1002: // annotation_set_ref_list
        case 0x1003: // annotation_set_item
        case 0x2000: // class_data_item
        case 0x2001: // code_item
        case 0x2002: // string_data_item
        case 0x2003: // debug_info_item
        case 0x2004: // annotation_item
        case 0x2005: // encoded_array_item
        case 0x2006: // annotations_directory_item
        case 0xF000: // hiddenapi_class_data_item
            return true;
        default:
            return false;
    }
}

uint32_t FixedItemSize(uint16_t type) {
    switch (type) {
        case 0x0000: return 112;
        case 0x0001: return 4;
        case 0x0002: return 4;
        case 0x0003: return 12;
        case 0x0004: return 8;
        case 0x0005: return 8;
        case 0x0006: return 32;
        case 0x0007: return 4;
        case 0x0008: return 8;
        case 0x1000: return 12;
        case 0x1002: return 4;
        case 0x1003: return 4;
        case 0x2001: return 0; // Variable length, 4-byte aligned.
        case 0x2006: return 16;
        default: return 0;
    }
}

bool RequiresFourByteAlignment(uint16_t type) {
    switch (type) {
        case 0x0000:
        case 0x0001:
        case 0x0002:
        case 0x0003:
        case 0x0004:
        case 0x0005:
        case 0x0006:
        case 0x0007:
        case 0x0008:
        case 0x1000:
        case 0x1001:
        case 0x1002:
        case 0x1003:
        case 0x2001:
        case 0x2006:
            return true;
        default:
            return false;
    }
}

} // namespace

bool DexMapVerifier::Verify(
    const uint8_t* data,
    size_t available_size,
    const DexHeaderInfo& header
) {
    error_.clear();

    if (data == nullptr) {
        error_ = "null DEX data";
        return false;
    }

    if (header.file_size < kHeaderSize ||
        header.file_size > available_size) {
        error_ = "invalid file size supplied by header";
        return false;
    }

    if (header.map_offset == 0) {
        error_ = "DEX map list is missing";
        return false;
    }

    if ((header.map_offset & 3U) != 0 ||
        header.map_offset < kHeaderSize ||
        header.map_offset > header.file_size - 4) {
        error_ = "invalid map-list offset";
        return false;
    }

    const uint32_t entry_count = ReadU32(data + header.map_offset);

    const uint64_t map_end =
        static_cast<uint64_t>(header.map_offset) + 4ULL +
        static_cast<uint64_t>(entry_count) * kMapItemSize;

    if (entry_count == 0 || map_end > header.file_size) {
        error_ = "map-list entries extend beyond DEX file";
        return false;
    }

    std::vector<MapEntry> entries;
    std::vector<Range> fixed_ranges;

    entries.reserve(entry_count);
    fixed_ranges.reserve(entry_count + 1);

    // The header itself occupies bytes 0 through 111.
    fixed_ranges.push_back({0, kHeaderSize, 0x0000});

    uint32_t previous_offset = 0;
    bool first = true;

    for (uint32_t i = 0; i < entry_count; ++i) {
        const uint8_t* p =
            data + header.map_offset + 4 +
            static_cast<size_t>(i) * kMapItemSize;

        MapEntry entry{
            ReadU16(p),
            ReadU16(p + 2),
            ReadU32(p + 4),
            ReadU32(p + 8)
        };

        if (!IsKnownType(entry.type)) {
            error_ = "unknown DEX map item type";
            return false;
        }

        if (entry.unused != 0) {
            error_ = "map item reserved field is not zero";
            return false;
        }

        if (entry.count == 0) {
            error_ = "map item has zero item count";
            return false;
        }

        if (entry.offset >= header.file_size) {
            error_ = "map item offset is outside DEX file";
            return false;
        }

        if (!first && entry.offset <= previous_offset) {
            error_ = "map items are not sorted by offset";
            return false;
        }

        if (RequiresFourByteAlignment(entry.type) &&
            (entry.offset & 3U) != 0) {
            error_ = "map item has invalid alignment";
            return false;
        }

        for (const MapEntry& old : entries) {
            if (old.type == entry.type) {
                error_ = "duplicate map item type";
                return false;
            }
        }

        if (entry.type == 0x0000 &&
            (entry.count != 1 || entry.offset != 0)) {
            error_ = "invalid header map entry";
            return false;
        }

        if (entry.type == 0x1000 &&
            (entry.count != 1 ||
             entry.offset != header.map_offset)) {
            error_ = "map-list entry does not match header";
            return false;
        }

        const uint32_t item_size = FixedItemSize(entry.type);

        if (item_size != 0) {
            const uint64_t end =
                static_cast<uint64_t>(entry.offset) +
                static_cast<uint64_t>(entry.count) * item_size;

            if (end > header.file_size) {
                error_ = "fixed-size map section exceeds DEX file";
                return false;
            }

            fixed_ranges.push_back({
                entry.offset, end, entry.type
            });
        }

        entries.push_back(entry);
        previous_offset = entry.offset;
        first = false;
    }

    auto find_entry = [&entries](uint16_t type)
        -> const MapEntry* {
        for (const MapEntry& entry : entries) {
            if (entry.type == type)
                return &entry;
        }
        return nullptr;
    };

    auto matches_header = [&](uint16_t type,
                              uint32_t count,
                              uint32_t offset) -> bool {
        const MapEntry* entry = find_entry(type);

        if (count == 0)
            return entry == nullptr;

        return entry != nullptr &&
               entry->count == count &&
               entry->offset == offset;
    };

    if (find_entry(0x0000) == nullptr) {
        error_ = "header map entry is missing";
        return false;
    }

    if (find_entry(0x1000) == nullptr) {
        error_ = "map-list map entry is missing";
        return false;
    }

    if (!matches_header(0x0001,
                        header.strings.count,
                        header.strings.offset) ||
        !matches_header(0x0002,
                        header.types.count,
                        header.types.offset) ||
        !matches_header(0x0003,
                        header.prototypes.count,
                        header.prototypes.offset) ||
        !matches_header(0x0004,
                        header.fields.count,
                        header.fields.offset) ||
        !matches_header(0x0005,
                        header.methods.count,
                        header.methods.offset) ||
        !matches_header(0x0006,
                        header.classes.count,
                        header.classes.offset)) {
        error_ = "map entries do not match DEX header sections";
        return false;
    }

    std::sort(
        fixed_ranges.begin(),
        fixed_ranges.end(),
        [](const Range& a, const Range& b) {
            return a.begin < b.begin;
        }
    );

    for (size_t i = 1; i < fixed_ranges.size(); ++i) {
        if (fixed_ranges[i].begin < fixed_ranges[i - 1].end) {
            error_ = "fixed-size DEX sections overlap";
            return false;
        }
    }

    return true;
}

const std::string& DexMapVerifier::GetError() const {
    return error_;
}

} // namespace dex
} // namespace art
