#ifndef HTRACKER_H
#define HTRACKER_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QJsonObject>
#include "newhabit.h"


QT_BEGIN_NAMESPACE
namespace Ui { class hTracker; }
QT_END_NAMESPACE

class hTracker : public QMainWindow
{
    Q_OBJECT

public:
    hTracker(QWidget *parent = nullptr);
    ~hTracker();

    int habitNumberTotal;
    QVector<newHabit *> allHabits;

public slots:
    void deleteHabit(int index);

private slots:
    void on_addHabitBtn_clicked();

private:
    Ui::hTracker *ui;
    void addNewHabit();

    void openReadHabitData();
    bool loadHabitData(const QJsonObject &json);

    bool writeAllData(QJsonObject &json);
    void saveData();

};
#endif // HTRACKER_H
