TEMPLATE = app
TARGET = activemq_monitor
QT += core \
    gui \
    xml \
    xmlpatterns \
    network \
    opengl \
    webkit
HEADERS += RemoteFrame.h \
    RemoteBroker.h \
    LocationContextDialog.h \
    DetailsPane.h \
    LocationItem.h \
    LocationPane.h \
    LocationProperties.h \
    ActiveMQMonitor.h
SOURCES += RemoteFrame.cpp \
    RemoteBroker.cpp \
    LocationContextDialog.cpp \
    DetailsPane.cpp \
    LocationItem.cpp \
    LocationPane.cpp \
    LocationProperties.cpp \
    ActiveMQMonitor.cpp \
    main.cpp
FORMS += LocationContextDialog.ui \
    DetailsPane.ui \
    LocationPane.ui \
    LocationProperties.ui \
    ActiveMQMonitor.ui
RESOURCES += 
