#ifndef WIN_MAIN_H
#define WIN_MAIN_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <Qdebug>
#include <QTimer>

#define baseURL QString("http://") + serverIP + QString("/")

namespace Ui {
class win_main;
}

class win_main : public QWidget
{
    Q_OBJECT

public:
    explicit win_main(QWidget *parent = 0);
    ~win_main();

private slots:
    void on_pushButton_clicked();
    void showAnswer(QNetworkReply *reply);
    void replyTimeout();

private:
    Ui::win_main *ui;
    QNetworkAccessManager* manager;
    QString serverIP = "127.0.0.1";
    QTimer* timer;
};

#endif // WIN_MAIN_H
