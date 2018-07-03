#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStringList>
#include <QMediaMetaData>
#include <QDebug>
#include <QMessageBox>

#include <exiv2/exiv2.hpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lePathIn->setText(QDir::homePath());
    ui->lePathOut->setText(QDir::homePath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cbDeleteSrcs_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
}

void MainWindow::on_pbChangeInDir_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QDir::homePath());
    QStringList fileNames;
    if (dialog.exec()){
        fileNames = dialog.selectedFiles();
        ui->lePathIn->setText(fileNames.first());
    }
}

void MainWindow::on_pbChangeOutDir_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QDir::homePath());
    QStringList fileNames;
    if (dialog.exec()){
        fileNames = dialog.selectedFiles();
        ui->lePathOut->setText(fileNames.first());
    }
}

void MainWindow::on_pbCancel_clicked()
{
    this->close();
}

void MainWindow::on_pbStart_clicked()
{
    QDir inDir(ui->lePathIn->text());
    QFileInfoList fileInfos;

    if ( ui->cbSubdirs->checkState() == Qt::Checked ){
        fileInfos = fileInfosRecursive(inDir);
    }
    else
        fileInfos = inDir.entryInfoList(QDir::Files);

    QStringList extensions = ui->cbFileExt->currentText().split(QRegExp("[ ,]"),QString::SkipEmptyParts); //(QStringList() << "JPG" << "JPEG");

    foreach (QFileInfo info, fileInfos)
      if ( extensions.contains( info.completeSuffix(), Qt::CaseInsensitive ) )
      {
		  std::wstring path = info.absoluteFilePath().toStdWString();         // <--- get the path
		  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path);    // <--- open it

          if ( !image.get() ){
              std::wstring error(path);
              qDebug() << QString::fromStdWString(error) << ": Can not open image";
			  continue;
          }
          image->readMetadata();

          //qDebug() << info.absoluteFilePath();

          Exiv2::ExifData &exifData = image->exifData();
           if (exifData.empty()) {
               std::wstring error(path);
               qDebug() << QString::fromStdWString(error) << ": No Exif data found in the file";
               continue;
           }

           Exiv2::Exifdatum& tag = exifData["Exif.Photo.DateTimeOriginal"];
           QString date = QString::fromStdString(tag.toString());
           //qDebug() << date;
           QStringList dateTime = date.split(QRegExp("[: ]"), QString::SkipEmptyParts);

           SaveImage(QString::fromStdWString(path), dateTime);
      }

    QMessageBox msgBox;
    msgBox.setText("Done!");
    msgBox.exec();
}

int MainWindow::SaveImage(QString path, QStringList dateTime)
{
    if (dateTime.length() < 6){
        QString error(path);
        error += ": wrong dateTime in Exif: ";
        error += dateTime.join(',');
        qDebug() << error;
        return -1;
    }

    QString LibPath = QDir::fromNativeSeparators(ui->lePathOut->text());
	QString filePath = LibPath + "/PhotoCopy/" + dateTime[0] + '/' + dateTime[1];// +'/' + dateTime[2];

    QDir d;
    if ( !d.mkpath(filePath) ){
        QString error(path);
        error += ": can not create path to file: ";
        error += filePath;
        qDebug() << error;
        return -1;
    }

	QString fileExt = path.section(".", -1, -1);

	QString fileName = dateTime[0] + '-' + dateTime[1] + '-' + dateTime[2] +
		' ' + dateTime[3] + '-' + dateTime[4] + '-' + dateTime[5];//path.section("/",-1,-1);
    filePath += '/' + fileName + '.' + fileExt;

	bool bCopy;
	if (ui->cbDeleteSrcs->checkState() == Qt::Checked)
		bCopy = QFile::rename(path, filePath);
	else
		bCopy = QFile::copy(path, filePath);

    if (!bCopy){
        QString error(path);
        error += ": can not copy file to: ";
        error += filePath;
        qDebug() << error;
        return -1;
    }

    return 0;
}

QFileInfoList MainWindow::fileInfosRecursive(QDir dir)
{
    QFileInfoList fileInfos = dir.entryInfoList(QDir::Files);

    QFileInfoList dirInfos = dir.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);

    foreach (QFileInfo dirInfo, dirInfos){
        QDir dir(dirInfo.absoluteFilePath());
        fileInfos += fileInfosRecursive(dir);
    }

    return fileInfos;
}
