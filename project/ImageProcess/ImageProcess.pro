#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T16:59:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageProcess
TEMPLATE = app

# INCLUDEPATH += C:\opencv\include

# LIBS += -LC:\opencv\lib -lopencv_calib3d249 -lopencv_contrib249 -lopencv_core249 -lopencv_features2d249 -lopencv_flann249 -lopencv_gpu249 -lopencv_highgui249 -lopencv_imgproc249 -lopencv_legacy249 -lopencv_ml249 -lopencv_nonfree249 -lopencv_objdetect249 -lopencv_ocl249 -lopencv_photo249 -lopencv_stitching249 -lopencv_superres249 -lopencv_ts249 -lopencv_video249 -lopencv_videostab249

INCLUDEPATH += $$(OPENCV_HOME)/include/
LIBS += $$(OPENCV_HOME)/x64/vc14/lib/opencv_world330d.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    any_angle.cpp

HEADERS  += mainwindow.h \
    any_angle.h

FORMS    += mainwindow.ui \
    any_angle.ui
