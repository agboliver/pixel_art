#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFileDialog>
#include <QLabel>
#include <QMenu>
#include <QProcess>
#include <QSpinBox>
#include <QTabBar>
#include <QMessageBox>
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
    void save_image();
    void load_info();
    void show_report();
    void quit();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    QScrollArea *scroll_original, *scroll_final;
    QLabel *label_original, *label_final, *label_original_2, *label_final_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QAction *actionOpen, *actionSave, *actionExit, *actionAbout_this_project;
    imgprocess *imgProcess;
    QSpinBox *spinBox;
    QTabBar *tabWidget;

};

#endif // MAINWINDOW_H
