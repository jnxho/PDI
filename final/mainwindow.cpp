#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
#include <QSpinBox>
#include <cmath>

using namespace cv;
using namespace std;

Mat csv_img;
Mat csv_res;
Mat csv_histo;
Mat Original;
bool img_loaded=false;
int option=-1;
int l=0;
int r=0;
bool ban = false;
int Max[3] = {0}, Min[3] = {0}, maximo[3] = {0}, minimo[3] = {300,300,300};
int H[3][256];
int nRenglones, nColumnas,nCan;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Timer = new QTimer(this);
    createActions();
    //connect(Timer, SIGNAL(timeout()), this, SLOT(DisplayImage()));
    //Timer->start(); //Will start the timer
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::DisplayImage(){
    Mat img;
    img = imread("/home/juan/Documents/Noveno/PDI/Final/test.jpg");
    cv::resize(img, img, Size(512, 384), 0, 0, INTER_LINEAR);
    cv::cvtColor(img,img,cv::COLOR_BGR2RGB);
    QImage imdisplay((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    ui->original->setPixmap(QPixmap::fromImage(imdisplay));
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    for (const QByteArray &mimeTypeName : supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
}

void MainWindow::open()
{
    QFileDialog dialog(this, tr("Abrir"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}
bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }
    //setImage(newImage);

    //setWindowFilePath(fileName);
    csv_img = imread(QDir::toNativeSeparators(fileName).toStdString());
    Mat img2res = csv_img.clone();
    cv::resize(img2res, img2res, Size(512, 384), 0, 0, INTER_LINEAR);
    cv::cvtColor(img2res,img2res,cv::COLOR_BGR2RGB);
    QImage imdisplay((uchar*)img2res.data, img2res.cols, img2res.rows, img2res.step, QImage::Format_RGB888);
    ui->original->setPixmap(QPixmap::fromImage(imdisplay));
    const QString message = tr("Archivo: \"%1\"")
        .arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    setHistograms();
    img_loaded=true;
    return true;
}
void MainWindow::setHistograms(){
    Mat csv_img2;
    cv::cvtColor(csv_img,csv_img2,cv::COLOR_BGR2GRAY);
      int nCanales = csv_img2.channels();
      int nRen = csv_img2.rows;
      int nCol = csv_img2.cols * nCanales;
      Mat resul;
      int maxx=0;
      int cubeta[256];

      fill(begin(cubeta), end(cubeta), 0);

      for(int i = 0; i < nRen; i++){
        uchar * pixel_src = csv_img2.ptr<uchar>(i);
        for(int j  = 0; j < nCol; j+= nCanales){
          cubeta[*(pixel_src + j + 0)] ++;
          if(cubeta[*(pixel_src + j + 0)] > maxx)
            maxx = cubeta[*(pixel_src + j + 0)];
        }
      }

      int dimx = 1024;
      int dimy = 500;
      double dx = dimx / (255*1.0);
      double dy = dimy / (maxx*1.0);
      resul = Mat::zeros(dimy, dimx, CV_8UC1);//Primero se pone lo alto (y) y lueego eje X
      int tam = sizeof cubeta / sizeof *cubeta;
      int xan =  0;
      int yan = (cubeta[0] * dy);

      for(int i = 1; i < tam ; i++){
        int xactual = i * dx;
        int yactual = (cubeta[i] * dy);
        line(resul, Point(xan, dimy-yan), Point(xactual, dimy-yactual), 255);
        xan = xactual;
        yan = yactual;
          //line(resul, Point(i, cubeta[i]), Point(i+1, cubeta[i+1]), CV_RGB(255,0,0), 2, CV_AA);
      }

      for(int i = 0; i < dimy-2; i++){
        uchar *x = resul.ptr<uchar>(i);
        uchar *x2 = resul.ptr<uchar>(i+1);
        for(int j = 0; j < nCol; j+= nCanales){
          if(*(x + j + 0) != 0)
             *(x2 + j+ 0) = 150;
        }
      }
      Mat ho = resul.clone();
      cv::resize(ho, ho, Size(600, 300), 0, 0, INTER_LINEAR);
      cv::cvtColor(ho,ho,cv::COLOR_GRAY2RGB);
      QImage imdisplay((uchar*)ho.data, ho.cols, ho.rows, ho.step, QImage::Format_RGB888);
      ui->histogramO->setPixmap(QPixmap::fromImage(imdisplay));
      int nHisto[256];

      fill(begin(nHisto), end(nHisto), 0);
      int sum = 0;
      double aux = 255.0/(nRen*nCol);
      for (int i = 0; i < 256; i++){
        sum+=cubeta[i];
        nHisto[i] = (int)round(sum*aux);
      }

      Mat res = Mat::zeros(nRen, nCol,CV_8UC1 );
      for(int i = 0; i < nRen; i++){
        uchar * pixel_src = csv_img2.ptr<uchar>(i);
        uchar * pixel_res = res.ptr<uchar>(i);
        for(int j  = 0; j < nCol; j+= nCanales){
          *(pixel_res + j + 0) = (nHisto[*(pixel_src + j + 0)]);
        }
      }
      cv::resize(res, res, Size(512, 384), 0, 0, INTER_LINEAR);
      cv::cvtColor(res,res,cv::COLOR_GRAY2RGB);
      QImage imdisplayr((uchar*)res.data, res.cols, res.rows, res.step, QImage::Format_RGB888);
      ui->result->setPixmap(QPixmap::fromImage(imdisplayr));
      fill(begin(cubeta), end(cubeta), 0);
      for(int i = 0; i < nRen; i++){
        uchar * pixel_src = res.ptr<uchar>(i);
        for(int j  = 0; j < nCol; j+= nCanales){
          cubeta[*(pixel_src + j + 0)] ++;
          if(cubeta[*(pixel_src + j + 0)] > maxx)
            maxx = cubeta[*(pixel_src + j + 0)];
        }
      }

       dimx = 1024;
       dimy = 500;
       dx = dimx / (255*1.0);
       dy = dimy / (maxx*1.0);
       resul = Mat::zeros(dimy, dimx, CV_8UC1);//Primero se pone lo alto (y) y lueego eje X
       xan =  0;
       yan = (cubeta[0] * dy);
      for(int i = 1; i < tam ; i++){
        int xactual = i * dx;
        int yactual = (cubeta[i] * dy);
        line(resul, Point(xan, dimy-yan), Point(xactual, dimy-yactual), 255);
        xan = xactual;
        yan = yactual;
          //line(resul, Point(i, cubeta[i]), Point(i+1, cubeta[i+1]), CV_RGB(255,0,0), 2, CV_AA);
      }

      for(int i = 0; i < dimy-2; i++){
        uchar *x = resul.ptr<uchar>(i);
        uchar *x2 = resul.ptr<uchar>(i+1);
        for(int j = 0; j < nCol; j+= nCanales){
          if(*(x + j + 0) != 0)
             *(x2 + j+ 0) = 150;
        }
      }
      cv::resize(resul, resul, Size(600, 300), 0, 0, INTER_LINEAR);
      cv::cvtColor(resul,resul,cv::COLOR_GRAY2RGB);
      QImage imdisplay2((uchar*)resul.data, resul.cols, resul.rows, resul.step, QImage::Format_RGB888);
      ui->histogramR->setPixmap(QPixmap::fromImage(imdisplay2));
}

Mat MainWindow::setHistoMove(Mat original){
      int nCanales = original.channels();
      int nRen = original.rows;
      int nCol = original.cols * nCanales;
      Mat resul;
      int maxx=0;
      int cubeta[256];
      fill(begin(cubeta), end(cubeta), 0);
      for(int i = 0; i < nRen; i++){
        uchar * pixel_src = original.ptr<uchar>(i);
        for(int j  = 0; j < nCol; j+= nCanales){
          cubeta[*(pixel_src + j + 0)] ++;
          if(cubeta[*(pixel_src + j + 0)] > maxx)
            maxx = cubeta[*(pixel_src + j + 0)];
        }
      }
      if (ban==false)
      {
        for (int i = 0; i < 256; i++){
        if (cubeta[i]!=0){
          break;
        }else
        {
          l++;
        }
      }
      for (int i = 255; i >=0; i--){
        if (cubeta[i]!=0){
          break;
        }else
        {
          r++;
        }
      }
      ban = true;
      }

      int dimx = 1024;
      int dimy = 500;
      double dx = dimx / (255*1.0);
      double dy = dimy / (maxx*1.0);
      resul = Mat::zeros(dimy, dimx, CV_8UC1);//Primero se pone lo alto (y) y lueego eje X
      int tam = sizeof cubeta / sizeof *cubeta;
      int xan =  0;
      int yan = (cubeta[0] * dy);
      for(int i = 1; i < tam ; i++){
        int xactual = i * dx;
        int yactual = (cubeta[i] * dy);
        line(resul, Point(xan, dimy-yan), Point(xactual, dimy-yactual), 255);
        xan = xactual;
        yan = yactual;
          //line(resul, Point(i, cubeta[i]), Point(i+1, cubeta[i+1]), CV_RGB(255,0,0), 2, CV_AA);
      }

      for(int i = 0; i < dimy-2; i++){
        uchar *x = resul.ptr<uchar>(i);
        uchar *x2 = resul.ptr<uchar>(i+1);
        for(int j = 0; j < nCol; j+= nCanales){
          if(*(x + j + 0) != 0)
             *(x2 + j+ 0) = 150;
        }
      }
      return resul;
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Archivo"));
    QAction *openAct = fileMenu->addAction(tr("&Abrir..."), this, &MainWindow::open);
    openAct->setShortcut(QKeySequence::Open);
}

void MainWindow::on_op1_clicked()
{
    if(img_loaded){
        option = 1;
        setHistograms();
    }
}

void MainWindow::on_op2_clicked()
{
    if(img_loaded){
        option = 2;
        Mat original;
        cv::cvtColor(csv_img,original,cv::COLOR_BGR2GRAY);
        Mat res = original.clone();
        cv::resize(res, res, Size(512, 384), 0, 0, INTER_LINEAR);
        cv::cvtColor(res,res,cv::COLOR_GRAY2RGB);
        QImage imdisplayr((uchar*)res.data, res.cols, res.rows, res.step, QImage::Format_RGB888);
        ui->result->setPixmap(QPixmap::fromImage(imdisplayr));
        Mat resul = setHistoMove(original);
        cv::resize(resul, resul, Size(600, 300), 0, 0, INTER_LINEAR);
        cv::cvtColor(resul,resul,cv::COLOR_GRAY2RGB);
        QImage imdisplay2((uchar*)resul.data, resul.cols, resul.rows, resul.step, QImage::Format_RGB888);
        ui->histogramO->setPixmap(QPixmap::fromImage(imdisplay2));
        ui->histogramR->setPixmap(QPixmap::fromImage(imdisplay2));
        ui->desp->setRange(0,l+r);
        ui->desp->setSliderPosition(l);
        ui->bInf->setRange(0,255);
        ui->bInf->setSliderPosition(0);
        ui->bSup->setRange(0,255);
        ui->bSup->setSliderPosition(0);
        ui->gInf->setRange(0,255);
        ui->gInf->setSliderPosition(0);
        ui->gSup->setRange(0,255);
        ui->gSup->setSliderPosition(0);
        ui->rInf->setRange(0,255);
        ui->rInf->setSliderPosition(0);
        ui->rSup->setRange(0,255);
        ui->rSup->setSliderPosition(0);
    }
}

void MainWindow::on_op3_clicked()
{
    if(img_loaded){
        option = 3;
        Original = csv_img.clone();
         nRenglones = Original.rows;
         nCan = Original.channels();
         nColumnas = Original.cols * Original.channels();

        int i, j,k;
        for(k=0;k<3;k++){
            for(j=0; j<nRenglones; j++){
                uchar *renglon = Original.ptr<uchar>(j);
                for(i=0; i<nColumnas; i+=nCan){
                    H[k][*(renglon+i+k)]++;
                }
            }

            for(i=0; i<256; i++){
                if(H[k][i]<minimo[k]) minimo[k]=H[k][i];
                if(H[k][i]>maximo[k]) maximo[k]=H[k][i];
            }
        }
        Mat img2res = Original.clone();
        cv::resize(img2res, img2res, Size(512, 384), 0, 0, INTER_LINEAR);
        cv::cvtColor(img2res,img2res,cv::COLOR_BGR2RGB);
        QImage imdisplay((uchar*)img2res.data, img2res.cols, img2res.rows, img2res.step, QImage::Format_RGB888);
        ui->result->setPixmap(QPixmap::fromImage(imdisplay));
        ui->bInf->setRange(0,255);
        ui->bInf->setSliderPosition(0);
        ui->bSup->setRange(0,255);
        ui->bSup->setSliderPosition(0);
        ui->gInf->setRange(0,255);
        ui->gInf->setSliderPosition(0);
        ui->gSup->setRange(0,255);
        ui->gSup->setSliderPosition(0);
        ui->rInf->setRange(0,255);
        ui->rInf->setSliderPosition(0);
        ui->rSup->setRange(0,255);
        ui->rSup->setSliderPosition(0);
        ui->desp->setRange(0,l+r);
        ui->desp->setSliderPosition(l);
    }
}

void MainWindow::on_desp_sliderMoved(int inc)
{
    if(option==2){
        Mat src;
        cv::cvtColor(csv_img,src,cv::COLOR_BGR2GRAY);
        inc =  inc-l;
        //Image data
        int nCanales = src.channels();
        int nRen = src.rows;
        int nCol = src.cols * nCanales;
        //Result images
        Mat res;
        //Original Histogram
        res = Mat::zeros(nRen,nCol,src.type());

        for(int i2 = 0; i2 < nRen; i2++){
          uchar * renglong = res.ptr <uchar>(i2);
          uchar * ren = src.ptr <uchar>(i2);
          for( int j = 0; j < nCol; j += nCanales ){
            if ((*(ren + j) + inc)<255)
              *(renglong + j) = *(ren + j) + inc;
          }
        }


        Mat histo = setHistoMove(res);
        cv::resize(histo, histo, Size(600, 300), 0, 0, INTER_LINEAR);
        cv::cvtColor(histo,histo,cv::COLOR_GRAY2RGB);
        QImage imdisplay2((uchar*)histo.data, histo.cols, histo.rows, histo.step, QImage::Format_RGB888);
        ui->histogramR->setPixmap(QPixmap::fromImage(imdisplay2));

        cv::resize(res, res, Size(512, 384), 0, 0, INTER_LINEAR);
        cv::cvtColor(res,res,cv::COLOR_GRAY2RGB);
        QImage imdisplayr((uchar*)res.data, res.cols, res.rows, res.step, QImage::Format_RGB888);
        ui->result->setPixmap(QPixmap::fromImage(imdisplayr));
    }
}
void MainWindow::on_rInf_sliderMoved(int position)
{
    if(option==3){
        Min[0] = position;
        histo(Min[0], 0);
    }
}

void MainWindow::on_rSup_sliderMoved(int position)
{
    if(option==3){
        Max[0] = position;
        histo(Max[0], 0);
    }
}

void MainWindow::on_gInf_sliderMoved(int position)
{
    if(option==3){
        Min[1] = position;
        histo(Min[1], 0);
    }
}

void MainWindow::on_gSup_sliderMoved(int position)
{
    if(option==3){
        Max[1] = position;
        histo(Max[1], 0);
    }
}

void MainWindow::on_bInf_sliderMoved(int position)
{
    if(option==3){
        Min[2] = position;
        histo(Min[2], 0);
    }
}

void MainWindow::on_bSup_sliderMoved(int position)
{
    if(option==3){
        Max[2] = position;
        histo(Max[2], 0);
    }
}
void MainWindow::segmentacion() {
    Mat img_seg = Mat(nRenglones, nColumnas/3, CV_8UC3, cv::Scalar::all(255));
    for (int j = 0; j < nRenglones; j++) {
        uchar* Ori = Original.ptr<uchar>(j);
        uchar* Nuevo = img_seg.ptr<uchar>(j);
        for (int i = 0; i < nColumnas; i+=nCan) {
            if (((*(Ori + i) >= Min[0]) && (*(Ori + i) <= Max[0])) && ((*(Ori + i+1) >= Min[1]) && (*(Ori + i+1) <= Max[1])) && ((*(Ori + i+2) >= Min[2]) && (*(Ori + i+2) <= Max[2]))) {
                *(Nuevo + (i ) + 0) = *(Ori + (i ) + 0);
                *(Nuevo + (i ) + 1) = *(Ori + (i ) + 1);
                *(Nuevo + (i ) + 2) = *(Ori + (i ) + 2);
            }
            else {
                *(Nuevo + (i) + 0) = *(Ori + i);
                *(Nuevo + (i) + 1) = *(Ori + i);
                *(Nuevo + (i) + 2) = *(Ori + i);
            }
        }
    }

    //imshow("Segmentacion", img_seg);
    Mat res = img_seg.clone();
    cv::resize(res, res, Size(512, 384), 0, 0, INTER_LINEAR);
    cv::cvtColor(res,res,cv::COLOR_BGR2RGB);
    QImage imdisplayr((uchar*)res.data, res.cols, res.rows, res.step, QImage::Format_RGB888);
    ui->result->setPixmap(QPixmap::fromImage(imdisplayr));
}

void MainWindow::histo(int, void*) {
    cv::Mat grafica = cv::Mat(900, 1580, CV_8UC3, cv::Scalar::all(0));
    for(int k=0;k<3;k++){
        int kk=0;
        for (int i = 0; i < 256; i++) {
            int x = (((float)H[k][i] - (float)minimo[k]) / ((float)maximo[k] - (float)minimo[k])) * 99.0;

            if (i >= Min[k] && i <= Max[k]) {
                cv::line(grafica, cv::Point(i+20+kk, (256*(k+1))), cv::Point(i+20+kk, (256*(k+1))-x), Scalar(0,0,255), 2);
            }
            else {
                cv::line(grafica, cv::Point(i+20+kk, (256*(k+1))), cv::Point(i+20+kk, (256*(k+1))-x), Scalar(50*(k+1),150,70*(k+1)), 2);
            }
            kk+=5;
        }
    }
    //imshow("grafica", grafica);
    Mat histog = grafica.clone();
    cv::resize(histog, histog, Size(600, 300), 0, 0, INTER_LINEAR);
    cv::cvtColor(histog,histog,cv::COLOR_BGR2RGB);
    QImage imdisplay2((uchar*)histog.data, histog.cols, histog.rows, histog.step, QImage::Format_RGB888);
    ui->histogramR->setPixmap(QPixmap::fromImage(imdisplay2));
    segmentacion();
}
