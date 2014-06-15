#ifndef LABEL_H
#define LABEL_H

//#include "font.h"
#include <QFont>
#include "geometry.h"
#include "icon.h"
#include "orientation.h"
#include <QImage>
#include <QPainter>
#include <QFontMetrics>

class Label
{
public:
    Label();
    Label(QString text, Geometry geometry, Icon icon, QFont font = QFont("arial", 8), Orientation orientation = horizontal);
    void setText(QString text);
    QString getText();
    void setFont(QFont font);
    QFont getFont();
    void setGeometry(Geometry geometry);
    Geometry& getGeometry();
    void setIcon(Icon icon);
    Icon& getIcon();
    void setOrientation(Orientation orientation);
    Orientation getOrientation();
    QPixmap& getPixmap();
    QPixmap draw();
    void refresh();
private:
    QString text;
    QFont font;
    Geometry geometry;
    Icon icon;
    Orientation orientation;
    QPixmap pixmap;
};

#endif // LABEL_H
