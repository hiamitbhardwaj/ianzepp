CONFIG += qt \
    debug
TEMPLATE = app
TARGET = activemq_monitor
QT += core \
    gui \
    xml \
    xmlpatterns \
    network \
    opengl \
    webkit
HEADERS += dialogs/AddConnectionWizard/TestPage.h \
    ConnectionSimpleTable.h \
    SubscriptionItem.h \
    ConnectionItem.h \
    LocationActionSubscribe.h \
    LocationActionDelete.h \
    LocationActionAddSubscription.h \
    LocationActionAddRemoteHost.h \
    RemoteFrame.h \
    RemoteBroker.h \
    LocationContextDialog.h \
    DetailsPane.h \
    LocationItem.h \
    LocationPane.h \
    LocationProperties.h \
    ActiveMQMonitor.h
SOURCES += dialogs/AddConnectionWizard/TestPage.cpp \
    ConnectionSimpleTable.cpp \
    SubscriptionItem.cpp \
    ConnectionItem.cpp \
    LocationActionSubscribe.cpp \
    LocationActionDelete.cpp \
    LocationActionAddSubscription.cpp \
    LocationActionAddRemoteHost.cpp \
    RemoteFrame.cpp \
    RemoteBroker.cpp \
    LocationContextDialog.cpp \
    DetailsPane.cpp \
    LocationItem.cpp \
    LocationPane.cpp \
    LocationProperties.cpp \
    ActiveMQMonitor.cpp \
    main.cpp
FORMS += dialogs/AddConnectionWizard/TestPage.ui \
    LocationContextDialog.ui \
    DetailsPane.ui \
    LocationPane.ui \
    LocationProperties.ui \
    ActiveMQMonitor.ui
RESOURCES += activemq_monitor.qrc
