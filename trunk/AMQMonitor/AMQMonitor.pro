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
HEADERS += AMQFrameProducer.h \
    AMQSubscriptionModel.h \
    AMQSubscription.h \
    AMQConnectionFrame.h \
    AMQConnection.h \
    AMQMonitor.h
SOURCES += AMQFrameProducer.cpp \
    AMQSubscriptionModel.cpp \
    AMQSubscription.cpp \
    AMQConnectionFrame.cpp \
    AMQConnection.cpp \
    main.cpp \
    AMQMonitor.cpp
FORMS += AMQMonitor.ui
RESOURCES += 
