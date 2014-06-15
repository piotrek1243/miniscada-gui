#ifndef SERIE_H
#define SERIE_H

#include "linestyle.h"
#include "label.h"
#include <vector>

/*enum ConnectingStyle{
    line,
    spline,
    none
};*/

class Serie
{
public:
    Serie(Label label = Label());
    void addPoint(double value);
    void clear();
    double getPoint(int id);
    void setLength(int length);
    int getLength(bool max=false);
    //void setTick(double tick);
    //double getTick();
    void setLineStyle(LineStyle style);
    LineStyle getLineStyle();
    //void setPointsConnectingStyle(ConnectingStyle style);
    //ConnectingStyle getPointsConnectingStyle();
    //bool getPointsConnected();
    //void setPointsConnected(bool connected);
    //void setDotsVisibility(bool visible);
    //bool getDotsVisibility();
    //void setDotStyle(DotStyle style);
    //DotStyle getDotStyle();
    void setAxisId(int id);
    int getAxisId();
    void setLabel(Label label);
    Label& getLabel();
private:
    std::vector<double> points;
    unsigned int length;
    //double tick;
    Label label;
    LineStyle lineStyle;
    //ConnectingStyle pointsConnectingStyle;
    //bool pointsConnected;
    //bool showDots;
    //DotStyle dotsStyle;
    int axisId;
};

#endif // SERIE_H
