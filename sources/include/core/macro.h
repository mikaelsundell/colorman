// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <QDebug>

class DebugHelper {
public:
    DebugHelper(const char* function)
        : stream(qDebug() << "Function:" << function) {}

    template <typename T>
    QDebug operator<<(const T& value) {
        return stream << value;
    }

private:
    QDebug stream;
};

#define CoreDebug() DebugHelper(__PRETTY_FUNCTION__)
