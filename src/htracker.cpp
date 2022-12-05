#include "htracker.h"
#include "ui_htracker.h"
#include <QString>
#include "newhabit.h"
#include "tophabit.h"
#include <QInputDialog>
#include <QVector>
#include <QWidget>
#include <QScrollBar>
#include <QScrollArea>



hTracker::hTracker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hTracker)
{
    ui->setupUi(this);
    //dayNumberTotal = getDayNumberTotal();
    topHabitptr = new topHabit(this);
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
        // connect(ui->habitLayout-><QScrollBar *>(), SIGNAL(valueChanged(int)), newHabitptr->findChild<QScrollArea::horizontalScrollBar *>(), SLOT(setValue(int)));
        ++habitNumberTotal;
    }
}


void hTracker::on_addHabitBtn_clicked()
{
    addNewHabit();
}

int hTracker::getDayNumberTotal()
{
    return 47;
}

