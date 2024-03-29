#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/core_c.h>
#include <limits.h>
#include <stdio.h>

void cvBuscar(const IplImage* frame, const IplImage* muestra, int *fM, int *cM, int *difM);
void cvPintar(IplImage* frame, int fM, int cM);

int main(int argc, char** argv){
    
    CvCapture* capture = cvCaptureFromFile(argv[2]);
    IplImage* frame = cvQueryFrame(capture);
    IplImage* muestra  = cvLoadImage(argv[1], 1);
    int fM,cM,difM;
    
    while(frame){
        fM=0, cM=0, difM=INT_MAX;
        cvBuscar(frame,muestra,&fM,&cM,&difM);
        //cvPintar(frame,fM,cM);
        //printf("F:%d - C:%d\n\n",fM,cM);
        cvRectangle(frame,cvPoint((cM/3),fM),cvPoint((cM/3)+48,fM+48),CV_RGB(0,255,255),2,CV_AA,0);
        //cvShowImage("Frame",frame); cvWaitKey(0);
        
        frame = cvQueryFrame(capture);
    }
    
    return EXIT_SUCCESS;
    
}

void cvBuscar(const IplImage* frame, const IplImage* muestra, int *fM, int *cM, int *difM){
    
    uchar *pC, *pM;
    int fI, cI, fC, cC, fAux, difC=0;
    
    for(fI=190; fI < 260; fI+=1){
        for(cI=700; cI< 1000; cI+=1){ difC=0; fAux=0;
            for(fC=fI; fC< fI+48; fC++){
                pC= (uchar *) frame->imageData + fC * frame->widthStep + cI;
                pM= (uchar *) muestra->imageData + fAux * muestra->widthStep; fAux++;
                 for(cC=0; cC<48; cC++){
                    if(*pM==255 && *(pM+1)==255 && *(pM+2)==255){pM+=3; pC+=3;}
                    else{
                        difC += abs(*pM++ - *pC++);
                        difC += abs(*pM++ - *pC++);
                        difC += abs(*pM++ - *pC++);}}}
            if(difC<*difM){
                *difM=difC;
                *fM=fI;
                *cM=cI;}}}
    
}
/*void cvPintar(IplImage* frame, int fM, int cM){
    
    uchar *pintar;
    
    for (int a=fM; a < fM+1; a++){
        for(int i=cM; i < cM+1; i++){
            for(int f=a+24; f < (36+a); f++){
                pintar  = (uchar *) frame->imageData + f * frame->widthStep + i +48;
                for(int c=0; c < 12; c++){
                    *pintar++ = 255;
                    *pintar++ = 255;
                    *pintar++ = 255;}}}}
    
}*/