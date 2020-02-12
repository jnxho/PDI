/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbrir;
    QAction *actionSalir;
    QWidget *centralwidget;
    QFrame *frame;
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *op1;
    QRadioButton *op2;
    QRadioButton *op3;
    QGroupBox *groupBox_2;
    QSlider *rInf;
    QSlider *rSup;
    QSlider *gInf;
    QSlider *gSup;
    QSlider *bInf;
    QSlider *bSup;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QGroupBox *groupBox_3;
    QSlider *desp;
    QFrame *imgBox;
    QLabel *original;
    QFrame *frame_3;
    QLabel *result;
    QFrame *frame_2;
    QLabel *histogramO;
    QFrame *frame_4;
    QLabel *histogramR;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1109, 748);
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName(QString::fromUtf8("actionAbrir"));
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QString::fromUtf8("actionSalir"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 10, 261, 421));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 221, 101));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 20, 87, 77));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        op1 = new QRadioButton(widget);
        op1->setObjectName(QString::fromUtf8("op1"));
        op1->setChecked(true);
        op1->setAutoRepeat(false);

        verticalLayout->addWidget(op1);

        op2 = new QRadioButton(widget);
        op2->setObjectName(QString::fromUtf8("op2"));

        verticalLayout->addWidget(op2);

        op3 = new QRadioButton(widget);
        op3->setObjectName(QString::fromUtf8("op3"));

        verticalLayout->addWidget(op3);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 190, 221, 221));
        rInf = new QSlider(groupBox_2);
        rInf->setObjectName(QString::fromUtf8("rInf"));
        rInf->setGeometry(QRect(50, 50, 160, 16));
        rInf->setOrientation(Qt::Horizontal);
        rSup = new QSlider(groupBox_2);
        rSup->setObjectName(QString::fromUtf8("rSup"));
        rSup->setGeometry(QRect(50, 70, 160, 16));
        rSup->setOrientation(Qt::Horizontal);
        gInf = new QSlider(groupBox_2);
        gInf->setObjectName(QString::fromUtf8("gInf"));
        gInf->setGeometry(QRect(50, 110, 160, 16));
        gInf->setOrientation(Qt::Horizontal);
        gSup = new QSlider(groupBox_2);
        gSup->setObjectName(QString::fromUtf8("gSup"));
        gSup->setGeometry(QRect(50, 130, 160, 16));
        gSup->setOrientation(Qt::Horizontal);
        bInf = new QSlider(groupBox_2);
        bInf->setObjectName(QString::fromUtf8("bInf"));
        bInf->setGeometry(QRect(50, 170, 160, 16));
        bInf->setOrientation(Qt::Horizontal);
        bSup = new QSlider(groupBox_2);
        bSup->setObjectName(QString::fromUtf8("bSup"));
        bSup->setGeometry(QRect(50, 190, 160, 16));
        bSup->setOrientation(Qt::Horizontal);
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 57, 15));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 90, 57, 15));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 150, 57, 15));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 50, 21, 16));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 70, 31, 16));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 130, 31, 16));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 110, 21, 16));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 190, 31, 16));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 170, 21, 16));
        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 120, 221, 61));
        desp = new QSlider(groupBox_3);
        desp->setObjectName(QString::fromUtf8("desp"));
        desp->setGeometry(QRect(20, 30, 160, 16));
        desp->setValue(0);
        desp->setSliderPosition(0);
        desp->setOrientation(Qt::Horizontal);
        imgBox = new QFrame(centralwidget);
        imgBox->setObjectName(QString::fromUtf8("imgBox"));
        imgBox->setGeometry(QRect(290, 10, 401, 421));
        imgBox->setFrameShape(QFrame::StyledPanel);
        imgBox->setFrameShadow(QFrame::Raised);
        original = new QLabel(imgBox);
        original->setObjectName(QString::fromUtf8("original"));
        original->setGeometry(QRect(0, 0, 401, 421));
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(700, 10, 401, 421));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        result = new QLabel(frame_3);
        result->setObjectName(QString::fromUtf8("result"));
        result->setGeometry(QRect(0, 0, 401, 421));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(20, 440, 541, 251));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        histogramO = new QLabel(frame_2);
        histogramO->setObjectName(QString::fromUtf8("histogramO"));
        histogramO->setGeometry(QRect(6, 4, 531, 251));
        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(570, 440, 531, 251));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        histogramR = new QLabel(frame_4);
        histogramR->setObjectName(QString::fromUtf8("histogramR"));
        histogramR->setGeometry(QRect(6, 4, 521, 241));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1109, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbrir->setText(QCoreApplication::translate("MainWindow", "Abrir Ctrl+O", nullptr));
        actionSalir->setText(QCoreApplication::translate("MainWindow", "Salir Q", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Opciones de Histogramas", nullptr));
        op1->setText(QCoreApplication::translate("MainWindow", "Equalizar", nullptr));
        op2->setText(QCoreApplication::translate("MainWindow", "Desplazar", nullptr));
        op3->setText(QCoreApplication::translate("MainWindow", "Rangos", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Ajustes de Color", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Rojo", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Verde", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Azul", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Inf", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Sup", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Sup", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Inf", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Sup", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Inf", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Ajustes Desplazar", nullptr));
        original->setText(QCoreApplication::translate("MainWindow", "                                               original", nullptr));
        result->setText(QCoreApplication::translate("MainWindow", "                                           Resultado", nullptr));
        histogramO->setText(QCoreApplication::translate("MainWindow", "                                                        Histograma Original", nullptr));
        histogramR->setText(QCoreApplication::translate("MainWindow", "                                                   Histograma Resultante", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
