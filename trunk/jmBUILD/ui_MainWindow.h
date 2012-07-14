/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Mon Sep 12 10:57:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <FrameLabel.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *connectToCameraAction;
    QAction *disconnectCameraAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *grayscaleAction;
    QAction *smoothAction;
    QAction *flipAction;
    QAction *dilateAction;
    QAction *erodeAction;
    QAction *cannyAction;
    QAction *settingsAction;
    QAction *actionStart_New_Game;
    QAction *deckShuffledAction;
    QAction *actionSet_black;
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    FrameLabel *frameLabel;
    QTextEdit *msgBoard;
    QTextEdit *historyBoard;
    QFrame *line_5;
    QVBoxLayout *verticalLayout_1;
    QHBoxLayout *horizontalLayout_1;
    QLabel *label_1;
    QProgressBar *imageBufferBar;
    QLabel *imageBufferLabel;
    QFrame *line_1;
    QLabel *label_2;
    QLabel *captureRateLabel;
    QFrame *line_2;
    QLabel *label_3;
    QLabel *processingRateLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *deviceNumberLabel;
    QFrame *line_3;
    QLabel *label_5;
    QLabel *cameraResolutionLabel;
    QFrame *line_4;
    QLabel *label_6;
    QLabel *roiLabel;
    QFrame *line_7;
    QLabel *label_7;
    QLabel *mouseCursorPosLabel;
    QPushButton *clearImageBufferButton;
    QFrame *line_6;
    QMenuBar *menubar;
    QMenu *mainMenu;
    QMenu *aboutMenu;
    QMenu *GameMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(927, 662);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(927, 662));
        MainWindow->setMaximumSize(QSize(927, 722));
        MainWindow->setAutoFillBackground(false);
        connectToCameraAction = new QAction(MainWindow);
        connectToCameraAction->setObjectName(QString::fromUtf8("connectToCameraAction"));
        disconnectCameraAction = new QAction(MainWindow);
        disconnectCameraAction->setObjectName(QString::fromUtf8("disconnectCameraAction"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        aboutAction = new QAction(MainWindow);
        aboutAction->setObjectName(QString::fromUtf8("aboutAction"));
        grayscaleAction = new QAction(MainWindow);
        grayscaleAction->setObjectName(QString::fromUtf8("grayscaleAction"));
        grayscaleAction->setCheckable(true);
        grayscaleAction->setEnabled(false);
        grayscaleAction->setVisible(false);
        smoothAction = new QAction(MainWindow);
        smoothAction->setObjectName(QString::fromUtf8("smoothAction"));
        smoothAction->setCheckable(true);
        smoothAction->setEnabled(false);
        smoothAction->setVisible(false);
        flipAction = new QAction(MainWindow);
        flipAction->setObjectName(QString::fromUtf8("flipAction"));
        flipAction->setCheckable(true);
        flipAction->setEnabled(false);
        flipAction->setVisible(false);
        dilateAction = new QAction(MainWindow);
        dilateAction->setObjectName(QString::fromUtf8("dilateAction"));
        dilateAction->setCheckable(true);
        dilateAction->setEnabled(false);
        dilateAction->setVisible(false);
        erodeAction = new QAction(MainWindow);
        erodeAction->setObjectName(QString::fromUtf8("erodeAction"));
        erodeAction->setCheckable(true);
        erodeAction->setEnabled(false);
        erodeAction->setVisible(false);
        cannyAction = new QAction(MainWindow);
        cannyAction->setObjectName(QString::fromUtf8("cannyAction"));
        cannyAction->setCheckable(true);
        cannyAction->setEnabled(false);
        cannyAction->setVisible(false);
        settingsAction = new QAction(MainWindow);
        settingsAction->setObjectName(QString::fromUtf8("settingsAction"));
        settingsAction->setEnabled(false);
        settingsAction->setVisible(false);
        actionStart_New_Game = new QAction(MainWindow);
        actionStart_New_Game->setObjectName(QString::fromUtf8("actionStart_New_Game"));
        deckShuffledAction = new QAction(MainWindow);
        deckShuffledAction->setObjectName(QString::fromUtf8("deckShuffledAction"));
        deckShuffledAction->setEnabled(false);
        actionSet_black = new QAction(MainWindow);
        actionSet_black->setObjectName(QString::fromUtf8("actionSet_black"));
        actionSet_black->setEnabled(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 908, 685));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frameLabel = new FrameLabel(layoutWidget);
        frameLabel->setObjectName(QString::fromUtf8("frameLabel"));
        frameLabel->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameLabel->sizePolicy().hasHeightForWidth());
        frameLabel->setSizePolicy(sizePolicy1);
        frameLabel->setMinimumSize(QSize(642, 482));
        frameLabel->setMouseTracking(true);
        frameLabel->setAutoFillBackground(true);
        frameLabel->setFrameShape(QFrame::Box);
        frameLabel->setFrameShadow(QFrame::Raised);
        frameLabel->setLineWidth(1);
        frameLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(frameLabel, 0, 0, 2, 1);

        msgBoard = new QTextEdit(layoutWidget);
        msgBoard->setObjectName(QString::fromUtf8("msgBoard"));
        sizePolicy1.setHeightForWidth(msgBoard->sizePolicy().hasHeightForWidth());
        msgBoard->setSizePolicy(sizePolicy1);
        msgBoard->setSizeIncrement(QSize(2, 0));
        msgBoard->setBaseSize(QSize(0, 0));
        msgBoard->setReadOnly(true);

        gridLayout->addWidget(msgBoard, 0, 1, 1, 1);

        historyBoard = new QTextEdit(layoutWidget);
        historyBoard->setObjectName(QString::fromUtf8("historyBoard"));
        sizePolicy.setHeightForWidth(historyBoard->sizePolicy().hasHeightForWidth());
        historyBoard->setSizePolicy(sizePolicy);
        historyBoard->setMinimumSize(QSize(0, 270));
        historyBoard->setMaximumSize(QSize(16777215, 300));
        historyBoard->setSizeIncrement(QSize(0, 0));
        historyBoard->setBaseSize(QSize(0, 0));

        gridLayout->addWidget(historyBoard, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        line_5 = new QFrame(layoutWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_5);

        verticalLayout_1 = new QVBoxLayout();
        verticalLayout_1->setObjectName(QString::fromUtf8("verticalLayout_1"));
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        label_1 = new QLabel(layoutWidget);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy2);
        label_1->setMinimumSize(QSize(0, 20));
        label_1->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        label_1->setFont(font);
        label_1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_1->addWidget(label_1);

        imageBufferBar = new QProgressBar(layoutWidget);
        imageBufferBar->setObjectName(QString::fromUtf8("imageBufferBar"));
        sizePolicy2.setHeightForWidth(imageBufferBar->sizePolicy().hasHeightForWidth());
        imageBufferBar->setSizePolicy(sizePolicy2);
        imageBufferBar->setMinimumSize(QSize(0, 20));
        imageBufferBar->setMaximumSize(QSize(16777215, 20));
        QFont font1;
        font1.setPointSize(8);
        imageBufferBar->setFont(font1);
        imageBufferBar->setValue(0);

        horizontalLayout_1->addWidget(imageBufferBar);

        imageBufferLabel = new QLabel(layoutWidget);
        imageBufferLabel->setObjectName(QString::fromUtf8("imageBufferLabel"));
        sizePolicy2.setHeightForWidth(imageBufferLabel->sizePolicy().hasHeightForWidth());
        imageBufferLabel->setSizePolicy(sizePolicy2);
        imageBufferLabel->setMinimumSize(QSize(0, 20));
        imageBufferLabel->setMaximumSize(QSize(16777215, 20));
        imageBufferLabel->setFont(font1);
        imageBufferLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_1->addWidget(imageBufferLabel);

        line_1 = new QFrame(layoutWidget);
        line_1->setObjectName(QString::fromUtf8("line_1"));
        line_1->setFrameShape(QFrame::VLine);
        line_1->setFrameShadow(QFrame::Sunken);

        horizontalLayout_1->addWidget(line_1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(0, 20));
        label_2->setMaximumSize(QSize(16777215, 20));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_1->addWidget(label_2);

        captureRateLabel = new QLabel(layoutWidget);
        captureRateLabel->setObjectName(QString::fromUtf8("captureRateLabel"));
        captureRateLabel->setEnabled(true);
        sizePolicy2.setHeightForWidth(captureRateLabel->sizePolicy().hasHeightForWidth());
        captureRateLabel->setSizePolicy(sizePolicy2);
        captureRateLabel->setMinimumSize(QSize(0, 20));
        captureRateLabel->setMaximumSize(QSize(40, 20));
        captureRateLabel->setFont(font1);
        captureRateLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_1->addWidget(captureRateLabel);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_1->addWidget(line_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMinimumSize(QSize(0, 20));
        label_3->setMaximumSize(QSize(16777215, 20));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_1->addWidget(label_3);

        processingRateLabel = new QLabel(layoutWidget);
        processingRateLabel->setObjectName(QString::fromUtf8("processingRateLabel"));
        sizePolicy2.setHeightForWidth(processingRateLabel->sizePolicy().hasHeightForWidth());
        processingRateLabel->setSizePolicy(sizePolicy2);
        processingRateLabel->setMinimumSize(QSize(0, 20));
        processingRateLabel->setMaximumSize(QSize(40, 20));
        processingRateLabel->setFont(font1);
        processingRateLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_1->addWidget(processingRateLabel);


        verticalLayout_1->addLayout(horizontalLayout_1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(0, 20));
        label_4->setMaximumSize(QSize(16777215, 20));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_4);

        deviceNumberLabel = new QLabel(layoutWidget);
        deviceNumberLabel->setObjectName(QString::fromUtf8("deviceNumberLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(30);
        sizePolicy3.setVerticalStretch(20);
        sizePolicy3.setHeightForWidth(deviceNumberLabel->sizePolicy().hasHeightForWidth());
        deviceNumberLabel->setSizePolicy(sizePolicy3);
        deviceNumberLabel->setMinimumSize(QSize(30, 20));
        deviceNumberLabel->setMaximumSize(QSize(16777215, 20));
        deviceNumberLabel->setFont(font1);
        deviceNumberLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(deviceNumberLabel);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_3);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(0, 20));
        label_5->setMaximumSize(QSize(16777215, 20));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_5);

        cameraResolutionLabel = new QLabel(layoutWidget);
        cameraResolutionLabel->setObjectName(QString::fromUtf8("cameraResolutionLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(70);
        sizePolicy4.setVerticalStretch(20);
        sizePolicy4.setHeightForWidth(cameraResolutionLabel->sizePolicy().hasHeightForWidth());
        cameraResolutionLabel->setSizePolicy(sizePolicy4);
        cameraResolutionLabel->setMinimumSize(QSize(70, 20));
        cameraResolutionLabel->setMaximumSize(QSize(16777215, 20));
        cameraResolutionLabel->setFont(font1);
        cameraResolutionLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(cameraResolutionLabel);

        line_4 = new QFrame(layoutWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_4);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMinimumSize(QSize(0, 20));
        label_6->setMaximumSize(QSize(16777215, 20));
        label_6->setFont(font);

        horizontalLayout_2->addWidget(label_6);

        roiLabel = new QLabel(layoutWidget);
        roiLabel->setObjectName(QString::fromUtf8("roiLabel"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(100);
        sizePolicy5.setVerticalStretch(20);
        sizePolicy5.setHeightForWidth(roiLabel->sizePolicy().hasHeightForWidth());
        roiLabel->setSizePolicy(sizePolicy5);
        roiLabel->setMinimumSize(QSize(70, 20));
        roiLabel->setMaximumSize(QSize(16777215, 20));
        roiLabel->setFont(font1);

        horizontalLayout_2->addWidget(roiLabel);

        line_7 = new QFrame(layoutWidget);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_7);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        horizontalLayout_2->addWidget(label_7);

        mouseCursorPosLabel = new QLabel(layoutWidget);
        mouseCursorPosLabel->setObjectName(QString::fromUtf8("mouseCursorPosLabel"));
        sizePolicy4.setHeightForWidth(mouseCursorPosLabel->sizePolicy().hasHeightForWidth());
        mouseCursorPosLabel->setSizePolicy(sizePolicy4);
        mouseCursorPosLabel->setMinimumSize(QSize(70, 20));
        mouseCursorPosLabel->setMaximumSize(QSize(16777215, 20));
        mouseCursorPosLabel->setFont(font1);

        horizontalLayout_2->addWidget(mouseCursorPosLabel);


        verticalLayout_1->addLayout(horizontalLayout_2);

        clearImageBufferButton = new QPushButton(layoutWidget);
        clearImageBufferButton->setObjectName(QString::fromUtf8("clearImageBufferButton"));
        clearImageBufferButton->setFont(font1);

        verticalLayout_1->addWidget(clearImageBufferButton);

        line_6 = new QFrame(layoutWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_1->addWidget(line_6);


        verticalLayout_2->addLayout(verticalLayout_1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 927, 23));
        mainMenu = new QMenu(menubar);
        mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        aboutMenu = new QMenu(menubar);
        aboutMenu->setObjectName(QString::fromUtf8("aboutMenu"));
        GameMenu = new QMenu(menubar);
        GameMenu->setObjectName(QString::fromUtf8("GameMenu"));
        GameMenu->setEnabled(true);
        MainWindow->setMenuBar(menubar);

        menubar->addAction(mainMenu->menuAction());
        menubar->addAction(GameMenu->menuAction());
        menubar->addAction(aboutMenu->menuAction());
        mainMenu->addAction(connectToCameraAction);
        mainMenu->addAction(disconnectCameraAction);
        mainMenu->addSeparator();
        mainMenu->addAction(actionSet_black);
        mainMenu->addSeparator();
        mainMenu->addAction(exitAction);
        aboutMenu->addAction(aboutAction);
        GameMenu->addAction(grayscaleAction);
        GameMenu->addAction(smoothAction);
        GameMenu->addAction(dilateAction);
        GameMenu->addAction(erodeAction);
        GameMenu->addAction(flipAction);
        GameMenu->addAction(cannyAction);
        GameMenu->addSeparator();
        GameMenu->addAction(settingsAction);
        GameMenu->addAction(deckShuffledAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "JackMate\302\256", 0, QApplication::UnicodeUTF8));
        connectToCameraAction->setText(QApplication::translate("MainWindow", "New Game", 0, QApplication::UnicodeUTF8));
        disconnectCameraAction->setText(QApplication::translate("MainWindow", "End Game", 0, QApplication::UnicodeUTF8));
        exitAction->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        aboutAction->setText(QApplication::translate("MainWindow", "About...", 0, QApplication::UnicodeUTF8));
        grayscaleAction->setText(QApplication::translate("MainWindow", "1: Grayscale", 0, QApplication::UnicodeUTF8));
        smoothAction->setText(QApplication::translate("MainWindow", "2: Smooth", 0, QApplication::UnicodeUTF8));
        flipAction->setText(QApplication::translate("MainWindow", "5: Flip", 0, QApplication::UnicodeUTF8));
        dilateAction->setText(QApplication::translate("MainWindow", "3: Dilate", 0, QApplication::UnicodeUTF8));
        erodeAction->setText(QApplication::translate("MainWindow", "4: Erode", 0, QApplication::UnicodeUTF8));
        cannyAction->setText(QApplication::translate("MainWindow", "6. Canny", 0, QApplication::UnicodeUTF8));
        settingsAction->setText(QApplication::translate("MainWindow", "Settings...", 0, QApplication::UnicodeUTF8));
        actionStart_New_Game->setText(QApplication::translate("MainWindow", "Start New Game", 0, QApplication::UnicodeUTF8));
        deckShuffledAction->setText(QApplication::translate("MainWindow", "deck shuffled", 0, QApplication::UnicodeUTF8));
        actionSet_black->setText(QApplication::translate("MainWindow", "Calib. Black", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("MainWindow", "Image Buffer Status (% full):", 0, QApplication::UnicodeUTF8));
        imageBufferLabel->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Capture Rate:", 0, QApplication::UnicodeUTF8));
        captureRateLabel->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "Processing Rate:", 0, QApplication::UnicodeUTF8));
        processingRateLabel->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Camera Dev No:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Camera Resolution:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "ROI:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Cursor", 0, QApplication::UnicodeUTF8));
        clearImageBufferButton->setText(QApplication::translate("MainWindow", "Clear Image Buffer", 0, QApplication::UnicodeUTF8));
        mainMenu->setTitle(QApplication::translate("MainWindow", "Main", 0, QApplication::UnicodeUTF8));
        aboutMenu->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        GameMenu->setTitle(QApplication::translate("MainWindow", "Game", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
