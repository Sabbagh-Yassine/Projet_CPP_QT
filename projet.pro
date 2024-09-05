QT       += sql core gui printsupport charts network



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += path/to/smtpclient/include

QMAKE_EXTRA_TARGETS += addpowershellpath
addpowershellpath.commands = set PATH=%PATH%;C:/Windows/System32/WindowsPowerShell/v1.0


SOURCES += \
    candidat.cpp \
    connection.cpp \
    gestionnairecandidats.cpp \
    gestionnaireoffres.cpp \
    main.cpp \
    mainwindow.cpp \
    offreemploi.cpp \
    statistiquesdialog.cpp \
    statsdialog.cpp

HEADERS += \
    candidat.h \
    connection.h \
    gestionnairecandidats.h \
    gestionnaireoffres.h \
    mainwindow.h \
    offreemploi.h \
    statistiquesdialog.h \
    statsdialog.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


