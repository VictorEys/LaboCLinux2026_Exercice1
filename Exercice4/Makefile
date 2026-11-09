#.SILENT:
CXX = g++
CXXFLAGS = -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ 

QT_LIBS = /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

# Options pour MySQL
MYSQL_FLAGS = -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

all: CLINUX_Exercice4 Traitement CreationBD


CLINUX_Exercice4: mainex4.o mainwindowex4.o moc_mainwindowex4.o
	$(CXX) -o CLINUX_Exercice4 mainex4.o mainwindowex4.o moc_mainwindowex4.o $(QT_LIBS)

mainex4.o : mainex4.cpp
	$(CXX) -c $(CXXFLAGS) -o mainex4.o mainex4.cpp

mainwindowex4.o: mainwindowex4.cpp
	$(CXX) -c $(CXXFLAGS) -o mainwindowex4.o mainwindowex4.cpp

moc_mainwindowex4.o: moc_mainwindowex4.cpp
	$(CXX) -c $(CXXFLAGS) -o moc_mainwindowex4.o moc_mainwindowex4.cpp

# --- TRAITEMENT ---
Traitement: maintraitement.o mainwindowtraitement.o moc_mainwindowtraitement.o
	$(CXX) -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl -o Traitement maintraitement.o mainwindowtraitement.o moc_mainwindowtraitement.o $(QT_LIBS)

maintraitement.o: maintraitement.cpp
	$(CXX) -c $(CXXFLAGS) -o maintraitement.o maintraitement.cpp

mainwindowtraitement.o: mainwindowtraitement.cpp
	$(CXX) -c $(CXXFLAGS) -I/usr/include/mysql -m64 -o mainwindowtraitement.o mainwindowmainwindowtraitement.cpp

moc_mainwindowtraitement.o: moc_mainwindowtraitement.cpp
	$(CXX) -c $(CXXFLAGS) -o moc_mainwindowtraitement.o moc_mainwindowtraitement.cpp

# --- CreationBD ---

CreationBD: CreationBD.cpp
	$(CXX) -o CreationBD CreationBD.cpp $(MYSQL_FLAGS)

# Nettoyage des fichiers objets
clean:
	rm -f *.o CLINUX_Exercice4 Traitement

