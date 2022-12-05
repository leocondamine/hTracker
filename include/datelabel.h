#ifndef DATELABEL_H
#define DATELABEL_H

#include <QWidget>
#include <QLabel>
#include <QString>

namespace Ui {
class dateLabel;
}

class dateLabel : public QWidget
{
    Q_OBJECT

public:
    explicit dateLabel(QWidget *parent = nullptr);
    ~dateLabel();
    void assignDateToLabel(QString day);

private:
    Ui::dateLabel *ui;

};

#endif // DATELABEL_H
