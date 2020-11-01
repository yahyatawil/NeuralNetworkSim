#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QSpinBox>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent * event);

private:
    const int INPUT_X =10 ;
    const int INPUT_Y =30 ;
    const int INPUT_len_X =42 ;
    const int INPUT_len_Y =22 ;
    const int INPUT_DELTA = 40;

    const int HIDDEN_X = 200;
    const int HIDDEN_Y = 30;
    const int HIDDEN_LEN = 30;
    const int HIDDEN_DELTA = 40;

    const int ACTIVATION_X = 400;
    const int ACTIVATION_LEN = 30;

    const int OUTPUT_X =600 ;
    const int OUTPUT_len_X =42 ;
    const int OUTPUT_len_Y =22 ;

    Ui::MainWindow *ui;
    uint8_t number_inputs=0;
    uint8_t number_nodes=0;
    QVector<QSpinBox*> inputs;
    QVector<QPushButton*> buttons;

    std::vector<std::vector<int>> all_weights;

    double sigmoid(double number);


private slots:
    void create_shapes();
    void output_calculation();
};
#endif // MAINWINDOW_H
