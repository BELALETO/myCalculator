#include "dialog.h"
#include "./ui_dialog.h"



double calcVal{0.0};
bool sumTrigger{false};
bool subTrigger{false};
bool mulTrigger{false};
bool divTrigger{false};


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    flags |= Qt::WindowContextHelpButtonHint;

    setWindowFlags(flags);
    setWindowTitle("Calculator");
    ui->lineEdit->setText(QString::number(calcVal));

    QPushButton *buttons[10];

    for(int i = 0; i < 10; i++)
    {
        QString strNum = "Button" + QString::number(i);
        buttons[i] = QDialog::findChild<QPushButton*>(strNum);
        connect(buttons[i], &QPushButton::clicked, this, &Dialog::numPressed);
    }


    connect(ui->btnSign,    &QPushButton::clicked, this, &Dialog::unaryPressed);
    connect(ui->btnModulus, &QPushButton::clicked, this, &Dialog::unaryPressed);

    connect(ui->btnSum, &QPushButton::clicked, this, &Dialog::binaryPressed);
    connect(ui->btnSub, &QPushButton::clicked, this, &Dialog::binaryPressed);
    connect(ui->btnMul, &QPushButton::clicked, this, &Dialog::binaryPressed);
    connect(ui->btnDiv, &QPushButton::clicked, this, &Dialog::binaryPressed);

    connect(ui->btnUndo, &QPushButton::clicked, this, &Dialog::on_btnUndo_clicked);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::numPressed()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString ButtonStr = btn ->text();
    QString displayStr = ui ->lineEdit->text();

    if((displayStr.toDouble() == 0) || (displayStr.toDouble() == 0.0))
    {
        ui->lineEdit->setText(ButtonStr);
    }
    else
    {
        QString newStr = displayStr + ButtonStr;
        double dblStr = newStr.toDouble();
        ui->lineEdit->setText(QString::number(dblStr, 'g', 15));
    }
}

void Dialog::unaryPressed()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString ButtonStr = btn ->text();
    QString displayStr = ui ->lineEdit->text();
    double dblNum = displayStr.toDouble();

    if(ButtonStr == "%")
    {
        dblNum*=0.01;
        QString newDbl = QString::number(dblNum, 'g', 15);
        ui->lineEdit->setText(newDbl);
    }
    else if(ButtonStr == "+/-")
    {
        dblNum*=-1;
        QString newDbl = QString::number(dblNum, 'g', 15);
        ui->lineEdit->setText(newDbl);
    }
}

void Dialog::binaryPressed()
{
    sumTrigger = false;
    subTrigger = false;
    mulTrigger = false;
    divTrigger = false;

    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString ButtonStr = btn ->text();
    QString displayStr = ui ->lineEdit->text();
    calcVal = displayStr.toDouble();

    ui->lineEdit->clear();

    if(ButtonStr == "+")
    {
        sumTrigger = true;
    }
    else if(ButtonStr == "-")
    {
        subTrigger = true;
    }
    else if(ButtonStr == "X")
    {
        mulTrigger = true;
    }
    else if(ButtonStr == "÷")
    {
        divTrigger = true;
    }
}

void Dialog::on_btnUndo_clicked()
{
    QString display = ui->lineEdit->text();

    ui->lineEdit->setText(display.removeLast());


}

void Dialog::on_btnC_clicked()
{
    ui->lineEdit->clear();
}

void Dialog::on_btnEql_clicked()
{
    double solution{0.0};
    QString secondStr = ui->lineEdit->text();
    double secondVal = secondStr.toDouble();

    if(sumTrigger || subTrigger || mulTrigger || divTrigger)
    {
        if(sumTrigger)
        {
            solution = calcVal + secondVal;
        }
        else if(subTrigger)
        {
            solution = calcVal - secondVal;
        }
        else if(mulTrigger)
        {
            solution = calcVal * secondVal;
        }
        else if(divTrigger)
        {
            solution = calcVal / secondVal;
        }
    }
    ui->lineEdit->setText(QString::number(solution));
}




