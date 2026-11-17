.SILENT:
CPP = g++
CPPFLAGS = -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++


all: Client Serveur


Client: main.o windowclient.o moc_windowclient.o
	$(CPP) -o Client main.o windowclient.o moc_windowclient.o -lpthread /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so


main.o: main.cpp windowclient.h
	$(CPP) $(CPPFLAGS) -c main.cpp -o main.o 

windowclient.o: windowclient.cpp windowclient.h 
	$(CPP) $(CPPFLAGS) -c windowclient.cpp -o windowclient.o 

moc_windowclient.o: moc_windowclient.cpp ui_windowclient.h 
	$(CPP) $(CPPFLAGS) -c moc_windowclient.cpp -o moc_windowclient.o 


Serveur: Serveur.cpp 
	$(CPP) $(CPPFLAGS) Serveur.cpp -o Serveur 


clean: 
	rm -f *.o Client Serveur