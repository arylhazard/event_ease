#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

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

private:
    Ui::Signup *ui;
    MainWindow* mainWindow;
};

#endif // SIGNUP_H
