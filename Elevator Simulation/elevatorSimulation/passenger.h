#ifndef PASSENGER_H
#define PASSENGER_H

#include <QObject>

class passenger : public QObject
{
    Q_OBJECT
public:
    passenger();
    int weight;
};

#endif // PASSENGER_H
