TEMPLATE = app
TARGET = activemq_monitor
QT += core \
    gui \
    xml \
    xmlpatterns \
    network \
    opengl \
    webkit
HEADERS += LocationCreateDialog.h \
    LocationItem.h \
    DetailsPane.h \
    LocationPane.h \
    LocationProperties.h \
    ActiveMQMonitor.h
SOURCES += LocationCreateDialog.cpp \
    LocationItem.cpp \
    DetailsPane.cpp \
    LocationPane.cpp \
    LocationProperties.cpp \
    main.cpp \
    ActiveMQMonitor.cpp
FORMS += LocationCreateDialog.ui \
    DetailsPane.ui \
    LocationPane.ui \
    LocationProperties.ui \
    ActiveMQMonitor.ui
RESOURCES += 
