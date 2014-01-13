#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QScrollArea>
#include <QMenu>
#include <QLabel>
#include <QScrollBar>
#include <QMenuBar>
#include <QtPrintSupport\qprinter.h>
#include <QDialog>
#include <QImage>
#include <QPixmap>

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewer();

private slots:
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();


private:
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    QAction *openAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;


    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *editMenu;
};

#endif
