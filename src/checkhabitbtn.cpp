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
    if (ui->pushButton->text() == "0")
    {
        ui->pushButton->setText("1");
    }
    else
    {
        ui->pushButton->setText("0");
    }
}

