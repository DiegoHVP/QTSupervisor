#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

/**
 * @brief A classe MainWindow representa a janela principal do aplicativo.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /**
   * @brief Constrói um objeto MainWindow.
   * @param parent O widget pai (padrão é nullptr).
   */
  explicit MainWindow(QWidget *parent = 0);
  /**
   * @brief Destrói o objeto MainWindow.
   */
  ~MainWindow();

  /**
   * @brief Estabelece uma conexão TCP.
   */
  void tcpConnect();

  /**
   * @brief Encerra a conexão TCP.
   */
  void tcpDisconnect();

  /**
   * @brief Envia dados pela conexão TCP.
   */
  void data();


public slots:
  /**
   * @brief Slot para conectar ao servidor.
   */
  void connectServer();

  /**
   * @brief Slot para desconectar do servidor.
   */
  void disconnectServer();

  /**
   * @brief Slot para iniciar o temporizador.
   */
  void startTimer();

  /**
   * @brief Slot para parar o temporizador.
   */
  void stopTimer();

  /**
   * @brief Slot para atualizar os dados.
   */
  void update();

private:
  bool conectado = false; /**< Variavel que sinalisa a conexão */
  bool isOnTimer = false; /**< Variavel que sinalisa o cronometro */
  QTimer *timer = nullptr; /**< Cronometro */
  Ui::MainWindow *ui;
  QTcpSocket *socket; /**< Vetor de valores para o eixo x do gráfico. */
};

#endif // MAINWINDOW_H
