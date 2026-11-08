#ifndef ML_SPI_GAUGE_HPP
#define ML_SPI_GAUGE_HPP

#include <cstdint>

namespace mylinux {

class SPIGauge {
public:
    virtual ~SPIGauge() = default;

    virtual int transfer(
        const uint8_t *transmit,
        uint8_t *receive,
        unsigned long length
    ) = 0;
};

}

#endif
