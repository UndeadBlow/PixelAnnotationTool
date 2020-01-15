/**
 * Image Annotation Tool for image annotations with pixelwise masks
 *
 * Author: Rudra Poudel
 */
#ifndef TestWindow_H
#define TestWindow_H

#include <QMainWindow>
#include <QRectF>
#include <QCloseEvent>
#include <QStringList>
#include <QVector>
#include <QList>
#include <QColor>
#include <QScrollArea>
#include <QAbstractListModel>
#include <QTimer>
#include <QtGlobal>

#include <qstringlistmodel.h>

#include "ui_main_window.h"
#include "image_canvas.h"
#include "label_widget.h"
#include "labels.h"

#include "tfwrapper/tensorflow_segmentator.hpp"

constexpr ushort AUTOSAVE_TIME_SECONDS = 180;

const QString VERSION = "v1.3beta";

class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

private:
	
	void loadConfigLabels();
	ImageCanvas * newImageCanvas();
	int getImageCanvas(QString name, ImageCanvas *ic) ;
    ImageCanvas * getImageCanvas(int index);

    void openDirectory();
    QTimer _timer_autosave;

    std::tuple<int, int> getCurrentItemIndecies();

    void loadJSON(const QString& file);

    TensorflowSegmentator *segmentator = nullptr;

public:
	ImageCanvas   *  image_canvas ;
    //std::vector<ImageCanvas*> _image_canvas;
	//QScrollArea   *  scroll_area  ;

	Name2Labels      labels       ;
	Id2Labels        id_labels    ;
	QAction        * save_action  ;
    QAction        * close_tab_action;
	QAction        * undo_action  ;
	QAction        * redo_action  ;

    QAction        * next_image_action  ;
    QAction        * prev_image_action  ;

    QString          curr_open_dir;

public:
	QString currentDir() const;
	QString currentFile() const;
    void updateConnect(ImageCanvas *ic);
    void allDisconnnect(ImageCanvas *ic);
    void runWatershed(ImageCanvas * ic);
    void setStarAtNameOfTab(bool star);
    bool eventFilter(QObject *target, QEvent *event);

public slots:

    void autosave();

    void pickNextImage();
    void pickPrevImage();

	void changeLabel(QListWidgetItem*, QListWidgetItem*);
    void changeColor(QListWidgetItem *item);
	void saveConfigFile();
	void loadConfigFile();
	void runWatershed();
	void on_tree_widget_img_currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);
	void on_actionOpenDir_triggered();
	//void on_actionOpen_jsq_triggered();
	void on_actionAbout_triggered();
	void closeTab(int index);
    void closeCurrentTab();
	void updateConnect(int index);
    void treeWidgetClicked();

private slots:
    void on_button_NeuralNetwork_clicked();
    void on_actionLoad_network_pb_triggered();
};

#endif
