#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include "weights_input.h"
#include <math.h>

double MainWindow::sigmoid(double number)
{
    return (1/(1+exp(-1*number)));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->set_pb, SIGNAL(clicked()), this , SLOT(create_shapes()));

    ui->output_sb->hide();

}


void MainWindow::create_shapes()
{
    ui->output_sb->show();

    //clear first, if exist
    if(inputs.size() != 0)
    {
        for (int i = 0; i<inputs.size();i++)
        {
           inputs.at(i)->~QSpinBox();
        }
        inputs.clear();
        inputs.shrink_to_fit();
    }

    //create
    uint16_t delta_y=0;
    for (int i = 0; i<ui->inputs_sb->value();i++)
    {
        delta_y = INPUT_DELTA*i;
        inputs.push_back( new QSpinBox(ui->centralwidget));
        inputs.at(i)->setGeometry(QRect(INPUT_X, INPUT_Y+delta_y, INPUT_len_X, INPUT_len_Y));
        inputs.at(i)->setButtonSymbols(QAbstractSpinBox::NoButtons);
        inputs.at(i)->raise();
        inputs.at(i)->show();
        inputs.at(i)->setEnabled(0);
    }

    QTimer::singleShot(10, this, [=](){
        number_nodes=ui->nodes_sb->value();
        update();}
    );

    inputs.at(0)->setEnabled(1);

    for (int i = 0; i<ui->inputs_sb->value();i++)
    {
        connect(inputs.at(i),&QSpinBox::editingFinished, [=]()
        {
            std::vector<int> temp;
            all_weights.push_back(temp);

            weights_input * inputs_widget = new weights_input(nullptr,i,number_nodes,&(all_weights.at(i)));
            inputs_widget->show();
            inputs_widget->raise();

            inputs.at(i)->blockSignals(true);

            if(i<(ui->inputs_sb->value()-1))
            {
                inputs.at(i+1)->setEnabled(1);
                //inputs.at(i+1)->setFocus();
            }
        });

    }

}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(ui->inputs_sb->value() > 0)
    {
        QPainter painter(this);
        painter.setPen(Qt::blue);

        uint16_t delta_y=0;
        for(int i=0;i<number_nodes;i++)
        {
            painter.setPen(Qt::blue);
            delta_y = HIDDEN_DELTA*i;
            QRectF rectangle(HIDDEN_X, HIDDEN_Y+delta_y, HIDDEN_LEN, HIDDEN_LEN);
            painter.drawEllipse(rectangle);

            uint16_t delta_y_line=0;
            painter.setPen(Qt::black);
            for (int j = 0; j<ui->inputs_sb->value();j++)
            {
                delta_y_line = HIDDEN_DELTA*j;
                QLineF line(INPUT_X+INPUT_len_X, (INPUT_Y+INPUT_len_Y/2)+delta_y, HIDDEN_X, (HIDDEN_Y+HIDDEN_LEN/2)+delta_y_line);
                painter.drawLine(line);
            }
        }

        painter.setPen(Qt::blue);
        QRectF rectangle(ACTIVATION_X, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y, ACTIVATION_LEN, ACTIVATION_LEN);
        painter.drawEllipse(rectangle);

        painter.setPen(Qt::black);
        uint16_t delta_y_line=0;
        for (int j = 0; j<ui->inputs_sb->value();j++)
        {
            delta_y_line = HIDDEN_DELTA*j;
            QLineF line(HIDDEN_X+HIDDEN_LEN, (HIDDEN_Y+HIDDEN_LEN/2)+delta_y_line, ACTIVATION_X, ((number_nodes/2)*HIDDEN_LEN+HIDDEN_Y)+ACTIVATION_LEN/2);
            painter.drawLine(line);
        }

        ui->output_sb->setGeometry(OUTPUT_X, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y, OUTPUT_len_X, OUTPUT_len_Y);

        QLineF line(ACTIVATION_X+ACTIVATION_LEN, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y+ACTIVATION_LEN/2, OUTPUT_X, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y+ACTIVATION_LEN/2);
        painter.drawLine(line);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
