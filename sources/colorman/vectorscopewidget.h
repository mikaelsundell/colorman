// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/utilities/vectorscope

#pragma once

#include <QWidget>

namespace colorman {

class VectorscopeWidgetPrivate;
class VectorscopeWidget : public QWidget
{
    Q_OBJECT
    public:
        VectorscopeWidget(QWidget* parent = nullptr);
        virtual ~VectorscopeWidget();
    
    public Q_SLOTS:
        void setImage(const QImage& image);
    
    protected:
        void paintEvent(QPaintEvent* event) override;
    
    private:
        QScopedPointer<VectorscopeWidgetPrivate> p;
};

}