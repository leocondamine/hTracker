#ifndef CHECKHABITBTN_H
#define CHECKHABITBTN_H

#include <QWidget>

namespace Ui {
class checkHabitBtn;
}

class checkHabitBtn : public QWidget
{
    Q_OBJECT

public:
    explicit checkHabitBtn(QWidget *parent = nullptr);
    ~checkHabitBtn();
    void assignDateToLabel(QString day);

    int State{0};
    void setStyleSheetDone();
    void setStyleSheetNotDone();

private slots:
    void on_pushButton_clicked();

private:
    Ui::checkHabitBtn *ui;
};

#endif // CHECKHABITBTN_H
