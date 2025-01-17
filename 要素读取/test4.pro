QT       += core gui xml svg

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

# Path to QGIS libraries
QGIS_LIBS = /usr/local/lib/qgis

# Link QGIS libraries
LIBS += -L$$QGIS_LIBS -lqgis_core -lqgis_gui

# Include QGIS headers
INCLUDEPATH += $$QGIS_LIBS

SOURCES += \
    changefill.cpp \
    feature.cpp \
    featureCheck.cpp \
    featureget.cpp \
    identifyresultdlg.cpp \
    main.cpp \
    mainwindow.cpp \
    qgsmaptoolselect.cpp \
    qgsmaptoolselectfeatures.cpp \
    show_att_of_feature.cpp

HEADERS += \
    changefill.h \
    feature.h \
    featureget.h \
    identifyresultdlg.h \
    mainwindow.h \
    qgsmaptoolselect.h \
    qgsmaptoolselectfeatures.h \
    show_att_of_feature.h

FORMS += \
    feature.ui \
    identifyresultdlg.ui \
    mainwindow.ui \
    show_att_of_feature.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
