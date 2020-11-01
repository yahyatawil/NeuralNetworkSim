#include "weights_input.h"
#include "ui_weights_input.h"
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include <QLabel>

weights_input::weights_input(QWidget *parent,int8_t input_num ,int8_t nodes_num, std::vector<int> * weights, QVector<QSpinBox*> * input_boxes,QVector<QPushButton*> * buttons):
    QWidget(parent),
    ui(new Ui::weights_input)
{

    _nodes_num = nodes_num;

    _weights = weights;

    ui->setupUi(this);

    QGridLayout * m_grid_layout = new QGridLayout(this);

   if(input_boxes != 0)
   {
       this->setWindowTitle(QString("Set weights of Input %1").arg(input_num));

       int j = 0;
       for(int raw=0;raw<10;raw++)
       {
        if(j >= nodes_num) break;
        for(int col=0;col<10;col=col+2)
        {
           weights_boxes.push_back( new QSpinBox(this));
           weights_boxes.at(j)->setButtonSymbols(QAbstractSpinBox::NoButtons);
           weights_boxes.at(j)->raise();
           weights_boxes.at(j)->show();
           QLabel * label = new QLabel(QString("W%1%2").arg(input_num).arg(j), this);
           m_grid_layout->addWidget(label,raw,col);
           m_grid_layout->addWidget(weights_boxes.at(j),raw,col+1);
           j++;
           if(j >= nodes_num) break;
        }
       }
   }
   else
   {
      this->setWindowTitle(QString("Set weights/bias"));

       int j = 0;
       for(int raw=0;raw<10;raw++)
       {
        if(j >= nodes_num) break;
        for(int col=0;col<10;col=col+2)
        {
           weights_boxes.push_back( new QSpinBox(this));
           weights_boxes.at(j)->setButtonSymbols(QAbstractSpinBox::NoButtons);
           weights_boxes.at(j)->raise();
           weights_boxes.at(j)->show();
           QLabel * label = new QLabel(QString("%1").arg(j), this);
           m_grid_layout->addWidget(label,raw,col);
           m_grid_layout->addWidget(weights_boxes.at(j),raw,col+1);
           j++;
           if(j >= nodes_num) break;
        }
       }

   }

   setbutton = new QPushButton("&Set", this);

   QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
   sizePolicy.setHorizontalStretch(0);
   sizePolicy.setVerticalStretch(0);
   sizePolicy.setHeightForWidth(setbutton->sizePolicy().hasHeightForWidth());
   setbutton->setSizePolicy(sizePolicy);

   m_grid_layout->addWidget(setbutton, 20, 0, 1, 2);


   connect(setbutton, &QPushButton::clicked, [=]()
   {
       for(int i=0;i<_nodes_num;i++)
       {
           //qDebug() << weights_boxes.at(i)->value();
           weights->push_back(weights_boxes.at(i)->value());
       }

       if(input_boxes != 0)
       {
           int j=0;

           QString ToolTipTxt = QString("Input%1").arg(input_num);
           ToolTipTxt.append("<table>");
           for(int i=0;i<10;i++)
           {
           ToolTipTxt.append("<tr>");
           for (int k=0;k<5;k++)
           {
               ToolTipTxt.append(QString("<th>%1</th>").arg(weights_boxes.at(j++)->value()));
               if(j>=_nodes_num) break;
           }
           ToolTipTxt.append("</tr>");
           if(j>=_nodes_num) break;
           }
           ToolTipTxt.append("</table>");

           input_boxes->at(input_num)->setToolTip(ToolTipTxt);
       }
       else
       {
           QString ToolTipTxt;
           for (int i=0;i<_nodes_num;i++)
               ToolTipTxt.append(QString("%1 ").arg(weights_boxes.at(i++)->value()));

           if(input_num == -1) // hidden bias
           {
                buttons->at(0)->setToolTip(ToolTipTxt);
           }
           else if(input_num == -2) // hidden weights
           {
               buttons->at(1)->setToolTip(ToolTipTxt);
           }
           else if(input_num == -3) // activation bias
           {
               buttons->at(2)->setToolTip(ToolTipTxt);
           }

       }
       this->close();
   });
}

weights_input::~weights_input()
{
    delete ui;
}
