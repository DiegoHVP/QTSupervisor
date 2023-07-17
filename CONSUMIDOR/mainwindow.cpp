#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>
#include <iostream>
#include "plotter.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  //CONECTAR
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(connectServer()));

  //DESCONECTAR
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(disconnectServer()));

  //START TIMER
  connect(ui->pushButtonStartTimer,
          SIGNAL(clicked(bool)),
          this,
          SLOT(startTimer()));

  //STOP TIMER
  connect(ui->pushButtonStopTimer,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopTimer()));

  //UPDATE
  connect(ui->pushButtonUpdate,
          SIGNAL(clicked(bool)),
          this,
          SLOT(update()));

}
void MainWindow::update(){
    QString text;
    ui->listWidgetIP->clear();
    if(conectado){
        socket->write("list\r\n");
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        if(socket->bytesAvailable() != 0 ){
            while(socket->bytesAvailable()){
                text = socket->readLine().replace("\n","").replace("\r","");
                ui->listWidgetIP->addItem(text);
            }
        }
    }
}

void MainWindow::tcpConnect(){
  QString ip = ui->lineEditIP->text();
  socket->connectToHost(ip,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Conectado";
    conectado = true;
    ui->labelStatus->setText("Server: <font color=\"blue\">Conectado</blue>");

  }
  else{
    qDebug() << "Desconectado";
    conectado = false;
    ui->labelStatus->setText("Status: <font color=\"red\">Descnectado</red>");

  }
}
void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    conectado = false;
    qDebug() << "Desconectado";
    ui->labelStatus->setText("Status: <font color=\"red\">Desconectado</red>");

}
void MainWindow::connectServer(){
    tcpConnect();
    update();
}
void MainWindow::disconnectServer(){
    tcpDisconnect();
}

void MainWindow::startTimer(){

    int timeSlide;
    if (conectado) {
        isOnTimer = true;
        qDebug()<<"isOnTimer: "<<isOnTimer;
    }

    if (isOnTimer && timer == nullptr) { //VERIFICA SE EXISTE ALGUM CRONOMETRO
        timer = new QTimer(this);
        QObject::connect(timer, &QTimer::timeout, [=]() {
            if (isOnTimer) {

                qDebug()<<"chamou data";
                data();
            }
        });

        timeSlide = ui->horizontalSliderTimer->value();
        timeSlide *= 1000;

        timer->setInterval(timeSlide);
        timer->start();
    }
}
void MainWindow::stopTimer(){
    timer->stop();
    timer = nullptr; //DESTROI O CRONOMETRO
    isOnTimer = false;
    qDebug()<<"isOnTimer: "<<isOnTimer;

}
void MainWindow::data(){
    QString str;
    QStringList list;
    qint64 thetime, numb;
    std::vector<double> xtime, ynumber;

    if(conectado){
        if(socket->isOpen()){
            qDebug() << "Lendo..";
            str = "get " + ui->listWidgetIP->currentItem()->text() + " 30\r\n";
            socket->write(str.toStdString().c_str());
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            xtime.clear();
            ynumber.clear();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");

                if(list.size() == 2){
                    bool ok;
                    str = list.at(0);
                    thetime = str.toLongLong(&ok);
                    xtime.push_back(thetime);

                    str = list.at(1);
                    numb = str.toLongLong(&ok);
                    ynumber.push_back(numb);
                    qDebug() << thetime << ": " << str;
                }
            }
        }
    }


    //NORMALIZAR
    double Xmin = *std::min_element(xtime.begin(), xtime.end());
    double Xmax = *std::max_element(xtime.begin(), xtime.end());

    double Ymin = *std::min_element(ynumber.begin(), ynumber.end());
    double Ymax = *std::max_element(ynumber.begin(), ynumber.end());

    std::vector<double> xplotter, yplotter;

    xplotter.clear(); yplotter.clear();
    for(int i = 0; i<30; i++){
        xplotter.push_back( (xtime[i] - Xmin)/(Xmax -Xmin) );
        yplotter.push_back( (ynumber[i] - Ymin)/(Ymax - Ymin) );
    }
    ui->widget->setDados(xplotter,yplotter);
}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
