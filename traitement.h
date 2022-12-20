#ifndef TRAITEMENT_H_INCLUDED
#define TRAITEMENT_H_INCLUDED
#include "include.h"

float Luminance(ImagePgm image);
float contraste(ImagePgm image);
ImagePgm generateHistogramme(ImagePgm image);
/// Amélioration du contraste
ImagePgm Transformation_lineaire(ImagePgm image);
ImagePgm Transformation_lineaire_saturation(ImagePgm image,int min,int max);
ImagePgm Transformation_non_lineaire(ImagePgm image,int gamma);
ImagePgm inversion(ImagePgm image);
ImagePgm Escalier(ImagePgm image,int pas);

/// Egalisation_histogramme
ImagePgm Egalisation_histogramme(ImagePgm image);
#endif