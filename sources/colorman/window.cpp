// Copyright 2022-present Contributors to the colorman project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "window.h"
#include "colorman.h"
#include "pythonwidget.h"
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

namespace colorman {

class WindowPrivate : public QObject
{
    Q_OBJECT
    public:
        WindowPrivate();
        void init();
        void stylesheet();
    
    public Q_SLOTS:
        void open(const QString& file);
        void about();
        void python();
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
        QPointer<Colorman> colorman;
        QPointer<Window> window;
        QScopedPointer<PythonWidget> pythonwidget;
        QScopedPointer<Ui_Colorman> ui;
};

WindowPrivate::WindowPrivate()
{
}

void
WindowPrivate::init()
{
    mac::setupMac();
    // ui
    ui.reset(new Ui_Colorman());
    ui->setupUi(window);
    // colorman
    colorman = Colorman::instance();
    // widgets
    pythonwidget.reset(new PythonWidget());
    // stylesheet
    stylesheet();
    // connect
    connect(colorman, SIGNAL(fileOpened(const QString&)), this, SLOT(open(const QString&)));
    connect(ui->imagewidget, &ImageWidget::imageDropped, ui->vectorscope, &VectorscopeWidget::setImage);
    connect(ui->about, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->python, SIGNAL(triggered()), this, SLOT(python()));
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
WindowPrivate::stylesheet()
{
    QDir resources(QApplication::applicationDirPath());
    QFile stylesheet(resources.absolutePath() + "/../Resources/App.css");
    stylesheet.open(QFile::ReadOnly);
    qApp->setStyleSheet(stylesheet.readAll());
}

void
WindowPrivate::open(const QString& file)
{
    window->setWindowTitle("Colorman: " + file);
}

void
WindowPrivate::about()
{
    QPointer<About> about = new About();
    about->show();
}

void
WindowPrivate::python()
{
    pythonwidget->show();
}

void
WindowPrivate::openGithubReadme()
{
    QDesktopServices::openUrl(QUrl("https://github.com/mikaelsundell/colorman/blob/master/README.md"));
}

void
WindowPrivate::openGithubIssues()
{
    QDesktopServices::openUrl(QUrl("https://github.com/mikaelsundell/colorman/issues"));
}

#include "window.moc"

Window::Window()
: QMainWindow(nullptr)
, p(new WindowPrivate())
{
    p->window = this;
    p->init();
}

Window::~Window()
{
}

}
