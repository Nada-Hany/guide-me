#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainClass.h"

class MainClass : public QMainWindow
{
    Q_OBJECT

public:
    MainClass(QWidget *parent = nullptr);
    ~MainClass();

private:
    Ui::MainClassClass ui;
};
