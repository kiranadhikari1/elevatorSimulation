#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "elevator.h"
#include <cstdlib>
#include <ctime>
#include <QObject>

// Set up MainWIndow & UI + connect slots & signals
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Init elevators & floor counts
    connect(ui->maxFloorCount, SIGNAL(editingFinished()), this, SLOT(disableMaxFloorText()));
    connect(ui->maxElevatorCountText, SIGNAL(editingFinished()), this, SLOT(initElevators()));
    // Passengers slots & signals
    passengers.addButton(ui->passengerOne, 1);
    passengers.addButton(ui->passengerTwo, 2);
    passengers.addButton(ui->passengerThree, 3);
    // Elevator slots & signals
    connect(ui->eUpButton, SIGNAL(released()), this, SLOT (handlePassengerFloor()));
    connect(ui->eDownButton, SIGNAL(released()), this, SLOT (handlePassengerFloor()));

}

// Deconstructor for MainWindow
MainWindow::~MainWindow()
{
    for (int i=0; i<elevators.size(); i++){
        delete elevators[i];
    }

    delete ui;
}

// This method sets up the connections for every widget/SLOT/SIGNAL from UI.
void MainWindow::setUpConnections(){
    for (int i=0; i<elevatorCount; i++){
        connect(ui->eFireButton, SIGNAL(released()), elevators[i], SLOT(sendFireSignal()));
        connect(ui->ePowerOutage, SIGNAL(released()), elevators[i], SLOT (sendPowerOutSignal()));
    }
    connect(ui->eOverloadButton, SIGNAL(released()), elevators[0], SLOT(sendMaxWeightSignal()));
    connect(ui->eDeloadButton, SIGNAL(released()), elevators[0], SLOT(sendDeloadSignal()));
    connect(ui->eCloseDoorButton, SIGNAL(released()), this, SLOT (handleFloorInput()));
    connect(ui->eOpenDoorButton, SIGNAL(released()), elevators[0], SLOT (sendObstacleSignal()));
    connect(ui->eHelpButton, SIGNAL(released()), elevators[0], SLOT (sendHelpSignal()));
}

// This method initializes the number of elevators from UI input and calls setupconnections() at the end.
void MainWindow::initElevators(){
    elevatorCount = ui->maxElevatorCountText->text().toInt();
    for (int i=0; i < elevatorCount; i++){
        elevators.append(new elevator(i+1));
    }
    ui->maxElevatorCountText->setDisabled(true);
    elevatorCount = elevators.size();
    setUpConnections();
}

// This function dynamically fetches the floor pressed and calls handleElevatorMovement by passing in that floor.
void MainWindow::handleFloorInput(){
    int selectedFloor = ui->lineEdit_2->text().toInt();

    if (selectedFloor >= 1){
        handleElevatorMovement(selectedFloor);
    }
}

// This method spawns a passenger at a random floor from 0-max floor (user input in UI) and initiates handleElevatorMovement to that floor.
void MainWindow::handlePassengerFloor(){
    srand(time(0)); // init a random seed
    maxFloorCount = ui->maxFloorCount->text().toInt();
    int passengerFloor = rand() % maxFloorCount + 1;
    int passengerID = passengers.checkedId();
    qInfo("Passenger %d has requested an elevator on floor %d", passengerID, passengerFloor);

    QTimer::singleShot(1000, [passengerID, this, passengerFloor]() {
        if (passengerID != -1){
            handleElevatorMovement(passengerFloor);
        }
    });

}

// This function disables the UI floor text from being overwritten.
void MainWindow::disableMaxFloorText(){
    ui->maxFloorCount->setDisabled(true);
}

// This method checks for elevator availability and initiates moveToFloor if free.
void MainWindow::handleElevatorMovement(int floor){
    int destinationFloor = floor;

    // Check elevator availability and send to requested passenger floor.
    for (int i=0; i<elevatorCount; i++){
        if (elevators[i]->isAvailable){
            qInfo("Elevator %d door closing", elevators[i]->getID());
            qInfo("...");
            QTimer::singleShot(1000, []() {
                qInfo("...");
            });
            QTimer::singleShot(1000, [this, i, destinationFloor]() {
                qInfo("Elevator %d is on its way to floor %d", elevators[i]->getID(), destinationFloor);
            });

            elevators[i]->moveToFloor(destinationFloor, i+1);
            break;
        }
    }
}
//
