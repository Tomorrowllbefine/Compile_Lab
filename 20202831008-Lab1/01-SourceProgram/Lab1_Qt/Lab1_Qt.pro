QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analyse_1.cpp \
    widget.cpp\
    main.cpp \



HEADERS += \
    analyse_1.h \
    analyse_1_global.h \
    widget.h

FORMS += \
    widget.ui
#LIBS += "D:\JuniorYear_1.1\Compile\Lab1\20202831008李谋坤-Lab1\01-源程序文件夹\build-Lab1_Qt-Desktop_Qt_6_5_2_MinGW_64_bit-Debug\debug\analyse_1.dll"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

