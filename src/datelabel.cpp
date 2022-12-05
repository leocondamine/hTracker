#include "datelabel.h"
#include "ui_datelabel.h"
#include <QLabel>
#include <QString>

dateLabel::dateLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dateLabel)
{
    ui->setupUi(this);
}

dateLabel::~dateLabel()
{
    delete ui;
}

void dateLabel::assignDateToLabel(QString day)
{
   ui->label->setText(day);
}
