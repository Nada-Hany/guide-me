#include "GuideMe.h"
#include "qmessagebox"
#include "Graph.h" 
#include <iterator> 
#include <QRandomGenerator>
#include <qcloseevent>
//#include <QGraphicsView>
#include<QMovie>

using namespace std;

void toLowerCase(string& str) {
    string result;
    for (char c : str)
        result += tolower(c);
    str = result;
}

//0-> main, 2->lowest_price_map, 1-> traverse, 3-> update_graph, 4-> find
GuideMe::GuideMe(QWidget* parent)
   : QMainWindow(parent)
{

  

    //same as on create func
    ui.setupUi(this);
    // Connect "openSecond" button to the slot function "on_openSecond_clicked"
    connect(ui.openSecond, &QPushButton::clicked, this, &GuideMe::on_openSecond_clicked);
    connect(ui.openThird, &QPushButton::clicked, this, &GuideMe::on_openThird_clicked);
    connect(ui.openThird_2, &QPushButton::clicked, this, &GuideMe::on_openThird_2_clicked);
    connect(ui.openUpdate, &QPushButton::clicked, this, &GuideMe::on_openUpdate_clicked);
    connect(ui.openTraverse, &QPushButton::clicked, this, &GuideMe::on_openTraverse_clicked);
    connect(ui.dfsButton, &QPushButton::clicked, this, &GuideMe::on_dfsButton_clicked);
    connect(ui.bfsButton, &QPushButton::clicked, this, &GuideMe::on_bfsButton_clicked);
    connect(ui.completeButton, &QPushButton::clicked, this, &GuideMe::on_completeButton_clicked);
    connect(ui.updateButton, &QPushButton::clicked, this, &GuideMe::on_updateButton_clicked);
    connect(ui.deleteButton, &QPushButton::clicked, this, &GuideMe::on_deleteButton_clicked);
    connect(ui.addButton, &QPushButton::clicked, this, &GuideMe::on_addButton_clicked);

    connect(ui.back2, &QPushButton::clicked, this, &GuideMe::on_back2_clicked);
    connect(ui.back3, &QPushButton::clicked, this, &GuideMe::on_back3_clicked);
    connect(ui.back4, &QPushButton::clicked, this, &GuideMe::on_back4_clicked);
    connect(ui.back5, &QPushButton::clicked, this, &GuideMe::on_back5_clicked);
    connect(ui.mainBack, &QPushButton::clicked, this, &GuideMe::on_mainBack_clicked);

    ui.stackedWidget->setCurrentIndex(0);
    QMovie* movie = new QMovie("C:/Users/HP/Desktop/guide-me/guide-me/img/airplan2.gif");
    ui.woman_label->setMovie(movie);
    movie->start();
}

GuideMe::~GuideMe()
{}

void GuideMe::setGraph(Graph* graph) {
    this->graph = graph;
    ui.sourceBox->clear();
    ui.destBox->clear();
    ui.sourceBox_2->clear();
    ui.destBox_2->clear();
   
    // Adding items to the drop boxes;
    for (auto& node : graph->allNodes) {
        ui.sourceBox->addItem(QString::fromStdString(node));
        ui.destBox->addItem(QString::fromStdString(node));
        ui.sourceBox_2->addItem(QString::fromStdString(node));
        ui.destBox_2->addItem(QString::fromStdString(node));
        ui.allNodes->addItem(QString::fromStdString(node));
    }
    ui.sourceBox->setCurrentIndex(-1);
    ui.destBox->setCurrentIndex(-1);
    ui.sourceBox_2->setCurrentIndex(-1);
    ui.destBox_2->setCurrentIndex(-1);
    ui.allNodes->setCurrentIndex(-1);

}

void GuideMe::setFile(File* f)
{
    this->file = f;
}


bool GuideMe::updateVariables(string& source, string& destination, float& budget, string& transportation, int action) {
    source = ui.sourceBox_2->currentText().toStdString();
    destination = ui.destBox_2->currentText().toStdString();
    budget = ui.budgetLine_2->text().toFloat();
    transportation = ui.transLine->text().toStdString();
    toLowerCase(source);
    toLowerCase(destination);
    toLowerCase(transportation);
    Node* src = graph->getNode(source);
    Node* dest = graph->getNode(destination);
    switch (action)
    {
    //add
    case 1:
        return src->addWeight(src, dest, budget, transportation);
    //delete
    case 2:
        return src->deleteWeight(src, dest,transportation);
    //modify 
    case 3:
        return src->changeWeightValue(src->weights[dest], budget, transportation);
    default:
        break;
    }
    return false;
}


void GuideMe::on_openSecond_clicked() {
    ui.stackedWidget->setCurrentIndex(4);
    QMovie* movie2 = new QMovie("C:/Users/HP/Desktop/guide-me/guide-me/img/road2.gif");
    ui.road_label->setMovie(movie2);
    movie2->start();
}

void GuideMe::on_openUpdate_clicked() {
    
    ui.stackedWidget->setCurrentIndex(3);
    QMovie* movie3 = new QMovie("C:/Users/HP/Desktop/guide-me/guide-me/img/road2.gif");
    ui.road_label_2->setMovie(movie3);
    movie3->start();
}
void GuideMe::on_updateButton_clicked() {
    string src, dest, transportation,result;
    float budget;
    bool check = updateVariables(src, dest, budget, transportation, 3);
    if (check)
        result = "UPDATED"; //nada (check updated or not )
    else
        result = "There's no such edge";
    ui.updateLabel->setText(QString::fromStdString(result));
}
void GuideMe::on_addButton_clicked() {
    string src, dest, transportation, result;
    float budget;
    bool check = updateVariables(src, dest, budget, transportation, 1);
    if (check)
        result = "ADDED"; //nada (check added or not )
    else
        result = "try again";
    ui.updateLabel->setText(QString::fromStdString(result));
}
void GuideMe::on_deleteButton_clicked() {
    string src, dest, transportation, result;
    float budget;
    bool check = updateVariables(src, dest, budget, transportation, 2);
    //nada (check deleted or not )
    if (check)
        result = "edge deleted";
    else
        result = "edge does't exist";
    ui.updateLabel->setText(QString::fromStdString(result));
}

void GuideMe::on_openTraverse_clicked() {
    ui.stackedWidget->setCurrentIndex(1);
    QMovie* movie4 = new QMovie("C:/Users/HP/Desktop/guide-me/guide-me/img/pharaoh.gif");
    ui.label_pharaoh->setMovie(movie4);
    movie4->start();
}


void GuideMe::on_openThird_clicked() {
    vector<string> pathS;
    set<string> visitS;

    if (ui.sourceBox->currentText().isEmpty() || ui.destBox->currentText().isEmpty() || ui.budgetLine->text().isEmpty()) {
        QMessageBox::information(this, "Error", "Please select a source, destination, and budget.");
        return;
    }

    string src = ui.sourceBox->currentText().toStdString();
    toLowerCase(src);
    string dest = ui.destBox->currentText().toStdString();
    toLowerCase(dest);
    float budget = ui.budgetLine->text().toInt();
    if (budget == 0) {
        ui.label->setText("Please enter a valid budget");
        return;
    }

    vector<pair<vector<string>, float>> paths = graph->lowestPath(src, dest, pathS, budget, visitS);

    if (paths.empty()) {
        ui.label->setText("No path found within budget");
    }
    else {
        string result = "Paths:\n";
        for (const auto& path : paths) {
            result += "Path: ";
            for (const string& node : path.first) {
                result += node + " ";
            }
            result += "\nBudget: " + to_string(path.second) + "\n";
        }
        ui.stackedWidget->setCurrentIndex(2);
        ui.mapPaths->setText(QString::fromStdString(result));

    }


}

void GuideMe::on_openThird_2_clicked() {

    if (ui.sourceBox->currentText().isEmpty() || ui.destBox->currentText().isEmpty() || ui.budgetLine->text().isEmpty()) {
        QMessageBox::information(this, "Error", "Please select a source, destination, and budget.");
        return;
    }

    string src = ui.sourceBox->currentText().toStdString();
    toLowerCase(src);
    string dest = ui.destBox->currentText().toStdString();
    toLowerCase(dest);
    float budget = ui.budgetLine->text().toInt();

    //nada (calling all paths function)
    if (budget == 0) {
        ui.label->setText("Please enter a valid budget");
        return;
    }
    else {
        ui.stackedWidget->setCurrentIndex(2);
    }

}


void GuideMe::on_dfsButton_clicked() {
    clearUp();
    string out = "";
    string source = ui.allNodes->currentText().toStdString();
    toLowerCase(source);
    graph->dfs(graph->getNode(source), out);
    ui.mapPathsAlgo->setText(QString::fromStdString(out)); //nada (DFS traversing map)
}

void GuideMe::on_bfsButton_clicked() {
    clearUp();
    string source = ui.allNodes->currentText().toStdString();
    toLowerCase(source);
    string out = graph->bfs(graph->getNode(source));
    ui.mapPathsAlgo->setText(QString::fromStdString(out)); //nada (BFS traversing map)
}

void GuideMe::on_completeButton_clicked() {
    bool isComplete = graph->checkCompleteness();
    if (isComplete)
        ui.mapPathsAlgo->setText("Graph is conmplete"); //nada (check complete)
    else
        ui.mapPathsAlgo->setText("Graph isn't conmplete");
}


void GuideMe::on_back2_clicked() {
    ui.stackedWidget->setCurrentIndex(0);
}
void GuideMe::on_back3_clicked() {
    ui.stackedWidget->setCurrentIndex(4);
}
void GuideMe::on_back4_clicked() {
    ui.stackedWidget->setCurrentIndex(0);
}
void GuideMe::on_back5_clicked() {
    ui.stackedWidget->setCurrentIndex(0);
}

void GuideMe::on_mainBack_clicked(){
    this->file->writeOnFile(graph);
    this->close();
}

void GuideMe::clearUp() {
    graph->clearPrevious();
    graph->clearVisted();
}

void GuideMe::closeEvent(QCloseEvent* event){

    file->writeOnFile(graph);
    event->accept();
}

//void GuideMe::drawGraphInStackedWidget(Graph* graph) {
//    // Get the current widget from the stacked widget
//    QWidget* currentWidget = ui.stackedWidget->currentWidget();
//    if (currentWidget != nullptr) {
//        // Set the scene to the graphics view of the current widget
//        QGraphicsView* graphicsView = currentWidget->findChild<QGraphicsView*>();
//        if (graphicsView != nullptr) {
//            QGraphicsScene* scene = graphicsView->scene();
//            if (scene == nullptr) {
//                scene = new QGraphicsScene(this);
//                graphicsView->setScene(scene);
//
//            }
//
//            int nodeSize = 20;
//
//            for (const auto& node : graph->getGraph()) {
//                QString nodeName = QString::fromStdString(node.first);
//                QPointF nodePos(QRandomGenerator::global()->bounded(graphicsView->width() - nodeSize), QRandomGenerator::global()->bounded(graphicsView->height() - nodeSize));
//                scene->addEllipse(nodePos.x() - nodeSize / 2, nodePos.y() - nodeSize / 2, nodeSize, nodeSize);
//                QGraphicsTextItem* label = scene->addText(nodeName);
//                label->setPos(nodePos.x() - nodeSize / 4, nodePos.y() - nodeSize / 4);
//
//                for (const auto& edge : node.second) {
//                    QString destNodeName = QString::fromStdString(edge.first);
//                    QPointF destNodePos;
//                    for (const auto& otherNode : graph->getGraph()) {
//                        if (otherNode.first == edge.first) {
//                            destNodePos = QPointF(QRandomGenerator::global()->bounded(graphicsView->width() - nodeSize), QRandomGenerator::global()->bounded(graphicsView->height() - nodeSize));
//                            break;
//                        }
//                    }
//                    scene->addLine(nodePos.x(), nodePos.y(), destNodePos.x(), destNodePos.y());
//                    QGraphicsTextItem* edgeLabel = scene->addText(QString::number(edge.second[0].first));
//                    edgeLabel->setPos((nodePos.x() + destNodePos.x()) / 2, (nodePos.y() + destNodePos.y()) / 2);
//
//                }
//            }
//        }
//    }
//}
