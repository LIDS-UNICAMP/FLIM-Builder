#ifndef PROJECTIONGRAPHICSVIEW_H
#define PROJECTIONGRAPHICSVIEW_H

#include "common.h"
#include "projection.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QtGui>
#include <QComboBox>
#include <QEvent>
#include <QTime>
#include <QDebug>
#include <QGraphicsItem>
#include <QMenu>

class ProjectionGraphicsView : public QGraphicsView
{
     Q_OBJECT
public:
    ProjectionGraphicsView(QWidget *parent = nullptr);
    ~ProjectionGraphicsView() override;
    bool autoReprojection;
    QColor sceneRectColor;
    QColor backgroundColor;

    int targetClass = -1;

    void computeSceneScalingFactor();
    void paintNodes();
    void paintNodesByTrueClass();
    void paintNodesByWeight();
    void paintNodesByDICE();

private:
    const int avaregeTimeDisplayToolTip_miliseconds = 0;
    const int avaregeTimeHumanReaction_miliseconds = 50;
    const int totalTimeReaction = avaregeTimeDisplayToolTip_miliseconds+avaregeTimeHumanReaction_miliseconds;
    int MouseX_old = 0;
    int MouseY_old = 0;
    int MouseX_new = 0;
    int MouseY_new = 0;
    int nMilliseconds;
    QElapsedTimer myTimer;
    QGraphicsItem* lastItem = nullptr;
    bool validStart;
    Projection *projection = nullptr;

signals:
    void mouseContextMenuRequest_signal(QContextMenuEvent *event);
    void sceneAreaSizeChanged_signal();

public slots:
    void updateSceneAutoReprojection_slot(bool autoReproject);
    void updateNodesPosition_slot();

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) override;
#endif
    void scaleView(qreal scaleFactor);
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PROJECTIONGRAPHICSVIEW_H
