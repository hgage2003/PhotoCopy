#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDir>
#include <QFileInfoList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_cbDeleteSrcs_clicked();

    void changeInDir();

    void changeOutDir();

    void on_pbCancel_clicked();

    void on_pbStart_clicked();

private:
    Ui::MainWindow *ui;

    int SaveImage(QString path, QStringList dateTime);
    QFileInfoList fileInfosRecursive(QDir dir, QStringList filters);
    void DeleteEmptyFoldersRecursive(QDir dir);
    QByteArray calcSha1(QString pathToFile);

    void loadSettings();
    void saveSettings();
};

#endif // MAINWINDOW_H
