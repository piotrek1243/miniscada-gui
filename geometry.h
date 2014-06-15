#ifndef GEOMETRY_H
#define GEOMETRY_H

class Geometry
{
public:
    Geometry();
    Geometry(const Geometry& geometry);
    Geometry(int x, int y, int width = -1, int height = -1);
    void setXY(int x, int y);
    int getX();
    int getY();
    void setWidth(int width);
    int getWidth();
    void setHeight(int height);
    int getHeight();

private:
    int x, y, width, height;
};

#endif // GEOMETRY_H
