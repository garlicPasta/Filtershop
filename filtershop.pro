#####################################################################
# Automatically generated by qmake (3.0) Mo. Juni 23 03:02:05 2014
######################################################################

TEMPLATE = app
TARGET = filtershop
INCLUDEPATH += . src

# Input
HEADERS += src/Filter.hpp src/ImageViewer.hpp src/MatHelper.hpp \
    src/Picturematrix.h
SOURCES += src/Filter.cpp src/ImageViewer.cpp src/main.cpp src/MatHelper.cpp \  
    src/Picturematrix.cpp
CONFIG += testcase

LIBS += -lQt5Widgets -larmadillo
QT += printsupport widgets
QMAKE_CXXFLAGS += -std=c++11
