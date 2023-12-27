// Copyright 2022-present Contributors to the vectorscope project.
// SPDX-License-Identifier: BSD-3-Clause
// https://github.com/mikaelsundell/utilities/vectorscope

#include "vectorscopewidget.h"
#include "colortools.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

namespace colorman {

class VectorscopeWidgetPrivate : public QObject
{
    Q_OBJECT
    public:
        VectorscopeWidgetPrivate();
        void init();
        QPair<qreal, qreal> uvFromRGB(qreal r, qreal g, qreal b);
        QPair<qreal, qreal> uvFromYIQ(qreal i, qreal q);
        QRgb multiplySat(QRgb rgb, qreal factor);
        
    public:
        QImage paintUvWheel(int w, int h, qreal dpr);
        QImage uvwheel;
        QImage image;
        int width;
        int height;
};

VectorscopeWidgetPrivate::VectorscopeWidgetPrivate()
: width(1024)
, height(1024)
{
}

void
VectorscopeWidgetPrivate::init()
{
    image = QImage("../../resources/smptecolorbar.png");
    uvwheel = paintUvWheel(width, height, 2.0); // hidpi
}

QPair<qreal, qreal>
VectorscopeWidgetPrivate::uvFromRGB(qreal r, qreal g, qreal b)
{
    // wikipedia:
    // https://en.wikipedia.org/wiki/YUV
    QPair<qreal, qreal> uv;
    uv.first = r * -0.14713 + g * -0.28886 + b * 0.436;
    uv.second = r * 0.615 + g * -0.51499 + b * -0.10001;
    return uv;
}

QPair<qreal, qreal>
VectorscopeWidgetPrivate::uvFromYIQ(qreal i, qreal q)
{
    // wikipedia:
    // https://en.wikipedia.org/wiki/YIQ
    QPair<qreal, qreal> uv;
    uv.first = i * -0.54464 + q * 0.83867;
    uv.second = i * 0.83867 + q * 0.54464;
    return uv;
}

QRgb
VectorscopeWidgetPrivate::multiplySat(QRgb rgb, qreal factor)
{
    // Extract red, green, and blue components
    int red = qRed(rgb);
    int green = qGreen(rgb);
    int blue = qBlue(rgb);

    // Convert to HSL
    float h, s, l;
    QColor(rgb).getHslF(&h, &s, &l);

    // Double the saturation value (clamped to [0, 1])
    s = qMin(1.0, factor * s);

    // Convert back to RGB
    QColor modifiedColor;
    modifiedColor.setHslF(h, s, l);
    return modifiedColor.rgb();
}

QImage
VectorscopeWidgetPrivate::paintUvWheel(int width, int height, qreal dpr)
{
    ColorTools colorTools;
    return (colorTools.yuvColorWheel(QSize(width * dpr, height * dpr), 0.5, 1.0, false, true));
}

#include "vectorscopewidget.moc"

VectorscopeWidget::VectorscopeWidget(QWidget* parent)
: QWidget(parent)
, p(new VectorscopeWidgetPrivate())
{
    p->init();
}

VectorscopeWidget::~VectorscopeWidget()
{
}

void
VectorscopeWidget::setImage(const QImage& image)
{
    p->image = image;
    update();
}

void
VectorscopeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect = event->rect();
    qreal diameter = std::min(rect.width(), rect.height());
    qreal radius = diameter/2.0;
    QPointF center(rect.width()/2.0, rect.height()/2.0);
    QRectF scaled(center.x() - radius, center.y() - radius, diameter, diameter);
    // uvwheel
    QImage uvwheel = p->uvwheel.scaled(
        scaled.width(), scaled.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation
    );
    painter.setOpacity(0.1);
    painter.drawImage(scaled, uvwheel);
    painter.setOpacity(0.4);
    // center
    painter.translate(center.x(), center.y());
    // primaries
    QList<QString> names
    {
        "R",
        "G",
        "B",
        "Y",
        "C",
        "M"
    };
    QList<QColor> primaries
    {
        QColor::fromRgbF(1, 0, 0, 0), // red
        QColor::fromRgbF(0, 1, 0, 0), // green
        QColor::fromRgbF(0, 0, 1, 0), // blue
        QColor::fromRgbF(1, 1, 0, 0), // yellow
        QColor::fromRgbF(0, 1, 1, 0), // cyan
        QColor::fromRgbF(1, 0, 1, 0), // magenta
    };
    {
        painter.save();
        painter.setPen(QPen(Qt::white, 2.0));
        // red
        for (int i = 0; i < primaries.size(); i++)
        {
            QColor rgb = primaries[i];
            QString name = names[i];
            
            QPair<qreal, qreal> uv = p->uvFromRGB(
                rgb.redF(), rgb.greenF(), rgb.blueF()
            );
            qreal x = uv.first * radius;
            qreal y = -uv.second * radius; // flip from Qt +Y
            // safe region
            qreal safe0 = 0.25;
            {
                qreal size = diameter * 0.02;
                QRectF region((x + -size/2)*safe0, (y + -size/2)*safe0, size, size);
                painter.drawRect(region);
                
                painter.setOpacity(1.0);
                painter.drawText(region, Qt::AlignCenter, "25");
                painter.setOpacity(0.4);
            }
            
            qreal safe1 = 0.50;
            {
                qreal size = diameter * 0.02;
                QRectF region((x + -size/2)*safe1, (y + -size/2)*safe1, size, size);
                painter.drawRect(region);
                
                painter.setOpacity(1.0);
                painter.drawText(region, Qt::AlignCenter, "50");
                painter.setOpacity(0.4);
            }
            
            qreal safe = 0.75;
            {
                qreal size = diameter * 0.02;
                QRectF region((x + -size/2)*safe, (y + -size/2)*safe, size, size);
                painter.drawRect(region);
                
                painter.setOpacity(1.0);
                painter.drawText(region, Qt::AlignCenter, "75");
                painter.setOpacity(0.4);
            }
            
            // full region
            qreal full = 1.00;
            {
                qreal size = diameter * 0.05;
                QRectF rectangle((x + -size/2)*full, (y + -size/2)*full, size, size);
                painter.drawRect(rectangle);
            
                painter.setOpacity(1.0);
                painter.drawText(rectangle, Qt::AlignCenter, name);
                painter.setOpacity(0.4);
            }
        }
        painter.restore();
    }
    // IQ lines
    {
        painter.save();
        painter.setPen(QPen(Qt::white, 2.0));
        
        QPair<qreal, qreal> iuv = p->uvFromYIQ(1, 0);
        QPair<qreal, qreal> quv = p->uvFromYIQ(0, 1);
        // iuv
        {
            qreal x = iuv.first * radius;
            qreal y = -iuv.second * radius; // flip from Qt +Y
            painter.drawLine(-x, -y, x, y);
        }
        // iuv
        {
            qreal x = quv.first * radius;
            qreal y = -quv.second * radius; // flip from Qt +Y
            painter.drawLine(-x, -y, x, y);
        }
        painter.restore();
    }
    // lines
    {
        painter.save();
        painter.setPen(QPen(Qt::white, 2.0));
        painter.drawLine(-radius, 0, radius, 0);
        painter.drawLine(0, -radius, 0, radius);
        painter.restore();
    }
    // circle
    {
        painter.save();
        painter.setPen(QPen(Qt::white, 2.0));
        int step = 5;
        qreal inner = radius * 0.98;
        for(int span=0; span<360; span++)
        {
            if ((span % step) == 0)
            {
                painter.drawLine(inner, 0, radius, 0);
                painter.rotate(step);
            }
        }
        painter.restore();
    }
    // colors
    painter.setOpacity(0.8);
    int factor=10;
    painter.setOpacity(0.8);
    for(int x=0; x<p->image.width(); x+=factor)
    {
        for(int y=0; y<p->image.height(); y+=factor)
        {
            QColor rgb = p->multiplySat(p->image.pixel(x, y), 2.0);
            
            QPair<qreal, qreal> uv = p->uvFromRGB(
                rgb.redF(), rgb.greenF(), rgb.blueF()
            );
            qreal px = uv.first * radius;
            qreal py = -uv.second * radius; // flip from Qt +Y
            qreal size = diameter * 0.01;
            QRectF region((px + -size/2), (py + -size/2), size, size);
            painter.fillRect(region, rgb);
        }
    }
    painter.end();
}

}
