#include "linestyle.h"

//LineStyle::LineStyle()
//{
//    this->color = Qt::black;
//    this->width = 1;
//    this->type = Qt::SolidLine;
//}

/**
 * @brief LineStyle::LineStyle
 * @param width szerokość linii
 * @param color kolor linii
 * @param lineType rodzaj linii
 */
LineStyle::LineStyle(int width, QColor color, Qt::PenStyle lineType)
{
    this->width = width;
    this->color = color;
    this->type = lineType;
}

/**
 * @brief LineStyle::setColor
 *ustawia kolor
 * @param color kolor linii
 */
void LineStyle::setColor(QColor color)
{
    this->color = color;
}

/**
 * @brief LineStyle::getColor
 * @return kolor linii
 */
QColor LineStyle::getColor()
{
    return this->color;
}

/**
 * @brief LineStyle::setWidth
 *ustawia szerokość
 * @param width szerokość linii
 */
void LineStyle::setWidth(int width)
{
    this->width = width;
}

/**
 * @brief LineStyle::getWidth
 * @return szerokość linii
 */
int LineStyle::getWidth()
{
    return this->width;
}

/**
 * @brief LineStyle::setType
 *ustawia typ
 * @param type rodzaj linii
 */
void LineStyle::setType(Qt::PenStyle type)
{
    this->type = type;
}

/**
 * @brief LineStyle::getType
 * @return rodzaj linii
 */
Qt::PenStyle LineStyle::getType()
{
    return this->type;
}
