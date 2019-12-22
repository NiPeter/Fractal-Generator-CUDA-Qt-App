#include "fractalgraphicsview.h"
#include <QWheelEvent>
#include <QTimeLine>


FractalGraphicsView::FractalGraphicsView(QWidget *parent)
  : FractalGraphicsView::QGraphicsView(parent),
  numScheduledScalings_(0),
  zoomAnimationTime_(500) {
}

void FractalGraphicsView::setZoomAnimationTime(int duration_ms) {
  if (duration_ms > 0) zoomAnimationTime_ = duration_ms;
}

void FractalGraphicsView::wheelEvent(QWheelEvent *event) {
  int numDegrees = event->delta() / 8;
  int numSteps = numDegrees / 15;

  numScheduledScalings_ += numSteps;

  if (numScheduledScalings_ * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
    numScheduledScalings_ = numSteps;

  QTimeLine *animation = new QTimeLine(zoomAnimationTime_, this);
  animation->setUpdateInterval(20);
  connect(animation, &QTimeLine::valueChanged, this, &FractalGraphicsView::scalingAnimationStep);
  connect(animation, &QTimeLine::finished, this, &FractalGraphicsView::scalingAnimationFinished);
  animation->start();
}

void FractalGraphicsView::scalingAnimationStep(qreal x) {
  x = 0; //!< Prevent warnings in IDE uhhhhh....
  qreal factor = 1.0 + qreal(numScheduledScalings_) / 300.0;

  scale(factor, factor);
}

void FractalGraphicsView::scalingAnimationFinished() {
  if (numScheduledScalings_ > 0) numScheduledScalings_--;
  else numScheduledScalings_++;

  sender()->~QObject();
}
