#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qextserialport.h"
#include <QTextCursor>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);
    


signals:
    void obstacleLeftOn();
    void obstacleLeftOff();
    void obstacleRightOn();
    void obstacleRightOff();
    void bumperLeftPressd(bool);
    void bumperLeftReleased();
    void bumperRightPressed();
    void bumperRightReleased();
    void gumbaPackageReceived(QString);
    void gumbaDataReceived(QString);

private slots:
    void on_connectButton_clicked();
    void on_toggleRTSButton_clicked();
    void on_forwardButton_clicked();
    void on_startRobotAppButton_clicked();
    void on_terminalInput_editingFinished();
    void on_leftButton_clicked();
    void on_backwardButton_clicked();
    void on_rightButton_clicked();
    void on_disconnectButton_clicked();
    void parseNewLine(const QString & gumbaString);
    void gumbaPackageAvalable();
    void on_stopButton_clicked();
    void on_rotateLeft_clicked();
    void on_rotateRight_clicked();
    void on_modMaualButton_clicked();
    void on_modCruiseButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    int serial_device;
    PortSettings gumbaPortSettings;
    QextSerialPort *gumba;
    QString gumbaHoleText;
    QTextCursor curser;
    QString m_gumbaBuffer;
    void printToTerminal(const QString &terminalString);
};

#endif // MAINWINDOW_H
