#ifndef WEIGHTS_INPUT_H
#define WEIGHTS_INPUT_H

#include <QWidget>
#include <QVector>
#include <QSpinBox>
#include <QPushButton>

namespace Ui {
class weights_input;
}

class weights_input : public QWidget
{
    Q_OBJECT

public:
    explicit weights_input(QWidget *parent = nullptr,int8_t input_num = 0,int8_t nodes_num = 0, std::vector<double> * weights = new std::vector<double>(10),QVector<QDoubleSpinBox*> * input_boxes =  new QVector<QDoubleSpinBox*>,QVector<QPushButton*> * buttons = new QVector<QPushButton*>);
    ~weights_input();

private:
    Ui::weights_input *ui;
    QVector<QDoubleSpinBox*> weights_boxes;
    int8_t _nodes_num;
    std::vector<double> * _weights;
    QPushButton * setbutton;
};

#endif // WEIGHTS_INPUT_H
