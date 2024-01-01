#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
class login; // Forward declaration for login class
class Signup; // Forward declaration for Signup class

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showLoginDialog();
    void returnToMainWindow(); // Declare returnToMainWindow

private slots:
    void on_pushButton_signup_clicked();
    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    login* loginDialog;
    Signup* signupDialog; // Declare signupDialog
};

#endif // MAINWINDOW_H
