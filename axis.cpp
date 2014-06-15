#include "axis.h"

/**
 * @brief Axis::Axis
 *tworzy oś z paramterami:
 *czcionka: Verdana, 8pt
 *wartość minimalna: 0
 *wartość maksymalna: 100
 *odstęp wartości: 10
 *podziałka: 4px skierowana do wewnątrz
 *pusta etykieta
 *bez jednostki
 *domyślny styl linii
 */
Axis::Axis()
{
    //this->autoscale = false;
    this->font = QFont("verdana", 8);
    this->geometry = Geometry();
    this->max = 100;
    this->min = 0;
    this->tick = 10;
    this->tickDirection = inside;
    this->tickSize = 4;
    this->position = left;
    this->showUnit = false;
    this->label = Label();
    this->unit = "";
    this->lineStyle = LineStyle();
}

/**
 * @brief Axis::setLabel
 *ustawia etykietę
 * @param label etykieta
 */
void Axis::setLabel(Label label)
{
    this->label = label;
}

/**
 * @brief Axis::getLabel
 * @return referencję do etykiety
 */
Label &Axis::getLabel()
{
    return this->label;
}

/**
 * @brief Axis::setLineStyle
 *ustawia styl linii
 * @param style styl linii
 */
void Axis::setLineStyle(LineStyle style)
{
    this->lineStyle = style;
}

/**
 * @brief Axis::getLineStyle
 * @return referencję do stylu linii
 */
LineStyle &Axis::getLineStyle()
{
    return this->lineStyle;
}

/**
 * @brief Axis::setTick
 *ustawia odstęp między podziałkami
 * @param tick odstęp wartości na osi
 */
void Axis::setTick(double tick)
{
    this->tick = tick;
}

/**
 * @brief Axis::getTick
 * @return odstęp wartości na osi
 */
double Axis::getTick()
{
    return this->tick;
}

/*void Axis::setAutoscale(bool autoscale)
{
    this->autoscale = autoscale;
}

bool Axis::getAutoscale()
{
    return this->autoscale;
}*/

/**
 * @brief Axis::setMin
 *ustawia minimalną wartość osi
 * @param min wartość minimalna na osi
 */
void Axis::setMin(double min)
{
    this->min = min;
}

/**
 * @brief Axis::getMin
 * @return wartość minimalną na osi
 */
double Axis::getMin()
{
    return this->min;
}

/**
 * @brief Axis::setMax
 *ustawia maksymalną wartość osi
 * @param max wartość maksymalna na osi
 */
void Axis::setMax(double max)
{
    this->max = max;
}

/**
 * @brief Axis::getMax
 * @return wartość maksymalną na osi
 */
double Axis::getMax()
{
    return this->max;
}

/**
 * @brief Axis::setTickSize
 *ustawia długość podziałki
 * @param size szerokość podziałki
 */
void Axis::setTickSize(int size)
{
    this->tickSize = size;
}

/**
 * @brief Axis::getTickSize
 * @return szerokość podziałki
 */
int Axis::getTickSize()
{
    return this->tickSize;
}

/**
 * @brief Axis::setTickDirection
 *ustawia kierunek podziałki
 * @param direction kierunek podziałki
 */
void Axis::setTickDirection(Direction direction)
{
    this->tickDirection = direction;
}

/**
 * @brief Axis::getTickDirection
 * @return kierunek podziałki
 */
Direction Axis::getTickDirection()
{
    return this->tickDirection;
}

/**
 * @brief Axis::setUnitVisibility
 *ustawia widoczność jednostek przy wartościach
 * @param visible widoczność jednostki
 */
void Axis::setUnitVisibility(bool visible)
{
    this->showUnit = visible;
}

/**
 * @brief Axis::getUnitVisibility
 * @return widoczność jednostki
 */
bool Axis::getUnitVisibility()
{
    return this->showUnit;
}

/**
 * @brief Axis::setFont
 *ustawia czcionkę
 * @param font czcionka
 */
void Axis::setFont(QFont font)
{
    this->font = font;
}

/**
 * @brief Axis::getFont
 * @return czcionkę
 */
QFont Axis::getFont()
{
    return this->font;
}

/**
 * @brief Axis::setPosition
 *ustawia pozycję osi
 * @param position pozycja osi (lewa/prawa/góra/dół)
 */
void Axis::setPosition(Position position)
{
    this->position = position;
}

/**
 * @brief Axis::getPosition
 * @return pozycję osi
 */
Position Axis::getPosition()
{
    return this->position;
}

/**
 * @brief Axis::setUnit
 *ustawia jednostkę pokazywaną przy wartościach
 * @param unit jednostka
 */
void Axis::setUnit(QString unit)
{
    this->unit = unit;
}

/**
 * @brief Axis::getUnit
 * @return jednostkę
 */
QString Axis::getUnit()
{
    return this->unit;
}

/**
 * @brief Axis::setGeometry
 *ustawia rozmiar osi
 * @param geometry rozmiar
 */
void Axis::setGeometry(Geometry geometry)
{
    this->geometry = geometry;
}

/**
 * @brief Axis::getGeometry
 * @return referencję do rozmiaru
 */
Geometry &Axis::getGeometry()
{
    return this->geometry;
}

/**
 * @brief Axis::draw
 *rysuje oś
 * @return narysowaną właśnie oś
 */
QPixmap Axis::draw()
{
    QFontMetrics fm(this->getFont());
    const int tickCount = (this->max-this->min)/this->tick;
    const QString unit = this->showUnit?" "+this->unit:"";
    int textWidth = fm.width(QString::number(this->max)+unit);
    int textHeight = fm.height();
    QPixmap temp;
    float space;

    //najdluzszy tekst
    for(int i=0; i<=tickCount; i++)
    {
        if(fm.width(QString::number(this->min+tick*i)+unit) > textWidth)
            textWidth = fm.width(QString::number(this->min+tick*i)+unit);
    }

    if(position==left || position==right)
    {
        //this->setGeometry(Geometry(0,0,textWidth+6+this->tickSize, this->geometry.getHeight()));
        int dodatek=0;
        if(this->label.getGeometry().getWidth()>0)
            dodatek = this->label.getGeometry().getWidth()+2;
        temp = QPixmap(textWidth+6+this->tickSize+dodatek, this->geometry.getHeight());
        space = (temp.height()-20)/(max-min)*tick;
        if(position == left)
            textWidth += dodatek;
    }
    else
    {
        //this->setGeometry(Geometry(0, 0, this->geometry.getWidth(), textHeight+6+tickSize));
        temp = QPixmap(this->geometry.getWidth(), textHeight+6+this->tickSize);
        space = (temp.width())/(max-min)*tick;
    }

    QPainter p;
    p.begin(&temp);
    p.fillRect(0, 0, temp.width(), temp.height(), Qt::white);
    p.setFont(this->getFont());

    if(position==left)
    {
        if(this->label.getGeometry().getWidth() > 0)
        {
            //textWidth += this->label.getGeometry().getWidth()+2;
            p.drawPixmap(0, (temp.height()-this->label.getGeometry().getHeight())/2, this->label.draw());
        }

        if(tickDirection==inside)
            p.drawLine(textWidth+5, 10, textWidth+5, temp.height()-10);
        else if(tickDirection == middle)
            p.drawLine(textWidth+5+tickSize/2, 10, textWidth+5+tickSize/2, temp.height()-10);
        else
            p.drawLine(textWidth+5+tickSize, 10, textWidth+5+tickSize, temp.height()-10);

        for(int i=tickCount; i>=0; i--)
        {
            p.drawLine(textWidth+5, temp.height()-10-i*space, textWidth+5+tickSize, temp.height()-10-i*space);
            p.drawText(0, temp.height()-10-i*space-textHeight/2, textWidth, textHeight, Qt::AlignRight, QString::number(min+tick*i)+unit);
        }
        p.drawLine(textWidth+5, 10, textWidth+5+tickSize, 10);
    }
    else if(position == right)
    {
        if(tickDirection==inside)
            p.drawLine(1+tickSize, 10, 1+tickSize, temp.height()-10);
        else if(tickDirection == middle)
            p.drawLine(1+tickSize/2, 10, 1+tickSize/2, temp.height()-10);
        else
            p.drawLine(1, 10, 1, temp.height()-10);

        for(int i=tickCount; i>=0; i--)
        {
            p.drawLine(1, temp.height()-10-i*space, 1+tickSize, temp.height()-10-i*space);
            p.drawText(6+tickSize, temp.height()-10-i*space-textHeight/2, textWidth, textHeight, Qt::AlignLeft, QString::number(min+tick*i)+unit);
        }
        p.drawLine(1, 10, 1+tickSize, 10);

        if(this->label.getGeometry().getWidth() > 0)
        {
            //textWidth += this->label.getGeometry().getWidth()+2;
            p.drawPixmap(6+tickSize+textWidth+2, (temp.height()-this->label.getGeometry().getHeight())/2, this->label.draw());
        }
    }
    else if(position == bottom)
    {
        if(tickDirection==outside)
            p.drawLine(0, 1, temp.width(), 1);
        else if(tickDirection == middle)
            p.drawLine(0, 1+tickSize/2, temp.width(), 1+tickSize/2);
        else
            p.drawLine(0, 1+tickSize, temp.width(), 1+tickSize);

        for(int i=tickCount; i>=0; i--)
        {
            p.drawLine(i*space, 1, i*space, 1+tickSize);
            //p.drawText(6+tickSize, temp.height()-10-i*space+textHeight/2, QString::number(min+tick*i)+unit);
        }
        p.drawLine(temp.width()-1, 1, temp.width()-1, 1+tickSize);
    }
    else    //top
    {
        if(tickDirection==outside)
            p.drawLine(10, 5+tickSize+textHeight, temp.width()-10, 5+tickSize+textHeight);
        else if(tickDirection == middle)
            p.drawLine(10, 5+tickSize/2+textHeight, temp.width()-10, 5+tickSize/2+textHeight);
        else
            p.drawLine(10, 5+textHeight, temp.width()-10, 5+textHeight);

        for(int i=tickCount; i>=0; i--)
        {
            p.drawLine(10+i*space, 6+textHeight, 10+i*space, 6+tickSize+textHeight);
            //p.drawText(6+tickSize, temp.height()-10-i*space+textHeight/2, QString::number(min+tick*i)+unit);
        }
        p.drawLine(temp.width()-10, 6+textHeight, temp.width()-10, 6+tickSize+textHeight);
    }

    p.end();
    this->geometry.setWidth(temp.width());
    this->geometry.setHeight(temp.height());

    return temp;
}
