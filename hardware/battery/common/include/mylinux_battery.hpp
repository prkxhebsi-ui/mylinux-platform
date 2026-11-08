#ifndef MYLINUX_BATTERY_HPP
#define MYLINUX_BATTERY_HPP

#include "mylinux_battery.h"

namespace mylinux {

class Battery {
public:
    explicit Battery(mylinux_battery_device device)
        : device_(device) {}

    int read(mylinux_battery_sample& sample) {
        return mylinux_battery_read(&device_, &sample);
    }

    mylinux_battery_configuration configuration() const {
        return device_.configuration;
    }

private:
    mylinux_battery_device device_;
};

} // namespace mylinux

#endif
