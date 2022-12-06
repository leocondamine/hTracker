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
        // TODO SetStyle sheet done
        State = 1;
    }
    else if (State == 1)
    {
        // TODO SetStyle sheet not done
        State = 0;
    }
}

void checkHabitBtn::assignDateToLabel(QString day)
{
   ui->pushButton->setText(day);
}


void checkHabitBtn::setStyleSheetDone()
{

}

void checkHabitBtn::setStyleSheetNotDone()
{

}
