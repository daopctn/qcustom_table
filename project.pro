QT += core gui widgets

TARGET = CustomTableApp
TEMPLATE = app

CONFIG += c++11

# Include paths
INCLUDEPATH += src

# Source files
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/actionbuttonswidget.cpp \
    src/actionbuttonsdelegate.cpp \
    src/infodialog.cpp

# Header files
HEADERS += \
    src/mainwindow.h \
    src/actionbuttonswidget.h \
    src/actionbuttonsdelegate.h \
    src/infodialog.h

# Resources
RESOURCES += \
    resources/resources.qrc

# Build directory
DESTDIR = build
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
