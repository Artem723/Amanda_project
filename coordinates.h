#ifndef COORDINATES_H
#define COORDINATES_H
#include <QString>
#include <QDebug>
#include<cmath>

class Coordinates
{
private:
    double latitude;
    double longitude;
public:
    Coordinates();
    Coordinates(double lat,double lon);

    double getLat();
    double getLon();

    void setLat(double lat);
    void setLon(double lon);

    void setLat(QString latStr /*Ex. 5542,2389 ==> 55° 42,2389' */);
    void setLon(QString lonStr /*Ex. 03741.6063 ==> 37° 41,6063' */);

    double distance(Coordinates c);

};

#endif // COORDINATES_H
