#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "detectimage.h"
#include "segmentimage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sushiClicked = false;
    segmentClicked = false;


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    if(sushiClicked){
        DetectImage detected(ui->imageNums->currentIndex() % 6);
        detected.run();
    }

}

void MainWindow::on_runSegmentButton_clicked()
{
    if(segmentClicked){
        SegmentImage segment(ui->imageNums->currentIndex() % 5);
        segment.run();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->imageNums->clear();
    for(int i = 1; i <= 4; ++i)
        ui->imageNums->addItem(QString::number(i));
    segmentClicked = true;
}


void MainWindow::on_sushiButton_clicked()
{
    ui->imageNums->clear();
    for(int i = 1; i <= 5; ++i)
        ui->imageNums->addItem(QString::number(i));
    sushiClicked = true;

}
