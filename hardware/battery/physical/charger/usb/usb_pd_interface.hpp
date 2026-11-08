#ifndef ML_USB_PD_INTERFACE_HPP
#define ML_USB_PD_INTERFACE_HPP

#include <cstdint>

namespace mylinux {

struct PDContract {
    uint32_t voltageMillivolts;
    uint32_t currentMilliamps;
    uint32_t powerMilliwatts;
    bool valid;
};

class USBPowerDeliveryController {
public:
    virtual ~USBPowerDeliveryController() = default;

    virtual int readContract(PDContract& contract) = 0;
    virtual int readFaultStatus(uint32_t& faults) = 0;
};

}

#endif
