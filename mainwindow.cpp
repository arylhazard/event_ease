#include "mainwindow.h"
#include "login.h"
#include "signup.h"
#include <QApplication>
#include <QSplashScreen>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QTimer>

#include<ui_mainwindow.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)

{
    ui->setupUi(this); // You need to call this first


   // Forward declare MainWindow and connect the "Back" button to returnToMainWindow
    connect(ui->pushButton_login, &QPushButton::clicked, this, &MainWindow::returnToMainWindow);
    connect(ui->pushButton_signup, &QPushButton::clicked, this, &MainWindow::returnToMainWindow);

    loginDialog = nullptr;
    signupDialog = nullptr;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    hide();
    loginDialog = new login(this);
    loginDialog->exec();
}

void MainWindow::on_pushButton_signup_clicked()
{
    hide();
    signupDialog = new Signup(this);
    signupDialog->exec();
}

void MainWindow::showLoginDialog()
{
    loginDialog = new login(this);
    loginDialog->exec();
}

void MainWindow::returnToMainWindow()
{
    show();
}

