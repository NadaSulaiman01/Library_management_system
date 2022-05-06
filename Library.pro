QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    editbook.cpp \
    editmember.cpp \
    finalmember.cpp \
    homepage.cpp \
    insert.cpp \
    main.cpp \
    library.cpp \
    returnbook.cpp \
    viewbooklist.cpp \
    viewmemberlist.cpp

HEADERS += \
    addbook.h \
    editbook.h \
    editmember.h \
    finalmember.h \
    homepage.h \
    insert.h \
    library.h \
    returnbook.h \
    viewbooklist.h \
    viewmemberlist.h

FORMS += \
    addbook.ui \
    editbook.ui \
    editmember.ui \
    finalmember.ui \
    homepage.ui \
    insert.ui \
    library.ui \
    returnbook.ui \
    viewbooklist.ui \
    viewmemberlist.ui

RC_ICONS = Iconsmind-Outline-Library-2.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
