#include "mainwindow.h"
#include <QCommandLineParser>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QGuiApplication::setApplicationDisplayName(MainWindow::tr("Histogramas"));
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(MainWindow::tr("[Archivo]"), MainWindow::tr("Image a abrir."));
    commandLineParser.process(QCoreApplication::arguments());
    MainWindow imageViewer;
    if (!commandLineParser.positionalArguments().isEmpty()
       && !imageViewer.loadFile(commandLineParser.positionalArguments().front())) {
       return -1;
    }

    w.show();
    return a.exec();
}
