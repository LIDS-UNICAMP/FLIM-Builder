#ifndef Projection_H
#define Projection_H

#include <QWidget>
#include "common.h"
#include "graphnode.h"

typedef enum {
    THREAD_TSNE_PROJECTION,
    THREAD_OPF_CLASSIFICATION,
    THREAD_THUMBNAIL,
    THREAD_GRAPH_EDGES
} ThreadTaskType;

typedef enum {
    PROJECT_KERNELS,
    PROJECT_PATCHES
} ProjectionType;

namespace Ui {
class Projection;
}

class MyThread;

class Projection : public QDialog
{
    Q_OBJECT

public:
    Ui::Projection *ui;

    explicit Projection(QWidget *parent = nullptr,
                              QString model_path="",
                              QString seeds_path="",
                              QString label_path="",
                              int layer_id=1);

    explicit Projection(QWidget *parent = nullptr,
                              QString img_path="",
                              QString seeds_path="",
                              QJsonObject json_arch=QJsonObject(),
                              int current_training_layer=1,
                              QString model_path="");

    ~Projection();

    void tsneProjectionOnCurrentDataSet();
    void enableWidgetsByMode(QString mode);

    /* Public Variables */
    iftDataSet *originalDataSet   = nullptr;
    iftDataSet *workingDataSet    = nullptr;
    iftMatrix  *kernelimportance  = nullptr;
    iftMatrix  *DICEimportance    = nullptr;
    QString edgeMode;
    QString dataSetName;
    int numbSamplesShown;
    int numbSamplesSelected;
    int targetMarker;
    QVector<GraphNode *>graphNodes;
    QVector<GraphEdge *>graphEdges;
    bool didSomething             = false;

    /* Thread */
    MyThread   *threadProjection  = nullptr;
    QTimer     *threadTimer       = nullptr;
    QElapsedTimer  threadElapsedTime;
    ThreadTaskType threadTaskType;

    /* Hash */
    QHash<unsigned long, GraphNode*> hashSampleId2GraphNodeRef;
    QHash<GraphNode*,unsigned long> hashGraphNodeRef2SampleId;
    QHash<QString, QColor> hashMarkerName2MarkerColor;
    QHash<int, QColor> hashClassId2ClassColor;
    QHash<int, QString> hashClassId2ClassName;

    /* Graphics View */
    int sceneScalingFactor = 0;
    QGraphicsScene* projGraphicsScene = nullptr;
    iftFileSet* thumbnailPath         = nullptr;
    iftFileSet *fileSet               = nullptr;
    QString currentNodeColorOption;
    bool drawShadowInPoints;
    float globalMinFeature = IFT_INFINITY_FLT;
    float globalMaxFeature = IFT_INFINITY_FLT_NEG;
    float globalMinFeatPerplexity = IFT_INFINITY_FLT;
    float globalMaxFeatPerplexity = IFT_INFINITY_FLT_NEG;
    float globalMinFeatMean = IFT_INFINITY_FLT;
    float globalMaxFeatMean = IFT_INFINITY_FLT_NEG;
    float globalMinFeatStdev= IFT_INFINITY_FLT;
    float globalMaxFeatStdev = IFT_INFINITY_FLT_NEG;
    float globalMinFeatWeight= IFT_INFINITY_FLT;
    float globalMaxFeatWeight = IFT_INFINITY_FLT_NEG;

    /* Methods */
    void initScene();
    void initGraphicsView();
    void clearAllData(bool clearDatasets=true);
    void updateNumbSamplesShown();
    void createComboBoxForClassFilters();
    void createHashBetweenClassesAndColors();
    void createHashBetweenGroupsAndColors();
    void updateDataSetInfoTextBoxes();
    void updateSampleTooltip();
    void computeKernelsImportancePerClass();
    void computeKernelsImportancePerClassOnMask();
    void setMarkersHash(QHash<QString, QColor> hash);
    void setDICEImportance(iftMatrix *DICE);
    void selectSampleFromMainWindow(int sample);
    void deselectSampleFromMainWindow(int sample);
    void paintNodes();
    QHash<QString, QColor> getMarkersHash();
    DrawingOption nodeTypeToDrawOption(QString nodeType);
    void ProjectKernels();
    void ProjectPatches();

    void setModelPath(QString path);
    QString getModelPath();

private:

    /* Private Variables */
    int layer_id          = 1;
    QString  model_path   = "";
    QString  image_path   = "";
    QString  seeds_path   = "";
    QString  label_path   = "";
    ProjectionType project_type;

    iftFLIMArch *flim_arch;
    int current_training_layer;
    float *mean = nullptr, *stdev = nullptr;
    long ninputchannels;

    /* Private Methods */
    QString formatTime(int miliseconds);
    void createConnections();
    void destroyConnections();

    void NormalizeImagePerBand(iftMImage *activ, iftImage *label_img);

signals:
    void kernelsSelected(iftSet *kernel_indexes);
    void kernelDoubleClicked(int index);
    void projectionClosed();

public slots:
    void on_hsPerplexity_valueChanged(int i);
    void on_hsNumIterTSNE_valueChanged(int i);
    void on_sbPerplexity_valueChanged(int i);
    void on_sbNumIterTSNE_valueChanged(int i);

    void on_cbNodeColorByRelevance_currentTextChanged(QString text);
    void on_cbNodeType_currentTextChanged(QString text);
    void on_cbFilterClass_currentIndexChanged(int i);

    void projectionFinished_slot(bool tsneExecuted);
    void on_pbProject_clicked();
    void on_pbSaveProjection_clicked();
    void timer_slot();

    void on_doubleClicked(int index);

    void on_pbSaveKernels_clicked();
    void on_pbSaveRelevance_clicked();

protected:
    void closeEvent(QCloseEvent* event);
    void keyPressEvent(QKeyEvent *e);
};


/*////////////////////////////////// MYTHREAD //////////////////////////////////*/

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(Projection* window, ThreadTaskType taskType);
    Projection* projection = nullptr;
    ThreadTaskType taskType;
    void run();

signals:
    void projectionFinished_signal(bool tsneExecuted);
};


#endif // Projection_H
