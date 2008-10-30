TEMPLATE = app
TARGET = zest
QT += core \
    gui
HEADERS += src/constants.h \
    src/process/delayCalculator.h \
    src/process/tapTempoCalculator.h \
    src/time/timeStamper.h \
    src/process/processor.h \
    src/dp/observable.h \
    src/dp/observer.h \
    src/model/delay.h \
    src/model/document.h \
    src/gui/widgets/zestmainwindow.h \
    src/gui/widgets/zestaboutdialog.h
SOURCES += src/constants.cpp \
    src/process/delayCalculator.cpp \
    src/process/tapTempoCalculator.cpp \
    src/time/timeStamper.cpp \
    src/process/processor.cpp \
    src/dp/observable.cpp \
    src/dp/observer.cpp \
    src/model/delay.cpp \
    src/model/document.cpp \
    src/main.cpp \
    src/gui/widgets/zestmainwindow.cpp \
    src/gui/widgets/zestaboutdialog.cpp
FORMS += src/gui/forms/zestmainwindow.ui \
    src/gui/forms/zestaboutdialog.ui
RESOURCES += resources/pixmaps.qrc
TRANSLATIONS = i18n/zest_fr.ts
