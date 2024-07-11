QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client_main.cpp \
    main.cpp \
    client.cpp \
    register.cpp

HEADERS += \
    client.h \
    client_main.h \
    register.h

FORMS += \
    client.ui \
    client_main.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc

DISTFILES += \
    C:/pictures/stock-market-modern-flat-concept-for-web-banner-design-male-trader-buys-and-sells-on-stock-exchange-analyzes-charts-and-statistics-invests-money-vector.jpg
