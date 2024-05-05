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
    file->convertWeights(graph);

    QApplication a(argc, argv);
    GuideMe w;
    w.setGraph(graph);
    w.setFile(file);
    w.show();

    return a.exec();
}
