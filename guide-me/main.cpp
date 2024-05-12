#include "GuideMe.h"
#include "File.h"
#include "Graph.h"
#include <iostream>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    Graph* graph = new Graph();
    File* file = new File("TransportationMap.txt");
    file->readFile();
    file->convertToObjects(graph);

    QApplication a(argc, argv);
    GuideMe w;
    //w.setWindowFlags(w.windowFlags() & ~Qt::WindowCloseButtonHint);
    w.setGraph(graph);
    w.setFile(file);
    w.resize(1920, 1080);
    w.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint); 
    w.setWindowState(Qt::WindowMaximized);
    w.showFullScreen();
    w.show();

    return a.exec();
}
