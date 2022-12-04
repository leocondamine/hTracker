#include "htracker.h"
#include "ui_htracker.h"
#include <QString>
#include "newhabit.h"
#include "tophabit.h"
#include <QInputDialog>
#include <QVector>

hTracker::hTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hTracker)
{
    ui->setupUi(this);
    topHabit *topHabitptr = new topHabit(this);
    ui->habitLayout->addWidget(topHabitptr);

}

hTracker::~hTracker()
{
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
    }
}


void hTracker::on_addHabitBtn_clicked()
{
    addNewHabit();
}

