#include "createdevicedialog.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QDate>

CreateDeviceDialog::CreateCarDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Создать устройство");
    setMinimumWidth(400);

    m_model          = new QLineEdit(this);
    m_brand         = new QDoubleSpinBox(this);
    m_year    = new QCheckBox("Беспроводное", this);
    m_mileage     = new QComboBox(this);
    m_description  = new QDateEdit(this);

    // Настройки полей
    m_name->setPlaceholderText("Название устройства");

    m_price->setRange(0.0, 999999.99);
    m_price->setDecimals(2);
    m_price->setSuffix(" ₽");
    m_price->setValue(0.0);

    m_condition->addItems({"new", "used", "refurbished", "damaged"});
    m_condition->setCurrentText("new");

    m_purchaseDate->setDate(QDate::currentDate());
    m_purchaseDate->setDisplayFormat("yyyy-MM-dd");
    m_purchaseDate->setCalendarPopup(true);

    // Форма
    auto *form = new QFormLayout();
    form->addRow("Название:",        m_name);
    form->addRow("Цена:",            m_price);
    form->addRow("",                 m_isWireless);
    form->addRow("Состояние:",       m_condition);
    form->addRow("Дата покупки:",    m_purchaseDate);

    auto *buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(buttons);
}

QJsonObject CreateDeviceDialog::deviceData() const
{
    QJsonObject obj;

    obj["model"] = m_model->text();
    obj["brand"] = m_brand->text();
    obj["year"] = m_year->value();
    obj["mileage"] = m_mileage->value();
    obj["price"] = m_price->value();
    obj["description"] = m_description->text();
    return obj;
}

CreateDeviceDialog::CreateDeviceDialog(const Device& device, QWidget *parent)
    : CreateDeviceDialog(parent)  // вызываем основной конструктор
{
    m_name->setText(device.name);
    m_price->setValue(device.price);
    m_isWireless->setChecked(device.isWireless);
    m_condition->setCurrentText(device.condition);
    m_purchaseDate->setDate(device.purchaseDate);
}