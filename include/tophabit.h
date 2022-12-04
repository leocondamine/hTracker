#ifndef TOPHABIT_H
#define TOPHABIT_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>

namespace Ui {
class topHabit;
}

class topHabit : public QWidget
{
    Q_OBJECT

public:
    explicit topHabit(QWidget *parent = nullptr);
    ~topHabit();

private:
    Ui::topHabit *ui;
};

#endif // TOPHABIT_H
