// signup.h

#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QRegularExpression>
#include <QMessageBox>

class MainWindow;
class login;

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr, MainWindow *mainWindow = nullptr, login *login = nullptr);
    ~Signup();

public slots:
    void returnToMainWindow();
    void goToLogin();
    void on_pushButton_back1_clicked();
    bool isValidEmail(const QString &email);
    void showMessage(const QString &title, const QString &text, QMessageBox::Icon icon = QMessageBox::Information, QFlags<QMessageBox::StandardButton> buttons = QMessageBox::Ok);

private slots:
    void on_pushButton_Signup_clicked();

private:
    Ui::Signup *ui;
    MainWindow *mainWindow;
    QSqlDatabase DB;
    login *login;
};

#endif // SIGNUP_H
