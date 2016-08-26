#include"connectdialog.h"
#include"mainwindow.h"
#include"ui_mainwindow.h"
#include<QPainter>
#include<QMessageBox>
#include<QString>
#include<QTextStream>
#include<QFile>
#include<QDebug>
#include<QStringList>
#include<QFiledialog>
#include<QListWidgetItem>
#include<windows.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    img = new QByteArray();
    ui->setupUi(this);
    clth = new Cloth(this);
    camView = new CameraView(this);
    //clth->setBaseSize(2000,2000);
    ui->verticalLayout->addWidget(clth);
    ui->horizontalLayout_3->addWidget(camView);

    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(dialog()));
//    point d[3];
//    d[0].X=10000; //10
//    d[0].Y=10000; //10
//    d[0].color=610;

//    d[1].X=10010; //30
//    d[1].Y=10010; //45
//    d[1].color=611;

//    d[2].X=10090; //110
//    d[2].Y=10090; //140
//    d[2].color=612;
//    clth->addDot(d[0]);
//    clth->addDot(d[1]);
//    clth->addDot(d[2]);
//    clth->repaint();
    ui->label_2->setText(QString::number(ui->verticalSlider->value()));
    ui->horizontalSlider_3->setValue(10);

    viewList = false;
   // this->setMaximumWidth(1137);

//    QListWidgetItem item;
//    item.setText(QString("Hello World"));

//        ui->listWidget->addItem("&item");
        //QPalette pl;

        ui->label_14->setStyleSheet("background-color:rgb(255,0,0);");
        ui->label_15->setStyleSheet("background-color:rgb(255,0,0);");
        ui->label->setStyleSheet("background-color:rgb(255,0,0);");

        sock_wheel = new QTcpSocket(this);
        sock_metal = new QTcpSocket(this);
        sock_camera = new QTcpSocket(this);

    connect(sock_wheel, SIGNAL(readyRead()), this, SLOT(onSock_Wheel_ReadyRead()));
    connect(sock_wheel, SIGNAL(connected()), this, SLOT(onSock_Wheel_Connected()));
    connect(sock_wheel, SIGNAL(disconnected()), this, SLOT(onSock_Wheel_Disconnected()));
    connect(sock_wheel, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSock_Wheel_DisplayError(QAbstractSocket::SocketError)));

    connect(sock_metal, SIGNAL(readyRead()), this, SLOT(onSock_Metal_ReadyRead()));
    connect(sock_metal, SIGNAL(connected()), this, SLOT(onSock_Metal_Connected()));
    connect(sock_metal, SIGNAL(disconnected()), this, SLOT(onSock_Metal_Disconnected()));
    connect(sock_metal, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSock_Metal_DisplayError(QAbstractSocket::SocketError)));


    connect(sock_camera, SIGNAL(readyRead()), this, SLOT(onSock_Camera_ReadyRead()));
    connect(sock_camera, SIGNAL(connected()), this, SLOT(onSock_Camera_Connected()));
    connect(sock_camera, SIGNAL(disconnected()), this, SLOT(onSock_Camera_Disconnected()));
    connect(sock_camera, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSock_Camera_DisplayError(QAbstractSocket::SocketError)));

    host_name = "";
    read_metal = "";

    isConnect = false;
    zalip = false;
    countCamFile = 0;
    map = NULL;





}

MainWindow::~MainWindow()
{

    clth->deleteLater();
    map->deleteLater();
    delete ui;
}

//void MainWindow::on_pushButton_clicked()
//{
//    QMessageBox ms;
//    //QString fileName = ui->lineEdit->text();
//    QString fileName = QFileDialog::getOpenFileName(this);
//    if(fileName.isEmpty())
//    {
//        ms.setInformativeText("line is empty!");
//        ms.exec();
//    }
//    else
//    {
//        QFile f(fileName);
//        if (!f.open(QFile::ReadOnly | QFile::Text))
//        {
//            ms.setInformativeText("Can't open file!");
//            ms.exec();

//        }
//        QTextStream in(&f);
//        QStringList pars, pars_gps;
//        QString str;
//        QString metal;
//        QString gps;
//       // QString str_XY;
//        zero_dots = 0;
//        int num_of_dots=0;
//        double lat1,lon1,lat_d,lon_d;//в градусах
//        QString grad_lat="";
//        QString min_lat="";
//        QString grad_lon="";
//        QString min_lon="";
//        QString latit="";
//        QString lontit="";
//        while(!in.atEnd())
//        {
//           // int metal_num;
//            //qDebug() << in.readLine();
//            str = in.readLine();
//            if(str.isEmpty())
//            {
//                continue;
//            }
//            pars = str.split('$');
//            metal = pars.first();
//           // metal_num = metal.toDouble();
//            //qDebug()<<metal_num;
//            gps = pars.back();
//            //qDebug()<<gps;
//            pars_gps = gps.split('#');
//            point p;
//            if(pars_gps.at(0).isEmpty())
//            {
//                 zero_dots++;
//                 num_of_dots++;
//                 continue;
//            }
//            //////Достаём из протокола координаты северной широты и восточной долготы

//            latit = pars_gps.at(0);
//            lontit = pars_gps.at(1);

//            grad_lat = latit.left(2);
//            min_lat = latit.right(latit.size()-2);

//            lat_d = grad_lat.toDouble() + min_lat.toDouble()/60;


//            grad_lon = lontit.left(3);
//            min_lon = lontit.right(lontit.size()-3);

//            lon_d = grad_lon.toDouble() + min_lon.toDouble()/60;

//            p.lat = lat_d;
//            p.lon = lon_d;
//            qDebug()<<"p.lat="<<p.lat;
//            qDebug()<<"p.lon="<<p.lon;
//            ////////

//            p.X = (pars_gps.takeFirst()).toDouble()*10000;
//            p.Y = (pars_gps.takeFirst()).toDouble()*10000;
//            p.color = metal.toDouble();
//            if(!pars_gps.isEmpty())
//                p.precision = (pars_gps.takeFirst()).toDouble();
//            else
//                p.precision=1;

//            num_of_dots++;
////            if(p.X==0 && p.Y ==0)
////            {
////                zero_dots++;
////                continue;
////            }
//            clth->addDot(p);

//           // qDebug()<<"p.X= "<<p.X;
//           // qDebug()<<"p.Y= "<<p.Y;

//        }

//        ui->label_5->setText(QString::number(zero_dots));
//        ui->label_7->setNum(num_of_dots);
//clth->repaint();

//    }

//}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox ms;
    //QString fileName = ui->lineEdit->text();
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName.isEmpty())
    {
        ms.setInformativeText("The file was not specified!");
        ms.exec();
    }
    else
    {
        QFile f(fileName);
        if (!f.open(QFile::ReadOnly | QFile::Text))
        {
            ms.setInformativeText("Can't open file!");
            ms.exec();

        }
        QTextStream in(&f);

        QString str;

       // QString str_XY;
        zero_dots = 0;
        int num_of_dots=0;

        point p;
        while(!in.atEnd())
        {
           // int metal_num;
            //qDebug() << in.readLine();
            str = in.readLine();
            if(str.isEmpty())
            {
                continue;
            }

            p=gps_parser(str);

            num_of_dots++;
            if(p.X==0 && p.Y ==0)
            {
                zero_dots++;
                continue;
            }
            clth->addDot(p);

           // qDebug()<<"p.X= "<<p.X;
           // qDebug()<<"p.Y= "<<p.Y;

        }

        ui->label_5->setText(QString::number(zero_dots));
        ui->label_7->setNum(num_of_dots);
        clth->repaint();

    }

}

void MainWindow::on_verticalSlider_valueChanged(int value)//задаём масштаб карты (значение value из сладера))
{
    if(value>0)
    {
        clth->setMapScale(value);

        ui->label_2->setText(QString::number(value));
    }
    else
    {
        switch(value)
        {
            case -1:clth->setMapScale(0.1);break;
            case -2:clth->setMapScale(0.01);break;
            case -3:clth->setMapScale(0.001);break;
            case -4:clth->setMapScale(0.0001);break;
            case -5:clth->setMapScale(0.00001);break;
        }
        ui->label_2->setText(QString::number(value));
    }
    clth->repaint();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    clth->setDotSize(value);
    //ui->label_3->setNum(value);
    clth->repaint();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    clth->setShiftX(value);
    clth->repaint();
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    clth->setShiftY(value);
    clth->repaint();
}

void MainWindow::on_pushButton_Clear_clicked()
{
    clth->clear();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    clth->setHDOP(value);
}

double MainWindow::distance(double lat1,double lon1,double lat2,double lon2)
{

}
//кнопка list
//void MainWindow::on_pushButton_3_clicked()
//{
//    QRect win=this->geometry();
//    if(viewList)
//    {
//        this->setMaximumWidth(1137);
//        win.setWidth(1137);
//        this->setGeometry(win);
//        viewList = false;

//    }
//    else
//    {
//        this->setMaximumWidth(1352);
//        win.setWidth(1352);
//        this->setGeometry(win);
//        viewList = true;
//    }

//}

void MainWindow::dialog()
{
    QMessageBox ms;

    dl = new connectDialog(this);
    dl->exec();
    host_name = dl->getHost();
    if(host_name.isEmpty())
    {
        ms.about(this,"ERROR","Connect error");
        return;
    }
    //sok_wheel->connectToHost(host_name, PORT_WHEEL);
    ui->connect_Button_Wheel->setEnabled(true);
    ui->connect_Button_Metal->setEnabled(true);
    ui->connect_Button_Camera->setEnabled(true);




    //qDebug()<<"HELLO___________________";
}

////
/// Слоты для сокета, отвечающий за движение
///
void MainWindow::onSock_Wheel_Connected()
{
ui->label_14->setStyleSheet("background-color:rgb(0,255,0);");
ui->connect_Button_Wheel->setText("disconnect");
//разблокирываем кнопки управления
ui->but_A->setEnabled(true);
ui->but_D->setEnabled(true);
ui->but_F->setEnabled(true);
ui->but_R->setEnabled(true);
ui->but_S->setEnabled(true);
ui->but_W->setEnabled(true);
ui->but_Q->setEnabled(true);

isConnect = true;

}

void MainWindow::onSock_Wheel_Disconnected()
{
ui->label_14->setStyleSheet("background-color:rgb(255,0,0);");
ui->connect_Button_Wheel->setText("connect");
ui->but_A->setEnabled(false);
ui->but_D->setEnabled(false);
ui->but_F->setEnabled(false);
ui->but_R->setEnabled(false);
ui->but_S->setEnabled(false);
ui->but_W->setEnabled(false);
ui->but_Q->setEnabled(false);

isConnect= false;
}

void MainWindow::onSock_Wheel_ReadyRead()
{
QMessageBox::information(this, "Wheel", "Prepare to ready: ");
}

void MainWindow::onSock_Wheel_DisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(this, "Error", "The following error occurred: "+sock_wheel->errorString());
    }
}


/////
/// слоты для сокета, отвечающего за метал
///
void MainWindow::onSock_Metal_Connected()
{
    ui->label_15->setStyleSheet("background-color:rgb(0,255,0);");
    ui->connect_Button_Metal->setText("disconnect");
    clth->clear();
    ui->groupBox_info->setEnabled(true);

}

void MainWindow::onSock_Metal_Disconnected()
{
    qDebug()<<"Disconnect";
    ui->label_15->setStyleSheet("background-color:rgb(255,0,0);");
    ui->connect_Button_Metal->setText("connect");
}

void MainWindow::onSock_Metal_ReadyRead()
{
//    char ch[2];
//    int n=0;
//    point p;
//    while((n = sok_metal->read(ch,2)) != 0)
//    {
//        if(n==-1)
//        {
//             QMessageBox::information(this, "Error(metal)", "Can't read from port!!!");
//             ui->connect_Button_Metal->setText("connect");
//             sok_metal->close();
//        }
//        if(ch[0]=='\n')
//        {
//            read_metal;//pars
//            p= this->gps_parser(read_metal);
//            qDebug()<<"X="<<p.X<<"Y="<<p.Y;
//            //Cloth.addDot(p);
//            read_metal = "";
//            continue;
//        }
//        read_metal.append(ch[0]);
//    }
    char dat[1000];
    int n=0;
    if((n = sock_metal->read(dat,1000))<0)
    {
        qDebug()<<n;
        QMessageBox::information(this, "Error(metal)", "Can't read from port!!!");
        ui->connect_Button_Metal->setText("connect");
        sock_metal->close();
    }

    qDebug()<<dat;
    point p;

    p=this->gps_parser(dat);
    if(p.X!=0 && p.Y!=0)
    {
        clth->addDot(p);
        if(p.metal<=1000)
            ui->Progress_Metal->setValue(p.metal);
        else
            ui->Progress_Metal->setValue(1000);
    }
    sock_metal->write("2");

}

void MainWindow::onSock_Metal_DisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error(metal)", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error(metal)", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(this, "Error(metal)", "The following error occurred: "+sock_metal->errorString());

    }
}
////

void MainWindow::on_connect_Button_Wheel_clicked()
{
     if(ui->connect_Button_Wheel->text() == "connect")
     {
        sock_wheel->connectToHost(host_name, PORT_WHEEL);
        ui->connect_Button_Wheel->setText("disconnect");

     }
     else
     {
         sock_wheel->write("exit");
         sock_wheel->close();
         ui->connect_Button_Wheel->setText("connect");
     }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

if(event->isAutoRepeat())
    return;
qDebug()<<"keyPress";
  if(sock_wheel->state() == QAbstractSocket::ConnectedState)
//    if(isConnect)
    {////ConnectedState

      if(event->key() == Qt::Key_W)
        {

            ui->but_W->setEnabled(false);
            sock_wheel->write("w",2);
             //qDebug()<<"write: w!";
           // Sleep(uint(1000));
             //qDebug()<<"write: w!";
            sock_wheel->write("w",2);
            //Sleep(uint(1000));

            sock_wheel->write("w",2);
            qDebug()<<"write: w!\nwrite: w!";
        }
        else if(event->key() == Qt::Key_A)
        {
            ui->but_A->setEnabled(false);
            sock_wheel->write("a",2);
            qDebug()<<"write: a!";
        }
        else if(event->key() == Qt::Key_S)
        {
            ui->but_S->setEnabled(false);
            sock_wheel->write("s",2);
            sock_wheel->write("s",2);
            sock_wheel->write("s",2);
            qDebug()<<"write: s!\nwrite: s!";
        }

        else if(event->key() == Qt::Key_D)
        {
            ui->but_D->setEnabled(false);
            sock_wheel->write("d",2);
            qDebug()<<"write: d!";
        }
        else if(event->key() == Qt::Key_R)
        {
            ui->but_R->setEnabled(false);
            qDebug()<<sock_wheel->write("w",2);
            qDebug()<<"write: w!";
        }
        else if(event->key() == Qt::Key_F)
        {
            ui->but_F->setEnabled(false);
            qDebug()<<sock_wheel->write("s",2);
            qDebug()<<"write: s!";
        }
        else if(event->key() == Qt::Key_Q)
        {
            ui->but_Q->setEnabled(false);
           qDebug()<<"q="<< sock_wheel->write("q",2);
           qDebug()<<"write: q!";
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
    qDebug()<<"keyRelease";
    qDebug()<<(sock_wheel->state());
    if(sock_wheel->state() == QAbstractSocket::ConnectedState)
   //if(isConnect)
    {////ConnectedState
        if(event->key() == Qt::Key_W)
        {

            ui->but_W->setEnabled(true);
            sock_wheel->write("q",2);
            qDebug()<<"write: q!";
        }
        else if(event->key() == Qt::Key_A)
        {
            ui->but_A->setEnabled(true);
            if(!ui->but_W->isEnabled())
            {
                sock_wheel->write("w",2);
            }
            else if(!ui->but_S->isEnabled())
            {
                sock_wheel->write("s",2);
            }
            else sock_wheel->write("q",2);

        }
        else if(event->key() == Qt::Key_S)
        {
            sock_wheel->write("q",2);
            ui->but_S->setEnabled(true);
        }

        else if(event->key() == Qt::Key_D)
        {
            ui->but_D->setEnabled(true);
            if(!ui->but_W->isEnabled())
            {
                sock_wheel->write("w",2);
            }
            else if(!ui->but_S->isEnabled())
            {
                sock_wheel->write("s",2);
            }
            else sock_wheel->write("q",2);

        }

        else if(event->key() == Qt::Key_R)
        {
            ui->but_R->setEnabled(true);
        }
        else if(event->key() == Qt::Key_F)
        {
            ui->but_F->setEnabled(true);
        }
        else if(event->key() == Qt::Key_Q)
        {
            ui->but_Q->setEnabled(true);

        }
    }
}
//сигнал нажатя кнопки connect для металло-детектора
void MainWindow::on_connect_Button_Metal_clicked()
{
    if(ui->connect_Button_Metal->text() == "connect")
    {
       sock_metal->connectToHost(host_name, PORT_METAL);
       ui->connect_Button_Metal->setText("disconnect");
       sock_metal->write("2");
    }
    else
    {
        sock_metal->write("exit");
        sock_metal->close();
        ui->connect_Button_Metal->setText("connect");

    }
}

point MainWindow::gps_parser(QString str)
{

    QStringList pars, pars_gps;

    QString metal;
    QString gps;
   // QString str_XY;


    double lat_d,lon_d;//в градусах
    QString grad_lat="";
    QString min_lat="";
    QString grad_lon="";
    QString min_lon="";
    QString latit="";
    QString lontit="";

    point p;
       // int metal_num;
        //qDebug() << in.readLine();

        if(str.isEmpty())
        {
            p.X=0;
            p.Y=0;
            p.metal=0;
            p.precision=0;
            p.lat=0;
            p.lon=0;
            return p;
        }
        pars = str.split('$');
        metal = pars.first();
       // metal_num = metal.toDouble();
        //qDebug()<<metal_num;
        gps = pars.back();
        //qDebug()<<gps;
        pars_gps = gps.split('#');

        if(pars_gps.at(0).isEmpty() || pars_gps.size()<3)
        {
            p.X=0;
            p.Y=0;
            p.metal=0;
            p.precision=0;
            p.lat=0;
            p.lon=0;
            return p;
        }
        //////Достаём из протокола координаты северной широты и восточной долготы

        latit = pars_gps.at(0);
        lontit = pars_gps.at(1);

        grad_lat = latit.left(2);
        min_lat = latit.right(latit.size()-2);

        lat_d = grad_lat.toDouble() + min_lat.toDouble()/60;


        grad_lon = lontit.left(3);
        min_lon = lontit.right(lontit.size()-3);

        lon_d = grad_lon.toDouble() + min_lon.toDouble()/60;

        p.lat = lat_d;
        p.lon = lon_d;
        qDebug()<<"p.lat="<<p.lat;
        qDebug()<<"p.lon="<<p.lon;
        ////////

        p.X = (pars_gps.takeFirst()).toDouble()*10000;
        p.Y = (pars_gps.takeFirst()).toDouble()*10000;
        p.metal = metal.toDouble();
        if(!pars_gps.isEmpty())
            p.precision = (pars_gps.takeFirst()).toDouble();
        else
            p.precision=1;


//            if(p.X==0 && p.Y ==0)
//            {
//                zero_dots++;
//                continue;
//            }
        return p;

       // qDebug()<<"p.X= "<<p.X;
       // qDebug()<<"p.Y= "<<p.Y;


}
void MainWindow::on_action_3_triggered()
{
    QMessageBox ms;
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName.isEmpty())
    {
        ms.setInformativeText("The file was not specified!");
        ms.exec();
        return;
    }
    this->save(fileName);
}

void MainWindow::save(QString fileName)
{
    QMessageBox ms;

    QString str;
    QVector<point> dots = clth->getDots();
    if(dots.isEmpty())
    {
        ms.setInformativeText("Can't open file for write!");
        ms.exec();
        return;
    }
    QFile f(fileName);
    if (!f.open(QFile::WriteOnly | QFile::Text))
    {
        ms.setInformativeText("Can't open file for write!");
        ms.exec();

    }
    QTextStream in(&f);
    point p;
    //qDebug()<<dots.isEmpty();
    while(!dots.isEmpty())
    {
        p = dots.takeFirst();
        str = "";
        str.append(QString::number(p.metal));
        str.append("$");
        double X= p.X/10000.0,Y= p.Y/10000.0;
        str.append(QString::number(X,'f',4));
        str.append("#");
        str.append(QString::number(Y,'f',4));
        str.append("#");
        str.append(QString::number(p.precision,'f',1));
        str.append('\n');
        //qDebug()<<str;
        in<<str;
    }
    f.close();
}

void MainWindow::on_action_4_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save as image"), "", tr("PNG file (*.png)"));
    if (path.isEmpty())
        return;
    clth->saveAsImage(path);
}


void MainWindow::onSock_Camera_Connected()
{
    ui->label->setStyleSheet("background-color:rgb(0,255,0);");
    ui->connect_Button_Camera->setText("disconnect");
    ui->pushButton_2->setEnabled(true);




}
void MainWindow::onSock_Camera_Disconnected()
{
    qDebug()<<"Disconnect Camera";
    ui->label->setStyleSheet("background-color:rgb(255,0,0);");
    ui->connect_Button_Camera->setText("connect");
    ui->pushButton_2->setEnabled(false);
}
void MainWindow::onSock_Camera_DisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(this, "Error", "RemoteHostClosedError");
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error", "The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error", "The connection was refused by the peer.");
        break;
    default:
        QMessageBox::information(this, "Error", "The following error occurred: "+sock_camera->errorString());
    }
}
void MainWindow::onSock_Camera_ReadyRead()
{
    //QByteArray dat;


    img->append(sock_camera->readAll());

    int pos=0;
    if((pos = img->indexOf("##$$$$##"))!=-1)
    {
        qDebug()<<"1--"<<img->length();
        QImage image;
        if(!image.loadFromData(img->left(pos)))
        {
            //QMessageBox::information(this, "Error", "can't load image.");
        }
        camView->drowImage(image);
        qDebug()<<"pos--"<<pos;
        qDebug()<<"temp--"<<((img->length())-(pos+8));
        QByteArray temp=img->right(img->length()-(pos+8));
        delete img;
        img = new QByteArray();
         img->append(temp);
         qDebug()<<"2--"<<img->length();
        ///!!!
    }

//    countCamFile++;
//    qDebug()<<"countCamFile ="<<countCamFile;


//    if(dat[0]==0)
//    {
//        camFile.close();
//        qDebug()<<"COUNT Write to file="<<countCamFile;
//        return;
//    }

    //wdata->writeBytes(dat);
//    if(camFile.isOpen())camFile.write(dat);
//    else
//    {
////        QMessageBox::information(this, "Write to file Error(Camera)", "File did not open.");
////        ui->connect_Button_Camera->setText("connect");
////        sock_camera->close();
//    }





}

void MainWindow::on_connect_Button_Camera_clicked()
{
    if(ui->connect_Button_Camera->text() == "connect")
    {
       sock_camera->connectToHost(host_name, PORT_CAMERA);
       ui->connect_Button_Camera->setText("disconnect");

    }
    else
    {
        sock_camera->write("exit");
        sock_camera->close();
        ui->connect_Button_Camera->setText("connect");
        camFile.close();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
//    QMessageBox ms;
//    QString FileName = "Z:\\Image.jpg";
//    camFile.setFileName(FileName);
//    if (!camFile.open(QFile::WriteOnly))
//    {
//        ms.setInformativeText("Can't open file for write!");
//        ms.exec();

//    }
//wdata = new QDataStream(&camFile);

    sock_camera->write("Hello, give me some image :)");


}

void MainWindow::on_actionMap_triggered()
{
    map = new Map(this);
    map->show();

}
