#include "mainwindow.h"
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <QApplication>
#include <QMainWindow>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;

    // Create the processLabel with the GIF
    QMovie *movie = new QMovie(":/resource/img/ezgif.com-resize.gif");
    QLabel *processLabel = new QLabel(nullptr, Qt::SplashScreen);  // Use Qt::SplashScreen to avoid showing in the taskbar
    processLabel->resize(600, 500);
    processLabel->setMovie(movie);
    movie->start();
    processLabel->show();

    // Create the main window
    QMainWindow w;
    w.setWindowFlags(w.windowFlags() | Qt::FramelessWindowHint);  // Set the frameless window flag for the main window

    // Create a QTimer to close the processLabel after 2 seconds
    QTimer::singleShot(2000, processLabel, SLOT(close()));
    QTimer::singleShot(2000, &mw, SLOT(show()));
    return a.exec();
}
