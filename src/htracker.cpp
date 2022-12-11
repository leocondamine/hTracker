#include "htracker.h"
#include "ui_htracker.h"
#include <QString>
#include "newhabit.h"
#include <QInputDialog>
#include <QVector>
#include <QWidget>
#include <QScrollBar>
#include <QScrollArea>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <iostream>
#include <QFileDialog>
#include <QIODevice>
#include <QDataStream>
#include <QStandardPaths>



hTracker::hTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hTracker)
{
    ui->setupUi(this);
    ui->addHabitBtn->setIcon(QIcon(QDir::currentPath() + "/plus.png"));
    ui->addHabitBtn->setIconSize(QSize(35,35));
    ui->upToDateBtn->setIcon(QIcon(QDir::currentPath() +"/refresh.png"));
    ui->upToDateBtn->setIconSize(QSize(30,30));

    openReadHabitData();
}

hTracker::~hTracker()
{
    saveData();
    delete ui;
}

void hTracker::addNewHabit()
{

    newHabit *newHabitptr = new newHabit(this);
    newHabitptr->nameHabitLabel();
    if (newHabitptr->habitName != "")
    {
        ui->habitLayout->addWidget(newHabitptr);
        connect(newHabitptr,SIGNAL(closeThisHabit(int)),this,SLOT(deleteHabit(int)));
        ++habitNumberTotal;
        newHabitptr->habitIndex = allHabits.size();
        allHabits.append(newHabitptr);
        newHabitptr->dayOfStart = QDate::currentDate();
        newHabitptr->dayOfStartstr = newHabitptr->dayOfStart.toString("dd/MM/yyyy");
        newHabitptr->loadedHabit = false;
        QJsonArray oneDataArrayJSON;
        oneDataArrayJSON.append("0");
        newHabitptr->setupCheckHabitBtn(oneDataArrayJSON);

    }
    connect(this, SIGNAL(sendGoToDayZero()), newHabitptr, SLOT(goToDayZero()));

}


void hTracker::on_addHabitBtn_clicked()
{
    addNewHabit();
}


void hTracker::openReadHabitData()
{
    QString fileName =  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/hTracker/autosave.json";
    qDebug() << fileName;
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    QJsonParseError JsonParseError;
    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData, &JsonParseError));
    if(JsonParseError.error != QJsonParseError::NoError){
            qDebug()<< "Parse Error"<< JsonParseError.errorString();
           // QMessageBox::warning(this,"Load JSON File","Please check the JSON file, there are some issues in it");
            return;
    }
    loadHabitData(loadDoc.object());

}

bool hTracker::loadHabitData(const QJsonObject &json)
{
    if(json.contains("Total Habits"))
    {
        habitNumberTotal = json["Total Habits"].toInt();
    }

    if(json.contains("Data") && json["Data"].isArray())
    {
        QJsonArray DataJSON = json["Data"].toArray();
        for(int index=0;index<DataJSON.size();index+=2)
        {
            QJsonObject habitDataJSON = DataJSON[index].toObject();

            newHabit *newHabitptr = new newHabit(this);
            newHabitptr->habitName = habitDataJSON["Habit Name"].toString();
            newHabitptr->nameHabitLabel();
            ui->habitLayout->addWidget(newHabitptr);
            connect(newHabitptr, SIGNAL(closeThisHabit(int)), this, SLOT(deleteHabit(int)));
            newHabitptr->habitIndex = allHabits.size();
            allHabits.append(newHabitptr);
            newHabitptr->dayOfStartstr = habitDataJSON["Day of start"].toString();
            newHabitptr->loadedHabit = true;
            QJsonArray checkHabitBtnDataJSON = DataJSON[index+1].toArray();
            newHabitptr->setupCheckHabitBtn(checkHabitBtnDataJSON);
            // newHabitptr->goToDayZero();
            connect(this, SIGNAL(sendGoToDayZero()), newHabitptr, SLOT(goToDayZero()));


        }
    }
    return true;
}

void hTracker::deleteHabit(int index)
{
    allHabits[index]->close();
    for (int i = index + 1; i < habitNumberTotal; ++i)
    {
        allHabits[i]->habitIndex--;
    }
    allHabits.remove(index);
    habitNumberTotal--;
}


bool hTracker::writeAllData(QJsonObject &json)
{
    json["Author Name"] = "Leo";
    json["Total Habits"] = allHabits.length();

    QJsonArray allDataJSON;
    for (int i=0; i<allHabits.length() ;i++ ) {
        QJsonObject habitDataJSON;

        habitDataJSON["Habit Name"] = allHabits[i]->habitName;
        habitDataJSON["Day of start"] = allHabits[i]->dayOfStartstr;


        QJsonArray allStateData;
        for (int j=0;j<allHabits[i]->allDaysState.length() ;j++ ) {
            QJsonObject stateData;
            stateData["State"] = allHabits[i]->allDaysState[j]->State;
            allStateData.append(stateData);
        }
        allDataJSON.append(habitDataJSON);
        allDataJSON.append(allStateData);
    }
    json["Data"] = allDataJSON;
    return true;
}


void hTracker::saveData()
{
    QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/hTracker");
    QString fileName =  QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/hTracker/autosave.json";
    qDebug() << fileName;
    QFile file(fileName);
    QJsonObject dataObject;
    writeAllData(dataObject);
    file.open(QIODevice::ReadWrite);
    file.write(QJsonDocument(dataObject).toJson());
    QDataStream out(&file);
    // file.save();
    file.close();
}

void hTracker::on_upToDateBtn_clicked()
{
    emit sendGoToDayZero();
}

