#ifndef COMMON_H
#define COMMON_H

#include "ift.h"

#include <QAbstractItemView>
#include <QBitArray>
#include <QColorDialog>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QElapsedTimer>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPlainTextEdit>
#include <QProgressDialog>
#include <QStandardItem>
#include <QTextEdit>
#include <QTextStream>
#include <QThread>
#include <QTimer>

#include <time.h>

// TMP dir
#define TMP_DIR "~/flim_tmp/"

// For QImage Structure
#define QIMAGE_FORMAT QImage::Format_RGB888

#define MAX_NUMBER_LABEL_COLORS 21

/*
 * Global variables (mostly used for projection)
 */
extern float pointDefaultRx;
extern float pointDefaultRy;
extern float textDefaultFontSize;
extern float boundBoxDefaultX;
extern float boundBoxDefaultY;
extern float boundBoxDefaultWidth;
extern float boundBoxDefaultHeight;

/**
 * @brief Returns a QImage generated from a iftImage
 *
 * @author Azael de Melo e Sousa
 *
 * Transforms an iftImage into a QImage
 *
 * @param <img  >       Pointer to an image stored in a iftImage data structure
 * @param <markers>     Pointer to the marker image
 * @param <hashMarkerId2MarkerColor> Hash table mapping the markers to its colors
 * @param <label>       Pointer to the label image
 * @param <hashLabelId2LabelColor> Hash table mapping the label to its colors
 * @return Same image stored in a QImage data structure
 */
QImage *iftImageToQImage(iftImage *img, iftImage *markers, QHash<QString,QColor> hashMarkerId2MarkerColor, iftImage *label, iftImage *label_border, QHash<int,QColor> hashLabelId2LabelColor);

/**
 * @brief Color a grayimage according to a colortable. The original intensity is maintained and only the saturation and hue is changed.
 *
 * @author Azael de Melo e Sousa
 *
 * Transforms an iftImage into a QImage
 *
 * @param <img> Pointer to an image stored in a iftImage data structure
 * @param <activation> Pointer to the activation image
 * @param <ctb> Pointer to an iftColorTable
 * @return Color image
 */
iftImage *iftColorGrayImageByActivation(iftImage *img, iftImage *activation, iftColorTable *ctb);

/**
 * @brief Find the first pixels of each object in the image
 *
 * @author Azael de Melo e Sousa
 *
 * Find first pixels of objects
 *
 * @param <img> Labeled image where each object has a different label
 * @return Labeled Set
 */
iftLabeledSet* iftFirstElemOfComponents(iftImage *label_image);

#endif // COMMON_H
