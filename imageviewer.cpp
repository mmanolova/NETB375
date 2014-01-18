#include <QtGui>
#include "imageviewer.h"


 ImageViewer::ImageViewer()
 {

     // Creating new QLabel
     imageLabel = new QLabel;
     imageLabel->setBackgroundRole(QPalette::Base);
     imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
     imageLabel->setScaledContents(true);

     // Creating new QScrollArea
     scrollArea = new QScrollArea;
     scrollArea->setBackgroundRole(QPalette::Dark);
     scrollArea->setWidget(imageLabel);
     setCentralWidget(scrollArea);

     createActions();
     createMenus();
     // Adding the name of the GUI
     setWindowTitle(tr("Image Viewer"));
     resize(500, 400);
}

 void ImageViewer::drawImage()
 {
     // Using the pointer when an image is emplty
     if (m_image->isNull()) {

         return;
     }
     imageLabel->setPixmap(QPixmap::fromImage(*m_image));
 }


 void ImageViewer::open()
 {
     // Opening an image in one of those formats
     m_fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"), " ",
                                     tr("JPEG (*.jpg *,jpeg );; BitMap(*.bmp);; TIF (*.tif);; PNG(*.png)"));
     // Checking if the filename is empty
     if (!m_fileName.isEmpty()) {
         m_image = new QImage(m_fileName);
         drawImage();
         scaleFactor = 1.0;

         // Enabling the functions when an image is opened
         saveAct->setEnabled(true);
         saveAsAct->setEnabled(true);
         blurAct->setEnabled(true);
         grayscaleAct->setEnabled(true);
         sharpenAct->setEnabled(true);
         imageLabel->adjustSize();

     }
 }

 void ImageViewer::save()
  {
      // Checking if the filename is empty
      if (!m_fileName.isEmpty()){
          if (m_image->isNull()) {
               // If the constructor returns a null image a QMessageBox will alert the user
              QMessageBox::information(this, tr("Image Viewer"),
                                       tr("Cannot save %1.").arg(m_fileName));
              return;
          }

          m_image->save(m_fileName);
      }
  }

 void ImageViewer::saveAs()
   {
       QString fileName = QFileDialog::getSaveFileName(this,
                                                       tr("Save Image"), "",
                                                       tr("JPEG (*.jpg *,jpeg );; BitMap(*.bmp);; TIF (*.tif);; PNG(*.png)"));

       if (!fileName.isEmpty()) {


           if (m_image->isNull()) {
               QMessageBox::information(this, tr("Image Viewer"),
                                        tr("Cannot save %1.").arg(fileName));
               return;
           }

           m_image->save(fileName);
       }
   }

  void ImageViewer::grayscale()
  {
      // Variables that'll contain a pixel and its grayscale value
      QRgb pixel;
      int gray;

      // Get its dimensions
      int width = imageLabel->pixmap()->width();
      int height = imageLabel->pixmap()->height();

      // Change each pixel to an grayscale
      for (int i = 0; i < width; ++i)
      {
          for (int j = 0; j < height; ++j)
          {
              pixel = m_image->pixel(i, j);
              gray = qGray(pixel);
              m_image->setPixel(i, j, qRgb(gray, gray, gray));
          }
      }

      // Overwrite the imageLabel with the new grayscale one
      imageLabel->setPixmap(QPixmap::fromImage(*m_image));
  }

 void ImageViewer::blur(){
     QImage * newImage = m_image;


     // the matrix for the blurring
     int kernel [5][5]= {{0,0,1,0,0},
                         {0,1,3,1,0},
                         {1,3,7,3,1},
                         {0,1,3,1,0},
                         {0,0,1,0,0}};
         int kernelSize = 5;
         int sumKernel = 27;

     int r,g,b;
     QColor color;

     for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
         for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

             r = 0;
             g = 0;
             b = 0;


             // The blurring algorithm
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

 void ImageViewer::sharpen(){
     QImage * newImage = m_image;

     // The matrix for the sharpening
        int kernel [5][5]= {
                                     { -1, -1, -1, -1, -1},
                                     {-1,  2,  2,  2, -1},
                                     {-1,  2,  8,  2, -1},
                                     {-1,  2,  2,  2, -1},
                                     {-1, -1, -1, -1, -1}};

          int kernelSize = 5;
          int sumKernel = 10;
     
     int r,g,b;
     QColor color;

     for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
         for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

             r = 0;
             g = 0;
             b = 0;

             // The same algorithm with different matrix
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
      // Connecting the SIGNALS with the SLOTS

      openAct = new QAction(tr("&Open"), this);
      openAct->setShortcut(tr("Ctrl+O"));
      connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

      saveAct = new QAction(tr("Save"), this);
      saveAct->setShortcut(tr("Ctrl+S"));
      saveAct->setEnabled(false);
      connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

      saveAsAct = new QAction(tr("SaveAs"), this);
      saveAsAct->setShortcut(tr("Ctrl+S"));
      saveAsAct->setEnabled(false);
      connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

      blurAct = new QAction(tr("Blur"), this);
      blurAct->setEnabled(false);
      connect(blurAct, SIGNAL(triggered()), this, SLOT(blur()));

      grayscaleAct = new QAction(tr("Grayscale"), this);
      grayscaleAct->setEnabled(false);
      connect(grayscaleAct, SIGNAL(triggered()), this, SLOT(grayscale()));


      sharpenAct = new QAction(tr("Sharpen"), this);
      sharpenAct->setEnabled(false);
      connect(sharpenAct, SIGNAL(triggered()), this, SLOT(sharpen()));

      exitAct = new QAction(tr("E&xit"), this);
      exitAct->setShortcut(tr("Ctrl+Q"));
      connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  }

  void ImageViewer::createMenus()
  {
      // Adding the functions to the Menus

      fileMenu = new QMenu(tr("&File"), this);
      fileMenu->addAction(openAct);
      fileMenu->addAction(saveAct);
      fileMenu->addAction(saveAsAct);
      fileMenu->addSeparator();
      fileMenu->addAction(exitAct);

      editMenu = new QMenu(tr("Edit"), this);
      editMenu->addAction(blurAct);
      editMenu->addAction(grayscaleAct);
      editMenu->addAction(sharpenAct);

      menuBar()->addMenu(fileMenu);
      menuBar()->addMenu(editMenu);

  }
