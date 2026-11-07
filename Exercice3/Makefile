# Compilateur et options partagées pour Qt
CXX = g++
QT_FLAGS = -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_QML_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I../UNIX_Exercice1 -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I/usr/lib64/qt5/mkspecs/linux-g++

# Options pour MySQL
MYSQL_FLAGS = -I/usr/include/mysql -m64 -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -lrt -lssl -lcrypto -ldl

# Cible principale (exécutée par un simple 'make')
all: CLINUX_Exercice3 CreationBD Lecture

# --- Compilation de l'application graphique CLINUX_Exercice3 ---
CLINUX_Exercice3: main.o mainwindowex3.o moc_mainwindowex3.o
	g++ -o CLINUX_Exercice3 main.o mainwindowex3.o moc_mainwindowex3.o /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread

main.o: main.cpp
	$(CXX) -c main.cpp -o main.o $(QT_FLAGS)

mainwindowex3.o: mainwindowex3.cpp
	$(CXX) -c mainwindowex3.cpp -o mainwindowex3.o $(QT_FLAGS)

moc_mainwindowex3.o: moc_mainwindowex3.cpp
	$(CXX) -c moc_mainwindowex3.cpp -o moc_mainwindowex3.o $(QT_FLAGS)


# --- Compilation de CreationBD ---
CreationBD: CreationBD.cpp
	g++ -o CreationBD CreationBD.cpp $(MYSQL_FLAGS)


# --- Compilation de Lecture ---
Lecture: Lecture.cpp
	g++ -o Lecture Lecture.cpp $(MYSQL_FLAGS)


# --- Nettoyage des fichiers générés ---
clean:
	rm -f *.o CLINUX_Exercice3 CreationBD Lecture