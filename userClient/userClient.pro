QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -L/opt/homebrew/Cellar/postgresql@14/14.6_1/lib/postgresql@14/ -lpq
#так сработало без добавления драйвера в папку   проектом
QT_DEBUG_PLUGINS = 1

SOURCES += \
    chatdialog.cpp \
    database/dbexporter.cpp \
    main.cpp \
    mainwindow.cpp \
    personclass.cpp \
    registrationform.cpp

HEADERS += \
    chatdialog.h \
    database/dbexporter.h \
    mainwindow.h \
    personclass.h \
    registrationform.h

FORMS += \
    chatdialog.ui \
    mainwindow.ui \
    registrationform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
