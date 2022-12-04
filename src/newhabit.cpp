#include "newhabit.h"
#include "ui_newhabit.h"
#include "checkhabitbtn.h"
#include <QInputDialog>
#include <QScrollArea>
#include <QWheelEvent>

newHabit::newHabit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newHabit)
{
    ui->setupUi(this);
    for (int i = 0; i < 10; ++i)
    {
        checkHabitBtn *checkHabitBtnptr = new checkHabitBtn(this);
        ui->trackingLayout->addWidget(checkHabitBtnptr);
    }
    checkHabitBtn *checkHabitBtnptr = new checkHabitBtn(this);
    ui->trackingLayout->addWidget(checkHabitBtnptr);
    ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:3px;}");
    ui->scrollArea->horizontalScrollBar()->setValue(50);
}

newHabit::~newHabit()
{
    delete ui;
}

void newHabit::nameHabitLabel()
{
    habitName = QInputDialog::getText(this, " ", "Quelle est votre nouvelle habitude ?");
    ui->habitLabel->setText(habitName);
}

void newHabit::on_habitLabel_clicked()
{
    habitName = QInputDialog::getText(this, " ", "Comment voulez vous  renommer votre habitube ?");
    ui->habitLabel->setText(habitName);
}



