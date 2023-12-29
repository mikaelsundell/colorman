// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <QMainWindow>

namespace colorman {

class WindowPrivate;
class Window : public QMainWindow
{
    Q_OBJECT
    public:
        Window();
        virtual ~Window();
    private:
        QScopedPointer<WindowPrivate> p;
};

}
