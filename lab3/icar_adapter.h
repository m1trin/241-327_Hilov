#ifndef ICAR_ADAPTER_H
#define ICAR_ADAPTER_H

#include "car.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QList>

class ICarAdapter
{
public:
    virtual ~ICarAdapter() = default;

    virtual Car toCar(const QJsonObject &json) const = 0;
    virtual QList<Car> toCarList(const QJsonArray &json) const = 0;
    virtual QList<Car> toCarListFromRoot(const QJsonObject &root) const = 0;
};

#endif // ICAR_ADAPTER_H