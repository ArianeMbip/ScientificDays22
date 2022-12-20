#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ImagePgm{
    int row;
    int col;
    int maxVal;
    int *matrix;
    int *hist;
}ImagePgm;

ImagePgm EmptyImage(int row,int col, int max);
void updateHist(ImagePgm *image);
int *allocateMatrix(int row, int col);
void freeMatrix(int *matrix);
int getHeader(FILE *f);
int skipComments(FILE *f);
int getNextInt(FILE *f);
ImagePgm ReadImage(char *img);
void printImageMatrix(ImagePgm image);
void saveImagePGM(char *file,ImagePgm image);
void dropImage(ImagePgm *image);

#endif // INCLUDE_H_INCLUDED
