#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainClass.h"
#include "Graph.h"

class MainClass : public QMainWindow
{
    Q_OBJECT
    Graph* graph;

public:
    MainClass(QWidget *parent = nullptr);
    void setGraph(Graph* graph);
    void closeEvent(QCloseEvent* event);
    ~MainClass();

private:
    Ui::MainClassClass ui;
};
