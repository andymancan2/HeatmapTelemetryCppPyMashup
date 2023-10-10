TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../utilLib/ -lutilLib

INCLUDEPATH += $$PWD/../utilLib
DEPENDPATH += $$PWD/../utilLib

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../utilLib/libutilLib.a
