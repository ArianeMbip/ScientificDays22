#ifndef CONVOLUTION_H_INCLUDED
#define CONVOLUTION_H_INCLUDED
#include "include.h"

float* create_Moy_Mask(int u, int v);
float* create_Gauss_Mask(int u, int v);

int getMedianne(int *matrix, int row, int x, int y, int u, int v);
float convolute(int *matrix, int row, int x, int y, float* filtre, int u, int v);
Myimage Filtre_moyenneur(Myimage image,int u,int v);
Myimage Filtre_gaussien(Myimage image,int u,int v);
Myimage Filtre_median(Myimage image,int u,int v);

#endif