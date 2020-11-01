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
    explicit weights_input(QWidget *parent = nullptr,int8_t input_num = 0,int8_t nodes_num = 0, std::vector<int> * weights = new std::vector<int>(10) );
    ~weights_input();

private:
    Ui::weights_input *ui;
    QVector<QSpinBox*> weights_boxes;
    int8_t _nodes_num;
    std::vector<int> * _weights;
    QPushButton * setbutton;
};

#endif // WEIGHTS_INPUT_H
