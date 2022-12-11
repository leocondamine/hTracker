#include "checkhabitbtn.h"
#include "ui_checkhabitbtn.h"

checkHabitBtn::checkHabitBtn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checkHabitBtn)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("QPushButton::hover{background-color: #FF6969;}");
}

checkHabitBtn::~checkHabitBtn()
{
    delete ui;
}

void checkHabitBtn::on_pushButton_clicked()
{
    if (State == 0)
    {
        setDone();
        emit habitNumberChanged(1);
    }
    else if (State == 1)
    {
        setNotDone();
        emit habitNumberChanged(-1);
    }
}

void checkHabitBtn::assignDateToLabel(QString day)
{
   ui->pushButton->setText(day);
}

void checkHabitBtn::setDone()
{
    setStyleSheetDone();
    State = 1;
}

void checkHabitBtn::setNotDone()
{
    setStyleSheetNotDone();
    State = 0;
}


void checkHabitBtn::setStyleSheetDone()
{
    ui->pushButton->setStyleSheet("QPushButton {background-color: #ff3333; color: #fff; font-size: 11px;font-weight: bold; border: none; border-radius: 3px; padding: 5px;} QPushButton::hover{background-color: #FF6969;}");
}

void checkHabitBtn::setStyleSheetNotDone()
{
    ui->pushButton->setStyleSheet("QPushButton {background-color: #fff; color: #ff3333; font-size: 11px;font-weight: bold; border: none; border-radius: 3px; padding: 5px;} QPushButton::hover{background-color: #FFE3E3;}");
}
