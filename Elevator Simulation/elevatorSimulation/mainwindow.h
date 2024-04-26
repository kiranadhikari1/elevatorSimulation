#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elevator.h"
#include <QButtonGroup>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QButtonGroup floorButtons;
    QButtonGroup passengers;
    QTimer *eTimer;
    int maxFloorCount;
    int elevatorCount;
    QVector<elevator*> elevators;


private slots:
    void handleElevatorMovement(int floor);
    void handleFloorInput();
    void handlePassengerFloor();
    void disableMaxFloorText();
    void initElevators();
    void setUpConnections();
};
#endif // MAINWINDOW_H
