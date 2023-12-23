// Copyright 2022-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "colorman.h"

#include <QAction>
#include <QBuffer>
#include <QPointer>

// generated files
#include "ui_about.h"
#include "ui_colorman.h"

class ColormanPrivate : public QObject
{
    Q_OBJECT
    public:
        ColormanPrivate();
        void init();
        void about();

    public:
        class About : public QDialog
        {
            public: About()
            {
                QScopedPointer<Ui_About> about;
                about.reset(new Ui_About());
                about->setupUi(this);
            }
        };
        QPointer<Colorman> window;
        QScopedPointer<Ui_Colorman> ui;
};

ColormanPrivate::ColormanPrivate()
{
}

void
ColormanPrivate::init()
{
    ui.reset(new Ui_Colorman());
    ui->setupUi(window);
    // connect
    connect(ui->imagewidget, &ImageWidget::imageDropped, ui->vectorscope, &VectorscopeWidget::setImage);
}

#include "colorman.moc"

Colorman::Colorman()
: QMainWindow(nullptr)
, p(new ColormanPrivate())
{
    p->window = this;
    p->init();
}

Colorman::~Colorman()
{
}
