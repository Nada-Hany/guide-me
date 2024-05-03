#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GuideMe.h"
#include "graph.h"
#include <QGraphicsView> // really?
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class GuideMe : public QMainWindow
{
    Q_OBJECT

public:
    GuideMe(QWidget* parent = nullptr);
    ~GuideMe();

    void on_openSecond_clicked();

    void on_openThird_clicked();

    void on_back2_clicked();

    void on_back3_clicked();

    void drawGraphInStackedWidget(Graph* graph);

    void displayGraph(const Graph& graph);

private:
    Ui::GuideMeClass ui;
    Graph* graph; // Add the graph member variable
public:
    void setGraph(Graph* graph);
};

