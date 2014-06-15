#include "legend.h"

//Legend::Legend()
//{
//    this->geometry = Geometry(0, 0, 0, 0);
//    this->orientation = vertical;
//}

/**
 * @brief Legend::Legend
 */
Legend::Legend()
{
    this->geometry = Geometry(0, 0, 0, 0);
}

/**
 * @brief Legend::addLabel
 *dodaje etykietę do legendy
 * @param label etykieta do dodania
 */
void Legend::addLabel(Label label)
{
    this->labels.push_back(label);

    int width=0, height=0;
    for(int i=0; i<this->getLabelsCount(); i++)
    {
        labels.at(i).refresh();
        if(labels.at(i).getGeometry().getWidth() > width)
            width = labels.at(i).getGeometry().getWidth();
        height += labels.at(i).getGeometry().getHeight();
    }
    this->setGeometry(Geometry(0, 0, width, height));
}

/**
 * @brief Legend::removeLabel
 *usuwa etykietę z legendy
 * @param id numer etykiety do usunięcia
 */
void Legend::removeLabel(int id)
{
    this->labels.erase(labels.begin()+id);

    int width=0, height=0;
    for(int i=0; i<this->getLabelsCount(); i++)
    {
        labels.at(i).refresh();
        if(labels.at(i).getGeometry().getWidth() > width)
            width = labels.at(i).getGeometry().getWidth();
        height += labels.at(i).getGeometry().getHeight();
    }
    this->setGeometry(Geometry(0, 0, width, height));
}

/**
 * @brief Legend::getLabel
 * @param id numer etykiety do poprania
 * @return referencję do etykiety
 */
Label &Legend::getLabel(int id)
{
    return this->labels[id];
}

/**
 * @brief Legend::setGeometry
 *ustawia rozmiar
 * @param geometry rozmiar
 */
void Legend::setGeometry(Geometry geometry)
{
    this->geometry = geometry;
}

/**
 * @brief Legend::getGeometry
 * @return referencję do rozmiaru
 */
Geometry &Legend::getGeometry()
{
    return this->geometry;
}

/**
 * @brief Legend::getLabelsCount
 * @return liczbę etykiet
 */
int Legend::getLabelsCount()
{
    return this->labels.size();
}

/**
 * @brief Legend::draw
 *rysuje legendę
 * @return narysowaną legendę
 */
QPixmap Legend::draw()
{
    int width=0, height=0, y=0;
    for(int i=0; i<this->getLabelsCount(); i++)
    {
        //this->labels[labels.begin()+i].refresh();
        labels.at(i).refresh();
        if(labels.at(i).getGeometry().getWidth() > width)
            width = labels.at(i).getGeometry().getWidth();
        height += labels.at(i).getGeometry().getHeight();
    }

    QPixmap temp(width, height);
    QPainter p;
    p.begin(&temp);
    p.fillRect(0, 0, width, height, Qt::white);

    for(int i=0; i<this->getLabelsCount(); i++)
    {
        p.drawPixmap(0, y, labels.at(i).getPixmap());
        y+= labels.at(i).getGeometry().getHeight();
    }

    p.end();
    this->setGeometry(Geometry(0, 0, width, height));

    return temp;
}

/**
 * @brief Legend::refresh
 *odświeża rozmiar legendy
 */
void Legend::refresh()
{
    this->pixmap = this->draw();
}
