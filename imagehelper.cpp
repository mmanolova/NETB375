#include "imagehelper.h"
#include "imageviewer.h"
#include "iostream"

ImageHelper::ImageHelper()
{

}

unsigned int* ImageHelper::getHistogram(QImage* image)
{
    if(!image)
        return NULL;

    unsigned int* histogram = new unsigned int[256];
    int sum = 0;
    for (int i = 1; i < 256; ++i)
        histogram[i] = 0;
    for ( int row = 0; row < image->height(); ++row )
        for ( int col = 0; col < image->width(); ++col )
        {
            QColor clrCurrent( image->pixel( col, row) );
            // Pretty much any of the 3 colors will do.
            histogram[clrCurrent.red()]++;

        }

    return &histogram[0];
}

unsigned int ImageHelper::calculateOtsuTreshold(unsigned int* histData, int pixels)
{

    // Total number of pixels
    int total = pixels;

    float sum = 0;
    for (int t=0 ; t<256 ; t++) sum += t * histData[t];

    float sumB = 0;
    int wB = 0;
    int wF = 0;

    float varMax = 0;
    int threshold = 0;

    for (int t=0 ; t<256 ; t++) {
       wB += histData[t];               // Weight Background
       if (wB == 0) continue;

       wF = total - wB;                 // Weight Foreground
       if (wF == 0) break;

       sumB += (float) (t * histData[t]);

       float mB = sumB / wB;            // Mean Background
       float mF = (sum - sumB) / wF;    // Mean Foreground

       // Calculate Between Class Variance
       float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

       // Check if new maximum found
       if (varBetween > varMax) {
          varMax = varBetween;
          threshold = t;
       }
    }


    return threshold;
}
void ImageHelper::binarizeImage(QImage* image,int treshold)
{
    std::cout << "Width: " << image->width() << "Treshold " << treshold << std::endl;
    for ( int row = 0; row < image->height(); ++row )
        for ( int col = 0; col < image->width(); ++col )
        {
            //std::cout << "Scale " <<
            QColor pixel( image->pixel( col, row) );
            if(pixel.red() < treshold){
                QRgb color = qRgb(0, 0, 0);
                image->setPixel(col, row, color);
            }else{
                QRgb color = qRgb(255, 255, 255);
                image->setPixel(col, row, color); // Yep, thats the value.
            }

        }
}
