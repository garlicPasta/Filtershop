#####################################################################
# Automatically generated by qmake (3.0) Mo. Juni 23 03:02:05 2014
######################################################################

TEMPLATE = app
TARGET = filtershop
INCLUDEPATH += . src

# Input
HEADERS += \
    src/mainwindow.hpp \
    src/filter.hpp \
    src/picturematrix.h
SOURCES += src/main.cpp \  
    src/mainwindow.cpp \
    src/filter.cpp \
    src/picturematrix.cpp
CONFIG += testcase

LIBS += -lQt5Widgets -larmadillo
QT += printsupport widgets core gui
QMAKE_CXXFLAGS += -std=c++11

FORMS +=  src/mainwindow.ui
