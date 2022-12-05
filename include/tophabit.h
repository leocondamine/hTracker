#ifndef TOPHABIT_H
#define TOPHABIT_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QDate>
#include "datelabel.h"
#include "htracker.h"


namespace Ui {
class topHabit;
}

class topHabit : public QWidget
{
    Q_OBJECT

public:
    explicit topHabit(QWidget *parent = nullptr);
    ~topHabit();
    int dayNumberTotal;
    int getDayNumberTotal();

private:
    Ui::topHabit *ui;
};

#endif // TOPHABIT_H
