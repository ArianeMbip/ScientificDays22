#include "convolution.h"
float* create_Moy_Mask(int u, int v){
    float *mask = malloc( u * v * sizeof(float));
    for (int i = 0; i < u * v; i++)
    {
        mask[i] = 1;
    }
    return mask;
}
float* create_Gauss_Mask(int u, int v){
    float *mask = malloc( u * v * sizeof(float));
    int i=0;
    mask[i] = 1 ;i++; mask[i] = 2 ;i++; mask[i] = 3 ;i++; mask[i] = 2 ;i++; mask[i] = 1 ;i++; 
    mask[i] = 2 ;i++; mask[i] = 6 ;i++; mask[i] = 8 ;i++; mask[i] = 6 ;i++; mask[i] = 2 ;i++; 
    mask[i] = 3 ;i++; mask[i] = 8 ;i++; mask[i] =10 ;i++; mask[i] = 8 ;i++; mask[i] = 3 ;i++; 
    mask[i] = 2 ;i++; mask[i] = 6 ;i++; mask[i] = 8 ;i++; mask[i] = 6 ;i++; mask[i] = 2 ;i++; 
    mask[i] = 1 ;i++; mask[i] = 2 ;i++; mask[i] = 3 ;i++; mask[i] = 2 ;i++; mask[i] = 1 ;i++; 
    return mask;
}
float convolute(int *matrix, int row, int x, int y, float* filtre, int u, int v){
    float r = 0,s = 0;
    for (int i = 0; i < u; i++){
        for (int j = 0; j < v; j++){
            s += filtre[i*u + j];
            r += matrix[(x+i-(int)u/2) * row + (y+j-(int)v/2)] * filtre[i*u + j];
        }   
    }
    r = s == 0 ? 0: r / s;
    return r;
}
ImagePgm Filtre_moyenneur(ImagePgm image,int u,int v){
    float *mask = create_Moy_Mask(u,v);
    ImagePgm out = EmptyImage(image.row, image.col, image.maxVal);
    for (int i = (int)u/2; i < image.row - (int)u/2; i++)
    {
        for (int j = (int)v/2; j < image.col - (int)v/2; j++)
        {
            out.matrix[i * image.row + j] = convolute(image.matrix,image.row,i,j,mask,u,v);
        }
    }
    updateHist(&out);
    return out;
}
ImagePgm Filtre_gaussien(ImagePgm image,int u,int v){
    float *mask = create_Gauss_Mask(u,v);
    ImagePgm out = EmptyImage(image.row, image.col, image.maxVal);
    for (int i = (int)u/2; i < image.row - (int)u/2; i++)
    {
        for (int j = (int)v/2; j < image.col - (int)v/2; j++)
        {
            out.matrix[i * image.row + j] = convolute(image.matrix,image.row,i,j,mask,u,v);
        }
    }
    updateHist(&out);
    return out;
}