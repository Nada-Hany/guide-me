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

    void updateVariables(string& src, string& dest, float& budget, string& transportation);

    void on_openSecond_clicked();

    void on_openThird_clicked();

    void on_back2_clicked();

    void on_back3_clicked();

    void on_back4_clicked();

    void on_back5_clicked();

    void on_openThird_2_clicked();

    void on_openUpdate_clicked();

    void on_updateButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_openTraverse_clicked();

    void on_dfsButton_clicked();

    void on_bfsButton_clicked();

    void on_completeButton_clicked();

    void drawGraphInStackedWidget(Graph* graph);

    void displayGraph(const Graph& graph);

private:
    Ui::GuideMeClass ui;
    Graph* graph; // Add the graph member variable
public:
    void setGraph(Graph* graph);
};

