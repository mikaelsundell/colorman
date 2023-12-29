// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "pythonwidget.h"
#include "pythoninterpreter.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QPointer>
#include <QVBoxLayout>
#include <QDebug>

namespace colorman {

class PythonWidgetPrivate : public QObject
{
    Q_OBJECT
    public:
        PythonWidgetPrivate();
        void init();
    
    public Q_SLOTS:
        void executeScript();
        
    public:
        QTextEdit* outputArea;
        QLineEdit* inputLine;
        QPointer<PythonWidget> widget;
};

PythonWidgetPrivate::PythonWidgetPrivate()
{
}

void
PythonWidgetPrivate::init()
{
    outputArea = new QTextEdit(widget);
    outputArea->setReadOnly(true);

    inputLine = new QLineEdit(widget);
    connect(inputLine, SIGNAL(returnPressed()), this, SLOT(executeScript()));

    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(outputArea);
    layout->addWidget(inputLine);
}

void
PythonWidgetPrivate::executeScript()
{
    PythonInterpreter* interpreter = PythonInterpreter::instance();
    
    QString command = inputLine->text();
    inputLine->clear();
    
    outputArea->append(interpreter->executeScript(command));
}

#include "pythonwidget.moc"

PythonWidget::PythonWidget(QWidget* parent)
: QWidget(parent)
, p(new PythonWidgetPrivate())
{
    p->widget = this;
    p->init();
}

PythonWidget::~PythonWidget()
{
}

}
