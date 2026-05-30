#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QInputDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_client = HttpClient::getInstance();

    connect(m_client, &HttpClient::dataReceived,
            this, &MainWindow::onDataReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QJsonObject MainWindow::inputCarData()
{
    QJsonObject json;

    bool ok = false;

    QString model = QInputDialog::getText(this, "Car", "Model:", QLineEdit::Normal, "", &ok);
    if (!ok) return QJsonObject();

    QString brand = QInputDialog::getText(this, "Car", "Brand:", QLineEdit::Normal, "", &ok);
    if (!ok) return QJsonObject();

    int year = QInputDialog::getInt(this, "Car", "Year:", 2024, 1900, 2100, 1, &ok);
    if (!ok) return QJsonObject();

    int mileage = QInputDialog::getInt(this, "Car", "Mileage:", 0, 0, 9999999, 1, &ok);
    if (!ok) return QJsonObject();

    double price = QInputDialog::getDouble(this, "Car", "Price:", 0, 0, 999999999, 2, &ok);
    if (!ok) return QJsonObject();

    QString description = QInputDialog::getText(this, "Car", "Description:", QLineEdit::Normal, "", &ok);
    if (!ok) return QJsonObject();

    json["model"] = model;
    json["brand"] = brand;
    json["year"] = year;
    json["mileage"] = mileage;
    json["price"] = price;
    json["description"] = description;

    return json;
}

void MainWindow::printCar(const Car &car)
{
    ui->outputTextEdit->append(
        QString("ID: %1\n"
                "Model: %2\n"
                "Brand: %3\n"
                "Year: %4\n"
                "Mileage: %5\n"
                "Price: %6\n"
                "Description: %7\n"
                "Date: %8\n"
                "---------------------------")
            .arg(car.id)
            .arg(car.model)
            .arg(car.brand)
            .arg(car.year)
            .arg(car.mileage)
            .arg(car.price)
            .arg(car.description)
            .arg(car.date)
        );
}

void MainWindow::onDataReceived(const QByteArray &data)
{
    ui->outputTextEdit->clear();

    if (data.isEmpty()) {
        ui->outputTextEdit->append("Готово.");
        return;
    }

    qDebug() << "RAW RESPONSE:" << data;

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull()) {
        ui->outputTextEdit->append(QString::fromUtf8(data));
        return;
    }

    if (doc.isArray()) {
        QList<Car> cars = m_adapter.toCarList(doc.array());

        qDebug() << "Cars count:" << cars.size();
        ui->outputTextEdit->append(QString("Получено машин: %1").arg(cars.size()));

        for (const Car &car : cars) {
            printCar(car);
            qDebug() << "CAR:" << car.id << car.brand << car.model;
        }

        return;
    }

    if (doc.isObject()) {
        QJsonObject root = doc.object();

        if (root.contains("cars")) {
            QList<Car> cars = m_adapter.toCarListFromRoot(root);

            ui->outputTextEdit->append(QString("Получено машин: %1").arg(cars.size()));

            for (const Car &car : cars) {
                printCar(car);
                qDebug() << "CAR:" << car.id << car.brand << car.model;
            }

            return;
        }

        Car car = m_adapter.toCar(root);
        printCar(car);

        qDebug() << "CAR:" << car.id << car.brand << car.model;
        return;
    }

    ui->outputTextEdit->append(QString::fromUtf8(data));
}

void MainWindow::on_getAllButton_clicked()
{
    ui->outputTextEdit->clear();
    ui->outputTextEdit->append("GET /api/cars/");

    m_client->list();
}

void MainWindow::on_getByIdButton_clicked()
{
    int id = ui->idSpinBox->value();

    ui->outputTextEdit->clear();
    ui->outputTextEdit->append(QString("GET /api/cars/%1/").arg(id));

    m_client->get(id);
}

void MainWindow::on_createButton_clicked()
{
    QJsonObject json = inputCarData();

    if (json.isEmpty()) {
        return;
    }

    QJsonDocument doc(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    qDebug() << "CREATE:" << data;

    ui->outputTextEdit->clear();
    ui->outputTextEdit->append("POST /api/cars/");

    m_client->create(data);
}

void MainWindow::on_updateButton_clicked()
{
    int id = ui->idSpinBox->value();

    QJsonObject json = inputCarData();

    if (json.isEmpty()) {
        return;
    }

    QJsonDocument doc(json);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    qDebug() << "UPDATE:" << id << data;

    ui->outputTextEdit->clear();
    ui->outputTextEdit->append(QString("PUT /api/cars/%1/").arg(id));

    m_client->update(id, data);
}

void MainWindow::on_deleteButton_clicked()
{
    int id = ui->idSpinBox->value();

    ui->outputTextEdit->clear();
    ui->outputTextEdit->append(QString("DELETE /api/cars/%1/").arg(id));

    m_client->remove(id);
}