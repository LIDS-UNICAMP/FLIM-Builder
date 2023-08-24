#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include "common.h"

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
    /* Indicate that I want to override the following member functions
     * from the original QGraphicsView class.
     */
    //using QGraphicsView::mousePressEvent;
    //using QGraphicsView::mouseMoveEvent;
    //using QGraphicsView::mouseReleaseEvent;

public:
    explicit MyGraphicsView(QWidget *parent = nullptr);
    ~MyGraphicsView() override;

signals:
    void printMarker(int x, int y);
    void eraseMarker(int x, int y);
    void showIntensity(int x, int y);
    void released();

    void forwardSlice(int ratio);
    void backwardSlice(int ratio);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    QGraphicsPathItem *myPath = nullptr;
    QPointF previous;
};

#endif // MYGRAPHICSVIEW_H
