QT       += \
    core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainmenu.cpp \
    model.cpp \
    morsetranslator.cpp \
    morsetranslatortests.cpp \
    scenewidget.cpp \
    studyquestion.cpp

HEADERS += \
    mainmenu.h \
    model.h \
    morsetranslator.h \
    morsetranslatortests.h \
    scenewidget.h \
    studyquestion.h

FORMS += \
    mainmenu.ui

LIBS += -L$$PWD/box2d/build/bin -lbox2d

INCLUDEPATH += $$PWD/box2d/include
DEPENDPATH += $$PWD/box2d/include

#macx: PRE_TARGETDEPS += $$PWD/box2d/build/bin/libbox2d.a
PRE_TARGETDEPS += $$PWD/box2d/build/bin/libbox2d.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
