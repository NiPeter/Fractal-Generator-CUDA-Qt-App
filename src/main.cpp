#include "mainwindow.h"
#include <QApplication>
#include <julia_set_generator.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  qRegisterMetaType<std::shared_ptr<bitmap_image> >();

  MainWindow w;
  w.show();

  return a.exec();
}
