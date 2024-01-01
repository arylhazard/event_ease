#ifndef QUESTION_H
#define QUESTION_H

#include <QDialog>
class login;

namespace Ui {
class question;
}

class question : public QDialog
{
    Q_OBJECT

public:
    explicit question(QWidget *parent = nullptr, login* login = nullptr);
    ~question();

private slots:
    void on_pushButton_done_clicked();

private:
    Ui::question *ui;
    login* login;
};

#endif // QUESTION_H
