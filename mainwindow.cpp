#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgProcess = new imgprocess();




    //Constructing labels
    label_original = new QLabel();
    label_final = new QLabel();



    //Constructing scrollarea
    scroll_original = new QScrollArea();
    scroll_original->setWidget(label_original);



    //Menus
    menuBar = new QMenuBar();
    menuFile = new QMenu();
    actionOpen = new QAction();
    menuFile->addAction(actionOpen);




    //Actions of the menu
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(load_image()));

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save_image()));

    connect(ui->actionAbout_this_project, SIGNAL(triggered()), this, SLOT(load_info()));

    connect(ui->actionProject_report, SIGNAL(triggered()), this, SLOT(show_report()));

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));




    //Add the menu into the widget
    menuBar->addMenu(menuFile);
}














MainWindow::~MainWindow()
{
    delete ui;
}














/*Function to show the ABOUT of the project*/
void MainWindow::load_info() {
    QMessageBox::about(this, tr("About this project"),
                               tr("This project promotes the developement of two \n"
                                  "pixel manipulation approaches: pixelize and pixel art - \n"
                                  "Developed by: AGBOHOUI Olivier \n"
                                  "Centre Universitaire Condorcet\n"
                                  "BSCV 2016-2017 \n"));
}









/*Function to show my report*/
void MainWindow :: show_report() {

    QProcess *p = new QProcess();
    p->start("C://WINDOWS/system32/xpsrchvw.exe",
        QStringList() <<"C://Users/AGBOLIVER/over.oxps");

}












/*Function to open the original image*/
void MainWindow::load_image() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open"),
                                                    "C://Users/AGBOLIVER/Pictures/2015-07");

    //Enable the first tab
    ui->tabWidget->setTabEnabled(0, true);
    ui->tabWidget->setTabEnabled(1, false);

    QImage image (filename);
    ui->label_original->setPixmap(QPixmap::fromImage(image));
    ui->label_original->adjustSize();
}











/*Function to save image into local hard drive*/
void MainWindow::save_image() {
    //Choose the filename of saving image
    QString path = QFileDialog::getSaveFileName(this, tr("Save"));

    //If no name was *NOT* put, return void
    if (path.isEmpty()) {
        return;
    }

    //If the name was put, see which tab is enable
    else {
        //First table
        if (ui->tab->isEnabled() == true) {
            ui->label_final->pixmap()->toImage().save(path,0);
        }

        //Second table
        else {
            ui->label_final_2->pixmap()->toImage().save(path,0);
        }
    }
}














/*Function to run the pixelize code*/
void MainWindow::on_pushButton_2_clicked()
{
    //Get the image on the scroll area
    QImage img = ui->label_original->pixmap()->toImage();

    //Get the value of the pixel size and see if it is higher than 0
    if (ui->spinBox->value() > 0) {
        //Run the pixelize code
        QImage img2 = imgProcess->pixeliseFunction(img, ui->spinBox->value());
        ui->label_final->setPixmap(QPixmap::fromImage(img2));
        ui->label_final->adjustSize();
    }

    //If the pixel size is lower or equal zero, a warning msg will be shown
    else {
        QMessageBox::warning(this, tr("Warning"),
                                   tr("The size of cube has to be higher than 0 \n"),
                                       QMessageBox::Ok);
    }
}













/*Function to run the pixel art code*/
void MainWindow::on_pushButton_clicked()
{
    //Select a data of images and put on std::vector of QImage
    QStringList imgPath = QFileDialog::getOpenFileNames(this, "Open");
    std::vector<QImage> vecImages;
    for (int i = 0; i < imgPath.size(); i++) {
        vecImages.push_back(QImage(imgPath[i]).scaled(ui->spinBox->value(),
                                                      ui->spinBox->value(),
                                                      Qt::KeepAspectRatio));
    }

    //Disable the first tab to put the second one
    ui->tabWidget->setTabEnabled(0, false);
    ui->tabWidget->setTabEnabled(1, true);

    //Put the pixelized image into the other tab
    QImage img = ui->label_final->pixmap()->toImage();
    ui->label_original_2->setPixmap(QPixmap::fromImage(img));

    //Run the pixel art code and put the result on the tab2
    QImage img2 = imgProcess->pixelArt (img, ui->spinBox->value(), vecImages);
    ui->label_final_2->setPixmap(QPixmap::fromImage(img2));
    ui->label_final_2->adjustSize();
}









/*Function to Exit*/
void MainWindow :: quit() {

    QApplication::quit();

}







