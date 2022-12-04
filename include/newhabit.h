#ifndef NEWHABIT_H
#define NEWHABIT_H

#include <QWidget>
#include <QVector>
#include <QScrollBar>
#include <QWheelEvent>

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


private slots:
    void on_habitLabel_clicked();
   // void scrollMouseEvent(QWheelEvent *event);

private:
    Ui::newHabit *ui;

};

#endif // NEWHABIT_H
