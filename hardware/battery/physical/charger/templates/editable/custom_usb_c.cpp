/* EDITABLE USB-C controller integration template. */

#include "../../usb/usb_c_controller.hpp"

class CustomUSBTypeC : public mylinux::USBTypeCController {
public:
    int readConnection(
        ml_usb_power_information& information
    ) override {
        (void)information;
        /* TODO: read a compliant Type-C controller. */
        return -1;
    }

    int readOrientation(int& orientation) override {
        (void)orientation;
        return -1;
    }
};
