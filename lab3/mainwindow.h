#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "httpclient.h"
#include "car_json_adapter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onDataReceived(const QByteArray &data);

    void on_getAllButton_clicked();
    void on_getByIdButton_clicked();
    void on_createButton_clicked();
    void on_updateButton_clicked();
    void on_deleteButton_clicked();

private:
    QJsonObject inputCarData();
    void printCar(const Car &car);

private:
    Ui::MainWindow *ui;
    HttpClient *m_client = nullptr;
    CarJsonAdapter m_adapter;
};

#endif // MAINWINDOW_H