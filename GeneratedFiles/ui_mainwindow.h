/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *lePathOut;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QPushButton *pbChangeInDir;
    QLineEdit *lePathIn;
    QPushButton *pbChangeOutDir;
    QCheckBox *cbSubdirs;
    QCheckBox *cbDeleteSrcs;
    QPushButton *pbStart;
    QPushButton *pbCancel;
    QComboBox *cbFileExt;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(383, 299);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 2);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        lePathOut = new QLineEdit(centralWidget);
        lePathOut->setObjectName(QStringLiteral("lePathOut"));

        gridLayout->addWidget(lePathOut, 3, 2, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        pbChangeInDir = new QPushButton(centralWidget);
        pbChangeInDir->setObjectName(QStringLiteral("pbChangeInDir"));

        gridLayout->addWidget(pbChangeInDir, 1, 4, 1, 2);

        lePathIn = new QLineEdit(centralWidget);
        lePathIn->setObjectName(QStringLiteral("lePathIn"));

        gridLayout->addWidget(lePathIn, 1, 2, 1, 2);

        pbChangeOutDir = new QPushButton(centralWidget);
        pbChangeOutDir->setObjectName(QStringLiteral("pbChangeOutDir"));

        gridLayout->addWidget(pbChangeOutDir, 3, 4, 1, 2);

        cbSubdirs = new QCheckBox(centralWidget);
        cbSubdirs->setObjectName(QStringLiteral("cbSubdirs"));

        gridLayout->addWidget(cbSubdirs, 2, 2, 1, 4);

        cbDeleteSrcs = new QCheckBox(centralWidget);
        cbDeleteSrcs->setObjectName(QStringLiteral("cbDeleteSrcs"));
        cbDeleteSrcs->setEnabled(false);

        gridLayout->addWidget(cbDeleteSrcs, 4, 2, 1, 3);

        pbStart = new QPushButton(centralWidget);
        pbStart->setObjectName(QStringLiteral("pbStart"));

        gridLayout->addWidget(pbStart, 6, 3, 1, 3);

        pbCancel = new QPushButton(centralWidget);
        pbCancel->setObjectName(QStringLiteral("pbCancel"));

        gridLayout->addWidget(pbCancel, 6, 0, 1, 2);

        cbFileExt = new QComboBox(centralWidget);
        cbFileExt->addItem(QString());
        cbFileExt->addItem(QString());
        cbFileExt->setObjectName(QStringLiteral("cbFileExt"));
        cbFileExt->setEnabled(false);
        cbFileExt->setEditable(true);

        gridLayout->addWidget(cbFileExt, 0, 2, 1, 4);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PhotoCopy", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\262", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\242\320\270\320\277\321\213 \321\204\320\260\320\271\320\273\320\276\320\262", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\320\260\320\274", nullptr));
        pbChangeInDir->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        pbChangeOutDir->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        cbSubdirs->setText(QApplication::translate("MainWindow", "\320\222\320\273\320\276\320\266\320\265\320\275\320\275\321\213\320\265 \320\277\320\260\320\277\320\272\320\270", nullptr));
        cbDeleteSrcs->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\321\217\321\202\321\214 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\320\265", nullptr));
        pbStart->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        pbCancel->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        cbFileExt->setItemText(0, QApplication::translate("MainWindow", "jpg, jpeg", nullptr));
        cbFileExt->setItemText(1, QApplication::translate("MainWindow", "jpg, jpeg, png, raw", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
