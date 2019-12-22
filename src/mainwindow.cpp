#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->pushButtonGenerate->setEnabled(!ui->checkBoxAutoGenerate->isChecked());
  scene = new QGraphicsScene(this);


  generator.
  setMaxIterations(static_cast<unsigned int>(ui->spinBoxMaxIterations->value())).
  setConstantRealis(ui->doubleSpinBoxConstRealis->value()).
  setConstantImaginalis(ui->doubleSpinBoxConstImaginalis->value()).
  setZoom(ui->doubleSpinBoxZoom->value()).
  setWidth(static_cast<unsigned int>(ui->spinBoxResolutionX->value())).
  setHeight(static_cast<unsigned int>(ui->spinBoxResolutionY->value()));


//  auto fractal = gen.setZoom(1.0).generate();
//  auto img = fractal->get_image();

//  image = image.fromData(img.get(), static_cast<int>(fractal->get_size()));


//  scene->addPixmap(QPixmap::fromImage(image));
//  scene->setSceneRect(image.rect());
//  ui->graphicsView->setScene(scene);
//  ui->
}

MainWindow::~MainWindow() {
  delete ui;
  delete scene;
}

void MainWindow::on_checkBoxAutoGenerate_clicked(bool checked) {
  ui->pushButtonGenerate->setEnabled(!checked);
}

void MainWindow::on_pushButtonGenerate_clicked() {
  generate_fractal();
}

void MainWindow::generate_fractal() {
//  generator.;

  auto fractal = generator.generate();
  auto raw_image = fractal->get_image();

  image = image.fromData(raw_image.get(), static_cast<int>(fractal->get_size()));

  scene->clear();
  scene->addPixmap(QPixmap::fromImage(image));
  scene->setSceneRect(image.rect());
  ui->graphicsView->setScene(scene);
  ui->graphicsView->fitInView(image.rect(), Qt::KeepAspectRatio);
}

void MainWindow::on_doubleSpinBoxZoom_valueChanged(double arg1) {
  generator.setZoom(1.0 / arg1);
}

void MainWindow::on_spinBoxResolutionX_valueChanged(int arg1) {
  generator.setWidth(static_cast<unsigned int>(arg1));
}

void MainWindow::on_spinBoxResolutionY_valueChanged(int arg1) {
  generator.setHeight(static_cast<unsigned int>(arg1));
}

void MainWindow::on_spinBoxMaxIterations_valueChanged(int arg1) {
  generator.setMaxIterations(static_cast<unsigned int>(arg1));
}

void MainWindow::on_OffsetX_valueChanged(double arg1) {
  generator.setOffsetX(arg1);
}

void MainWindow::on_OffsetY_valueChanged(double arg1) {
  generator.setOffsetY(arg1);
}

void MainWindow::on_doubleSpinBoxConstRealis_valueChanged(double arg1) {
  generator.setConstantRealis(arg1);
}

void MainWindow::on_doubleSpinBoxConstImaginalis_valueChanged(double arg1) {
  generator.setConstantImaginalis(arg1);
}

void MainWindow::on_pushButtonFitToView_clicked() {
  int width = ui->graphicsView->width();
  int height = ui->graphicsView->height();

  ui->spinBoxResolutionX->setValue(width);
  ui->spinBoxResolutionY->setValue(height);
}
