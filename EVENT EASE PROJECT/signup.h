// signup.h

#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QRegularExpression>
#include <QMessageBox>
class MainWindow;

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr, MainWindow* mainWindow = nullptr);
    ~Signup();

public slots:
    void returnToMainWindow();

private slots:
    void on_pushButton_back1_clicked();



    void on_pushButton_next_clicked();

     bool isValidEmail(const QString &email);
    void showMessage(const QString &title, const QString &text, QMessageBox::Icon icon = QMessageBox::Information, QFlags<QMessageBox::StandardButton> buttons = QMessageBox::Ok);


private:
    Ui::Signup *ui;
    MainWindow* mainWindow;
    QSqlDatabase DB;
};

#endif // SIGNUP_H
