#include "icon.h"
#include <stdlib.h>

/**
 * @brief Icon::Icon
 *  Ikona o losowym kolorze i rozmiarze 10x10
 */
Icon::Icon()
{
    this->color = QColor((float)qrand()/RAND_MAX*255, (float)qrand()/RAND_MAX*255, (float)qrand()/RAND_MAX*255);
    this->geometry = Geometry(0, 0, 10, 10);
}

/**
 * @brief Icon::Icon
 * @param color kolor ikony
 * @param geometry rozmiar ikony
 */
Icon::Icon(QColor color, Geometry geometry)
{
    this->color = color;
    this->geometry = geometry;
}

/**
 * @brief Icon::setGeometry
 *ustawia rozmiar
 * @param geometry rozmiar ikony
 */
void Icon::setGeometry(Geometry geometry)
{
    this->geometry = geometry;
}

/**
 * @brief Icon::getGeometry
 * @return referencję do geometrii
 */
Geometry &Icon::getGeometry()
{
    return this->geometry;
}

/**
 * @brief Icon::setColor
 *ustawia kolor
 * @param color kolor ikony
 */
void Icon::setColor(QColor color)
{
    this->color = color;
}

/**
 * @brief Icon::getColor
 * @return kolor ikony
 */
QColor Icon::getColor()
{
    return this->color;
}
