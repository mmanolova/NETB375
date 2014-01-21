#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
#include <QScrollArea>
#include <QMenu>
#include <QLabel>
#include <QScrollBar>
#include <QMenuBar>
#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QDebug>

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
    void drawImage();
private slots:

    void open();
    void save();
    void saveAs();
    void grayscale();
    void blur();
    void sharpen();
    void otsu();

private:
    void createActions();
    void createMenus();
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *grayscaleAct;
    QAction *otsuAct;
    QAction *exitAct;
    QAction *blurAct;
    QAction *sharpenAct;
    QMenu   *fileMenu;
    QMenu   *editMenu;
    QImage   *m_image;
    QString   m_fileName;
};

#endif
