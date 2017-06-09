#include "FL.h"

//Imagem a ser normalizada, tamanho da região de adjacência a ser levada em consideração
Image* computeNormalization(Image* image){
    
    Image* normalized = createImage(image->nx, image->ny, image->nchannels);
    int iMax = image->channel[0][0], iMin = image->channel[0][0];
    
    //Para cada píxel da imagem original, calcular min e max
    for (int i=0; i < image->ny*image->nx; i++) {
        if(image->channel[0][i] > iMax)
            iMax = image->channel[0][i];
        
        if(image->channel[0][i] < iMin)
            iMin = image->channel[0][i];
    }

    for (int i=0; i < image->ny*image->nx; i++) {
        normalized->channel[0][i] = (image->scalingFactor * (image->channel[0][i] - (float)iMin)) / (float)(iMax-iMin);
        //printf("img: %f norm: %f\n", image->channel[0][i],normalized->channel[0][i]);
    }
    
    return normalized;
}

int main(int argc, char **argv) {
    char             ext[10],*pos;
    
    if (argc != 3) {
        printf("histogram <image.[pgm,ppm]> <adjrelation size>");
        exit(-1);
    }
    
    pos = strrchr(argv[1],'.') + 1;
    sscanf(pos,"%s",ext);

//    if (strcmp(ext,"pgm")==0){
//        Image *grayImage = readImage(argv[1]);
//        destroyImage(&grayImage);
//    } else { /* ppm */
//        Image *colorImage =  readImage(argv[1]);
//        destroyImage(&colorImage);
//    }
    Image* morfo;
    Image* image = readImage(argv[1]);
    
    Image* out = computeNormalization(image);
    
    AdjacencyRelation* adjRel = createCircularAdjacency(atof(argv[2]));
    morfo = morphologicGradient(out,adjRel);
    
    writeImage(morfo, "normalized.pgm");
    
    destroyImage(&image);
    destroyImage(&out);
    
    
    return 0;
}
