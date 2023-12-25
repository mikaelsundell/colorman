// Copyright 2022-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "colorman.h"
#include "mac.h"

#include <QAction>
#include <QBuffer>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
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
        void stylesheet();
    
    public Q_SLOTS:
        void about();
        void openGithubReadme();
        void openGithubIssues();
    
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
    mac::setupMac();
    // ui
    ui.reset(new Ui_Colorman());
    ui->setupUi(window);
    // stylesheet
    stylesheet();
    // connect
    connect(ui->imagewidget, &ImageWidget::imageDropped, ui->vectorscope, &VectorscopeWidget::setImage);
    connect(ui->about, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->openGithubReadme, SIGNAL(triggered()), this, SLOT(openGithubReadme()));
    connect(ui->openGithubIssues, SIGNAL(triggered()), this, SLOT(openGithubIssues()));
    // debug
    #ifdef QT_DEBUG
        QMenu* menu = ui->menubar->addMenu("Debug");
        {
            QAction* action = new QAction("Reload stylesheet...", this);
            action->setShortcut(QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_S));
            menu->addAction(action);
            connect(action, &QAction::triggered, [&]() {
                this->stylesheet();
            });
        }
    #endif
}

void
ColormanPrivate::stylesheet()
{
    QDir resources(QApplication::applicationDirPath());
    QFile stylesheet(resources.absolutePath() + "/../Resources/App.css");
    stylesheet.open(QFile::ReadOnly);
    qApp->setStyleSheet(stylesheet.readAll());
}

void
ColormanPrivate::about()
{
    QPointer<About> about = new About();
    about->show();
}

void
ColormanPrivate::openGithubReadme()
{
    QDesktopServices::openUrl(QUrl("https://github.com/mikaelsundell/colorman/blob/master/README.md"));
}

void
ColormanPrivate::openGithubIssues()
{
    QDesktopServices::openUrl(QUrl("https://github.com/mikaelsundell/colorman/issues"));
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
