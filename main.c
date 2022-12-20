#include "include.h"
#include "traitement.h"
#include "convolution.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    //image pgm
    char *img = "viral.pgm"; 
    
    ImagePgm image,out;
    ImagePgm hist;

    //affichage de l'image pgm
    image = ReadImage(img); 

    //création de l'histogramme
    hist = generateHistogramme(image);
    saveImagePGM("img1.ppm",image);
    saveImagePGM("hist1.ppm",hist);

    out = Transformation_lineaire(image);

    //création de l'histogramme
    hist = generateHistogramme(out);
    saveImagePGM("img2.ppm",out);
    saveImagePGM("hist2.ppm",hist);

    out = Transformation_lineaire_saturation(image,8,200);

    //création de l'histogramme
    hist = generateHistogramme(out);
    saveImagePGM("img3.ppm",out);
    saveImagePGM("hist3.ppm",hist);

    out = inversion(image);

    //création de l'histogramme
    hist = generateHistogramme(out);
    saveImagePGM("img4.ppm",out);
    saveImagePGM("hist4.ppm",hist);

    out = Egalisation_histogramme(image);

    //création de l'histogramme
    hist = generateHistogramme(out);
    saveImagePGM("img5.ppm",out);
    saveImagePGM("hist5.ppm",hist);
    
    out = Escalier(image,8);

    //création de l'histogramme
    hist = generateHistogramme(out);
    saveImagePGM("img6.ppm",out);
    saveImagePGM("hist6.ppm",hist);


    out = Filtre_moyenneur(image,5,5);

    //création de l'histogramme
    hist = generateHistogramme(out);
    saveImagePGM("img7.ppm",out);
    saveImagePGM("hist7.ppm",hist);

    out = Filtre_gaussien(image,5,5);

    //création de l'histogramme
    hist = generateHistogramme(out);
    saveImagePGM("img8.ppm",out);
    saveImagePGM("hist8.ppm",hist);

    return 0;
}