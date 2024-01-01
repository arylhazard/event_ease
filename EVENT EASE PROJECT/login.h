#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include  <QMessageBox>
#include  <QRegularExpression>
#include <QDialog>
#include "signup.h"
#include "verify.h"
class MainWindow;

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr, MainWindow* mainWindow = nullptr, class verify* verify = nullptr);
    ~login();
public slots:
    void returnToMainWindow();


private slots:
    void on_pushButton_back_clicked();



    void on_pushButton_done_clicked();
   void showMessage(const QString &title, const QString &text, QMessageBox::Icon icon = QMessageBox::Information, QFlags<QMessageBox::StandardButton> buttons = QMessageBox::Ok);


   void on_pushButton_clicked();

   private:
    Ui::login *ui;
    MainWindow* mainWindow;
    verify* verify;
    QSqlDatabase DB_Connection;
};

#endif // LOGIN_H
