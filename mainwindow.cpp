#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Constructing labels
    label_original = new QLabel();

    //Constructing scrollarea
    scroll_original = new QScrollArea();
    scroll_original->setWidget(label_original);

    //Menus
    menuBar = new QMenuBar();
    menuFile = new QMenu();
    actionOpen = new QAction();
    menuFile->addAction(actionOpen);

    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(load_image()));

    menuBar->addMenu(menuFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_image() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"),
                                                    QDir::currentPath());

    QImage image (filename);
    ui->label_original->setPixmap(QPixmap::fromImage(image));
    ui->label_original->adjustSize();
}
