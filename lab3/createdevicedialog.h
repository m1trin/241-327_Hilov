#ifndef CREATEDEVICEDIALOG_H
#define CREATEDEVICEDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include "car.h"

class QLineEdit;
class QDoubleSpinBox;
class QComboBox;
class QCheckBox;
class QDateEdit;

class CreateDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDeviceDialog(QWidget *parent = nullptr);
    explicit CreateDeviceDialog(const Device& device, QWidget *parent = nullptr);  // ← добавить
    QJsonObject deviceData() const;

private:
    QLineEdit *m_model;
    QLineEdit *m_brand;
    QSpinBox *m_year;
    QSpinBox *m_mileage;
    QDoubleSpinBox *m_price;
    QLineEdit *m_description;
};

#endif // CREATEDEVICEDIALOG_H