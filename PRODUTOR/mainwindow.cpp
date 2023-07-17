#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QDateTime>
#include <QTimer>

bool conectado = false, isOnTimer = false;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);


  //CONECTAR
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(connectServer()));

  //DISCONECTAR
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(disconnectServer()));
  //START TIME
  connect(ui->pushButtonStartTimer,
          SIGNAL(clicked(bool)),
          this,
          SLOT(startTimer()));

  //STOP TIMER
  connect(ui->pushButtonStopTimer,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopTimer()));
}

void MainWindow::tcpConnect(){
  socket->connectToHost(QString(ui->lineEditIP->text()),1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Conectado";
    ui->textBrowserDados->append("Conectado");
    conectado = true;
    ui->labelStatus->setText("Status: <font color=\"blue\">Conectado</blue>");
  }
  else{
    qDebug() << "Desconectado";
    ui->textBrowserDados->append("Desconectado");
    conectado = false;
  }
}
void MainWindow::tcpDisconnect(){
    socket->disconnectFromHost();
    conectado = false;
    qDebug() << "Desconectado";
    ui->textBrowserDados->append("Desconectado");
    ui->labelStatus->setText("Status: <font color=\"red\">Desconectado</red>");
}
void MainWindow::connectServer(){
  tcpConnect();
}

void MainWindow::disconnectServer(){
   tcpDisconnect();
}
void MainWindow::startTimer(){
    int timeSlide;

    if (conectado) {
        isOnTimer = true;
    }

    if (isOnTimer && timer == nullptr) { //VERIFICA SE EXISTE ALGUM CRONOMETRO
        timer = new QTimer(this);
        QObject::connect(timer, &QTimer::timeout, [=]() {
            if (isOnTimer) {
                gerarDados();
            }
        });

        timeSlide = ui->horizontalSliderTimer->value();
        timeSlide *= 1000;

        timer->setInterval(timeSlide);
        timer->start();
    }

}
void MainWindow::stopTimer(){
    isOnTimer = false;
    qDebug()<<"isOnTimer: "<<isOnTimer;
    timer->stop();
    timer = nullptr;
}

void MainWindow::gerarDados(){
    int max, min, number, aux;
    max = ui->horizontalSliderMax->value()+1;
    min = ui->horizontalSliderMin->value();

    if(min>max){
        aux = min;
        min = max;
        max = aux;
        number = min + (qrand()%(max-min));
    }
    else{
        number = min + (qrand()%(max-min));
    }

    QDateTime timer;
    QString text;
    qint64 msecdate;
    QString str;
    if(conectado){

      msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();
      qDebug()<<msecdate;
      str = "set "+ QString::number(msecdate) + " " +
      QString::number(number);
      ui->textBrowserDados->append(str);
      qDebug() << str;
      qDebug() <<"escrevendo "<<socket->write(str.toStdString().c_str())<<"bytes";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "escreveu";
      }
    }
}


MainWindow::~MainWindow(){
  delete socket;
  delete ui;
}
