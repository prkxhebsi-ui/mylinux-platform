#ifndef MYLINUX_ART_DEX_MAP_VERIFIER_H
#define MYLINUX_ART_DEX_MAP_VERIFIER_H

#include <cstddef>
#include <cstdint>
#include <string>

#include <mylinux/art/dex/DexVerifier.h>

namespace art {
namespace dex {

class DexMapVerifier {
public:
    bool Verify(
        const uint8_t* data,
        size_t available_size,
        const DexHeaderInfo& header
    );

    const std::string& GetError() const;

private:
    std::string error_;
};

} // namespace dex
} // namespace art

#endif
