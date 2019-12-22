#include "fractalworker.h"
#include <QElapsedTimer>

FractalWorker::FractalWorker(JuliaSetGenerator *generator, QObject *parent) : QThread(parent) {
  generator_ = generator;
  lastDuration_ = 0;
}

void FractalWorker::run() {
  QElapsedTimer timer;

  timer.start();
  std::unique_ptr<bitmap_image> fractal = generator_->generate();

  lastDuration_ = timer.elapsed();
  std::shared_ptr<bitmap_image> shared = std::move(fractal);
  emit fractalReady(shared);
}
