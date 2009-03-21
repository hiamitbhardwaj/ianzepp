TEMPLATE = app
TARGET = AMQMonitor
QT += core \
    gui \
    xml \
    network
HEADERS += AMQSubscription.h \
    AMQConnectionFrame.h \
    AMQConnection.h \
    AMQMonitor.h
SOURCES += AMQSubscription.cpp \
    AMQConnectionFrame.cpp \
    AMQConnection.cpp \
    AMQMonitor.cpp \
    main.cpp
FORMS += AMQMonitor.ui
RESOURCES += 
