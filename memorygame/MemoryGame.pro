QT += quick

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cell.cpp \
        cellmodel.cpp \
        main.cpp

RESOURCES += \
            resources.qrc

DISTFILES += \
    qml/main.qml
    qml/Cell.qml

HEADERS += \
        cell.hpp \
        cellmodel.hpp

