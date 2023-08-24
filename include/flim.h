#ifndef FLIM_H
#define FLIM_H

#include "common.h"
#include <QProcess>

class FLIM
{
public:
    FLIM();
    ~FLIM();

    /* Public member functions */
    bool IsArchitectureValid();

    /* @brief Train a specific FLIM layer. In case of missing kernels from the previous layers,
     * the method recursively computes them.
     */
    bool TrainLayerFLIM(int layer);
    bool ExtractFeaturesFromLayer(int layer);
    bool ExtractFeaturesFromLayerForTraining(int layer);
    bool modelExists(int layer);

    QString ExtractFeaturesWithPython();

    /* Variables */
    QJsonObject arch_json;
    QString orig_dir;
    QString param_dir;
    QString seeds_dir;
    QString object_dir;
    QString images_list_path;
    QString arch_path;

    int device;

    iftFLIMArch *ift_arch;
};

/* FLIM-related public methods */
iftFLIMArch *JSONArchToFLIMArch(QJsonObject arch_json);
iftMImage *ReadInputMImage(char *filename);
iftMatrix *LearnKernelBank(iftMImage *input, iftLabeledSet *M, iftAdjRel *A, int nsamples, int nkernels_per_marker);
iftMatrix *ComputeKernelBank(iftDataSet *Z, int *ngroups, uchar grouping_method);
iftDataSet *ComputeSeedDataSet(iftMImage *img, iftLabeledSet *S, iftAdjRel *A, int nsamples);
iftMatrix *SelectRelevantKernelsByPCA(iftMatrix *kernels, int number_of_kernels);
iftMatrix *SelectRelevantKernelsByKmeans(iftMatrix *K, int ngroups);
void NormalizeImageByZScore(iftMImage *img, float *mean, float *stdev);
void WriteMeanStdev(char *basepath, float *mean, float *stdev, long ninput_channels);
void StatisticsFromAllSeeds(iftFileSet *fs_seeds, char *inputdata_dir, iftAdjRel *A, float *mean, float *stdev, float stdev_factor, char *ext);

#endif // FLIM_H
