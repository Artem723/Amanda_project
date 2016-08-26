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

class CameraView : public QWidget
{
    Q_OBJECT
private:
    QImage image;

    QVector<MapPoint> points;



public:
    explicit CameraView(QWidget *parent = 0);
    void drowImage(QImage &image);
    void addPoint(int x, int y, QColor color, int size);


signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CAMERAVIEW_H
