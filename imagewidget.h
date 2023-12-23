// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#pragma once

#include <QWidget>

class ImageWidgetPrivate;
class ImageWidget : public QWidget
{
    Q_OBJECT
    public:
        ImageWidget(QWidget* parent = nullptr);
        virtual ~ImageWidget();
    
    Q_SIGNALS:
        void imageDropped(const QImage& image);

    protected:
        void dragEnterEvent(QDragEnterEvent* event) override;
        void dropEvent(QDropEvent* event) override;
        void paintEvent(QPaintEvent* event) override;
    
    private:
        QScopedPointer<ImageWidgetPrivate> p;
};
