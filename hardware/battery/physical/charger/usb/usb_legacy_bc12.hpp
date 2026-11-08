#ifndef ML_USB_LEGACY_BC12_HPP
#define ML_USB_LEGACY_BC12_HPP

#include "usb_common.h"

namespace mylinux {

class LegacyUSBDetector {
public:
    virtual ~LegacyUSBDetector() = default;

    virtual int detect(
        ml_usb_power_information& information
    ) = 0;
};

}

#endif
