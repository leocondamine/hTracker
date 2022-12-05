#ifndef NEWHABIT_H
#define NEWHABIT_H

#include <QWidget>
#include <QVector>
#include <QScrollBar>
#include <QWheelEvent>
#include "htracker.h"

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

    Ui::newHabit *ui;


private slots:
    void on_habitLabel_clicked();
   // void scrollMouseEvent(QWheelEvent *event);

private:
    int getDayNumberTotal();


};

#endif // NEWHABIT_H
