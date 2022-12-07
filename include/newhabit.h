#ifndef NEWHABIT_H
#define NEWHABIT_H

#include <QWidget>
#include <QVector>
#include <QScrollBar>
#include <QWheelEvent>
#include <QVector>
#include <checkhabitbtn.h>
#include <QDate>


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
    int habitIndex;

    int dayNumberTotal{1};
    QVector<checkHabitBtn *> allDaysState;

    QDate dayOfStart;
    QString dayOfStartstr;
    bool loadedHabit;
    void setupCheckHabitBtn(QJsonArray &habitStateArray);

    void closeHabit(int index);

public slots:
    void displayNewNumberHabit(int N);

private slots:
    void on_habitLabel_clicked();

    void on_closeButton_clicked();

private:
    int numberHabitDone{0};
    int getDayNumberTotal();
    void openReadDayData();
    bool loadDayData(const QJsonObject &json);
    Ui::newHabit *ui;

signals:
    void closeThisHabit(int index);


};

#endif // NEWHABIT_H
