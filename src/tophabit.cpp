#include "tophabit.h"
#include "ui_tophabit.h"
#include "datelabel.h"
#include <QScrollArea>
#include <QDate>
#include <QString>
#include <QCalendar>
#include "htracker.h"

topHabit::topHabit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topHabit)
{
    ui->setupUi(this);
    ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:3px;}");
    QDate dateOfToday = QDate::currentDate();
    QDate dateValue = dateOfToday;

    int dayNumberTotal = getDayNumberTotal();
    for (int i = 0; i < dayNumberTotal; ++i)
    {
        int dayValueInt = dateValue.day();
        QString dayValue = QString::number(dayValueInt);

        dateLabel *dateptr = new dateLabel(this);
        dateptr->assignDateToLabel(dayValue);
        ui->trackingDateLayout->addWidget(dateptr);

        dateValue = dateOfToday.addDays(i+1);
    }
}

topHabit::~topHabit()
{
    delete ui;
}

int topHabit::getDayNumberTotal()
{
    return 47;
}

