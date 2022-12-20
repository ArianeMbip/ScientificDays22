#include "include.h"
ImagePgm generateHistogramme(ImagePgm image){
    ImagePgm outputImage;
    int norm = 0,h=256;
    int tab[image.maxVal+1];
    
    for (int i = 0; i < image.maxVal+1; i++){
        image.hist[i] = 0;
    }
    for (int i = 0; i < image.row * image.col; i++)    {
        image.hist[image.matrix[i]] += 1;
    }
    for (int i = 0; i < image.maxVal+1; i++){
        tab[i] = image.hist[i];
        norm = norm < image.hist[i] ? image.hist[i] : norm ;
    }
    for (int i = 0; i < image.maxVal+1; i++){
        tab[i] = tab[i] * h / norm;
    }
    norm = h;
    
    outputImage = EmptyImage(norm, image.maxVal+1,1);
    for (int i = 0; i < outputImage.col; i++) {
        for (int j = 0; j < tab[i]; j++){
            outputImage.matrix[((norm-j-1)%norm) * outputImage.col + i] = 1;
        }
    }
    return outputImage;
}
float Luminance(ImagePgm image){
    float moy = 0;
    for (int i = 0; i < image.row * image.col; i++){
        moy = ( 1.0 ) * ( moy * i + image.matrix[i] )/( i+1 ); 
    }
    return moy;
}
float contraste(ImagePgm image){
    float c;
    int min=0,max=0;
    for (int i = 0; i <= image.maxVal; i++){
        min = min > image.hist[i] ? image.hist[i] : min;   
        max = max < image.hist[i] ? image.hist[i] : max;   
    }
    if(max == 0){
        return 1.0;
    }else{
        return 1.0*(max - min)/(max + min);
    }
}
ImagePgm Transformation_lineaire(ImagePgm image){
    ImagePgm out = EmptyImage(image.row, image.col, 255);
    int min = image.maxVal,max = 0;
    for (int i = 0; i <= image.row * image.col; i++){
        if(image.matrix[i] > max){
            max = image.matrix[i];
        }  
        if(image.matrix[i] < min){
            min = image.matrix[i];
        }
    }
    int maxmin = max - min;
    if(max == 0){
        maxmin = 1;
    }
    int LUT[256];
    for (int i = 0; i < 256; i++){
        LUT[i]=(int)(1.0*(i - min) * 255 / maxmin);
    }
    
    for (int i = 0; i < image.row * image.col; i++)
    {
        out.matrix[i] = LUT[image.matrix[i]];
    }
    updateHist(&out);
    return out;
}
ImagePgm Transformation_lineaire_saturation(ImagePgm image,int min,int max){
    ImagePgm out = EmptyImage(image.row, image.col, 255);
    int maxmin = max - min;
    if(max == 0){
        maxmin = 1;
    }
    int LUT[256];
    for (int i = 0; i < 256; i++){
        LUT[i]=(int)(1.0*(i - min) * 255 / maxmin);
        if(LUT[i]<0){
            LUT[i] = 0;
        }
        if(LUT[i]>255){
            LUT[i] = 255;
        }
    }
    for (int i = 0; i < image.row * image.col; i++)
    {
        out.matrix[i] = LUT[image.matrix[i]];
    }
    updateHist(&out);
    return out;
}
ImagePgm inversion(ImagePgm image){
    ImagePgm out = EmptyImage(image.row,image.col,image.maxVal);
    for (int i = 0; i < image.row * image.col; i++)
    {
        out.matrix[i] = image.maxVal - image.matrix[i];
    }
    return out;
}
ImagePgm Egalisation_histogramme(ImagePgm image){
    double hn[image.maxVal+1];
    double C[image.maxVal+1];
    for (int i = 0; i <= image.maxVal; i++)
    {
        hn[i] = 1.0*image.hist[i]/(image.row * image.col);
    }
    
    for (int i = 0; i <= image.maxVal; i++)
    {
        C[i] = 0.0;
        for (int j = 0; j <= i; j++)
        {
            C[i] = C[i] + hn[j];
        }        
    }
    ImagePgm out = EmptyImage(image.row,image.col,255);
    for (int i = 0; i < image.col * image.row; i++)
    {
        out.matrix[i] = C[image.matrix[i]] * 255.0;
    }
    updateHist(&out);
    return out;
}
ImagePgm Escalier(ImagePgm image,int pas){
    ImagePgm out = EmptyImage(image.row,image.col,image.maxVal);
    for (int i = 0; i < image.row * image.col; i++)
    {
        out.matrix[i] = (int)(image.matrix[i]/pas)*pas;
    }
    return out;   
}
