#ifndef CLOTH_H
#define CLOTH_H

#include <QWidget>
#include<QVector>
#include<QString>
#include<QImage>

struct point
{   
    int X;//координата для отображения на виджете по оси X
    int Y; //координата для отображения на виджете по оси Y
    int metal;//значение металлоискателя
    double precision;//погрешность нахождения координат по GPS
    double lat;//градус широты
    double lon;//градус долготы

};

class QPaintEvent;

class Cloth : public QWidget
{
    Q_OBJECT
public:
    explicit Cloth(QWidget *parent = 0);
    void addDot(point);
    void clear();
    void setMapScale(double);
    void setDotSize(int);
    void setShiftX(int);
    void setShiftY(int);
    void setHDOP(int);
    QVector<point> getDots();

    bool isSaving;

    bool saveAsImage(QString);

signals:

public slots:

private:
QVector<point> dots;
double map_scale; //масштаб, 1ед длины в пикселях
int max_metal;//максимальное значение металло-искателя
int min_metal;//минимальное  значение металло-искателя
int dot_size;
int shift_x;
int shift_y;
int zero_dots;
int hdop;//погрешность gps

void imgClear();

 QImage* img;
 QColor getColor(int); //возвращает QColor, относительно сигнала металоискателя

 double measure(const point* d1,const point* d2);
 double measure2(const point* d1,const point* d2);

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CLOTH_H
