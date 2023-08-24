#ifndef MARKERS_H
#define MARKERS_H

#include "common.h"
#include "orientation.h"

class Markers
{
public:
    Markers();

    void setBrush(double ratio);

    void draw(iftImage *img, QImage *qimg, iftVoxel u, int marker_label, QColor marker_color);
    void draw(iftImage *img, QImage *qimg, iftVoxel u, int marker_label, QColor marker_color, Orientation *orient);
    void erase(iftImage *img, QImage *marked_img, QImage clean_img, iftVoxel u);
    void erase(iftImage *img, QImage *marked_img, QImage clean_img, iftVoxel u, Orientation *orient);

    /* VARIABLES */
    const double max_ratio = 20.;
    const double min_ratio = 1.;
    double current_ratio;

private:
    iftAdjRel *brush = nullptr;
    iftVoxel lastPoint;
};

#endif // MARKERS_H
