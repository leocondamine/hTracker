#ifndef HTRACKER_H
#define HTRACKER_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class hTracker; }
QT_END_NAMESPACE

class hTracker : public QMainWindow
{
    Q_OBJECT

public:
    hTracker(QWidget *parent = nullptr);
    ~hTracker();
    int habitNumberTotal;
    int dayNumberTotal;
    int getDayNumberTotal();

private slots:
    void on_addHabitBtn_clicked();

private:
    Ui::hTracker *ui;
    void addNewHabit();

};
#endif // HTRACKER_H
