#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"cloth.h"
#include"connectdialog.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QKeyEvent>
#include "cameraview.h"
#include <QDataStream>
#include "map.h"
#include "coordinates.h"
#include "metaldata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void save(QString fileName);
    ~MainWindow();

signals:


private slots:
    void on_pushButton_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_pushButton_Clear_clicked();

    void on_horizontalSlider_3_valueChanged(int value);



    void dialog();

//    void onSok_Metal_Connected();
//    void onSok_Metal_Disconnected();
//    //сигнал readyRead вызывается, когда сокет получает пакет (который может быть лишь частью отправленых данных) байтов
//    void onSok_Metal_ReadyRead();
//    void onSok_Metal_DisplayError(QAbstractSocket::SocketError socketError);

    void onSock_Wheel_Connected();
    void onSock_Wheel_Disconnected();
    //сигнал readyRead вызывается, когда сокет получает пакет (который может быть лишь частью отправленых данных) байтов
    void onSock_Wheel_ReadyRead();
    void onSock_Wheel_DisplayError(QAbstractSocket::SocketError socketError);



    void onSock_Metal_Connected();
    void onSock_Metal_Disconnected();
    //сигнал readyRead вызывается, когда сокет получает пакет (который может быть лишь частью отправленых данных) байтов
    void onSock_Metal_ReadyRead();
    void onSock_Metal_DisplayError(QAbstractSocket::SocketError socketError);


    void onSock_Camera_Connected();
    void onSock_Camera_Disconnected();
    //сигнал readyRead вызывается, когда сокет получает пакет (который может быть лишь частью отправленых данных) байтов
    void onSock_Camera_ReadyRead();
    void onSock_Camera_DisplayError(QAbstractSocket::SocketError socketError);


    void on_connect_Button_Wheel_clicked();

    void on_connect_Button_Metal_clicked();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_connect_Button_Camera_clicked();

    void on_pushButton_2_clicked();

    void on_actionMap_triggered();

private:
    Ui::MainWindow *ui;
    Cloth* clth;
    int zero_dots;
    bool viewList; //для отображения Списка
    connectDialog* dl;
    QString host_name;

    static const int PORT_WHEEL = 51000; //номер порта сервера управления роботом
    static const int PORT_METAL = 51001;//номер порта сервера metal_info
    static const int PORT_CAMERA = 51002;

    QTcpSocket* sock_metal;

    QTcpSocket* sock_wheel;

    QTcpSocket* sock_camera;

    QString read_metal;

    point gps_parser(QString gps);

    double distance(double,double,double,double);
    bool isConnect;
    bool zalip;
//
    CameraView* camView;
    QFile camFile;
    QDataStream* wdata;
    int countCamFile;

    QByteArray* img;
    Map *map;

    MetalData* m;


//
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
