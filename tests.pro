TEMPLATE = app
TARGET = qrest_unit_tests
QT = core \
    testlib
MOC_DIR = tmp
OBJECTS_DIR = tmp
HEADERS += tests/process/delayCalculatorTestCase.h \
    src/process/processor.h \
    src/process/delayCalculator.h \
    src/model/document.h \
    src/model/delay.h \
    src/dp/observable.h
SOURCES += tests/main.cpp \
    tests/process/delayCalculatorTestCase.cpp \
    src/process/processor.cpp \
    src/process/delayCalculator.cpp \
    src/model/document.cpp \
    src/model/delay.cpp \
    src/dp/observable.cpp
