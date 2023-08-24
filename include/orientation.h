#ifndef ORIENTATION_H
#define ORIENTATION_H

#include "common.h"

#define AXIAL 0
#define CORONAL 1
#define SAGITTAL 2

class Orientation
{
public:
    Orientation();
    ~Orientation();

    iftMatrix *getAxialOrientationMatrix();
    iftMatrix *getCoronalOrientationMatrix();
    iftMatrix *getSagittalOrientationMatrix();

    iftMatrix *getAxialInvertedOrientationMatrix();
    iftMatrix *getCoronalInvertedOrientationMatrix();
    iftMatrix *getSagittalInvertedOrientationMatrix();

    void setAxialOrientationMatrix(iftMatrix *m);
    void setCoronalOrientationMatrix(iftMatrix *m);
    void setSagittalOrientationMatrix(iftMatrix *m);

    void setOrientationToRadiologists();
    void setOrientationToNeurologists();

    iftVoxel mapPixelToVolume(iftVoxel u, int slice, int plane);
    iftVoxel mapPixelToVolume(iftVoxel u);

    iftImage* applyOrientationOnSlice(iftImage *img, int plane);

    int plane;
    int slice;

private:
    iftMatrix *A = nullptr, *C = nullptr, *S = nullptr;
    iftMatrix *Ainv = nullptr, *Cinv = nullptr, *Sinv = nullptr;
    iftVoxel offset[3];

    char dimension;
};

#endif // ORIENTATION_H
