//
// Created by taylla on 16/01/23.
//
#ifndef IFT_MESOTHELIOMA_H
#define IFT_MESOTHELIOMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ift.h"
#include "ift/segm/iftSICLE.h"

float* iftMesoMeanIntensityCurves(iftImage *img, iftImage * label, int n_label);
iftImage* iftMesoProjectSeedsOnNextImage(iftImage *prev_img, iftImage *img, iftImage *mask, iftMImage *mimg, iftLabeledSet *ith_centroids, char* SEGMENTATION_METHOD);
float iftMesoMeanBackgroundSeeds(iftImage *img, iftLabeledSet* background_seeds);

iftImage** iftMesoAutoECE(iftImage** imgs, iftImage** masks_fluid,  float  max_dist, int num_init_seeds, int num_superpixels, int n_images, iftLabeledSet** background_seeds,  int* time_sec, char* SUPERVOXEL_METHOD, char* SEGMENTATION_METHOD, float*** mean_intensity_superspels);


float*  iftMesoSphericPatch(iftImage *Img, iftVoxel u, iftAdjRel *A_patch);

iftImage* iftMesoRegionContainingPleura(iftImage *img, iftImage *mask, float max_dist);

float** iftMeanIntensitySuperspelsFromImageAndLabel(iftImage** imgs, iftImage** labels_ECE, int n_imgs);

iftImage** iftMesoMaskDilation(iftImage** imgs, iftImage** fluid_masks, float dilation_ratio, int n_images);

iftImage** iftMesoSuperspels(iftImage** imgs, iftImage** masks_meso, iftLabeledSet** background_seeds, int num_init_seeds, int num_superpixels, char* SUPERVOXEL_METHOD, char* SEGMENTATION_METHOD, int n_images, float*** mean_intensity_superspels);

iftImage** iftMesoSelectLabels(iftImage** imgs, iftImage** labels, float** mean_intensity_superspels, int n_images,int num_superpixels, int* time_sec, float*** final_mean_intensity_superspels);

iftImage ** iftMesoAutoECE2(iftImage** imgs, iftImage** masks_fluid,  float  max_dist, int num_init_seeds, int num_superpixels, int n_images, iftLabeledSet** background_seeds, int* time_sec, char* SUPERVOXEL_METHOD, char* SEGMENTATION_METHOD, float*** final_mean_intensity_superspels);


#ifdef __cplusplus
}
#endif

#endif
