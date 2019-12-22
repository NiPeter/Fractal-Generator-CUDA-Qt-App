#ifndef FRACTALWORKER_H
#define FRACTALWORKER_H

#include <QThread>
#include <julia_set_generator.h>

class FractalWorker : public QThread {
  Q_OBJECT
  public:
    FractalWorker(JuliaSetGenerator *generator, QObject *parent = nullptr);

    void run() override;

    qint64 lastGenerateDurationMs() const {
      return lastDuration_;
    }

  private:
    JuliaSetGenerator *generator_;

    qint64 lastDuration_;
  signals:
    void fractalReady(std::shared_ptr<bitmap_image> fractal);

  public slots:
};

#endif // FRACTALWORKER_H
