#ifndef MYLINUX_ART_DEX_VERIFIER_H
#define MYLINUX_ART_DEX_VERIFIER_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace art {
namespace dex {

struct DexSection {
    uint32_t count = 0;
    uint32_t offset = 0;
    uint32_t item_size = 0;
};

struct DexHeaderInfo {
    char version[4] = {};
    uint32_t checksum = 0;
    uint32_t file_size = 0;
    uint32_t header_size = 0;
    uint32_t endian_tag = 0;
    uint32_t link_size = 0;
    uint32_t link_offset = 0;
    uint32_t map_offset = 0;

    DexSection strings;
    DexSection types;
    DexSection prototypes;
    DexSection fields;
    DexSection methods;
    DexSection classes;

    uint32_t data_size = 0;
    uint32_t data_offset = 0;
};

class DexVerifier {
public:
    bool VerifyHeader(
        const uint8_t* data,
        size_t available_size,
        DexHeaderInfo* output
    );

    const std::string& GetError() const;

private:
    bool ValidateSection(
        const DexSection& section,
        uint32_t file_size,
        const char* name
    );

    std::string error_;
};

} // namespace dex
} // namespace art

#endif
