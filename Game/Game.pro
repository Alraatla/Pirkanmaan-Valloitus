TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    mapwindow.cc \
    gamemenu.cpp \
    gameeventhandler.cpp \
    objectmanager.cpp \
    playerobject.cpp \
    mountain.cpp \
    tyokkari.cpp \
    mine.cpp \
    gamescene.cpp \
    mapitem.cpp \
    farmer.cpp \
    miner.cpp \
    endscreen.cpp \
    water.cpp

HEADERS += \
    mapwindow.hh \
    gamemenu.h \
    gameeventhandler.h \
    objectmanager.h \
    playerobject.h \
    mountain.h \
    teamresourcemaps.h \
    tyokkari.h \
    mine.h \
    gamescene.h \
    mapitem.h \
    farmer.h \
    miner.h \
    endscreen.h \
    water.h

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    gamemenu.ui \
    endscreen.ui

DISTFILES += \
    EndDocument

RESOURCES += \
    gameresources.qrc
