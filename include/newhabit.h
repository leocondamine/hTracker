#ifndef NEWHABIT_H
#define NEWHABIT_H

#include <QWidget>
#include <QVector>
#include <QScrollBar>
#include <QWheelEvent>
#include <QVector>
#include <checkhabitbtn.h>
#include <QDate>


namespace Ui {
class newHabit;
}

class newHabit : public QWidget
{
    Q_OBJECT

public:
    explicit newHabit(QWidget *parent = nullptr);
    ~newHabit();
    void nameHabitLabel();

    QString habitName;

    int dayNumberTotal;
    QVector<checkHabitBtn *> allDaysState;

    QDate dayOfStart;
    QString dayOfStartstr;



private slots:
    void on_habitLabel_clicked();

private:
    int getDayNumberTotal();
    void loadDayData();
    Ui::newHabit *ui;


};

#endif // NEWHABIT_H
