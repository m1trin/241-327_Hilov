#include "car_json_adapter.h"

#include <QJsonValue>

Car CarJsonAdapter::toCar(const QJsonObject &json) const
{
    Car car;

    car.id = json["id"].toInt();
    car.model = json["model"].toString();
    car.brand = json["brand"].toString();
    car.year = json["year"].toInt();
    car.mileage = json["mileage"].toInt();
    car.price = json["price"].toDouble();
    car.description = json["description"].toString();
    car.date = json["date"].toString();

    return car;
}

QList<Car> CarJsonAdapter::toCarList(const QJsonArray &json) const
{
    QList<Car> list;

    for (const QJsonValue &value : json) {
        if (value.isObject()) {
            list.append(toCar(value.toObject()));
        }
    }

    return list;
}

QList<Car> CarJsonAdapter::toCarListFromRoot(const QJsonObject &root) const
{
    QJsonArray carsArray = root["cars"].toArray();
    return toCarList(carsArray);
}