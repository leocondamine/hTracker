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
    ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:3px;}");

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

void newHabit::openReadDayData()
{
    QString fileName =  QDir::currentPath() + "/autosave.json";
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QJsonParseError JsonParseError;
    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &JsonParseError));
    if(JsonParseError.error != QJsonParseError::NoError)
    {
            qDebug()<< "Parse Error"<< JsonParseError.errorString();
           // QMessageBox::warning(this,"Load JSON File","Please check the JSON file, there are some issues in it");
            return;
    }
    loadDayData(loadDoc.object());
}

void newHabit::closeHabit(int index)
{
    emit closeThisHabit(index);
}

bool newHabit::loadDayData(const QJsonObject &json)
{
    if(json.contains("Data") && json["Data"].isArray())
    {
        QJsonArray DataJSON = json["Data"].toArray();
        // std::cout << DataJSON.size();
        for(int index=1;index<DataJSON.size();index+=2)
        {
            QJsonObject habitDataJSON = DataJSON[index].toObject();
/*
            newHabit *newHabitptr = new newHabit(this);
            newHabitptr->habitName = habitDataJSON["Habit Name"].toString();
            newHabitptr->nameHabitLabel();
            ui->habitLayout->addWidget(newHabitptr);
            newHabitptr->setAttribute(Qt::WA_DeleteOnClose, true);
            allHabits.append(newHabitptr);

            newHabitptr->dayOfStartstr = habitDataJSON["Day of start"].toString();
            //newHabitptr->dayOfStart = QDate::currentDate(); // TO DO convert to QDate
*/
        }
    }
    return true;
}


void newHabit::on_closeButton_clicked()
{
    QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation de suppression", "Etes vous sûr de vouloir abandonner cette habitude ?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            closeHabit(habitIndex);
        }
}

