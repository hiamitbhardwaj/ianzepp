TEMPLATE = app
TARGET = AMQMonitor
QT += core \
    gui \
    sql \
    xml \
    network \
    svg \
    opengl \
    webkit
HEADERS += AMQSubscription.h \
    AMQConnectionFrame.h \
    AMQConnection.h \
    AMQMonitor.h
SOURCES += AMQSubscription.cpp \
    AMQConnectionFrame.cpp \
    AMQConnection.cpp \
    main.cpp \
    AMQMonitor.cpp
FORMS += AMQMonitor.ui
RESOURCES += 
