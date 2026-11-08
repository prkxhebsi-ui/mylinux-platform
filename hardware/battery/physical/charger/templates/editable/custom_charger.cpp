/* EDITABLE C++ charger driver template. */

#include "../../interfaces/charger_hardware.hpp"

class CustomCharger : public mylinux::ChargerHardware {
public:
    int initialize() override {
        /* TODO: initialize the selected charger controller. */
        return -1;
    }

    int readStatus(
        ml_charger_status& status
    ) override {
        (void)status;
        /* TODO: read actual controller status. */
        return -1;
    }

    int readFaults(uint32_t& faults) override {
        (void)faults;
        return -1;
    }

    const char *driverName() const override {
        return "MyLinux Custom Charger";
    }
};
