// Copyright 2022-present Contributors to the colorpicker project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "mac.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

namespace mac
{
    void setupMac()
    {
        // we force dark aque no matter appearance set in system settings
        [NSApp setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameDarkAqua]];
    }
}
