#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QTimer>

class display : public QObject
{
    Q_OBJECT
public:
    display();
    void displayElevatorArrived(int elevatorID, int currentFloor);
    void displayElevatorMoving(int elevatorID, int currentFloor, int destinationFloor, int floorsLeftToVisit);
    void displayFireAlert();
    void displayOverloadAlert();
    void displayPowerOutageAlert(int elevatorID);
    void displayDoorObstacleAlert();
    void displayElevatorAtGroundFloor(int elevatorID);
    void helpSignalAlert(int elevatorID);
    void displayInit911Call(int elevatorID);
    void displayDeload(int elevatorID);
};

#endif // DISPLAY_H
