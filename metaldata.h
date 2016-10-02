#ifndef METALDATA_H
#define METALDATA_H
#include "coordinates.h"
#include <QString>
#include <QStringList>
#include <QRegExp>

class MetalData
{
private:
    Coordinates coord;
    double metalDetectorValue;
    double precision;
    //bool empty;

public:
    MetalData();
    MetalData(Coordinates _coord, double _metalDetectorValue, double _precision);
    MetalData(QString protocolMetalInfo);

    void setCoord(Coordinates _coord);
    void setMetalValue(double _metalDetectorValue);
    void setPrecision(double _precision);

    Coordinates getCoord();
    double getMetalValue();
    double getPrecision();

    bool isEmpty();
};

#endif // METALDATA_H
