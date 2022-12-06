#include "newhabit.h"
#include "checkhabitbtn.h"
#include "ui_newhabit.h"
#include <QInputDialog>
#include <QScrollArea>
#include <QWheelEvent>
#include <QDate>
#include <QDialog>

newHabit::newHabit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newHabit)
{
    ui->setupUi(this);
    ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:3px;}");

    QDate dateOfToday = QDate::currentDate();
    QDate dateValue = dateOfToday;

    int dayNumberTotal = 30;
    for (int i = 0; i < dayNumberTotal; ++i)
    {
        int dayValueInt = dateValue.day();
        QString dayValue = QString::number(dayValueInt);

        checkHabitBtn *checkHabitBtnptr = new checkHabitBtn(this);
        checkHabitBtnptr->assignDateToLabel(dayValue);
        ui->trackingLayout->addWidget(checkHabitBtnptr);

        allDaysState.append(checkHabitBtnptr);

        dateValue = dateOfToday.addDays(i+1);

    }

}

newHabit::~newHabit()
{
    delete ui;
}

void newHabit::nameHabitLabel()
{
    if (habitName == "")
    {
        habitName = QInputDialog::getText(this, " ", "Quelle est votre nouvelle habitude ?");
    }
    ui->habitLabel->setText(habitName);
}

void newHabit::on_habitLabel_clicked()
{
    habitName = QInputDialog::getText(this, " ", "Comment voulez vous  renommer votre habitube ?");
    if (habitName != "")
    {
        ui->habitLabel->setText(habitName);
    }
    else
    {
        // TODO error empty habit
    }

}

void newHabit::loadDayData()
{

}



