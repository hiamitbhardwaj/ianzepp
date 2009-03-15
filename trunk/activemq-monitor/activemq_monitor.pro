TEMPLATE = app
TARGET = activemq_monitor
QT += core \
    gui \
    xml \
    xmlpatterns \
    network \
    opengl \
    webkit
HEADERS += DetailsPane.h \
    LocationPane.h \
    LocationProperties.h \
    ActiveMQMonitor.h
SOURCES += DetailsPane.cpp \
    LocationPane.cpp \
    LocationProperties.cpp \
    main.cpp \
    ActiveMQMonitor.cpp
FORMS += DetailsPane.ui \
    LocationPane.ui \
    LocationProperties.ui \
    ActiveMQMonitor.ui
RESOURCES += 
