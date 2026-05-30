#ifndef CAR_H
#define CAR_H

#include <QString>

struct Car
{
    int id = 0;
    QString model;
    QString brand;
    int year = 0;
    int mileage = 0;
    double price = 0.0;
    QString description;
    QString date;
};

#endif // CAR_H