#include "GuideMe.h"
#include "qmessagebox"
#include "Graph.h" 
#include <iterator> 
#include <QRandomGenerator>
//#include <QGraphicsView>

using namespace std;

void toLowerCase(string& str) {
    string result;
    for (char c : str)
        result += tolower(c);
    str = result;
}

//0-> main, 2->second, 1-> third
GuideMe::GuideMe(QWidget* parent)
   : QMainWindow(parent)
{
    //same as on create func
    ui.setupUi(this);
    // Connect "openSecond" button to the slot function "on_openSecond_clicked"
    connect(ui.openSecond, &QPushButton::clicked, this, &GuideMe::on_openSecond_clicked);
    connect(ui.openThird, &QPushButton::clicked, this, &GuideMe::on_openThird_clicked);
    connect(ui.back2, &QPushButton::clicked, this, &GuideMe::on_back2_clicked);
    connect(ui.back3, &QPushButton::clicked, this, &GuideMe::on_back3_clicked);
    ui.stackedWidget->setCurrentIndex(0);

}

GuideMe::~GuideMe()
{}

void GuideMe::setGraph(Graph* graph) {
    this->graph = graph;
    ui.sourceBox->clear();
    ui.destBox->clear();
   
    // Adding items to the drop boxes;
    for (auto& node : graph->allNodes) {
        ui.sourceBox->addItem(QString::fromStdString(node));
        ui.destBox->addItem(QString::fromStdString(node));
    }
}


void GuideMe::on_openSecond_clicked() {
    ui.stackedWidget->setCurrentIndex(2);
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
        ui.label->setText("please enter a valid budget");
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
        ui.stackedWidget->setCurrentIndex(1);
        ui.mapPaths->setText(QString::fromStdString(result));
    }


}

void GuideMe::on_back2_clicked() {
    ui.stackedWidget->setCurrentIndex(0);

}
void GuideMe::on_back3_clicked() {
    ui.stackedWidget->setCurrentIndex(2);
}

void GuideMe::drawGraphInStackedWidget(Graph* graph) {
    // Get the current widget from the stacked widget
    QWidget* currentWidget = ui.stackedWidget->currentWidget();
    if (currentWidget != nullptr) {
        // Set the scene to the graphics view of the current widget
        QGraphicsView* graphicsView = currentWidget->findChild<QGraphicsView*>();
        if (graphicsView != nullptr) {
            QGraphicsScene* scene = graphicsView->scene();
            if (scene == nullptr) {
                scene = new QGraphicsScene(this);
                graphicsView->setScene(scene);

            }

            int nodeSize = 20;

            for (const auto& node : graph->getGraph()) {
                QString nodeName = QString::fromStdString(node.first);
                QPointF nodePos(QRandomGenerator::global()->bounded(graphicsView->width() - nodeSize), QRandomGenerator::global()->bounded(graphicsView->height() - nodeSize));
                scene->addEllipse(nodePos.x() - nodeSize / 2, nodePos.y() - nodeSize / 2, nodeSize, nodeSize);
                QGraphicsTextItem* label = scene->addText(nodeName);
                label->setPos(nodePos.x() - nodeSize / 4, nodePos.y() - nodeSize / 4);

                for (const auto& edge : node.second) {
                    QString destNodeName = QString::fromStdString(edge.first);
                    QPointF destNodePos;
                    for (const auto& otherNode : graph->getGraph()) {
                        if (otherNode.first == edge.first) {
                            destNodePos = QPointF(QRandomGenerator::global()->bounded(graphicsView->width() - nodeSize), QRandomGenerator::global()->bounded(graphicsView->height() - nodeSize));
                            break;
                        }
                    }
                    scene->addLine(nodePos.x(), nodePos.y(), destNodePos.x(), destNodePos.y());
                    QGraphicsTextItem* edgeLabel = scene->addText(QString::number(edge.second[0].first));
                    edgeLabel->setPos((nodePos.x() + destNodePos.x()) / 2, (nodePos.y() + destNodePos.y()) / 2);

                }
            }
        }
    }
}