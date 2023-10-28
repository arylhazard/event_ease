#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

class MainWindow;

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr, MainWindow* mainWindow = nullptr);
    ~login();
public slots:
    void returnToMainWindow();


private slots:
    void on_pushButton_back_clicked();

private:
    Ui::login *ui;
    MainWindow* mainWindow;
};

#endif // LOGIN_H
