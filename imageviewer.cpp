#include <QtGui>

#include "imageviewer.h"



#include <QDebug>


 ImageViewer::ImageViewer()
 {
     imageLabel = new QLabel;
     imageLabel->setBackgroundRole(QPalette::Base);
     imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel->setScaledContents(true);

     scrollArea = new QScrollArea;
     scrollArea->setBackgroundRole(QPalette::Dark);
     scrollArea->setWidget(imageLabel);
     setCentralWidget(scrollArea);

     createActions();
     createMenus();

     setWindowTitle(tr("Image Viewer"));
     resize(500, 400);

}

 void ImageViewer::drawImage()
 {
     if (m_image->isNull()) {

         return;
     }
     imageLabel->setPixmap(QPixmap::fromImage(*m_image));
 }

 void ImageViewer::open()
 {
     QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), " ",
                                     tr("JPEG (*.jpg *,jpeg );; BitMap(*.bmp);; TIF (*.tif);; PNG(*.png)"));
     if (!fileName.isEmpty()) {
         m_image = new QImage(fileName);
         drawImage();
         scaleFactor = 1.0;

         blurAct->setEnabled(true);
         sharpenAct->setEnabled(true);

             imageLabel->adjustSize();
     }
 }



 void ImageViewer::blur()
     {
     qDebug() << "aklsjdskld";
/*
     // Variables that'll contain a pixel and its grayscale value
          QRgb pixel;
          int blur;

          // convert the pixmap the imageLabel to an QImage
          QImage image = imageLabel->pixmap()->toImage();

          // Get its dimensions
          int width = imageLabel->pixmap()->width();
          int height = imageLabel->pixmap()->height();
          int max_length = (i -1);

              for (int j = 0; j < height; ++j)
              {
                  pixel = image.pixel(j, i);
                  blur = qBlur(pixel);
                  for ( int i = 1; i < MAX_LENGTH; i = i + 2 )
                   { Blur( width, height, Size( i, i ), 0, 0 );
                     if( hight( DELAY_BLUR ) != 0 ) { return 0; } }

        }
           // Overwrite the imageLabel with the new grayscale one
           imageLabel->setPixmap(QPixmap::fromImage(image));
       }



*/

 }

 void ImageViewer::sharpen(){
     QImage * newImage = m_image;

     int kernel [3][3]= {{0,-1,0},
                         {-1,5,-1},
                         {0,-1,0}};
     int kernelSize = 3;
     int sumKernel = 1;
     int r,g,b;
     QColor color;

     for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
         for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

             r = 0;
             g = 0;
             b = 0;

             for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                 for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                     color = QColor(m_image->pixel(x+i, y+j));
                     r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                     g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                     b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                 }
             }

             r = qBound(0, r/sumKernel, 255);
             g = qBound(0, g/sumKernel, 255);
             b = qBound(0, b/sumKernel, 255);

             newImage->setPixel(x,y, qRgb(r,g,b));

         }
     }
     drawImage();
 }

  void ImageViewer::createActions()
  {
      openAct = new QAction(tr("&Open"), this);
      openAct->setShortcut(tr("Ctrl+O"));
      connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

      blurAct = new QAction(tr("Blur"), this);
      blurAct->setEnabled(false);
      connect(blurAct, SIGNAL(triggered()), this, SLOT(blur()));

      sharpenAct = new QAction(tr("Sharpen"), this);
      sharpenAct->setEnabled(false);
      connect(sharpenAct, SIGNAL(triggered()), this, SLOT(sharpen()));

      exitAct = new QAction(tr("E&xit"), this);
      exitAct->setShortcut(tr("Ctrl+Q"));
      connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  }

  void ImageViewer::createMenus()
  {
      fileMenu = new QMenu(tr("&File"), this);
      fileMenu->addAction(openAct);
      fileMenu->addSeparator();
      fileMenu->addAction(exitAct);

      editMenu = new QMenu(tr("Edit"), this);
      editMenu->addAction(blurAct);
      editMenu->addAction(sharpenAct);

      menuBar()->addMenu(fileMenu);
      menuBar()->addMenu(editMenu);

  }
