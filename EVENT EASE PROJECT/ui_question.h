/********************************************************************************
** Form generated from reading UI file 'question.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUESTION_H
#define UI_QUESTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_question
{
public:
    QFrame *frame;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    QFrame *frame_2;
    QPushButton *pushButton_done;
    QLabel *labelMessage;
    QLineEdit *home;
    QLineEdit *book;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *question)
    {
        if (question->objectName().isEmpty())
            question->setObjectName("question");
        question->resize(600, 500);
        frame = new QFrame(question);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 600, 500));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 50, 521, 411));
        label_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,100);\n"
"border-radius:20px;"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 600, 501));
        label->setMinimumSize(QSize(400, 0));
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/resource/img/_d2c400d3-68a4-4544-bea0-9303c338e05f.jpeg);"));
        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(190, 10, 201, 31));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"color: rgba(255,255,255,255);\n"
"\n"
"font: 700 20pt \"Myriad Pro Cond\";\n"
""));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(160, 80, 281, 351));
        frame_2->setStyleSheet(QString::fromUtf8("background:rgba(0,0,0,0);\n"
"border:none;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        pushButton_done = new QPushButton(frame_2);
        pushButton_done->setObjectName("pushButton_done");
        pushButton_done->setGeometry(QRect(200, 290, 61, 24));
        pushButton_done->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_done->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"border: none;\n"
"color: rgba(255,255,255,255);\n"
"background-color: rgb(5, 77, 101);\n"
"font : 700 12pt \"Myriad Pro Cond\";\n"
"}\n"
"\n"
"QPushButton:Hover\n"
"{\n"
"\n"
"	background-color: rgb(30, 104, 154);\n"
"}\n"
""));
        labelMessage = new QLabel(frame_2);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setGeometry(QRect(40, 269, 171, 21));
        labelMessage->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        home = new QLineEdit(frame_2);
        home->setObjectName("home");
        home->setGeometry(QRect(40, 130, 191, 24));
        home->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,230);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,210);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));
        book = new QLineEdit(frame_2);
        book->setObjectName("book");
        book->setGeometry(QRect(40, 230, 191, 24));
        book->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"border: none;\n"
"border-bottom: 2px solid rgba(225,228,225,255);\n"
"color: rgba(255,255,255,230);\n"
"padding-bottom: 7px;\n"
"font-color:rgba(255,255,255,210);\n"
"font: 700 11pt \"Myriad Pro Cond\";\n"
""));
        label_5 = new QLabel(frame_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(40, 90, 201, 31));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"color: rgba(255,255,255,255);\n"
"\n"
"font: 700 14pt \"Myriad Pro Cond\";\n"
""));
        label_6 = new QLabel(frame_2);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(40, 190, 201, 31));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);\n"
"color: rgba(255,255,255,255);\n"
"\n"
"font: 700 14pt \"Myriad Pro Cond\";\n"
""));
        label->raise();
        label_2->raise();
        frame_2->raise();
        label_4->raise();

        retranslateUi(question);

        QMetaObject::connectSlotsByName(question);
    } // setupUi

    void retranslateUi(QDialog *question)
    {
        question->setWindowTitle(QCoreApplication::translate("question", "Security Questions", nullptr));
        label_2->setText(QString());
        label->setText(QString());
        label_4->setText(QCoreApplication::translate("question", "SECURITY QUESTIONS", nullptr));
        pushButton_done->setText(QCoreApplication::translate("question", "SIGN UP", nullptr));
        labelMessage->setText(QString());
        home->setPlaceholderText(QCoreApplication::translate("question", "Answer", nullptr));
        book->setPlaceholderText(QCoreApplication::translate("question", "Answer", nullptr));
        label_5->setText(QCoreApplication::translate("question", "What is your hometown?", nullptr));
        label_6->setText(QCoreApplication::translate("question", "What is your favourite book?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class question: public Ui_question {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUESTION_H
