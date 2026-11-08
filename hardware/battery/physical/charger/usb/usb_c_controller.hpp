#ifndef ML_USB_C_CONTROLLER_HPP
#define ML_USB_C_CONTROLLER_HPP

#include "usb_common.h"

namespace mylinux {

class USBTypeCController {
public:
    virtual ~USBTypeCController() = default;

    virtual int readConnection(
        ml_usb_power_information& information
    ) = 0;

    virtual int readOrientation(int& orientation) = 0;
};

}

#endif
