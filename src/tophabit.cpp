#include "tophabit.h"
#include "ui_tophabit.h"
#include <QScrollArea>

topHabit::topHabit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::topHabit)
{
    ui->setupUi(this);
    ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar {height:3px;}");
    ui->scrollArea->setStyleSheet("QScrollArea {border:0px;}");
}

topHabit::~topHabit()
{
    delete ui;
}
