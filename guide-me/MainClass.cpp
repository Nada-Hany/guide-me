#include "MainClass.h"
#include "Graph.h"
MainClass::MainClass(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainClass::setGraph(Graph* graph2) {
    this->graph = graph2;
}

MainClass::~MainClass()
{}
