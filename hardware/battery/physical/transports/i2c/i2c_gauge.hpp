#ifndef ML_I2C_GAUGE_HPP
#define ML_I2C_GAUGE_HPP

#include <cstdint>

namespace mylinux {

class I2CGauge {
public:
    virtual ~I2CGauge() = default;

    virtual int readRegister(
        uint8_t address,
        uint8_t *data,
        unsigned long length
    ) = 0;

    virtual int writeRegister(
        uint8_t address,
        const uint8_t *data,
        unsigned long length
    ) = 0;
};

}

#endif
