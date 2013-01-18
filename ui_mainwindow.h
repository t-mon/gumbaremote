/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jan 17 14:40:25 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *obstacleRight;
    QPushButton *rotateLeft;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QPushButton *backwardButton;
    QPushButton *stopButton;
    QPushButton *forwardButton;
    QPushButton *connectButton;
    QPushButton *toggleRTSButton;
    QPushButton *startRobotAppButton;
    QFrame *line;
    QFrame *line_2;
    QPushButton *disconnectButton;
    QFrame *line_3;
    QLabel *bumperLeft;
    QLabel *obstacleLeft;
    QLabel *bumperRight;
    QPushButton *rotateRight;
    QLabel *bateryLineEdit;
    QLabel *label_3;
    QLabel *motorLeftLable;
    QLabel *motorRightLable;
    QLabel *lightLeftLable;
    QLabel *lightRightLable;
    QPushButton *modMaualButton;
    QPushButton *modCruiseButton;
    QLabel *speedLable;
    QSlider *horizontalSlider;
    QTextEdit *terminalTextEdit;
    QLineEdit *terminalInput;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(815, 569);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 806, 519));
        layoutWidget->setMaximumSize(QSize(16777215, 531));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        obstacleRight = new QLabel(layoutWidget);
        obstacleRight->setObjectName(QString::fromUtf8("obstacleRight"));
        obstacleRight->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(obstacleRight, 1, 3, 1, 1);

        rotateLeft = new QPushButton(layoutWidget);
        rotateLeft->setObjectName(QString::fromUtf8("rotateLeft"));

        gridLayout->addWidget(rotateLeft, 0, 5, 1, 1);

        leftButton = new QPushButton(layoutWidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(leftButton, 1, 5, 1, 1);

        rightButton = new QPushButton(layoutWidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(rightButton, 1, 7, 1, 1);

        backwardButton = new QPushButton(layoutWidget);
        backwardButton->setObjectName(QString::fromUtf8("backwardButton"));
        backwardButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(backwardButton, 2, 6, 1, 1);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(stopButton, 1, 6, 1, 1);

        forwardButton = new QPushButton(layoutWidget);
        forwardButton->setObjectName(QString::fromUtf8("forwardButton"));
        forwardButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(forwardButton, 0, 6, 1, 1);

        connectButton = new QPushButton(layoutWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(connectButton, 0, 0, 1, 1);

        toggleRTSButton = new QPushButton(layoutWidget);
        toggleRTSButton->setObjectName(QString::fromUtf8("toggleRTSButton"));
        toggleRTSButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(toggleRTSButton, 1, 0, 1, 1);

        startRobotAppButton = new QPushButton(layoutWidget);
        startRobotAppButton->setObjectName(QString::fromUtf8("startRobotAppButton"));
        startRobotAppButton->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(startRobotAppButton, 2, 0, 1, 1);

        line = new QFrame(layoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 1, 1, 1);

        line_2 = new QFrame(layoutWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 2, 1, 1, 1);

        disconnectButton = new QPushButton(layoutWidget);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));

        gridLayout->addWidget(disconnectButton, 11, 0, 1, 1);

        line_3 = new QFrame(layoutWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 0, 1, 1, 1);

        bumperLeft = new QLabel(layoutWidget);
        bumperLeft->setObjectName(QString::fromUtf8("bumperLeft"));
        bumperLeft->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(bumperLeft, 0, 2, 1, 1);

        obstacleLeft = new QLabel(layoutWidget);
        obstacleLeft->setObjectName(QString::fromUtf8("obstacleLeft"));
        obstacleLeft->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(obstacleLeft, 1, 2, 1, 1);

        bumperRight = new QLabel(layoutWidget);
        bumperRight->setObjectName(QString::fromUtf8("bumperRight"));
        bumperRight->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(bumperRight, 0, 3, 1, 1);

        rotateRight = new QPushButton(layoutWidget);
        rotateRight->setObjectName(QString::fromUtf8("rotateRight"));

        gridLayout->addWidget(rotateRight, 0, 7, 1, 1);

        bateryLineEdit = new QLabel(layoutWidget);
        bateryLineEdit->setObjectName(QString::fromUtf8("bateryLineEdit"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        bateryLineEdit->setFont(font);
        bateryLineEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(bateryLineEdit, 10, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        motorLeftLable = new QLabel(layoutWidget);
        motorLeftLable->setObjectName(QString::fromUtf8("motorLeftLable"));

        gridLayout->addWidget(motorLeftLable, 10, 2, 1, 1);

        motorRightLable = new QLabel(layoutWidget);
        motorRightLable->setObjectName(QString::fromUtf8("motorRightLable"));

        gridLayout->addWidget(motorRightLable, 10, 3, 1, 1);

        lightLeftLable = new QLabel(layoutWidget);
        lightLeftLable->setObjectName(QString::fromUtf8("lightLeftLable"));

        gridLayout->addWidget(lightLeftLable, 11, 2, 1, 1);

        lightRightLable = new QLabel(layoutWidget);
        lightRightLable->setObjectName(QString::fromUtf8("lightRightLable"));

        gridLayout->addWidget(lightRightLable, 11, 3, 1, 1);

        modMaualButton = new QPushButton(layoutWidget);
        modMaualButton->setObjectName(QString::fromUtf8("modMaualButton"));

        gridLayout->addWidget(modMaualButton, 10, 5, 1, 1);

        modCruiseButton = new QPushButton(layoutWidget);
        modCruiseButton->setObjectName(QString::fromUtf8("modCruiseButton"));

        gridLayout->addWidget(modCruiseButton, 11, 5, 1, 1);

        speedLable = new QLabel(layoutWidget);
        speedLable->setObjectName(QString::fromUtf8("speedLable"));
        speedLable->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(speedLable, 0, 4, 1, 1);

        horizontalSlider = new QSlider(layoutWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(4);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(2);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 1, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);

        terminalTextEdit = new QTextEdit(layoutWidget);
        terminalTextEdit->setObjectName(QString::fromUtf8("terminalTextEdit"));
        terminalTextEdit->setMinimumSize(QSize(220, 200));
        terminalTextEdit->setReadOnly(true);

        verticalLayout->addWidget(terminalTextEdit);

        terminalInput = new QLineEdit(layoutWidget);
        terminalInput->setObjectName(QString::fromUtf8("terminalInput"));

        verticalLayout->addWidget(terminalInput);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 815, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gumba Remote", 0, QApplication::UnicodeUTF8));
        obstacleRight->setText(QApplication::translate("MainWindow", "Obstacle Right", 0, QApplication::UnicodeUTF8));
        rotateLeft->setText(QApplication::translate("MainWindow", "Rotate Left", 0, QApplication::UnicodeUTF8));
        leftButton->setText(QApplication::translate("MainWindow", "Left", 0, QApplication::UnicodeUTF8));
        rightButton->setText(QApplication::translate("MainWindow", "Right", 0, QApplication::UnicodeUTF8));
        backwardButton->setText(QApplication::translate("MainWindow", "Backward", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        forwardButton->setText(QApplication::translate("MainWindow", "Forward", 0, QApplication::UnicodeUTF8));
        forwardButton->setShortcut(QString());
        connectButton->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        toggleRTSButton->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        startRobotAppButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        disconnectButton->setText(QApplication::translate("MainWindow", "Close Connection", 0, QApplication::UnicodeUTF8));
        bumperLeft->setText(QApplication::translate("MainWindow", "Bumper Left", 0, QApplication::UnicodeUTF8));
        obstacleLeft->setText(QApplication::translate("MainWindow", "Obstacle Left", 0, QApplication::UnicodeUTF8));
        bumperRight->setText(QApplication::translate("MainWindow", "Bumper Right", 0, QApplication::UnicodeUTF8));
        rotateRight->setText(QApplication::translate("MainWindow", "Rotate Right", 0, QApplication::UnicodeUTF8));
        bateryLineEdit->setText(QApplication::translate("MainWindow", "0 V", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
        motorLeftLable->setText(QApplication::translate("MainWindow", "Motor Left: 0", 0, QApplication::UnicodeUTF8));
        motorRightLable->setText(QApplication::translate("MainWindow", "Motor Right: 0", 0, QApplication::UnicodeUTF8));
        lightLeftLable->setText(QApplication::translate("MainWindow", "Light Left: 0", 0, QApplication::UnicodeUTF8));
        lightRightLable->setText(QApplication::translate("MainWindow", "Light Right: 0", 0, QApplication::UnicodeUTF8));
        modMaualButton->setText(QApplication::translate("MainWindow", "Move Manual", 0, QApplication::UnicodeUTF8));
        modCruiseButton->setText(QApplication::translate("MainWindow", "Cruise Around", 0, QApplication::UnicodeUTF8));
        speedLable->setText(QApplication::translate("MainWindow", "v = med", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
