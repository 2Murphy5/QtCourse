#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QHostAddress>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QJsonObject>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->loginpage);
    m_chatClient=new ChatClient(this);
    connect(m_chatClient,&ChatClient::connected,this,&MainWindow::connectedToServer);

    connect(m_chatClient,&ChatClient::jsonReceived,this,&MainWindow::jsonReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    m_chatClient->connectToServer(QHostAddress(ui->serverEdit->text()),1967);
}


void MainWindow::on_sayButton_clicked()
{
    QString messageText = ui->saylineEdit->text();
    if (!messageText.isEmpty()) {
        //m_chatClient->sendMessage(messageText, "message");
        m_chatClient->sendMessage(ui->saylineEdit->text(), "message");
        ui->roomtextEdit->append(QString("Me: %1").arg(messageText));  // 直接更新 roomtextEdit
        ui->saylineEdit->clear();  // 清空输入框
    }
}


void MainWindow::on_logoutButton_clicked()
{
    m_chatClient->disconnectFromHost();
    ui->stackedWidget->setCurrentWidget(ui->loginpage);
    for (auto aItem : ui->userlistWidget->findItems(ui->usernameEdit->text(), Qt::MatchExactly)) {
        qDebug("remove");
        ui->userlistWidget->removeItemWidget(aItem);
        delete aItem;
    }

}

void MainWindow::connectedToServer()
{
    ui->stackedWidget->setCurrentWidget(ui->chatpage);
    m_chatClient->sendMessage(ui->usernameEdit->text(),"login");
}

void MainWindow::messageReceived(const QString &sender, const QString &text)
{
    ui->roomtextEdit->append(QString("%1 : %2").arg(sender).arg(text));
    //ui->roomtextEdit->append(QString("%1 %2").arg(sender, text));
   //ui->roomtextEdit->append("Test message");

}

void MainWindow::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if (typeVal.isNull() ||!typeVal.isString())
        return;

    if (typeVal.toString().compare("message", Qt::CaseInsensitive) == 0) {
        const QJsonValue textVal = docObj.value("text");
        const QJsonValue senderVal = docObj.value("sender");
        if (textVal.isNull() ||!textVal.isString())
            return;
        if (senderVal.isNull() ||!senderVal.isString())
            return;

        messageReceived(senderVal.toString(),textVal.toString());
    } else if (typeVal.toString().compare("newuser", Qt::CaseInsensitive) == 0) {
        const QJsonValue usernameVal = docObj.value("username");
        if (usernameVal.isNull() ||!usernameVal.isString())
            return;

        userJoined(usernameVal.toString());

    }
    else if (typeVal.toString().compare("userdisconnected", Qt::CaseInsensitive) == 0) {
        const QJsonValue usernameVal = docObj.value("username");
        if (usernameVal.isNull() ||!usernameVal.isString())
            return;

        userLeft(usernameVal.toString());

    }
    else if (typeVal.toString().compare("userlist", Qt::CaseInsensitive) == 0) {
        const QJsonValue userlistVal = docObj.value("userlist");
        if (userlistVal.isNull() ||!userlistVal.isArray())
            return;
        qDebug()<<userlistVal.toVariant().toStringList();
        userListReceived(userlistVal.toVariant().toStringList());
        userLeft(userlistVal.toString());

    }
}

void MainWindow::userJoined(const QString &user)
{
    ui->userlistWidget->addItem(user);
}

void MainWindow::userLeft(const QString &user)
{
    for (auto aItem : ui->userlistWidget->findItems(user, Qt::MatchExactly)) {
        qDebug("remove");
        ui->userlistWidget->removeItemWidget(aItem);
        delete aItem;
    }
}

void MainWindow::userListReceived(const QStringList &list)
{
    ui->userlistWidget->clear();
    // 使用addItems函数
    ui->userlistWidget->addItems(list);
}

