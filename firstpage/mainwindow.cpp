#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/LENOVO/Desktop/_d2c400d3-68a4-4544-bea0-9303c338e05f.jpeg");
    int w = ui->pic->width();
    int h = ui->pic->height();
    ui->pic->setFixedHeight(h);
    ui->pic->setFixedWidth(w);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    //    login login;
    //    login.setModal(true);
    //    login.exec();
    hide();
    login = new class login(this);
    login->show();
}


void MainWindow::on_pushButton_signup_clicked()
{
    //    login login;
    //    login.setModal(true);
    //    login.exec();
    hide();
    Signup = new class Signup(this);
    Signup->show();
}

