#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GuideMe.h"
#include <QGraphicsView> // really?
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

#include "graph.h"
#include "File.h"
#include <stack>

class GuideMe : public QMainWindow
{
    Q_OBJECT
    Ui::GuideMeClass ui;
    Graph* graph; // Add the graph member variable
    File* file;
    int actionMade = -1;
    //first -> action , second.first -> nodes[.first>start, .second>target], second.second ->[.first>weight, .second>way]
    stack<pair<int, pair<pair<Node*, Node*>, pair<float, string>>>> actions;
    stack<float> previousWeight;

public:
    GuideMe(QWidget* parent = nullptr);
    ~GuideMe();

    bool updateVariables(string& src, string& dest, float& budget, string& transportation, int);

    void on_openSecond_clicked();

    void on_openThird_clicked();

    void on_back2_clicked();

    void on_back3_clicked();

    void on_back4_clicked();

    void on_back5_clicked();

    void on_mainBack_clicked();

    void clearUp();

    void closeEvent(QCloseEvent* event) override;

    void on_openThird_2_clicked();

    void on_openUpdate_clicked();

    void on_updateButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_undoButton_clicked();

    void on_openTraverse_clicked();

    void on_dfsButton_clicked();

    void on_bfsButton_clicked();

    void on_completeButton_clicked();

    void drawGraphInStackedWidget(Graph* graph);

    void setGraph(Graph* graph);
    void setFile(File*);
};

