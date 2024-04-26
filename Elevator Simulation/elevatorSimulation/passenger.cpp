#include "passenger.h"

// Constructor for passenger weight.
passenger::passenger()
{
    srand(time(0));
    this->weight = rand() % 101 + 50;
}
