#include "newhabit.h"
#include "checkhabitbtn.h"
#include "qjsonarray.h"
#include "ui_newhabit.h"
#include <QInputDialog>
#include <QScrollArea>
#include <QWheelEvent>
#include <QDate>
#include <QDialog>
#include <QFile>
#include <QJsonParseError>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

newHabit::newHabit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newHabit)
{
    ui->setupUi(this);
    //ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:3px;}");

}

newHabit::~newHabit()
{
    delete ui;
}

void newHabit::setupCheckHabitBtn(QJsonArray &habitStateArray)
{
    if (loadedHabit == false)
    {
        QDate dateOfToday = QDate::currentDate();
        QDate dateValue = dateOfToday;
        int dayValueInt = dateValue.day();
        QString dayValue = QString::number(dayValueInt);
        checkHabitBtn *checkHabitBtnptr = new checkHabitBtn(this);
        checkHabitBtnptr->assignDateToLabel(dayValue);
        checkHabitBtnptr->setStyleSheetNotDone();
        ui->trackingLayout->addWidget(checkHabitBtnptr);
        allDaysState.append(checkHabitBtnptr);
        connect(checkHabitBtnptr, SIGNAL(habitNumberChanged(int)), this, SLOT(displayNewNumberHabit(int)));

    }
    else
    {
        dayOfStart = QDate::fromString(dayOfStartstr,"dd/MM/yyyy");
        QDate dateValue = dayOfStart;
        dayNumberTotal = dayOfStart.daysTo(QDate::currentDate()); // TO DO Calculate days
        dayNumberTotal++ ;
        for (int i = 0; i < dayNumberTotal; ++i)
        {
            int dayValueInt = dateValue.day();
            QString dayValue = QString::number(dayValueInt);

            checkHabitBtn *checkHabitBtnptr = new checkHabitBtn(this);
            checkHabitBtnptr->assignDateToLabel(dayValue);
            if (i < habitStateArray.size())
            {
                QJsonObject habitStateJSON = habitStateArray[i].toObject();
                if (habitStateJSON["State"] == 0)
                {
                    checkHabitBtnptr->setNotDone();
                }
                else
                {
                    checkHabitBtnptr->setDone();
                }

            }
            else
            {
               checkHabitBtnptr->setNotDone();
            }
            ui->trackingLayout->addWidget(checkHabitBtnptr);
            allDaysState.append(checkHabitBtnptr);
            dateValue = dateValue.addDays(1);

            connect(checkHabitBtnptr, SIGNAL(habitNumberChanged(int)), this, SLOT(displayNewNumberHabit(int)));

        }

    }
    for (int i = 0; i < allDaysState.length(); ++i)
    {
        if (allDaysState[i]->State == 1)
        {
            numberHabitDone++;
        }
    }
    displayNewNumberHabit(0);
}

void newHabit::displayNewNumberHabit(int N)
{
    numberHabitDone += N;
    QString numberHabitDoneToDisplay = QString::number(numberHabitDone);
    QString numberDayTotalToDisplay = QString::number(dayNumberTotal);
    ui->trackNumberLabel->setText(numberHabitDoneToDisplay + " / " + numberDayTotalToDisplay);
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


void newHabit::closeHabit(int index)
{
    emit closeThisHabit(index);
}

void newHabit::on_closeButton_clicked()
{
    QMessageBox reply;
    reply.setText("Etes vous sûr de vouloir abandonner cette habitude ?");
    QAbstractButton *yes = reply.addButton(("Oui"), QMessageBox::YesRole);
    QAbstractButton *no = reply.addButton(("Non"), QMessageBox::NoRole);
    reply.setIcon(QMessageBox::Question);
    reply.exec();

    if(reply.clickedButton() == yes)
    {
        closeHabit(habitIndex);
    }
}

