#include "GuideMe.h"
#include "File.h"
#include "Graph.h"
#include <iostream>
#include <QtWidgets/QApplication>



int main(int argc, char *argv[])
{
    File file("TransportationMap.txt");
    file.readFile();
    Graph* graph = new Graph();
    file.convertToObjects(graph);
    file.convertWeights(graph);

    QApplication a(argc, argv);
    GuideMe w;
    w.setGraph(graph);
    w.show();
    
    return a.exec();
}
