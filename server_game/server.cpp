
#include "server.h"
#include<iostream>
#include "JsonHelper.h"
#include "MyThread.h"
#include "MyTask.h"
#include    <QDateTime>

MyServer::MyServer(QObject *parent) :
    QObject(parent)
{
    this->pool = new QThreadPool(this);
    this->pool->setMaxThreadCount(5);

    this->users = readUser(_USER_FILE);

    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, PORT))
    {
        qDebug() << "Server could not start!";
    }
    else
    {
        qDebug() << "Server started!";
        qDebug() << "Waiting for connection...";

        while(server->waitForNewConnection(100000000)){

        }
    }
}

void MyServer::newConnection()
{

    if(!server->hasPendingConnections()) return;
    //while(true){
    qDebug() << "New Client Connected!";
        QTcpSocket *socket = server->nextPendingConnection();
//        process(socket);
        MyRunnable *task = new MyRunnable(this, socket);
        task->setAutoDelete(true);
        this->pool->start(task);
   // }
}

void MyServer::send(QTcpSocket *socket, QString action, QString data){
    QString message = action + "&" + data + "\r\n";
    socket->write(message.toLocal8Bit());
    socket->waitForBytesWritten(1000);
}

QString MyServer::receive(QTcpSocket *socket){
    socket->waitForReadyRead(60000);
    QByteArray data = socket->readAll();
    return QString(data);
}


void MyServer::process(QTcpSocket* socket){

    while(socket->isOpen()){
        socket->waitForReadyRead(60000);
        QByteArray bytes = socket->readAll();
        if(bytes.isEmpty()) continue;
        QString message = QString(bytes);
        qDebug() << message;

        handle(socket, message);
    }
}

void MyServer::handle(QTcpSocket* socket, QString message){
    qDebug() << message;
    QStringList elements = message.split("&");
    if(elements.size() < 3) return;
    QString action = elements[0];
    QString user = elements[1];
    QString data = elements[2];

    if(action == "START_GAME"){
        QVector<Question> question = readJson(_QUESTION_FILE);
        QVector<Question> qMode;

        if(data == "1"){
            for(Question q: question){
                if(q.hard == 1){
                    qMode.push_back(q);
                }
            }
        }
        if(data == "2"){
            for(Question q: question){
                if(q.hard == 2){
                    qMode.push_back(q);
                }
            }
        }
        QByteArray quesionJson = toJson(qMode);
        send(socket, "QUESION_LIST", QString(quesionJson));
    }

    if(action == "REGISTER"){
        User u;
        u.username = user;
        u.password = data;
        u.score = "0";
        u.rank = "Bronze";
        this->users.push_back(u);
        addUser(_USER_FILE, u);
        send(socket, "REGISTER_SUCCESS", user);
    }

    if(action == "LOGIN"){
        User u;
        u.username = user;
        u.password = data;

        if(checkLogin(u)){
            this->socketMap[u.username] = socket;
            User myUser = getByUsername(u.username);
            send(socket, "LOGIN_SUCCESS", myUser.score + "|" + myUser.rank);
//            User user = getByUsername(u.username);
            qDebug() << "User " << u.username << " online...";
//            if(user.username != "-1")
//                onlines[user.username] = user;
        } else {
            send(socket, "LOGIN_FAIL", user);

        }
    }

    if(action == "END_GAME"){
        History h;
        h.user = user;
        QStringList tmp = data.split("|");

        h.score = tmp[0];
        h.event = tmp[1];

        QDateTime date = QDateTime::currentDateTime();
        h.date = date.toString("yyyy-MM-dd");

        if(h.event.startsWith("PvP")){
            QStringList tmp = h.event.split(" ");
            QString userPvp = tmp[2];
            if(pvpResult.find(userPvp) != pvpResult.end()){
                QString user1Result = h.score;
                QString user2Result = pvpResult[userPvp].score;

                if(user1Result > user2Result){
                    updateScore(h.user, 1);
                    updateScore(userPvp, -1);
                    fflushUserData(_USER_FILE, users);

                    send(socket, "PVP_RESULT", "YOU WIN! Competitor's Score: " + user1Result);
                    send(socketMap[userPvp], "PVP_RESULT", "YOU LOSE! Competitor's Score: " + user2Result);
                }
                else if(user1Result == user2Result){
                    send(socket, "PVP_RESULT", "DRAW!");
                    send(socketMap[userPvp], "PVP_RESULT", "DRAW!");
                }
                else {
                    updateScore(h.user, -1);
                    updateScore(userPvp, 1);
                    fflushUserData(_USER_FILE, users);
                    send(socket, "PVP_RESULT", "YOU LOSE! Competitor's Score: " + user1Result);
                    send(socketMap[userPvp], "PVP_RESULT", "YOU WIN! Competitor's Score: " + user2Result);
                }
                pvpResult.remove(userPvp);
            } else {
                pvpResult[h.user] = h;
            }
        }

        addHistory(_HISTORY_PATH + user + "_score.txt", h);
    }

    if(action == "GET_HISTORY"){
        QVector<History> histories = readHistory(_HISTORY_PATH + user + "_score.txt");
        QString response = "";
        for(History h: histories){
            response += h.user +"," + h.event + "," + h.score + "," + h.date + "|";
        }
        send(socket, "GET_HISTORY_RESPONSE", response);
    }

    if(action == "WAIT_REQUEST"){
        waitings[user] = "1";
    }

    if(action == "DISABLE_WAIT_REQUEST"){
        waitings[user] = "0";
    }

    if(action == "SENT_PVP_REQUEST"){
        QString pvpUser = data;
        if(waitings[pvpUser] == "1" && socketMap.find(pvpUser) != socketMap.end()){
            User u1 = getByUsername(user);
            User u2 = getByUsername(pvpUser);
            if(u1.username != "-1" && u2.username != "-1"){
                int sc1 = u1.score.toInt() / 10;
                int sc2 = u2.score.toInt() / 10;
                if(sc1 - sc2 >= 2 || sc1 - sc2 <= -2){
                    send(socket, "SENT_PVP_REQUEST_not_rank", user);
                } else {
                    QTcpSocket* pvpSocket = socketMap[pvpUser];
                    send(pvpSocket, "PVP_REQUEST", user);
                    send(socket, "SENT_PVP_REQUEST_ok", user);
                }
            } else {
                send(socket, "SENT_PVP_REQUEST_fail", user);
            }
        } else {
            send(socket, "SENT_PVP_REQUEST_fail", user);
        }
    }

    if(action == "ACCEPT_PVP_REQUEST"){
        QString sentUser = data;
        if(socketMap.find(sentUser) != socketMap.end()){
            QTcpSocket* pvpSocket = socketMap[sentUser];
            qDebug() << "Sent ACCEPT_PVP_REQUEST";
            send(pvpSocket, "ACCEPT_PVP_REQUEST", user);
        }
    }

    if(action == "CONFUSE_PVP_REQUEST"){
        QString sentUser = data;
        if(socketMap.find(sentUser) != socketMap.end()){
            QTcpSocket* pvpSocket = socketMap[sentUser];
            send(pvpSocket, "CONFUSE_PVP_REQUEST", user);
        }
    }

}


bool MyServer::checkLogin(User user){
    for(User u: users){
        if(u.username == user.username && u.password == user.password)
            return true;
    }
    return false;
}


User MyServer::getByUsername(QString username){
    for(User u: users){
        if(u.username == username)
            return u;
    }

    User u;
    u.username = "-1";
    return u;
}

void MyServer::updateScore(QString user, int score){
    for(int i=0; i<users.size(); i++){
        if(users[i].username == user){
        qDebug() << "Update score: " << users[i].username;
            int sc = users[i].score.toInt();
            sc += score;
            if(sc < 0) sc = 0;
            int div = sc / 10;
            if(div == 0)
                users[i].rank = "Bronze";
            if(div == 1)
                users[i].rank = "Silver";
            if(div == 2)
                users[i].rank = "Gold";
            if(div == 3)
                users[i].rank = "PLATINUM";
            if(div == 4)
                users[i].rank = "MASTER";
            users[i].score = QString::number(sc);

        }
    }
}
