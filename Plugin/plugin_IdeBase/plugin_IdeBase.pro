QT += widgets

TEMPLATE = lib
DEFINES += PLUGIN_IDEBASE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



DESTDIR = $$OUT_PWD/../../release/plg/Plugin_IdeBase
TARGET = Plugin_IdeBase



SOURCES += \
    Dialog/Dialog_Index.cpp \
    Plugin_IdeBase.cpp

HEADERS += \
    Dialog/Dialog_Index.h \
    plugin_IdeBase_global.h \
    Plugin_IdeBase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Dialog/Dialog_Index.ui


RESOURCES += \
    res.qrc
