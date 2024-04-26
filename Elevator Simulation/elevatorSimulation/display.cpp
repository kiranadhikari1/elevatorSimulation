#include "display.h"
#include <QTimer>

// Display constructor
display::display(){}

// This method displays the elevator arrival message.
void display::displayElevatorArrived(int elevatorID, int currentFloor){
    QTimer::singleShot(1000, [elevatorID, currentFloor]() {
        qInfo("Elevator %d has arrived at floor: %d", elevatorID, currentFloor);
        QTimer::singleShot(1000, [elevatorID]() {
            qInfo("Elevator %d door is opening.", elevatorID);
            QTimer::singleShot(1000, []() {
                qInfo("Ring! Ring!");
            });
        });
    });

}

// This method displays the moving elevator message
void display::displayElevatorMoving(int elevatorID, int currentFloor, int destinationFloor, int floorsLeftToVisit){
    QTimer::singleShot(1000, [elevatorID, currentFloor, destinationFloor, floorsLeftToVisit]() {
        qInfo("Elevator %d is on floor %d and is moving to floor %d. Number of floors left to visit: %d", elevatorID, currentFloor, destinationFloor, floorsLeftToVisit);
    });
}

// This method displays the fire alert
void display::displayFireAlert(){
    qInfo("Fire Alert! Moving to the safest and nearest exit floor -> Ground Floor!!");
}

// This method displays the overload alert
void display::displayOverloadAlert(){
    qInfo("Overload signal sent.");
    qInfo("Please reduce the elevator weight.");
}

// This method displays the power-out alert
void display::displayPowerOutageAlert(int elevatorID){
    qInfo("...");
    qInfo("Power outage has occured. Elevator %d is now on backup power and will proceed to the ground floor. Please exit upon arrival.", elevatorID);
}

// This method displays the door obstacle alert
void display::displayDoorObstacleAlert(){
    qInfo("Obstacle disturbance signal received.");
    qInfo("Door will stay opened momentarily...");
    qInfo("...");

    QTimer::singleShot(2000, []() {
        qInfo("...");
    });
}

// This method displays the help button alert
void display::helpSignalAlert(int elevatorID){
    qInfo("Elevator %d is now connected to the on site emergency technician.", elevatorID);
    qInfo("If there is no response from either side within a few seconds, a 911 emergency call will be placed.");
}

// Method that informs if elevator is already at ground floor (safe floor).
void display::displayElevatorAtGroundFloor(int elevatorID){
    qInfo("Elevator %d is already at the ground floor, please exist.", elevatorID);
}

// This method displays 911 emergency alert.
void display::displayInit911Call(int elevatorID){
    qInfo("A 911 emergency call has been placed for elevator %d.", elevatorID);
}

// This method displays de-load message.
void display::displayDeload(int elevatorID){
    qInfo("Elevator %d has been deloaded and will resume it's regular path.", elevatorID);
}
