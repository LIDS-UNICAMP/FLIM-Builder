#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsDropShadowEffect>
#include "common.h"


typedef enum {
    optionPoint = 0,
    optionFeatPie = 1,
    optionFeatHistogram = 2,
    optionText = 3,
    optionImage = 4,
    optionDrawingEdges = 5
} DrawingOption;

typedef enum {
    EdgeMode_None,
    EdgeMode_Predecessor,
    EdgeMode_Neighbours
} EdgeMode;

class GraphEdge;
class SignalHandler;

class GraphNode : public QGraphicsItem
{

public:
    GraphNode(iftSample *sampPtr, int numFeats);
    ~GraphNode() override;
    SignalHandler *signalhandler;
    float radiusX;
    float radiusY;
    float radiusX_highlight;
    float radiusY_highlight;
    float radiusX_unhighlight;
    float radiusY_unhighlight;
    iftSample *samplePtr = nullptr;
    int nFeats;
    float featPerplexity;
    float featMean;
    float featStdev;
    float featWeight;
    bool displayNodeDataAsPointBorder;
    QString currentNodeDataMode;
    float maxGlobalFeatPerplexity;
    float minGlobalFeatPerplexity;
    float maxGlobalFeatMean;
    float minGlobalFeatMean;
    float maxGlobalFeatStdev;
    float minGlobalFeatStdev;
    float maxGlobalFeatWeight;
    float minGlobalFeatWeight;
    QRect obj_boundingRect;
    QColor fillColor_original;
    QColor fillColor;    
    QColor borderColor_unselected;
    QColor borderColor_selected;
    QColor borderColor_supervised;
    QColor borderColor_propagated;
    qreal fontSize;
    QString sampleImagePath;
    QString thumbnailImagePath;
    QString sampleName;
    bool currentSupervising;
    bool isMarked;
    bool isHovered;
    unsigned long numberTimesChecked;
    EdgeMode edgeMode;
    DrawingOption drawOption;
    qreal Z;
    QString sampleText;
    qreal fontSizeScalingFactor;
    QVector<GraphEdge*> sourceEdges;
    QVector<GraphEdge*> destEdges;
    QGraphicsDropShadowEffect *shadowEffect;
    bool drawShadowInPoints;
    bool isSelectedByClassOrGroup;
    bool showClassGroupColorOnTooltip;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mountToolTip();
    using QGraphicsItem::hoverEnterEvent; //to prevent warning
    void hoverEnterEvent();
    using QGraphicsItem::hoverLeaveEvent; //to prevent warning
    void hoverLeaveEvent();
    void computeFeatPerplexity();
    void computeFeatMean();
    void computeFeatStdev();
    void computeFeatWeight();
    void setMaxGlobalFeatPerplexity(float val);
    void setMinGlobalFeatPerplexity(float val);
    void setMaxGlobalFeatMean(float val);
    void setMinGlobalFeatMean(float val);
    void setMaxGlobalFeatStdev(float val);
    void setMinGlobalFeatStdev(float val);
    void setMaxGlobalFeatWeight(float val);
    void setMinGlobalFeatWeight(float val);
    void setDisplayNodeDataAsPointBorder(bool val);
    void setCurrentNodeDataMode(QString val);
    void setDrawShadowInPoints(bool val);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

};

// signal handler
class SignalHandler: public QObject
{
    Q_OBJECT
public:
    SignalHandler() {}
    virtual ~SignalHandler() {}

signals:
    void doubleClicked(int index);
};


#endif // GRAPHNODE_H

