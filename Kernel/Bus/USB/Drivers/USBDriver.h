/*
 * Copyright (c) 2023, Jesse Buhagiar <jesse.buhagiar@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/AtomicRefCounted.h>
#include <AK/Error.h>
#include <AK/NonnullRefPtr.h>
#include <Kernel/DriverInitTable.h>

namespace Kernel::USB {

#define USB_DEVICE_DRIVER(driver_name) DRIVER_INIT_FUNCTION(driver_name, driver_name::init)

class Device;
struct USBDeviceDescriptor;
class USBInterface;

class Driver : public AtomicRefCounted<Driver> {
public:
    Driver(StringView name)
        : m_driver_name(name)
    {
    }

    virtual ~Driver() = default;

    virtual ErrorOr<void> probe(USB::Device&) = 0;
    virtual void detach(USB::Device&) = 0;
    StringView name() const { return m_driver_name; }

protected:
    StringView const m_driver_name;
};
}
