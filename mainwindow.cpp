#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qextserialport.h"

#include <QDebug>
#include <QString>

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <QKeyEvent>
#include <qjson/parser.h>
#include <QMap>
#include <QVariant>
#include <QVariantMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    curser = ui->terminalTextEdit->textCursor();

    ui->bumperLeft->setStyleSheet("background-color:green;");
    ui->bumperRight->setStyleSheet("background-color:green;");
    ui->obstacleLeft->setStyleSheet("background-color:green;");
    ui->obstacleRight->setStyleSheet("background-color:green;");


    gumbaPortSettings.BaudRate = BAUD38400;
    gumbaPortSettings.DataBits = DATA_8;
    gumbaPortSettings.FlowControl = FLOW_XONXOFF;
    gumbaPortSettings.Parity = PAR_NONE;
    gumbaPortSettings.StopBits = STOP_1;
    gumbaPortSettings.Timeout_Millisec = 500;

    gumba = new QextSerialPort("/dev/ttyUSB0",gumbaPortSettings);
    gumba->flush();
    connect(gumba,SIGNAL(readyRead()),this,SLOT(gumbaPackageAvalable()));
    connect(this,SIGNAL(gumbaPackageReceived(QString)),this,SLOT(parseNewLine(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent( QKeyEvent *event)
{

    switch (event->key()){
    case Qt::Key_W:
        qDebug() << "w pressed";
        ui->forwardButton->click();
        break;
    case Qt::Key_A:
        qDebug() << "a pressed";
        ui->leftButton->click();
        break;
    case Qt::Key_S:
        qDebug() << "s pressed";
        ui->backwardButton->click();
        break;
    case Qt::Key_D:
        qDebug() << "d pressed";
        ui->rightButton->click();
        break;
    case Qt::Key_Q:
        qDebug() << "q pressed";
        ui->rotateLeft->click();
        break;
    case Qt::Key_E:
        qDebug() << "e pressed";
        ui->rotateRight->click();
        break;
    case Qt::Key_X:
        qDebug() << "x pressed";
        ui->stopButton  ->click();
        break;
    }

}



void MainWindow::on_connectButton_clicked()
{

    if(gumba->open(QextSerialPort::ReadWrite) == true){
        qDebug() << "Port open!";
        printToTerminal("> Connected! OK");
        on_toggleRTSButton_clicked();
    }else if(gumba->open(QextSerialPort::ReadWrite) == false){
        qDebug() << "Port not opend!";
        printToTerminal("> Could not Connect!! FAIL");
        on_toggleRTSButton_clicked();
    }

    QString readyString = gumba->readLine();

}

void MainWindow::on_toggleRTSButton_clicked()
{
    qDebug() << "toggle RTS";
    gumba->setRts(true);
    gumba->setRts(false);
    printToTerminal("> toggle RTS...    RESET ROBOT");
}




void MainWindow::gumbaPackageAvalable()
{
    m_gumbaBuffer.append(gumba->readAll());
    //qDebug() << "got Buffer" << m_gumbaBuffer;
    int newLinePosGumba = m_gumbaBuffer.indexOf('\n')+1;
    qDebug() << "newline index" << newLinePosGumba;
    emit gumbaPackageReceived(m_gumbaBuffer.left(newLinePosGumba));
    m_gumbaBuffer = m_gumbaBuffer.right(m_gumbaBuffer.length() - newLinePosGumba);
}


void MainWindow::on_startRobotAppButton_clicked()
{
    gumba->write("s\n");
    printToTerminal("> start roboter application");
    gumba->flush();

}

void MainWindow::on_terminalInput_editingFinished()
{
    QString terminalInput;
    terminalInput = ui->terminalInput->text() + '\n';
    gumba->write(terminalInput.toUtf8());
    printToTerminal(ui->terminalInput->text());
    ui->terminalInput->clear();
}

void MainWindow::on_forwardButton_clicked()
{
gumba->write("w\n");
printToTerminal("> forward");
gumba->flush();
}

void MainWindow::on_leftButton_clicked()
{
    gumba->write("a\n");
    printToTerminal("> left");
    gumba->flush();

}

void MainWindow::on_backwardButton_clicked()
{
    gumba->write("s\n");
    printToTerminal("> backwards");
    gumba->flush();

}

void MainWindow::on_rightButton_clicked()
{
    gumba->write("d\n");
    printToTerminal("> right");
    gumba->flush();


}
void MainWindow::on_stopButton_clicked()
{
    gumba->write("x\n");
    printToTerminal("> stop all movements");
    gumba->flush();

}

void MainWindow::on_disconnectButton_clicked()
{
    on_toggleRTSButton_clicked();
    gumba->close();
    printToTerminal("> close connection");
}

void MainWindow::on_rotateLeft_clicked()
{
    gumba->write("q\n");
    printToTerminal("> rotate left");
    gumba->flush();
}

void MainWindow::on_rotateRight_clicked()
{
    gumba->write("e\n");
    printToTerminal("> rotate right");
    gumba->flush();
}

void MainWindow::on_modMaualButton_clicked()
{
    gumba->write("k\n");
    printToTerminal("> MODE: move manual");
    gumba->flush();
}

void MainWindow::on_modCruiseButton_clicked()
{
    gumba->write("l\n");
    printToTerminal("> MODE: cruise around");
    gumba->flush();
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    switch(position){

    case 1:
        gumba->write("u\n");
        printToTerminal("> speedlevel: 1");
        gumba->flush();
        ui->speedLable->setText("v = low");
        break;
    case 2:
        gumba->write("i\n");
        printToTerminal("> speedlevel: 2");
        gumba->flush();
        ui->speedLable->setText("v = med");
        break;
    case 3:
        gumba->write("o\n");
        printToTerminal("> speedlevel: 3");
        gumba->flush();
        ui->speedLable->setText("v = high");
        break;
    case 4:
        gumba->write("p\n");
        printToTerminal("> speedlevel: MAX");
        gumba->flush();
        ui->speedLable->setText("v = max");
        break;
    }
}


void MainWindow::parseNewLine(const QString &gumbaString)
{
    qDebug() << "Line to parse: _--------------" << gumbaString;

    //    if(gumbaString.at(0) == '[' && gumbaString.at(1) == 'R' && gumbaString.at(2) == 'P' ){
    //        qDebug() << "Got [READY] string...";

    //        gumba->write("•\n");
    //    }


    if (gumbaString.at(0) == '{'){
        QVariantMap sensors;
        QJson::Parser parser;
        sensors = parser.parse(gumbaString.toAscii()).toMap();

        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'e')){
            if(sensors.value("energy").toMap().value("batery").toInt() == 1){
                double ubat = sensors.value("energy").toMap().value("voltage").toDouble();
                double iMotorR = sensors.value("energy").toMap().value("motor_r").toDouble();
                double iMotorL = sensors.value("energy").toMap().value("motor_l").toDouble();
                double lightR = sensors.value("energy").toMap().value("light_r").toDouble();
                double lightL = sensors.value("energy").toMap().value("light_l").toDouble();

                qDebug() << "Batery Voltage: " << ubat;
                qDebug() << "Motor right: " << iMotorR;
                qDebug() << "Motor left: " << iMotorL;
                qDebug() << "Light right: " << lightR;
                qDebug() << "Light left: " << lightL;

                ui->motorRightLable->setText("Motor Right: " + QString::number(iMotorR));
                ui->motorLeftLable->setText("Motor Left: " + QString::number(iMotorL));
                ui->lightLeftLable->setText("Light Left: " + QString::number(lightL));
                ui->lightRightLable->setText("Light Right: " + QString::number(lightR));


                ubat = ubat/100;
                if (ubat != 0){
                    if(ubat > 5.8){
                        ui->bateryLineEdit->setStyleSheet("background-color:green;");
                    }else if (ubat <= 5.8){
                        ui->bateryLineEdit->setStyleSheet("background-color:red;");
                    }
                    ui->bateryLineEdit->clear();
                    ui->bateryLineEdit->setText(QString::number(ubat) +"V");
                }

            }
        }

        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'o')){
            if(sensors.value("obstacles").toMap().value("left").toInt() == 0){
                emit obstacleLeftOff();
                ui->obstacleLeft->setStyleSheet("background-color:green;");
                qDebug() << "Obstacle Left OFF";
            } if(sensors.value("obstacles").toMap().value("left").toInt() == 1){
                emit obstacleLeftOn();
                ui->obstacleLeft->setStyleSheet("background-color:red;");
                qDebug() << "Obstacle Left ON";
            } if(sensors.value("obstacles").toMap().value("right").toInt() == 0){
                emit obstacleRightOff();
                ui->obstacleRight->setStyleSheet("background-color:green;");
                qDebug() << "Obstacle Right OFF";
            } if(sensors.value("obstacles").toMap().value("right").toInt() == 1){
                emit obstacleRightOn();
                ui->obstacleRight->setStyleSheet("background-color:red;");
                qDebug() << "Obstacle Right ON";
            }
        }
        if((gumbaString.at(0) == '{') && (gumbaString.at(1) == '"') && (gumbaString.at(2) == 'b')){
            if(sensors.value("bumper").toMap().value("left").toInt() == 0){
                emit bumperLeftReleased();
                ui->bumperLeft->setStyleSheet("background-color:green;");
                qDebug() << "Bumper Left OFF";
            } if(sensors.value("bumper").toMap().value("left").toInt() == 1){
                emit bumperLeftPressd(true);
                ui->bumperLeft->setStyleSheet("background-color:red;");
                qDebug() << "Bumper Left ON";
            } if(sensors.value("bumper").toMap().value("right").toInt() == 0){
                emit bumperRightReleased();
                ui->bumperRight->setStyleSheet("background-color:green;");
                qDebug() << "Bumper Right OFF";
            } if(sensors.value("bumper").toMap().value("right").toInt() == 1){
                emit bumperRightPressed();
                ui->bumperRight->setStyleSheet("background-color:red;");
                qDebug() << "Bumper Right ON";
            }
        }
    }
    if(gumbaString.at(0) == '[' || gumbaString.at(0) == '#' ){

        printToTerminal("       " + gumbaString);
    }


}

void MainWindow::printToTerminal(const QString &terminalString)
{
    gumbaHoleText = gumbaHoleText + "\n" + terminalString;
    ui->terminalTextEdit->setTextColor(QColor(0, 255, 0,255));
    ui->terminalTextEdit->setText(gumbaHoleText);
    curser.movePosition(QTextCursor::End);
    ui->terminalTextEdit->setTextCursor(curser);
}




