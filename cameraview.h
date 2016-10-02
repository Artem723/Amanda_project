#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QVector>
#include <QPen>

struct MapPoint
{
    int x;
    int y;
    QColor color;
    int size;

};

struct MapPoint2
{
    int x;
    int y;
    double value;
    int size;

};

class CameraView : public QWidget
{
    Q_OBJECT
private:
    QImage image;

    QVector<MapPoint> points;
    QVector<MapPoint2> points2;

    double minValue;
    double maxValue;


public:
    explicit CameraView(QWidget *parent = 0);
    void drowImage(QImage &image);
    void addPoint(int x, int y, QColor color, int size);
    void addPoint2(int x, int y, double value, int size);
    void removeAllPoints();
    QColor getColorByValue(double metal);



signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CAMERAVIEW_H
