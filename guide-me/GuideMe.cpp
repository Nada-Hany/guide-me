#include "GuideMe.h"
#include "qmessagebox"
#include "Graph.h" 
#include <iterator> 
#include <QRandomGenerator>
#include <qcloseevent>
#include <QMovie>
#include <sstream>
#include <iomanip>
#include <QFontDatabase>

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
    connect(ui.undoButton, &QPushButton::clicked, this, &GuideMe::on_undoButton_clicked);
    connect(ui.back2, &QPushButton::clicked, this, &GuideMe::on_back2_clicked);
    connect(ui.back3, &QPushButton::clicked, this, &GuideMe::on_back3_clicked);
    connect(ui.back4, &QPushButton::clicked, this, &GuideMe::on_back4_clicked);
    connect(ui.back5, &QPushButton::clicked, this, &GuideMe::on_back5_clicked);
    connect(ui.mainBack, &QPushButton::clicked, this, &GuideMe::on_mainBack_clicked);
    //font case
    QFontDatabase fontDb;
    int fontId = fontDb.addApplicationFont("img/GeorgiaPro-CondBold.ttf");
    QFont font;
    font.setFamily(fontDb.applicationFontFamilies(fontId).at(0));
    ui.label_10->setFont(font);

    ui.stackedWidget->setCurrentIndex(0);
    QMovie* movie = new QMovie("img/airplan2.gif");
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

void GuideMe::on_openSecond_clicked() {
    ui.budgetLine->clear();
    ui.sourceBox->setCurrentIndex(-1);
    ui.destBox->setCurrentIndex(-1);
    ui.stackedWidget->setCurrentIndex(4);
    QMovie* movie2 = new QMovie("img/road2.gif");
    ui.road_label->setMovie(movie2);
    movie2->start();
}

bool GuideMe::updateVariables(string& source, string& destination, float& budget, string& transportation, int action) {
    source = ui.sourceBox_2->currentText().toStdString();
    destination = ui.destBox_2->currentText().toStdString();
    budget = ui.budgetLine_2->text().toFloat();
    transportation = ui.transLine->text().toStdString();
    Node* src = graph->getNode(source);
    Node* dest = graph->getNode(destination);
    if (!(transportation.empty() && budget == 0))
    {
        switch (action)
        {
            //add
        case 1:
            return src->addWeight(src, dest, budget, transportation);
            //delete
        case 2:
            return src->deleteWeight(src, dest, transportation, budget);
            //modify 
        case 3:
            return src->changeWeightValue(src->weights[dest], budget, transportation);
        default:
            break;
        }
    }
    delete src, dest;
    return false;
}

void GuideMe::on_openUpdate_clicked() {
    ui.transLine->clear();
    ui.budgetLine_2->clear();
    ui.sourceBox_2->setCurrentIndex(-1);
    ui.destBox_2->setCurrentIndex(-1);
    ui.stackedWidget->setCurrentIndex(3);
    QMovie* movie3 = new QMovie("img/road2.gif");
    ui.road_label_2->setMovie(movie3);
    movie3->start();
}
void GuideMe::on_updateButton_clicked() {
    string src, dest, transportation,result;
    float budget;
    bool check = updateVariables(src, dest, budget, transportation, 3);
    Node* srcNode = graph->getNode(src);
    Node* destNode = graph->getNode(dest);
    if (check)
    {
        actionMade = 3;
        float weight = graph->getCurrentWeight(srcNode->weights[destNode], transportation);
        previousWeight.push(weight);
        actions.push(make_pair(actionMade, make_pair(make_pair(srcNode, destNode), make_pair(budget, transportation))));
        result = "UPDATED"; 
    }
    else
        result = "There's no such edge";
    ui.updateLabel->setText(QString::fromStdString(result));
}
void GuideMe::on_addButton_clicked() {
    string src, dest, transportation, result;
    float budget;
    bool check = updateVariables(src, dest, budget, transportation, 1);
    Node* srcNode = graph->getNode(src);
    Node* destNode = graph->getNode(dest);
    if (check)
    {
        actionMade = 1;
        actions.push(make_pair(actionMade, make_pair(make_pair(srcNode, destNode), make_pair(budget, transportation))));
        result = "ADDED";
    }
    else
        result = "try again";
    ui.updateLabel->setText(QString::fromStdString(result));
}
void GuideMe::on_deleteButton_clicked() {
    string src, dest, transportation, result;
    float budget;
    bool check = updateVariables(src, dest, budget, transportation, 2);
   
    Node* srcNode = graph->getNode(src);
    Node* destNode = graph->getNode(dest);
    
    if (check)
    {
        actionMade = 2;
        actions.push(make_pair(actionMade, make_pair(make_pair(srcNode, destNode), make_pair(budget, transportation))));
        result = "edge deleted";
    }
    else
        result = "edge doesn't exist";
    ui.updateLabel->setText(QString::fromStdString(result));
}
void GuideMe::on_undoButton_clicked() {
    // [1->ADD -> delete][2->DELETE -> add][3->MODIFY]
    if (actions.size() != 0)
    {
        if (actions.top().first == 1) {
            actions.top().second.first.first->deleteWeight(actions.top().second.first.first, actions.top().second.first.second, actions.top().second.second.second, actions.top().second.second.first);
            ui.updateLabel->setText("edge deleted");
        }
        else if (actions.top().first == 2) {
            actions.top().second.first.first->addWeight(actions.top().second.first.first, actions.top().second.first.second, actions.top().second.second.first, actions.top().second.second.second);
            ui.updateLabel->setText("edge added");
        }
        else if (actions.top().first == 3) {
            actions.top().second.first.first->changeWeightValue(actions.top().second.first.first->weights[actions.top().second.first.second], previousWeight.top(), actions.top().second.second.second);
            previousWeight.pop();
            ui.updateLabel->setText("edge modified");
        }
        actions.pop();
    }
    else
        ui.updateLabel->setText("no actions were made");

}
void GuideMe::on_openTraverse_clicked() {
    ui.mapPathsAlgo->setText(QString::fromStdString(""));
    drawGraph(*graph, ui.graphicsView_2, false);
    ui.stackedWidget->setCurrentIndex(1);
}

void GuideMe::on_openThird_clicked() {
    vector<string> pathS;
    set<string> visitS;

    if (ui.sourceBox->currentText().isEmpty() || ui.destBox->currentText().isEmpty() || ui.budgetLine->text().isEmpty()) {
        QMessageBox::information(this, "Error", "Please select a source, destination, and budget.");
        return;
    }

    string src = ui.sourceBox->currentText().toStdString();
    string dest = ui.destBox->currentText().toStdString();
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
            stringstream ss;
            ss << fixed << setprecision(2) << path.second;
            result += "\nBudget: " + ss.str() + "\n";
        }
        ui.stackedWidget->setCurrentIndex(2);
        ui.mapPaths->setText(QString::fromStdString(result));
        drawGraph(*graph, ui.graphicsView, true);
    }
}

void GuideMe::on_openThird_2_clicked() {

    if (ui.sourceBox->currentText().isEmpty() || ui.destBox->currentText().isEmpty() || ui.budgetLine->text().isEmpty()) {
        QMessageBox::information(this, "Error", "Please select a source, destination, and budget.");
        return;
    }
    clearUp();
    string src = ui.sourceBox->currentText().toStdString();
    Node* srcNode = graph->getNode(src);
    string dest = ui.destBox->currentText().toStdString();
    Node* destNode = graph->getNode(dest);
    float budget = ui.budgetLine->text().toInt();
    if (budget == 0) {
        ui.label->setText("Please enter a valid budget");
        return;
    }
    if(srcNode!=destNode)
    {
        vector<pair<float, string>> paths = graph->getAllPaths(srcNode, destNode, budget);
        if (paths.empty()) {
            ui.label->setText("No path found within budget");
        }
        else {
            string result = "Paths:\n";
            for (auto path : paths)
            {
                stringstream ss;
                ss << fixed << setprecision(2) << path.first;
                result = result + path.second + ss.str() + "LE\n";
            }
            ui.stackedWidget->setCurrentIndex(2);
            ui.mapPaths->setText(QString::fromStdString(result));
            drawGraph(*graph, ui.graphicsView, true);
        }
    }
    else {
        QMessageBox::information(this, "Error", "Please select a different source/destination.");
        drawGraph(*graph, ui.graphicsView, false);
    }
}

void GuideMe::on_dfsButton_clicked() {
    clearUp();
    string source = ui.allNodes->currentText().toStdString();
    if(!source.empty())
    {
        string out = "";
        graph->dfs(graph->getNode(source), out);
        ui.mapPathsAlgo->setText(QString::fromStdString(out)); 
        drawGraph(*graph, ui.graphicsView_2, true);
    }else
    {
        ui.mapPathsAlgo->setText(QString::fromStdString("choose a city"));
        drawGraph(*graph, ui.graphicsView_2, false);
    }

}

void GuideMe::on_bfsButton_clicked() {
    clearUp();
   
    string source = ui.allNodes->currentText().toStdString(), out ="choose city";
 
    if (!source.empty())
    {
        out = graph->bfs(graph->getNode(source));
        ui.mapPathsAlgo->setText(QString::fromStdString(out));
        drawGraph(*graph, ui.graphicsView_2, true);
    }
    else
    {
        ui.mapPathsAlgo->setText(QString::fromStdString("choose a city"));
        drawGraph(*graph, ui.graphicsView_2, false);
    }
}

void GuideMe::on_completeButton_clicked() {
    clearUp();
    bool isComplete = graph->checkCompleteness();
    if (isComplete)
        ui.mapPathsAlgo->setText("Graph is complete"); 
    else
        ui.mapPathsAlgo->setText("Graph isn't complete");
    drawGraph(*graph, ui.graphicsView_2, true);
}

void GuideMe::drawGraph(const Graph& graph, QGraphicsView* view, bool draw) {
    QGraphicsScene* scene = new QGraphicsScene(this);
    //ui.graphicsView->setScene(scene);
    view->setScene(scene);

    unordered_map<string, QPointF> nodePositions;

    // Determine the position of each node
    int numNodes = graph.allNodes.size();
    int angleStep = 360 / numNodes;
    int radius = 200;
    int centerX = ui.graphicsView->width() / 2;
    int centerY = ui.graphicsView->height() / 2;

    int angle = 0;
    if (draw)
    {
        for (const auto& node : graph.allNodes) {
            qreal x = centerX + radius * qCos(qDegreesToRadians(angle));
            qreal y = centerY + radius * qSin(qDegreesToRadians(angle));
            QPointF position(x, y);
            nodePositions[node] = position;
            angle += angleStep;
        }

        // Draw nodes
        for (const auto& pair : nodePositions) {
            qreal x = pair.second.x();
            qreal y = pair.second.y();
            QGraphicsEllipseItem* nodeItem = scene->addEllipse(x - 10, y - 10, 60, 60, QPen(Qt::white), QBrush(Qt::black));
            QGraphicsTextItem* textItem = scene->addText(QString::fromStdString(pair.first));
            textItem->setPos(x - 10, y - 25); // or 20? -> 
            //change text style
            QFont font = textItem->font();
            font.setPointSize(12);
            font.setWeight(QFont::Bold);
            textItem->setFont(font);
            textItem->setDefaultTextColor(Qt::white);
            // font.setFamily("Arial");
             //text position
            QRectF textRect = textItem->boundingRect();
            qreal textX = x - textRect.width() / 2.5;
            qreal textY = y + 45;
            textItem->setPos(textX, textY);
        }

        // Draw edges
        for (const auto& pair : graph.adj) {
            Node* sourceNode = pair.first;
            const vector<Node*>& destNodes = pair.second;
            QPointF sourcePos = nodePositions[sourceNode->value];
            for (const auto& destNode : destNodes) {
                QPointF destPos = nodePositions[destNode->value];
                QGraphicsLineItem* edgeItem = scene->addLine(sourcePos.x(), sourcePos.y(), destPos.x(), destPos.y(), QPen(Qt::white));

            }
        }
    }
    else
        scene->clear();
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
    delete file, graph;
    this->close();
}

void GuideMe::clearUp() {
    graph->clearPrevious();
    graph->clearVisted();
    graph->paths.clear();
}

void GuideMe::closeEvent(QCloseEvent* event){

    file->writeOnFile(graph);
    delete file, graph;
    event->accept();
}
