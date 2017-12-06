#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <cv.h>
#include <highgui.h>

GtkBuilder * builderG;
#define MAXFFBUFFER 1000
typedef struct {
  int count;
  double x[MAXFFBUFFER];
  double y[MAXFFBUFFER];
} free_form;

#if defined (_MAIN_C_)
        GtkBuilder *builderG;
        double xoffG=100;
        double yoffG=150;
	double fontSizeFactorG=1;
        free_form ffG={0};   //init count to zero. Do not affect x and y.
	IplImage *dst_imageG , *src_imageG;
        CvCapture *captureG;	
#else
        extern GtkBuilder *builderG;
        extern double xoffG;
        extern double yoffG;
	extern double fontSizeFactorG;
        extern free_form ffG;
	extern IplImage *dst_imageG , *src_imageG;
        extern CvCapture *captureG;
#endif

#include "prototypes.h"
