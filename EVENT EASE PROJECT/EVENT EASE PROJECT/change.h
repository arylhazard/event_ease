#ifndef CHANGE_H
#define CHANGE_H

#include <QDialog>


namespace Ui {
class change;
}

class change : public QDialog
{
    Q_OBJECT

public:
    explicit change(QWidget *parent = nullptr, class login* login = nullptr);
    ~change();

private slots:
    void on_pushButton_done_2_clicked();

private:
    Ui::change *ui;
    login* login;
};

#endif // CHANGE_H
