#include "chart.h"

/**
 * @brief Chart::Chart
 *tworzy wykres
 */
Chart::Chart()
{
    this->showGrid = true;
    this->showLabel = true;
    this->showLegend = true;
    this->geometry = Geometry(0, 0, 500, 400);
    this->gridForAxis = 0;
    this->gridStyle = LineStyle(1, Qt::gray, Qt::DashLine);
    this->legend = Legend();
    this->label = Label("wykres", Geometry(0,0,0,0), Icon(Qt::red, Geometry(0,0,0,0)), QFont("Arial", 12));
}

/**
 * @brief Chart::draw
 *rysuje wykres
 * @return narysowany wykres
 */
QPixmap Chart::draw()
{
    QPixmap temp(this->background.width(), this->background.height());
    QPainter p;
    p.begin(&temp);
    p.fillRect(0, 0, temp.width(), temp.height(), Qt::white);
    p.drawPixmap(0, 0, this->background);

    //początkowa pozycja rysowania
    int x=0;
    int y=this->getAxisY(0).getGeometry().getHeight()-10;
    if(this->showLabel) y+=this->getLabel().getGeometry().getHeight();
    for(int i=0; i<this->getAxisCount(); i++)
    {
        if(this->getAxisY(i).getPosition() == left)
            x+= this->getAxisY(i).draw().width();
    }

    float space = (float)this->getAxisX().getGeometry().getWidth()/(this->getSerie(0)->getLength(true)-1);

    //dla każdej serii
    for(int j=0; j<this->getSeriesCount(); j++)
    {
        const double scale = double(this->getAxisY(this->getSerie(j)->getAxisId()).getGeometry().getHeight()-20)/(this->getAxisY(this->getSerie(j)->getAxisId()).getMax()-this->getAxisY(this->getSerie(j)->getAxisId()).getMin());
        for(int i=0; i<this->getSerie(j)->getLength()-1; i++)
        {
            p.setPen(QPen(QBrush(this->getSerie(j)->getLineStyle().getColor()), this->getSerie(j)->getLineStyle().getWidth(), this->getSerie(j)->getLineStyle().getType()));
            p.drawLine(x+i*space, y-scale*(this->getSerie(j)->getPoint(i)-this->getAxisY(this->getSerie(j)->getAxisId()).getMin()), (i+1)*space+x, y-scale*(this->getSerie(j)->getPoint(i+1)-this->getAxisY(this->getSerie(j)->getAxisId()).getMin()));
        }
    }

    p.end();
    return temp;
}

/**
 * @brief Chart::drawBackground
 *rysuje tło (osie, legendę, tytuł) do bufora
 */
void Chart::drawBackground()
{
//    int width = 0, yWidth = 0, ostTick = 0;
//    for(int i=0; i<this->getAxisCount(); i++)
//    {
//        this->getAxisY(i).draw();
//        if(this->getAxisY(i).getPosition() == left)
//        {
//            yWidth+= this->getAxisY(i).getGeometry().getWidth();
//            ostTick = this->getAxisY(i).getTickSize();
//        }
//        width += this->getAxisY(i).getGeometry().getWidth();
//    }

//    //do poprawy:
//    width -= ostTick;

//    width += this->getAxisX().getGeometry().getWidth();
//    if(this->getLegendVisibility())
//        width += this->legend.getGeometry().getWidth();

//    int height = 0;
//    height += this->getAxisY(0).getGeometry().getHeight();
//    height += this->getAxisX().getGeometry().getHeight();

//    //QPixmap temp(this->getGeometry().getWidth(), this->getGeometry().getHeight());
//    QPixmap temp(width, height);
//    QPainter p;
//    p.begin(&temp);
//    p.fillRect(0, 0, temp.width(), temp.height(), Qt::white);

//    int prevWidth = 0;
//    //oś x
//    p.drawPixmap(yWidth-11-this->getAxisY(0).getTickSize(), this->getAxisY(0).getGeometry().getHeight()-10, this->getAxisX().draw());
//    //lewe osie y
//    for(int i=0; i<this->getAxisCount(); i++)
//    {
//        if(this->getAxisY(i).getPosition() == left)
//        {
//            p.drawPixmap(prevWidth, 0, this->getAxisY(i).draw());
//            prevWidth+= this->getAxisY(i).getGeometry().getWidth();
//        }
//    }
//    //siatka
//    p.setPen(QPen(QBrush(this->getGridStyle().getColor()), this->getGridStyle().getWidth(), this->getGridStyle().getType()));
//    const float space = (this->getAxisY(gridForAxis).getGeometry().getHeight()-20)/(this->getAxisY(gridForAxis).getMax()-this->getAxisY(gridForAxis).getMin())*this->getAxisY(gridForAxis).getTick();
//    const int tickCount = (this->getAxisY(gridForAxis).getMax()-this->getAxisY(gridForAxis).getMin())*this->getAxisY(gridForAxis).getTick();
//    for(int i=tickCount; i>=0; i--)
//    {
//        p.drawLine(prevWidth, this->getAxisY(gridForAxis).getGeometry().getHeight()-10-i*space, prevWidth+this->getAxisX().getGeometry().getWidth(), this->getAxisY(gridForAxis).getGeometry().getHeight()-10-i*space);
//    }
//    p.drawLine(prevWidth, 10,  prevWidth+this->getAxisX().getGeometry().getWidth(), 10);

//    //prawe osie y
//    prevWidth += this->getAxisX().getGeometry().getWidth()-20;
//    for(int i=0; i<this->getAxisCount(); i++)
//    {
//        if(this->getAxisY(i).getPosition() == right)
//        {
//            p.drawPixmap(prevWidth, 0, this->getAxisY(i).draw());
//            prevWidth+= this->getAxisY(i).getGeometry().getWidth();
//        }
//    }

//    p.drawPixmap(width-this->legend.getGeometry().getWidth(), 0, this->getLegend().draw());

//    //p.drawPixmap();
    int textWidth = 0, textHeight = 0, szerRys = this->getGeometry().getWidth();
    QPixmap temp(this->getGeometry().getWidth(), this->getGeometry().getHeight());
    QPainter p;
    p.begin(&temp);
    p.fillRect(0, 0, temp.width(), temp.height(), Qt::white);

    //tytuł wykresu
    if(this->getLabelVisibility())
    {
        this->getLabel().draw();
        textWidth = this->getLabel().getGeometry().getWidth();
        textHeight = this->getLabel().getGeometry().getHeight();
        p.drawPixmap((this->getGeometry().getWidth()-textWidth)/2, 0, this->getLabel().draw());
    }
    //wysokość dla osi y
    int wysY = this->getGeometry().getHeight()-textHeight-this->getAxisX().getGeometry().getHeight()+10;

    for(int i=0; i<this->getAxisCount(); i++)
    {
        this->getAxisY(i).getGeometry().setHeight(wysY);
        this->getAxisY(i).draw();
        szerRys -= this->getAxisY(i).getGeometry().getWidth();
    }

    //legenda
    if(this->getLegendVisibility())
    {
        szerRys -= this->getLegend().getGeometry().getWidth();
        p.drawPixmap(temp.width()-this->getLegend().getGeometry().getWidth(), textHeight, this->getLegend().draw());
    }

    int prevX = 0;
    //osie y (lewe)
    for(int i=0; i<this->getAxisCount(); i++)
    {
        if(this->getAxisY(i).getPosition()==left)
        {
            p.drawPixmap(prevX, textHeight, this->getAxisY(i).draw());
            prevX += this->getAxisY(i).getGeometry().getWidth();
        }
    }

    //oś x
    this->getAxisX().getGeometry().setWidth(szerRys);
    p.drawPixmap(prevX, temp.height()-this->getAxisX().getGeometry().getHeight(), this->getAxisX().draw());

    //siatka
    p.setPen(QPen(QBrush(this->getGridStyle().getColor()), this->getGridStyle().getWidth(), this->getGridStyle().getType()));
    const float space = (this->getAxisY(gridForAxis).getGeometry().getHeight()-20)/(this->getAxisY(gridForAxis).getMax()-this->getAxisY(gridForAxis).getMin())*this->getAxisY(gridForAxis).getTick();
    const int tickCount = (this->getAxisY(gridForAxis).getMax()-this->getAxisY(gridForAxis).getMin())/this->getAxisY(gridForAxis).getTick();
    for(int i=tickCount; i>=0; i--)
    {
        p.drawLine(prevX, textHeight+this->getAxisY(gridForAxis).getGeometry().getHeight()-10-i*space, prevX+szerRys, textHeight+this->getAxisY(gridForAxis).getGeometry().getHeight()-10-i*space);
    }
    p.drawLine(prevX, textHeight+10,  prevX+szerRys, textHeight+10);
    prevX += szerRys;

    //osie y (prawe)
    for(int i=0; i<this->getAxisCount(); i++)
    {
        if(this->getAxisY(i).getPosition()==right)
        {
            p.drawPixmap(prevX, textHeight, this->getAxisY(i).draw());
            prevX += this->getAxisY(i).getGeometry().getWidth();
        }
    }

    p.end();
    this->background = temp;
}

/**
 * @brief Chart::setGeometry
 *ustawia położenie i rozmiar
 * @param geometry położenie i rozmiar
 */
void Chart::setGeometry(Geometry geometry)
{
    this->geometry = geometry;
}

/**
 * @brief Chart::getGeometry
 * @return referencję do położenia i rozmiaru
 */
Geometry &Chart::getGeometry()
{
    return this->geometry;
}

/**
 * @brief Chart::addSerie
 *przypisuje serię do wykresu
 * @param serie wskaźnik do serii do podłączenia
 */
void Chart::addSerie(Serie *serie)
{
    series.push_back(serie);
    this->legend.addLabel(serie->getLabel());
}

/**
 * @brief Chart::removeSerie
 *usuwa serię z wykresu
 * @param id numer serii do odłączenia
 */
void Chart::removeSerie(int id)
{
    series.erase(series.begin()+id);
    legend.removeLabel(id);
}

/**
 * @brief Chart::getSerie
 * @param id numer serii
 * @return referencję do serii
 */
Serie *Chart::getSerie(int id)
{
    return series.at(id);
}

/**
 * @brief Chart::setLabel
 *ustawia tytuł wykresu
 * @param label etykieta wykresu
 */
void Chart::setLabel(Label label)
{
    this->label = label;
}

/**
 * @brief Chart::getLabel
 * @return referencję do etykiety
 */
Label &Chart::getLabel()
{
    return this->label;
}

/**
 * @brief Chart::setTick
 *ustawia odstęp czasowy pomiędzy punktami
 * @param tick odstęp czasowy
 */
void Chart::setTick(double tick)
{
    this->tick = tick;
}

/**
 * @brief Chart::getTick
 * @return odstęp czasowy między punktami
 */
double Chart::getTick()
{
    return this->tick;
}

/**
 * @brief Chart::setGridStyle
 *ustawia styl siatki
 * @param style styl siatki
 */
void Chart::setGridStyle(LineStyle style)
{
    this->gridStyle = style;
}

/**
 * @brief Chart::getGridStyle
 * @return referencję do stylu siatki
 */
LineStyle &Chart::getGridStyle()
{
    return this->gridStyle;
}

/**
 * @brief Chart::setLegend
 *ustawia legendę
 * @param legend legenda
 */
void Chart::setLegend(Legend legend)
{
    this->legend = legend;
}

/**
 * @brief Chart::getLegend
 * @return referencję do legendy
 */
Legend &Chart::getLegend()
{
    return this->legend;
}

/**
 * @brief Chart::setAxisX
 *ustawia oś poziomą
 * @param axis oś pozioma
 */
void Chart::setAxisX(Axis axis)
{
    this->axisX = axis;
}

/**
 * @brief Chart::getAxisX
 * @return referencję do osi poziomej
 */
Axis &Chart::getAxisX()
{
    return this->axisX;
}

/**
 * @brief Chart::addAxisY
 *dodaje oś pionową
 * @param axis oś pionowa
 */
void Chart::addAxisY(Axis axis)
{
    this->axisY.push_back(axis);
}

/**
 * @brief Chart::removeAxisY
 *usuwa oś pionową
 * @param id numer osi do usunięcia
 */
void Chart::removeAxisY(int id)
{
    axisY.erase(axisY.begin()+id);
}

/**
 * @brief Chart::getAxisY
 * @param id numer osi pionowej
 * @return referencję do osi pionowej
 */
Axis &Chart::getAxisY(int id)
{
    return axisY.at(id);
}

/**
 * @brief Chart::setGridVisibility
 *ustawia widoczność siatki
 * @param visible widoczność siatki
 */
void Chart::setGridVisibility(bool visible)
{
    this->showGrid = visible;
}

/**
 * @brief Chart::getGridVisibility
 * @return widoczność siatki
 */
bool Chart::getGridVisibility()
{
    return this->showGrid;
}

/**
 * @brief Chart::setLegendVisibility
 *ustawia widoczność legendy
 * @param visible widoczność legendy
 */
void Chart::setLegendVisibility(bool visible)
{
    this->showLegend = visible;
}

/**
 * @brief Chart::getLegendVisibility
 * @return widoczność legendy
 */
bool Chart::getLegendVisibility()
{
    return this->showLegend;
}

/**
 * @brief Chart::setLabelVisibility
 *ustawia widoczność tytułu
 * @param visible widoczność tytułu
 */
void Chart::setLabelVisibility(bool visible)
{
    this->showLabel = visible;
}

/**
 * @brief Chart::getLabelVisibility
 * @return widoczność tytułu
 */
bool Chart::getLabelVisibility()
{
    return this->showLabel;
}

/**
 * @brief Chart::getAxisCount
 * @return liczbę osi pionowych
 */
int Chart::getAxisCount()
{
    return this->axisY.size();
}

/**
 * @brief Chart::getSeriesCount
 * @return liczbę przypisanych serii
 */
int Chart::getSeriesCount()
{
    return this->series.size();
}

/**
 * @brief Chart::getGridAxis
 * @return numer osi, na podstawie której rysowana jest siatka
 */
int Chart::getGridAxis()
{
    return this->gridForAxis;
}

/**
 * @brief Chart::setGridAxis
 *ustawia, dla której osi rysowana jest siatka
 * @param id numer osi pionowej
 */
void Chart::setGridAxis(int id)
{
    this->gridForAxis = id;
}

/**
 * @brief Chart::exportData eksportuje dane wykresu do QStringa
 * @param separator separator wartości (domyślnie ';')
 * @return dane w formacie CSV
 */
QString Chart::exportData(QString separator)
{
    QString temp("x"+separator);
    for(int i=0; i<this->getSeriesCount(); i++)
    {
        temp += this->getSerie(i)->getLabel().getText();
        if(i != this->getSeriesCount()-1)
            temp += separator;
    }
    for(int i=0; i<this->getSerie(0)->getLength(); i++)
    {
        QString templine(QString::number(i)+separator);
        for(int j=0; j<this->getSeriesCount(); j++)
        {
            templine += QString::number(this->getSerie(j)->getPoint(i));
            templine.replace(".", ",");
            if(j != this->getSeriesCount()-1)
                templine += separator;
        }
        temp.append("\n"+templine);
    }
    return temp;
}
