#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

// Forward declaration
class QImage;

class ImageHelper
{
public:
    ImageHelper();

    unsigned int calculateOtsuTreshold(unsigned int* histogram, int pixels);
    unsigned int* getHistogram(QImage* image);
    void binarizeImage(QImage* image,int treshold);
};

#endif // IMAGEHELPER_H
