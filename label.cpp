#include "label.h"

/**
 * @brief Label::Label
 */
Label::Label()
{
    this->geometry = Geometry();
    this->font = QFont("verdana", 10);
    this->orientation = horizontal;
    this->icon = Icon(Qt::white, Geometry(0, 0, 0, 0));
    this->text = "";
}

/**
 * @brief Label::Label
 * @param text treść
 * @param geometry rozmiar
 * @param icon ikona
 * @param font czcionka
 * @param orientation orientacja (pozioma, pionowa)
 */
Label::Label(QString text, Geometry geometry, Icon icon, QFont font, Orientation orientation)
{
    this->text = text;
    this->geometry = geometry;
    this->icon = icon;
    this->font = font;
    this->orientation = orientation;
}

/**
 * @brief Label::setText
 *ustawia treść
 * @param text treść
 */
void Label::setText(QString text)
{
    this->text = text;
}

/**
 * @brief Label::getText
 * @return treść
 */
QString Label::getText()
{
    return this->text;
}

/**
 * @brief Label::setFont
 *ustawia czcionkę
 * @param font czionka
 */
void Label::setFont(QFont font)
{
    this->font = font;
}

/**
 * @brief Label::getFont
 * @return czcionkę
 */
QFont Label::getFont()
{
    return this->font;
}

/**
 * @brief Label::setGeometry
 *ustawia rozmiar
 * @param geometry rozmiar
 */
void Label::setGeometry(Geometry geometry)
{
    this->geometry = geometry;
}

/**
 * @brief Label::getGeometry
 * @return referencję do rozmiaru
 */
Geometry &Label::getGeometry()
{
    return this->geometry;
}

/**
 * @brief Label::setIcon
 *ustawia ikonę
 * @param icon ikona
 */
void Label::setIcon(Icon icon)
{
    this->icon = icon;
}

/**
 * @brief Label::getIcon
 * @return referencję do ikony
 */
Icon &Label::getIcon()
{
    return this->icon;
}

/**
 * @brief Label::setOrientation
 *ustawia orientację
 * @param orientation orientacja (pionowa, pozioma)
 */
void Label::setOrientation(Orientation orientation)
{
    this->orientation = orientation;
}

/**
 * @brief Label::getOrientation
 * @return orientację
 */
Orientation Label::getOrientation()
{
    return this->orientation;
}

/**
 * @brief Label::getPixmap
 * @return narysowaną poprzednio etykietę
 */
QPixmap &Label::getPixmap()
{
    return this->pixmap;
}

/**
 * @brief Label::draw
 *rysuje etykietę
 * @return narysowaną właśnie etykietę
 */
QPixmap Label::draw()
{
    QFontMetrics fm(this->getFont());
    int textWidth = fm.width(this->text);
    int textHeight = fm.height();

    int wys = this->icon.getGeometry().getHeight()>textHeight?this->icon.getGeometry().getHeight():textHeight;

    this->setGeometry(Geometry(0, 0, 15+textWidth+this->icon.getGeometry().getWidth(), 10+wys));

    QPixmap temp(this->getGeometry().getWidth(), this->getGeometry().getHeight());
    QPainter p;

    p.begin(&temp);


    p.fillRect(0, 0, temp.width(), temp.height(), Qt::white);
    p.setFont(this->getFont());
    p.fillRect(5, (this->getGeometry().getHeight()-this->icon.getGeometry().getHeight())/2, this->icon.getGeometry().getWidth(), this->icon.getGeometry().getWidth(), this->icon.getColor());
    p.drawText(10+this->icon.getGeometry().getWidth(), (this->getGeometry().getHeight()+textHeight)/2-5, this->text);

    p.end();
    if(this->orientation == vertical)
    {
        QMatrix rm;
        rm.translate(temp.width()/2, temp.height()/2);
        rm.rotate(-90);
        this->setGeometry(Geometry(0, 0, 10+wys, 15+textWidth+this->icon.getGeometry().getWidth()));
        return temp.transformed(rm);
    }

    return temp;
}

/**
 * @brief Label::refresh
 *Rysuje etykietę w celu ustalenia geometrii
 */
void Label::refresh()
{
    this->pixmap = this->draw();
}
