#ifndef FRACTALGRAPHICSVIEW_H
#define FRACTALGRAPHICSVIEW_H
#include <QObject>
#include <QWidget>
#include <QGraphicsView>

class FractalGraphicsView : public QGraphicsView {
  Q_OBJECT
  public:
    FractalGraphicsView(QWidget *parent);

    void setZoomAnimationTime(int duration_ms);

    void wheelEvent(QWheelEvent *event);

  private:
    int numScheduledScalings_; //!< How much to scale during one animation step
    int zoomAnimationTime_;

  private slots:
    void scalingAnimationStep(qreal x);

    void scalingAnimationFinished();
};

#endif // FRACTALGRAPHICSVIEW_H
