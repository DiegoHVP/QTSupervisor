#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
  void tcpConnect();
  void tcpDisconnect();
  void gerarDados();
public slots:
  void connectServer();
  void disconnectServer();
  void startTimer();
  void stopTimer();
signals:
  void timeout();
private:
  QTimer *timer = nullptr;
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
