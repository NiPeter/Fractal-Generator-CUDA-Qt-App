#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDoubleValidator>
#include <fractalgraphicsview.h>
#include <julia_set_generator.h>
#include <fractalworker.h>

Q_DECLARE_METATYPE(std::shared_ptr<bitmap_image>);


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void on_checkBoxAutoGenerate_clicked(bool checked);

    void on_pushButtonGenerate_clicked();

    void on_doubleSpinBoxZoom_valueChanged(double arg1);

    void on_spinBoxResolutionX_valueChanged(int arg1);

    void on_spinBoxResolutionY_valueChanged(int arg1);

    void on_spinBoxMaxIterations_valueChanged(int arg1);

    void on_OffsetX_valueChanged(double arg1);

    void on_OffsetY_valueChanged(double arg1);

    void on_doubleSpinBoxConstRealis_valueChanged(double arg1);

    void on_doubleSpinBoxConstImaginalis_valueChanged(double arg1);

    void on_pushButtonFitToView_clicked();

  private:
    Ui::MainWindow *ui;

    QImage image;
    QGraphicsScene *scene;
    JuliaSetGenerator generator;
    FractalWorker *generator_thread;

  private slots:
    void handleFractalResults(std::shared_ptr<bitmap_image> fractal);
};

#endif // MAINWINDOW_H
