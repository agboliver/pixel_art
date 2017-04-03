#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFileDialog>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <iostream>

#include "imgprocess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void load_image();

private:
    Ui::MainWindow *ui;
    QScrollArea *scroll_original, *scroll_final;
    QLabel *label_original, *label_final;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QAction *actionOpen, *actionSave, *actionExit;
    imgprocess *imgProcess;

};

#endif // MAINWINDOW_H
