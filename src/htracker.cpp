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



hTracker::hTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hTracker)
{
    ui->setupUi(this);
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
        newHabitptr->setAttribute(Qt::WA_DeleteOnClose, true);
        ++habitNumberTotal;
        allHabits.append(newHabitptr);
    }
    newHabitptr->dayOfStart = QDate::currentDate();
    newHabitptr->dayOfStartstr = newHabitptr->dayOfStart.toString("dd.MM.yyyy");
}


void hTracker::on_addHabitBtn_clicked()
{
    addNewHabit();
}


void hTracker::openReadHabitData()
{
    QString fileName =  QDir::currentPath() + "/autosave.json";
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
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
        std::cout << DataJSON.size();
        for(int index=0;index<DataJSON.size();index+=2)
        {
            QJsonObject habitDataJSON = DataJSON[index].toObject();

            newHabit *newHabitptr = new newHabit(this);
            newHabitptr->habitName = habitDataJSON["Habit Name"].toString();
            newHabitptr->nameHabitLabel();
            ui->habitLayout->addWidget(newHabitptr);
            newHabitptr->setAttribute(Qt::WA_DeleteOnClose, true);
            allHabits.append(newHabitptr);

            newHabitptr->dayOfStartstr = habitDataJSON["Day of start"].toString();
            //newHabitptr->dayOfStart = QDate::currentDate(); // TO DO convert to QDate

        }
    }
    return true;
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
    QString fileName =  QDir::currentPath() + "/autosave.json";
    QFile file(fileName);
    QJsonObject dataObject;
    writeAllData(dataObject);
    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(dataObject).toJson());
    QDataStream out(&file);
    // file.save();
    file.close();
}
