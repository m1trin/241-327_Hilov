#ifndef CAR_JSON_ADAPTER_H
#define CAR_JSON_ADAPTER_H

#include "icar_adapter.h"

class CarJsonAdapter : public ICarAdapter
{
public:
    Car toCar(const QJsonObject &json) const override;
    QList<Car> toCarList(const QJsonArray &json) const override;
    QList<Car> toCarListFromRoot(const QJsonObject &root) const override;
};

#endif // CAR_JSON_ADAPTER_H