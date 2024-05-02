#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainClass.h"
#include "graph.h"
#include <QGraphicsView> // really?
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class MainClass : public QMainWindow
{
    Q_OBJECT

public:
    MainClass(QWidget* parent = nullptr);
    ~MainClass();

    void on_openSecond_clicked();

    void on_openThird_clicked();

    void on_back2_clicked();

    void on_back3_clicked();

    void drawGraphInStackedWidget(const Graph& graph);

    void displayGraph(const Graph& graph);

private:
    Ui::MainClassClass ui;
    Graph graph; // Add the graph member variable
public:
    void setGraph(Graph& graph);
};

