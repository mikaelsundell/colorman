// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <QWidget>

namespace colorman {

class PythonWidgetPrivate;
class PythonWidget : public QWidget
{
    Q_OBJECT
    public:
        PythonWidget(QWidget* parent = nullptr);
        virtual ~PythonWidget();
    
    private:
        QScopedPointer<PythonWidgetPrivate> p;
};

}
