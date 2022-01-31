#-------------------------------------------------
#
# Project created by QtCreator 2013-02-20T12:36:23
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Travianator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    class/widget/button.cpp \
    class/travianwiki.cpp \
    class/time.cpp \
    class/widget/combobox.cpp \
    class/accountmanager.cpp \
    class/account.cpp \
    class/travianrequest.cpp \
    class/task.cpp \
    class/list/list.cpp \
    class/item/item.cpp \
    class/buildingmapitem.cpp \
    class/buildingmap.cpp \
    class/building.cpp \
    class/buildingsocket.cpp \
    class/item/itembuilding.cpp \
    class/item/itembuildinghorizontal.cpp \
    class/list/listitembuilding.cpp \
    class/village.cpp \
    class/dialog/dialogshows.cpp \
    class/item/itemconstruction.cpp \
    class/item/itembuildtask.cpp \
    class/list/listitembuildtask.cpp \
    class/list/listitemconstruction.cpp \
    class/widget/buttonlist.cpp \
    class/dialog/dialoggettime.cpp \
    class/dialog/dialoginfo.cpp \
    class/dialog/dialogbuildingtobuild.cpp \
    class/language.cpp \
    class/servertype.cpp \
    class/dialog/dialoglanguages.cpp

HEADERS  += mainwindow.h \
    class/widget/button.h \
    class/travianwiki.h \
    class/time.h \
    class/widget/combobox.h \
    class/accountmanager.h \
    class/Enums.h \
    class/account.h \
    class/travianrequest.h \
    class/task.h \
    class/list/list.h \
    class/item/item.h \
    class/buildingmapitem.h \
    class/buildingmap.h \
    class/building.h \
    class/buildingtobuildlist.h \
    class/buildingsocket.h \
    class/item/itembuilding.h \
    class/item/itembuildinghorizontal.h \
    class/list/listitembuilding.h \
    class/village.h \
    class/dialog/dialogshows.h \
    class/item/itemconstruction.h \
    class/item/itembuildtask.h \
    class/list/listitembuildtask.h \
    class/list/listitemconstruction.h \
    class/widget/buttonlist.h \
    class/dialog/dialoggettime.h \
    class/dialog/dialoginfo.h \
    class/dialog/dialogbuildingtobuild.h \
    class/language.h \
    class/servertype.h \
    class/dialog/dialoglanguages.h

FORMS    += mainwindow.ui \
    class/accountmanager.ui \
    class/item/itembuilding.ui \
    class/item/itembuildinghorizontal.ui \
    class/dialog/dialogshows.ui \
    class/item/itemconstruction.ui \
    class/item/itembuildtask.ui \
    class/dialog/dialoggettime.ui \
    class/dialog/dialoginfo.ui \
    class/dialog/dialoglanguages.ui

RESOURCES += \
    Res.qrc

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/layout/splash.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/version.xml \
    icon.rc

win32:RC_FILE=icon.rc
