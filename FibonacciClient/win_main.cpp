#include "win_main.h"
#include "ui_win_main.h"

win_main::win_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::win_main)
{
    ui->setupUi(this);

    ui->textEdit->setReadOnly(1);
    ui->lineEdit_length->setReadOnly(1);

    ui->lineEdit_timeout->setValidator(new QIntValidator(0, 60000));
    ui->lineEdit_input->setValidator(new QIntValidator(0, 1000000000));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(replyTimeout()));
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(showAnswer(QNetworkReply*)));
}

win_main::~win_main()
{
    delete manager;
    delete timer;
    delete ui;
}

void win_main::on_pushButton_clicked()
{
    if (ui->lineEdit_serverip->text() != "")
        serverIP = ui->lineEdit_serverip->text();
    else
        serverIP = "127.0.0.1";

    QNetworkRequest req;
    req.setUrl(baseURL + ui->lineEdit_input->text());
    manager->get(req);

    if (QVariant(ui->lineEdit_timeout->text()).toInt())
        timer->start(QVariant(ui->lineEdit_timeout->text()).toInt());
    else
        timer->start(20000);

    ui->pushButton->setText("Calculating...");
    ui->pushButton->setDisabled(1);

    ui->lineEdit_input->setFocus();
}

void win_main::showAnswer(QNetworkReply *reply)
{
    QJsonDocument JDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject replyObj = JDoc.object();

    if (!timer->remainingTime())
        return;
    timer->stop();

    if (replyObj["code"] == 200)
    {
        ui->textEdit->setText(replyObj["answer"].toString());
        ui->lineEdit_length->setText(QVariant(replyObj["answer"].toString().size()).toString());
    }
    else
    {
        ui->textEdit->setText(replyObj["message"].toString());
        ui->lineEdit_length->setText("");
    }

    ui->pushButton->setText("Calculate");
    ui->pushButton->setDisabled(0);
}

void win_main::replyTimeout()
{
    ui->textEdit->setText("Request timeout...");
    ui->lineEdit_length->setText("");

    ui->pushButton->setText("Calculate");
    ui->pushButton->setDisabled(0);
}
