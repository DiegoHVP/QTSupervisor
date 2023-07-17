#include "plotter.h"
#include <QPaintEvent>
#include <QPen>
#include <QBrush>
#include <QPainter>

Plotter::Plotter(QWidget *parent) : QWidget(parent){
    //INICIALIZA OS VERES COM ZEROS
    for(int i=0; i<30; i++){
        xtime.push_back(0);
        ynumber.push_back(0);
    }
}

void Plotter::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    //FUNDO AMARELO
    QBrush brush(QColor(255, 255, 200));
    brush.setStyle(Qt::SolidPattern);

    //BORDA (CANETA PRETA)
    QPen pen(QColor(0, 0, 0));
    pen.setWidth(2);

    //ENTREGA PRO PINTOR
    painter.setBrush(brush);
    painter.setPen(pen);

    //DESENHAR UM QUADRADO COM O QUE FOI ENTREGUE PARA O PINTOR
    painter.drawRect(0, 0, width(), height());

    //LINHA GRAFICO (CANETA AZUL)
    QPen pen2(QColor(0, 0, 255));
    pen.setWidth(3);
    painter.setPen(pen2);

    //POSICOES INICIAS
    x0 = xtime[0]*width();
    y0 = ynumber[0]*(height()-ynumber[0]);

    for(int i=1; i<30; i++){
        //POSICAO NORMALIZADA
        x1=xtime[i]*width();
        y1=ynumber[i]*(height()-ynumber[i]);
        //DESENHA LINHA ENTRE AS POSICOES (x0,y0) e (x1,y1)
        painter.drawLine(x0,y0,x1,y1);
        //ATUALIZA A POSICAO (x0,y0) PARA DESENHAR APARTIR DO FINAL DA ULTIMA LINHA
        x0 = x1;
        y0 = y1;
    }
}

void Plotter::setDados(std::vector<double> _xtime, std::vector<double> _ynumber){
    //RECEBE OS DADOS
    xtime = _xtime;
    ynumber = _ynumber;
    repaint();
}
