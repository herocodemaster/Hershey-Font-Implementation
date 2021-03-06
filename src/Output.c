//Display adapter, receives an output image to overlay
//Should be interrupt driven

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "opencv/cv.h"
#include "opencv2/highgui/highgui_c.h"

#include "Config.h"
#include "output.h"

int outputDevice = 0;

int outputGridToDisplay(int8_t grid[][yres]) {
	switch(outputDevice) {
        case 0:
        	outputToConsole(grid);
        break;
        case 1:
        	outputToWindow(grid);
        break;
        default:
        	return -1;
        break;
    }
    return 0;
}

int outputInitialise(int device) {
    outputDevice = device;

    if(outputDevice == 1){
        //Open window, set size etc.
        cvNamedWindow( "OSD", CV_WINDOW_AUTOSIZE );
    }

    return 0;
}

int outputDestroy() {
    switch(outputDevice) {
        case 0:
        break;
        case 1:
        	cvDestroyWindow( "Hershey Font" );
        break;
        default:
        	return -1;
        break;
    }
    return 0;
}

void outputToWindow(int8_t grid[][yres]) {

    //Create image from grid
	IplImage* img = cvCreateImage(cvSize(xres, yres), IPL_DEPTH_8U, 3);

    for(int x=0; x<xres; x++){
    	for(int y=0; y<yres;y++){

            switch(grid[x][y]) {
                case 0:
                	img->imageData[3*(y*img->width+x)+0] = 0;
            		img->imageData[3*(y*img->width+x)+1] = 0;
            		img->imageData[3*(y*img->width+x)+2] = 0;
                break;
                case 1:
                	img->imageData[3*(y*img->width+x)+0] = 255;
            		img->imageData[3*(y*img->width+x)+1] = 255;
            		img->imageData[3*(y*img->width+x)+2] = 255;
                break;
                case -1:
                break;
                default:
                break;
            }
        }
    }

    //Show image in the previously created window
    cvShowImage("OSD", img);
    cvResizeWindow("OSD",xres,yres);
    cvWaitKey(0);
    cvReleaseImage( &img );
}

void outputToConsole(int8_t grid[][yres]) {
    //Console window
    for(int x=0; x<xres; x++) {
        for(int y=0; y<yres; y++){
            printf("%d",grid[x][y]);
        }
        printf("\n");
    }
}
