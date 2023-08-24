#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.h"
#include "markers.h"
#include "flim.h"
#include "orientation.h"
#include "projection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /* Methods */
    void createTmpDir();
    void createWidgetsConnections();
    void createThumbnail(QString image_dir);
    void createActivationThumbnail();

    void insertMissingMarkersInHashTable();

    void enable3DImageVisualization();
    void enable2DImageVisualization();
    void enable3DMImageVisualization();
    void enable2DMImageVisualization();
    void enableActivationVisualization();
    void disableActivationVisualization();
    void resetImageVisualization();

    bool prepareFLIM();
    bool isModelTrained();

    bool transformMarkerImages2SeedFiles();
    void generateSeedsForLayer(int layer_index);
    void generateInputForLayer(int layer_index, QSet<QString> listOfNewMarkers);
    bool canRun(QSet<int> *layersToComputeDICE);
    bool runIFS();
    bool runFLIM();
    bool runFeatExtract();

    void cleanWorkspace();
    void cleanImageData();

    void updateActivations(QBitArray *activation_checked = nullptr);
    void updateGraphicsView();
    void updateListOfMarkers();
    void updateCursor();

    void addMarkerOnList();
    void createListOfMakers();
    void cleanListOfMarkers();

    bool thereAreScribblesOfMarker(QString marker_name);

    void computeDICEonActivation(QSet<int> layersToBeComputed);

private slots:

    void on_pbOpenTrainFolder_clicked();
    void on_pbSaveMarkers_clicked();
    void on_pbOpenMarkers_clicked();
    void on_pbRemoveDrawnMarkers_clicked();
    void on_pbLoadGroundTruth_clicked();
    void on_pbRemoveGroundTruth_clicked();

    void on_pbZoomIn_clicked();
    void on_pbZoomOut_clicked();
    void on_pbFitWindow_clicked();
    void on_pbOriginalSize_clicked();
    void on_hsBrightness_valueChanged(int value);
    void on_hsContrast_valueChanged(int value);
    void on_pbAddMarker_clicked();
    void on_pbRemoveMarker_clicked();
    void on_lwListOfMarkers_itemDoubleClicked(QListWidgetItem *item);

    void on_lwTrain_itemDoubleClicked(QListWidgetItem *item);

    void on_sbSliceNum_valueChanged(int value);
    void on_cb3DPlane_currentIndexChanged(int index);
    void on_sbBandNum_valueChanged(int value);

    void on_gvDisplay_released();
    void on_gvDisplay_printMarker(int x, int y);
    void on_gvDisplay_eraseMarker(int x, int y);
    void on_gvDisplay_forwardSlice(int ratio);
    void on_gvDisplay_backwardSlice(int ratio);
    void on_gvDisplay_showIntensity(int x,int y);

    void on_sbBrush_valueChanged(int value);

    void on_pbOpenModelDir_clicked();
    void on_cbSelectTrainingLayers_itemClicked(int index);
    void on_pbRun_clicked();
    void on_pbLoadArch_clicked();
    void on_pbSaveArch_clicked();
    void on_teFLIM_Arch_focusChanged();

    void on_cbMarkers_currentTextChanged(QString s);

    void on_cbLayer_currentIndexChanged(int i);

    void on_lwActivation_itemDoubleClicked(QListWidgetItem *item);
    void on_lwActivation_itemChanged(QListWidgetItem *item);

    void on_cbMarkersVisibility_currentTextChanged(QString s);
    void on_cbActivationVisibility_currentTextChanged(QString s);
    void on_cbGtVisibility_currentTextChanged(QString s);
    void on_pbSelectKernelsManual_clicked();
    void on_pbProjectKernels_clicked();
    void on_pbInvertKernels_clicked();
    void on_projectionClosed();
    void on_kernelsSelected(iftSet *kernel_indexes);
    void on_kernelDoubleClicked(int index);


private:
    Ui::MainWindow *ui;

    /* hash structures */
    QHash<QString, QColor> hashMarkerName2MarkerColor;
    QHash<int, QColor> hashLabelId2LabelColor;
    QHash<QString, iftLabeledSet *> hashScribble2LabeledSet;
    QHash<int, long*> hashListOfMarkersItem2ScribbleCenterAndId;
    QHash<int, QHash<QString, iftMatrix *>> hashDICEscorePerImagePerLayer;
    QHash<QString, iftMatrix *> hashDICEscorePerImage;

    QMap<int,int> mapLabel2MarkerClass;


    /* variables */
    QListWidgetItem *current_item = nullptr;
    QGraphicsPixmapItem *current_display_image = nullptr;    
    QString tmp_dir                   = "";
    QString images_path               = "";
    QString thumbnail_path            = "";
    QString activation_thumbnail_path = "";
    QString markers_path              = "";
    QString seeds_path                = "";
    QString model_path                = "";
    QString arch_path                 = "";
    QString gt_path                   = "";
    QString current_marker_filename   = "";
    QString last_known_dir            = "";
    QString norm_type                 = "marker-norm";
    double abs_scale_factor           = 1.0;
    int current_axial_slice           = 0;
    int current_coronal_slice         = 0;
    int current_sagittal_slice        = 0;

    /* custom class instances */
    Markers *markers              = nullptr;
    FLIM *flim                    = nullptr;
    Orientation *orientation      = nullptr;
    Projection *kernel_proj       = nullptr;

    /* Image Structures */
    iftImage *current_activation           = nullptr;
    iftImage *current_activation_interp    = nullptr;
    iftImage *current_markers              = nullptr;
    iftImage *current_ift_img              = nullptr;
    iftImage *current_ift_img_norm         = nullptr;
    iftImage *current_gt                   = nullptr;
    iftImage *current_gt_border            = nullptr;
    iftMImage *current_ift_mimg            = nullptr;
    QImage *current_qt_img                 = nullptr;

    /* Matrix Structures */
    iftMatrix *DICEimportance              = nullptr;

    /* Window and Level Variables */
    double f1,f2,g1,g2;

};

#endif // MAINWINDOW_H
