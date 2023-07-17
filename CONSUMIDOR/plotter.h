#ifndef PLOTTER_H
#define PLOTTER_H

#include <QPaintEvent>
#include <QWidget>
#include <iostream>
#include <vector>

class Plotter : public QWidget
{
    Q_OBJECT

private:
    std::vector<double> xtime;  /**< Vetor contendo os valores de tempo */
    std::vector<double> ynumber;  /**< Vetor contendo os valores numéricos */
    int x0, x1, y0, y1;  /**< Coordenadas do retângulo de desenho */

public:
    /**
     * @brief Constrói um objeto Plotter.
     * @param parent O widget pai (padrão é nullptr).
     */
    explicit Plotter(QWidget *parent = nullptr);

    /**
     * @brief Sobrescreve o evento de pintura.
     * @param event - O evento de pintura.
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief Define os dados para exibição no gráfico.
     * @param xtime Os valores de tempo.
     * @param ynumber Os valores numéricos.
     */
    void setDados(std::vector<double> xtime, std::vector<double> ynumber);

signals:
};

#endif // PLOTTER_H
