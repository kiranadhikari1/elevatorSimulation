#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QTimer>
#include "display.h"

class elevator : public QObject
{
    Q_OBJECT
public:
    // constructors
    elevator();
    elevator(int id);

    int getID();
    void stopElevator(); // stops elevator in case of emergency or safety signal
    bool isAvailable;
private:
    int elevatorID;
    int maxWeight;
    int currentWeight;
    int floorsLeftToVisit;
    int currentFloor = 1;
    int destinationFloor = 1;

    QTimer *eTimer;
    display elevatorDisplay;

public slots:
    void isMaxWeight();

    void sendMaxWeightSignal();
    void sendHelpSignal();
    void sendObstacleSignal();
    void sendFireSignal();
    void sendPowerOutSignal();
    void moveToFloor(int destinationFloor, int elevatorID);
    void sendDeloadSignal();
};

#endif // ELEVATOR_H
