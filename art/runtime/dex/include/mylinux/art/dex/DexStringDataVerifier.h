#ifndef MYLINUX_ART_DEX_STRING_DATA_VERIFIER_H
#define MYLINUX_ART_DEX_STRING_DATA_VERIFIER_H

#include <cstddef>
#include <cstdint>
#include <string>

#include <mylinux/art/dex/DexVerifier.h>

namespace art {
namespace dex {

class DexStringDataVerifier {
public:
    bool Verify(
        const uint8_t* data,
        size_t available_size,
        const DexHeaderInfo& header,
        uint32_t* verified_count = nullptr
    );

    const std::string& GetError() const;

private:
    bool VerifyString(
        const uint8_t* data,
        uint32_t file_size,
        uint32_t offset,
        uint32_t string_index
    );

    std::string error_;
};

} // namespace dex
} // namespace art

#endif
