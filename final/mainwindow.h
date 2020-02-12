#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv4/opencv2/opencv.hpp>
#include "opencv4/opencv2/imgproc/imgproc.hpp"
#include "opencv4/opencv2/highgui/highgui.hpp"
#include "opencv4/opencv2/core/core.hpp"
using namespace  std;
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:    // A slot or function is defined which will be intiated by timer
    void DisplayImage();
    void open();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool loadFile(const QString &);
    QImage imdisplay;  //This will create QImage which is shown in Qt label
    QTimer* Timer;   // A timer is needed in GUI application


private slots:
    void on_op1_clicked();

    void on_op2_clicked();

    void on_op3_clicked();

    void on_rInf_sliderMoved(int position);

    void on_rSup_sliderMoved(int position);

    void on_gInf_sliderMoved(int position);

    void on_gSup_sliderMoved(int position);

    void on_bInf_sliderMoved(int position);

    void on_bSup_sliderMoved(int position);

    void on_desp_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QImage image;
    void createActions();
    void createMenus();
    void setImage(const QImage &newImage);
    void setHistograms();
    Mat setHistoMove(Mat);
    void histo(int, void*);
    void segmentacion();
};
#endif // MAINWINDOW_H
