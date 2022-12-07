#include "checkhabitbtn.h"
#include "ui_checkhabitbtn.h"

checkHabitBtn::checkHabitBtn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checkHabitBtn)
{
    ui->setupUi(this);
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
    ui->pushButton->setStyleSheet("QPushButton {color: red; border: 3px}");
}

void checkHabitBtn::setStyleSheetNotDone()
{
    ui->pushButton->setStyleSheet("QPushButton {color: blue; border: 3px}");
}
