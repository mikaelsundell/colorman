// Copyright 2023-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <QMainWindow>

class ColormanPrivate;
class Colorman : public QMainWindow
{
    Q_OBJECT
    public:
        Colorman();
        virtual ~Colorman();
    private:
        QScopedPointer<ColormanPrivate> p;
};
