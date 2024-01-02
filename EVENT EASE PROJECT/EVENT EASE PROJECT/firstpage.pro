QT       += core gui sql


INCLUDEPATH += /path/to/Qt/5.x.x/your/compiler/include


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17




# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    change.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    signup.cpp \
    verify.cpp


HEADERS += \
    change.h \
    login.h \
    mainwindow.h \
    signup.h \
    verify.h

FORMS += \
    change.ui \
    login.ui \
    mainwindow.ui \
    signup.ui \
    verify.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
