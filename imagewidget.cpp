// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/colorman

#include "imagewidget.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QDragEnterEvent>
#include <QLabel>
#include <QMimeData>
#include <QVBoxLayout>
#include <QPainter>
#include <QPointer>
#include <QDebug>

class ImageWidgetPrivate : public QObject
{
    Q_OBJECT
    public:
        ImageWidgetPrivate();
        void init();
        void dropEvent(QDropEvent *event);
        void paintEvent(QPaintEvent* event);
    
    public:
        QImage image;
        QPointer<ImageWidget> widget;
};

ImageWidgetPrivate::ImageWidgetPrivate()
{
}

void
ImageWidgetPrivate::init()
{
    QDir resources(QApplication::applicationDirPath());
    QFile smtpcolorbar(resources.absolutePath() + "/../Resources/smptecolorbar.png");
    image = QImage(smtpcolorbar.fileName());
}

void
ImageWidgetPrivate::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            QString path = urlList.first().toLocalFile();
            image = QImage(path);
            widget->update();
            emit widget->imageDropped(image);
        }
    }
    if (mimeData->hasImage()) {
        image = qvariant_cast<QImage>(event->mimeData()->imageData());
        widget->update();
        emit widget->imageDropped(image);
    }
}

void
ImageWidgetPrivate::paintEvent(QPaintEvent* event)
{
    QPainter painter(widget);
    painter.fillRect(widget->rect(), Qt::black);
    {
        QSize size = image.size();
        QSize scaled = size.scaled(widget->size(), Qt::KeepAspectRatio);
        int x = (widget->width() - scaled.width()) / 2;
        int y = (widget->height() - scaled.height()) / 2;
        
        // set the interpolation mode to high-quality
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.drawImage(x, y, image.scaled(scaled, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

#include "imagewidget.moc"

ImageWidget::ImageWidget(QWidget *parent)
: QWidget(parent)
, p(new ImageWidgetPrivate())
{
    setAcceptDrops(true);
    p->widget = this;
    p->init();
}

ImageWidget::~ImageWidget()
{
}

void
ImageWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void
ImageWidget::dropEvent(QDropEvent *event)
{
    p->dropEvent(event);
}

void
ImageWidget::paintEvent(QPaintEvent* event)
{
    p->paintEvent(event);
}
