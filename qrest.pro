TEMPLATE = app
TARGET = qrest
ICON = resources/pix/qrest.icns
linux-* { 
    BINDEST = /usr/bin/
    SHARE = /usr/share/$$TARGET
    
    DOCDEST = /usr/share/doc/$$TARGET
    LANGDEST = $$SHARE/i18n
    MANDEST = /usr/share/man/man1/
    ICONDEST = $$SHARE/icons
    DOCSRC = doc/html
    LANGSRC = i18n/*.qm
    BINSRC = ./qrest
    MANSRC = doc/manpages/man1/qrest.1.gz
    ICONSRC = resources/pix/qresticon.png
}
QT += core \
    gui

HEADERS += src/helpers/localeHelper.h \
    src/gui/widgets/custom/progressPie.h \
    src/gui/widgets/qrestpreferencesdialog.h \
    src/settings/settings.h \
    src/gui/widgets/qrestmainwindow.h \
    src/gui/widgets/qresthelpviewer.h \
    src/gui/widgets/qrestaboutdialog.h \
    src/constants.h \
    src/process/delayCalculator.h \
    src/process/tapTempoCalculator.h \
    src/time/timeStamper.h \
    src/process/processor.h \
    src/dp/observable.h \
    src/dp/observer.h \
    src/model/delay.h \
    src/model/document.h

SOURCES += src/helpers/localeHelper.cpp \
    src/gui/widgets/custom/progressPie.cpp \
    src/gui/widgets/qrestpreferencesdialog.cpp \
    src/settings/settings.cpp \
    src/gui/widgets/qrestmainwindow.cpp \
    src/gui/widgets/qresthelpviewer.cpp \
    src/gui/widgets/qrestaboutdialog.cpp \
    src/constants.cpp \
    src/process/delayCalculator.cpp \
    src/process/tapTempoCalculator.cpp \
    src/time/timeStamper.cpp \
    src/process/processor.cpp \
    src/dp/observable.cpp \
    src/dp/observer.cpp \
    src/model/delay.cpp \
    src/model/document.cpp \
    src/main.cpp

#We only complie the WidgetSizeHelper on Mac
macx {
    HEADERS += src/helpers/widgetsizehelper.h
    SOURCES += src/helpers/widgetsizehelper.cpp
}

FORMS += src/gui/forms/qrestpreferencesdialog.ui \
    src/gui/forms/qrestmainwindow.ui \
    src/gui/forms/qresthelpviewer.ui \
    src/gui/forms/qrestaboutdialog.ui
RESOURCES += resources/pixmaps.qrc \
    resources/i18n.qrc \
    resources/online_doc.qrc
TRANSLATIONS = resources/i18n/qrest_fr.ts \
    resources/i18n/qrest_es.ts \
    resources/i18n/qrest_pt.ts
UI_DIR = src/gui/forms
MOC_DIR = tmp
OBJECTS_DIR = tmp
RCC_DIR = tmp
RC_FILE = resources/winicon.rc
linux-* { 
    userguides.path = $$DOCDEST
    userguides.files = $$DOCSRC
    INSTALLS += userguides
    languages.path = $$LANGDEST
    languages.files = $$LANGSRC
    INSTALLS += languages
    target.path = /usr/bin
    INSTALLS += target
    manpages.path = $$MANDEST
    manpages.files = $$MANSRC
    INSTALLS += manpages
    icons.path = $$ICONDEST
    icons.files = $$ICONSRC
    INSTALLS += icons
}
