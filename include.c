#include "include.h"
int *allocateMatrix(int row, int col){
    int *matrix;
    matrix = malloc(row * col * sizeof(int));
    return matrix;
}
void freeMatrix(int *matrix){
    free(matrix);
}
int getHeader(FILE *f){
    int c=0,tmp=0;
    c = fgetc(f);
    while (c != EOF)
    {
        if(c == '\n'){
            return tmp;
        }
        tmp = c;
        c = fgetc(f);
    }
    return 0;
}
int getNextInt(FILE *f){
    int a = -1;
    fscanf(f,"%d",&a);
    return a;
}
ImagePgm ReadImage(char *img){
    ImagePgm image;
    FILE *f = NULL;
    f = fopen(img,"r");
    int c = 0;
    int r = 0;
    int m = 0;
    char h;
    if(f != NULL){


        c = getHeader(f);
        c = getNextInt(f);
        r = getNextInt(f);
        m = getNextInt(f);
        
        image = EmptyImage(r,c,m);
        image.matrix = allocateMatrix(image.col, image.row);
        image.hist = malloc((image.maxVal + 1) * sizeof(int));
        for (int i = 0; i < image.col * image.row; i++)
        {
            image.matrix[i] = getNextInt(f);
        }
    }
    fclose(f);
    return image;
}
ImagePgm EmptyImage(int row,int col, int max){
    ImagePgm image;
    image.matrix = allocateMatrix(row, col);
    image.hist = malloc((max + 1) * sizeof(int));
    for (int i = 0; i < row * col; i++){
        image.matrix[i] = 0;
    }
    for (int i = 0; i < max; i++){
        image.hist[i] = 0;
    }
    image.row = row;
    image.col = col;
    image.maxVal = max;
    return image;
}
void printImageMatrix(ImagePgm image){
    printf("\nAffichage\n");
    int n;
    for(int i = 0; i<image.col * image.row; i++){
        n = image.matrix[i];
        if(i % image.col == 0){
            printf("\n");
            printf("%d\n",i);
        }
        if(n < 10){
            printf("  %d",n);
        }else if(n < 100){
            printf(" %d",n);
        }else if(n < 256){
            printf(" %d",n);
        }else{
            printf(" 255");
        }
    }
}
void saveImagePGM(char *filename,ImagePgm image){
    FILE *f = NULL;
    f = fopen(filename, "w");
    if (f == NULL) {
        perror("cannot open file to read");
        exit(EXIT_FAILURE);
    }
    fprintf(f,"P2\n");
    fprintf(f,"%d %d\n",image.col,image.row);
    fprintf(f,"%d\n",image.maxVal);
    int n;
    for(int i = 0; i<image.col * image.row; i++){
        n = image.matrix[i];
        if(i % image.col == 0){
            fprintf(f,"\n");
        }
        if(n < 10){
            fprintf(f,"   %d",n);
        }else if(n < 100){
            fprintf(f,"  %d",n);
        }else if(n < 1000){
            fprintf(f," %d",n);
        }
    }
    fclose(f);
}
void updateHist(ImagePgm *image){
    for (int i = 0; i < image->maxVal+1; i++){
        image->hist[i] = 0;
    }
    for (int i = 0; i < image->row * image->col; i++){
        image->hist[image->matrix[i]] += 1;
    }
}
