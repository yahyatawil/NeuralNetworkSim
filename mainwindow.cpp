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

void MainWindow::output_calculation()
{
//Z11 = W11X1+W12X2 ... + Wn1Xn + b11
//Z21 = W12X1+W22X2 ... + Wn2Xn + b12
// ...
//Z = W1a1 + W2a2+ .. + Wm + b
//all_weights = <W1,W2,B,w,b>

    qDebug()<<all_weights;

    for(int i = 0;i<all_weights.size();i++)
    {
        QString text_to_print;
        if(i < ui->inputs_sb->value())
        {
            text_to_print.append("Input weights:");
        }
        else if(i == ui->inputs_sb->value())
        {
            text_to_print.append("Hidden layer bias:");
        }
        else if(i == (ui->inputs_sb->value() +1 ))
        {
            text_to_print.append("Hidden layer weights:");
        }
        else if(i == (ui->inputs_sb->value()+2))
        {
            text_to_print.append("\nOutput Bias:");
        }
        for(int j = 0;j < all_weights.at(i).size() ; j++)
        {
            if(i < ui->inputs_sb->value())
            {
                text_to_print.append(QString::fromLatin1("W%1%2 = %3,").arg(i).arg(j).arg(all_weights.at(i).at(j)));
            }
            else if(i == ui->inputs_sb->value())
            {
                text_to_print.append(QString::fromLatin1("B%1 = %3,").arg(j).arg(all_weights.at(i).at(j)));
            }
            else if(i == (ui->inputs_sb->value()+1))
            {
                text_to_print.append(QString::fromLatin1("W%1 = %3,").arg(j).arg(all_weights.at(i).at(j)));
            }
            else if(i == (ui->inputs_sb->value()+2))
            {
                text_to_print.append(QString::fromLatin1("B=%1").arg(all_weights.at(i).at(j)));
            }
        }
        ui->allweights_tb->append(text_to_print);
    }
    ui->allweights_tb->scroll(0,0);
    std::vector<double> hidden_biase;
    hidden_biase = all_weights.at(ui->inputs_sb->value());
    qDebug()<<hidden_biase;
    std::vector<double> hidden_weights;
    hidden_weights = all_weights.at(ui->inputs_sb->value()+1);
    qDebug()<<hidden_weights;

    for(int i=0;i<number_nodes;i++)
    {
        double output =0;
        for(int j=0;j<ui->inputs_sb->value();j++)
        {
        qDebug()<<(all_weights.at(j)).at(i)<<'*'<<inputs.at(j)->value();

        output += ((all_weights.at(j)).at(i)*inputs.at(j)->value());
        }
        qDebug()<<'+'<<hidden_biase.at(i);

        output += hidden_biase.at(i);
        qDebug()<<output<<sigmoid(output);
        hidden_layer_output.push_back(sigmoid(output));
    }

    double pre_output =0;
    for(int i=0;i<number_nodes;i++)
    {
        pre_output += (hidden_layer_output.at(i)*hidden_weights.at(i));
    }
    pre_output += all_weights.at(ui->inputs_sb->value()+2).at(0);

    ui->output_l->setNum(sigmoid(pre_output));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttons.push_back(ui->SethiddenLayerBias_pb);
    buttons.push_back(ui->SethiddenLayerwehights_pb);
    buttons.push_back(ui->SetactivationLayerBias_pb);

    ui->toActivateLabel_l->setText(QString("<ul>\
                                            <li>Set inputs values and wehights.</li>\
                                            <li>Set weights of Hidden layer to Activation Layer.</li>\
                                            <li>Set biases of Hidden layer nodes.</li>\
                                            <li>Set biases of Activation Layer nodes.</li>\
                                            </ul>"));

    connect(ui->set_pb, SIGNAL(clicked()), this , SLOT(create_shapes()));
    connect(ui->calculate_pb, SIGNAL(clicked()),this , SLOT(output_calculation()));
    ui->output_l->hide();

    connect(ui->SethiddenLayerBias_pb,&QPushButton::clicked,[=](){
        std::vector<double> temp;
        all_weights.push_back(temp);
        weights_input * inputs_widget = new weights_input(nullptr,-1,number_nodes,&(all_weights.at(all_weights.size()-1)),0,&buttons);
        inputs_widget->show();
        inputs_widget->raise();

        ui->toActivateLabel_l->setText(QString("<ul>\
                                                <li>Set weights of Hidden layer to Activation Layer.</li>\
                                                <li>Set biases of Activation Layer nodes.</li>\
                                                </ul>"));
        ui->SethiddenLayerwehights_pb->setEnabled(1);

    });

    connect(ui->SethiddenLayerwehights_pb,&QPushButton::clicked,[=](){
        std::vector<double> temp;
        all_weights.push_back(temp);
        weights_input * inputs_widget = new weights_input(nullptr,-2,number_nodes,&(all_weights.at(all_weights.size()-1)),0,&buttons);
        inputs_widget->show();
        inputs_widget->raise();

        ui->toActivateLabel_l->setText(QString("<ul>\
                                                <li>Set biases of Activation Layer nodes.</li>\
                                                </ul>"));
        ui->SetactivationLayerBias_pb->setEnabled(1);

    });

    connect(ui->SetactivationLayerBias_pb,&QPushButton::clicked,[=](){
        std::vector<double> temp;
        all_weights.push_back(temp);
        weights_input * inputs_widget = new weights_input(nullptr,-3,1,&(all_weights.at(all_weights.size()-1)),0,&buttons);
        inputs_widget->show();
        inputs_widget->raise();

        ui->toActivateLabel_l->setText(QString("<ul>\
                                                <li>Ready to Calculate</li>\
                                                </ul>"));
        ui->calculate_pb->setEnabled(1);

    });

}


void MainWindow::create_shapes()
{
    ui->output_l->show();

    //clear first, if exist
    if(inputs.size() != 0)
    {
        ui->toActivateLabel_l->setText(QString("<ul>\
                                                <li>Set inputs values and wehights.</li>\
                                                <li>Set weights of Hidden layer to Activation Layer.</li>\
                                                <li>Set biases of Hidden layer nodes.</li>\
                                                <li>Set biases of Activation Layer nodes.</li>\
                                                </ul>"));

        ui->SethiddenLayerBias_pb->setEnabled(0);
        ui->SethiddenLayerwehights_pb->setEnabled(0);
        ui->SetactivationLayerBias_pb->setEnabled(0);
        ui->calculate_pb->setEnabled(0);

        for (int i = 0; i<inputs.size();i++)
        {
           inputs.at(i)->~QDoubleSpinBox();
        }
        inputs.clear();
        inputs.shrink_to_fit();
        all_weights.clear();
        all_weights.shrink_to_fit();

        buttons.at(0)->setToolTip("");
        buttons.at(1)->setToolTip("");
        buttons.at(2)->setToolTip("");

    }

    //create
    uint16_t delta_y=0;
    for (int i = 0; i<ui->inputs_sb->value();i++)
    {
        delta_y = INPUT_DELTA*i;
        inputs.push_back( new QDoubleSpinBox(ui->centralwidget));
        inputs.at(i)->setGeometry(QRect(INPUT_X, INPUT_Y+delta_y, INPUT_len_X, INPUT_len_Y));
        inputs.at(i)->setButtonSymbols(QAbstractSpinBox::NoButtons);
        inputs.at(i)->setMinimum(-99.000000000000000);
        inputs.at(i)->raise();
        inputs.at(i)->show();
        inputs.at(i)->setEnabled(0);

        inputs.at(i)->setToolTip("");
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
            std::vector<double> temp;
            all_weights.push_back(temp);

            weights_input * inputs_widget = new weights_input(nullptr,i,number_nodes,&(all_weights.at(i)),&inputs,&buttons);
            inputs_widget->show();
            inputs_widget->raise();

            inputs.at(i)->blockSignals(true);

            if(i<(ui->inputs_sb->value()-1))
            {
                inputs.at(i+1)->setEnabled(1);
                //inputs.at(i+1)->setFocus();
            }
            else
            {
                ui->toActivateLabel_l->setText(QString("<ul>\
                                                        <li>Set weights of Hidden layer to Activation Layer.</li>\
                                                        <li>Set biases of Hidden layer nodes.</li>\
                                                        <li>Set biases of Activation Layer nodes.</li>\
                                                        </ul>"));
                ui->SethiddenLayerBias_pb->setEnabled(1);
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
                QLineF line(INPUT_X+INPUT_len_X, (INPUT_Y+INPUT_len_Y/2)+delta_y_line, HIDDEN_X, (HIDDEN_Y+HIDDEN_LEN/2)+delta_y);
                painter.drawLine(line);
            }
        }

        painter.setPen(Qt::blue);
        QRectF rectangle(ACTIVATION_X, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y, ACTIVATION_LEN, ACTIVATION_LEN);
        painter.drawEllipse(rectangle);

        painter.setPen(Qt::black);
        uint16_t delta_y_line=0;
        for (int j = 0; j<number_nodes;j++)
        {
            delta_y_line = HIDDEN_DELTA*j;
            QLineF line(HIDDEN_X+HIDDEN_LEN, (HIDDEN_Y+HIDDEN_LEN/2)+delta_y_line, ACTIVATION_X, ((number_nodes/2)*HIDDEN_LEN+HIDDEN_Y)+ACTIVATION_LEN/2);
            painter.drawLine(line);
        }

        ui->output_l->setGeometry(OUTPUT_X, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y, OUTPUT_len_X, OUTPUT_len_Y);

        QLineF line(ACTIVATION_X+ACTIVATION_LEN, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y+ACTIVATION_LEN/2, OUTPUT_X, (number_nodes/2)*HIDDEN_LEN+HIDDEN_Y+ACTIVATION_LEN/2);
        painter.drawLine(line);

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
