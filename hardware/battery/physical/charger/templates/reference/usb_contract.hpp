#ifndef ML_CANONICAL_USB_CONTRACT_HPP
#define ML_CANONICAL_USB_CONTRACT_HPP

#include "../../interfaces/charger_hardware.hpp"

/* Canonical USB charger integration reference. */

namespace mylinux {

struct USBChargerReference {
    uint32_t inputVoltageMillivolts;
    uint32_t inputCurrentMilliamps;
    bool cablePresent;
    bool contractValid;
};

}

#endif
