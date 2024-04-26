#include "elevator.h"
#include <QTimer>
#include <QEventLoop>
#include <iostream>

// Elevator Constructor
elevator::elevator(int id){
    this->currentFloor = 1;
    this->destinationFloor = 1;
    this->elevatorID = id;
    this->isAvailable = true;
}

// Function that moves an elevator to the destination floor
void elevator:: moveToFloor(int destinationFloor, int elevatorID){
    // Initialize timer for interval tasks.
    isAvailable = false;
    this->destinationFloor = destinationFloor;
    eTimer = new QTimer(this);
    connect(eTimer, &QTimer::timeout, this, [this, destinationFloor, elevatorID]() mutable {

        floorsLeftToVisit = (currentFloor > destinationFloor) ? currentFloor - destinationFloor : destinationFloor - currentFloor;
        elevatorDisplay.displayElevatorMoving(elevatorID, currentFloor, destinationFloor, floorsLeftToVisit);

        if (currentFloor < destinationFloor){
            currentFloor++;
        }
        else if (currentFloor > destinationFloor){
            currentFloor--;
         }

        if (currentFloor == destinationFloor){
            elevatorDisplay.displayElevatorArrived(elevatorID, currentFloor);

            eTimer->stop();
            eTimer->deleteLater();
            eTimer = nullptr;
            isAvailable = true;
        }

    });
    eTimer->start(1000);
}

// Method that stops the elevator from moving.
void elevator::stopElevator(){
    if (eTimer != nullptr){
        currentFloor--;
        eTimer->stop();
        eTimer = nullptr;
    }
}

// Method that checks if elevator is equal or over the weight limit.
void elevator::isMaxWeight(){
    if (currentWeight > maxWeight){
        sendMaxWeightSignal();
    }
}

// This method stops the elevator and displays overload message.
void elevator::sendMaxWeightSignal(){
    if (eTimer != nullptr){
        if (eTimer->isActive()){
            stopElevator(); // if moving, stop the elevator
        }
    }
    QTimer::singleShot(1000, [this]() {
        elevatorDisplay.displayOverloadAlert(); // display overload message
    });

}

// This method displays fire signal message and moves all elevators to ground floor.
void elevator::sendFireSignal(){

    if (currentFloor == 1){
        elevatorDisplay.displayElevatorAtGroundFloor(elevatorID);
        return;
    }

    if (eTimer != nullptr){
        if (eTimer->isActive()){
            stopElevator(); // if moving, stop the elevator
        }
        else{
            currentFloor = 1;
        }
    }
    if (currentFloor != 1) {
        elevatorDisplay.displayFireAlert();
        moveToFloor(1, getID());
    }
}

// Getter for elevator ID
int elevator:: getID(){
    return elevatorID;
}

// This method stops the elvator, timer, and displays help alert.
void elevator::sendHelpSignal(){
    // Elevator sendHelpSignal method
    qInfo("Help signal received.");
    if (eTimer != nullptr){
        if (eTimer->isActive()){
            stopElevator(); // if moving, stop the elevator
        }
    }

    QTimer::singleShot(1000, [this]() {
        elevatorDisplay.helpSignalAlert(elevatorID); // display help signal message
        qInfo("..");
        QTimer::singleShot(5000, [this]() {
            elevatorDisplay.displayInit911Call(elevatorID);
        });
    });

}

// This method stops the elevator then calls displayDoorObstacleAlert() before waiting a few seconds and attempting to close the door again.
void elevator::sendObstacleSignal(){

    if (eTimer != nullptr && eTimer->isActive()){
        stopElevator();
    }

    elevatorDisplay.displayDoorObstacleAlert(); // display obstruction message

    QTimer::singleShot(4000, [this]() {
        if (destinationFloor != 0){
            qInfo("Door closed, elevator %d will now proceed its original path to floor %d", elevatorID, destinationFloor);
            moveToFloor(destinationFloor, getID());
        }
    });

}

// Method that stops the timer & elevator then displays power-out message before initiating all elevators to move to ground floor.
void elevator::sendPowerOutSignal(){

    if (currentFloor == 1){
        elevatorDisplay.displayElevatorAtGroundFloor(elevatorID);
        return;
    }

    if (eTimer != nullptr){
        if (eTimer->isActive()){
            stopElevator(); // if moving, stop the elevator
        }
        else{
            currentFloor = 1;
        }
    }

    elevatorDisplay.displayPowerOutageAlert(elevatorID); // display power out message

    if (currentFloor != 1) {
        moveToFloor(1, getID());
    }

}

// This method calls a deload signal message then allows elevator to move in its regular path.
void elevator::sendDeloadSignal(){
    QTimer::singleShot(1000, [this]() {
        elevatorDisplay.displayDeload(elevatorID);
    });
    moveToFloor(destinationFloor, elevatorID);
}
