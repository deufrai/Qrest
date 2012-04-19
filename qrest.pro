TEMPLATE = app
TARGET = qrest
ICON = resources/pix/qrest.icns
QT += core \
    gui
HEADERS += src/midi/events/midieventfactory.h \
    src/midi/events/midicontrolchange.h \
    src/midi/events/midinoteon.h \
    src/midi/events/midicontinue.h \
    src/midi/events/midistop.h \
    src/midi/events/midistart.h \
    src/midi/events/midiclock.h \
    src/midi/events/mididoubleevent.h \
    src/midi/events/midiprogramchange.h \
    src/midi/events/midisimpleevent.h \
    src/midi/events/midievent.h \
    src/gui/widgets/settingsdialog.h \
    src/midi/midicontroller.h \
    src/midi/contrib/RtError.h \
    src/midi/contrib/RtMidi.h \
    src/midi/rtmidiengine.h \
    src/midi/midiengine.h \
    src/helpers/localeHelper.h \
    src/gui/widgets/custom/progressPie.h \
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
SOURCES += src/midi/events/midieventfactory.cpp \
    src/midi/events/midicontrolchange.cpp \
    src/midi/events/midinoteon.cpp \
    src/midi/events/midicontinue.cpp \
    src/midi/events/midistop.cpp \
    src/midi/events/midistart.cpp \
    src/midi/events/midiclock.cpp \
    src/midi/events/mididoubleevent.cpp \
    src/midi/events/midipogramchange.cpp \
    src/midi/events/midisimpleevent.cpp \
    src/midi/events/midievent.cpp \
    src/gui/widgets/settingsdialog.cpp \
    src/midi/midicontroller.cpp \
    src/midi/contrib/RtMidi.cpp \
    src/midi/rtmidiengine.cpp \
    src/midi/midiengine.cpp \
    src/helpers/localeHelper.cpp \
    src/gui/widgets/custom/progressPie.cpp \
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

# Platform specific compilations
macx { 
    # WidgetSizehelper is only used on Mac
    HEADERS += src/helpers/widgetsizehelper.h
    SOURCES += src/helpers/widgetsizehelper.cpp
    
    # RtMidi needs those
    DEFINES += __MACOSX_CORE__
    LIBS += -framework \
        CoreAudio \
        -framework \
        CoreMidi \
        -framework \
        CoreFoundation
}
linux-* { 
    # RtMidi needs those
    LIBS += -lasound \
        -lpthread
    DEFINES += __LINUX_ALSASEQ__
}
win32 { 
    # RtMidi needs those
    DEFINES += __WINDOWS_MM__
    LIBS += -lwinmm
}
FORMS += src/gui/forms/settingsdialog.ui \
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

# Linux install
linux-* { 
    BINSRC = ./qrest
    BINDEST = /usr/bin/
    SHARE = /usr/share/$$TARGET
    MANSRC = doc/manpages/man1/qrest.1.gz
    MANDEST = /usr/share/man/man1/
    ICONSRC = resources/pix/qresticon.png
    ICONDEST = $$SHARE/icons
    target.path = /usr/bin
    INSTALLS += target
    manpages.path = $$MANDEST
    manpages.files = $$MANSRC
    INSTALLS += manpages
    icons.path = $$ICONDEST
    icons.files = $$ICONSRC
    INSTALLS += icons
}
