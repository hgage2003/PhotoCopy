#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStringList>
#include <QMediaMetaData>
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>

#include <exiv2/exiv2.hpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbInDir, &QPushButton::clicked, this, &MainWindow::changeInDir);
    connect(ui->pbOutDir, &QPushButton::clicked, this, &MainWindow::changeOutDir);

    ui->lePathIn->setText(QDir::homePath());
    ui->lePathOut->setText(QDir::homePath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cbDeleteSrcs_stateChanged(int arg1)
{
    //TODO: warning message
    Q_UNUSED(arg1)
}

void MainWindow::changeInDir()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(ui->lePathIn->text());
    QStringList fileNames;
    if (dialog.exec()){
        fileNames = dialog.selectedFiles();
        ui->lePathIn->setText(fileNames.first());
    }
}

void MainWindow::changeOutDir()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(ui->lePathOut->text());
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

    QStringList extensions = ui->cbFileExt->currentText().split(QRegExp("[ ,]"),QString::SkipEmptyParts);

    QStringList filters;
    foreach (auto ext, extensions)
        filters.append("*." + ext);

    QFileInfoList fileInfos;

    if ( ui->cbSubdirs->checkState() == Qt::Checked ){
        fileInfos = fileInfosRecursive(inDir, filters);
    }
    else
        fileInfos = inDir.entryInfoList(filters, QDir::Files, QDir::Name);

    foreach (auto info, fileInfos){
        QString path = info.absoluteFilePath();

        Exiv2::Image::AutoPtr image;

#ifdef Q_OS_WIN
        image = Exiv2::ImageFactory::open(path.toStdWString());
#else
        image = Exiv2::ImageFactory::open(path.toStdString());
#endif

        if ( !image.get() ){
            QString error(Q_FUNC_INFO);
            qDebug() << error << ": Can not open image: " << path;
            continue;
        }
        image->readMetadata();

        //qDebug() << info.absoluteFilePath();

        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()){
            QString error(Q_FUNC_INFO);
            qDebug() << error << ": No Exif data found in the file: " + path;
            continue;
        }

        Exiv2::Exifdatum& tag = exifData["Exif.Photo.DateTimeOriginal"];
        QString date = QString::fromStdString(tag.toString());
        //qDebug() << date;
        QStringList dateTime = date.split(QRegExp("[: ]"), QString::SkipEmptyParts);

        SaveImage(path, dateTime);
   }

    QMessageBox msgBox;
    msgBox.setText(tr("Готово!"));
    msgBox.exec();
}

int MainWindow::SaveImage(QString path, QStringList dateTime)
{
    if (dateTime.length() < 6){
        QString error(Q_FUNC_INFO);
        error += ": wrong dateTime in file:" + path + " Exif: ";
        error += dateTime.join(',');
        qDebug() << error;
        return -1;
    }

    QString LibPath = QDir::fromNativeSeparators(ui->lePathOut->text());

    QString libFormat = ui->libraryFormat->currentText();
    libFormat.replace("%Y",dateTime[0],Qt::CaseInsensitive);
    libFormat.replace("%M",dateTime[1],Qt::CaseInsensitive);
    libFormat.replace("%D",dateTime[2],Qt::CaseInsensitive);
    QString filePath = LibPath + '/' + libFormat;

    QDir d;
    if ( !d.mkpath(filePath) ){
        QString error(Q_FUNC_INFO);
        error += ": can not create path to file: ";
        error += filePath;
        qDebug() << error;
        return -1;
    }

	QString fileExt = path.section(".", -1, -1);

	QString fileName = dateTime[0] + '-' + dateTime[1] + '-' + dateTime[2] +
        ' ' + dateTime[3] + '-' + dateTime[4] + '-' + dateTime[5];
    QString fullFilePath = filePath + '/' + fileName + '.' + fileExt;

    if ( QFile::exists(fullFilePath) )
    {
        // compare sha1
        QByteArray shaFrom = calcSha1(path);
        QByteArray shaTo = calcSha1(fullFilePath);

        // error opening
        if ((shaFrom == QByteArray()) ||(shaTo == QByteArray()))
            return -1;

        // if identical
        if (shaFrom == shaTo)
        {
            if (ui->cbDeleteSrcs->checkState() == Qt::Checked)
            {
                QFile::remove(path);
            }
            return 0;
        }

        // if different
        QString oldFileNameWithExt = path.section("/", -1, -1);
        fullFilePath = filePath + '/' + fileName + '_' + oldFileNameWithExt;
    }

    bool bCopy;

    if (ui->cbDeleteSrcs->checkState() == Qt::Checked)
        bCopy = QFile::rename(path, fullFilePath);
    else
        bCopy = QFile::copy(path, fullFilePath);

    if (!bCopy){
        QString error(Q_FUNC_INFO);
        error += ": can not copy file:" + path + " to: ";
        error += fullFilePath;
        qDebug() << error;
        return -1;
    }

    return 0;
}

QFileInfoList MainWindow::fileInfosRecursive(QDir dir, QStringList filters)
{
    QFileInfoList fileInfos = dir.entryInfoList(filters, QDir::Files, QDir::Name);

    QFileInfoList dirInfos = dir.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot, QDir::Name);

    foreach (QFileInfo dirInfo, dirInfos){
        QDir dir(dirInfo.absoluteFilePath());
        fileInfos += fileInfosRecursive(dir, filters);
    }

    return fileInfos;
}

QByteArray MainWindow::calcSha1(QString pathToFile)
{
    QCryptographicHash hash(QCryptographicHash::Sha1);
    QFile file(pathToFile);

    if (file.open(QIODevice::ReadOnly)){
        hash.addData(file.readAll());
    }
    else{
        QString error(Q_FUNC_INFO);
        error +=  ": can not open file " + pathToFile;
        qDebug() << error;
        return QByteArray();
    }

    return hash.result();
}
