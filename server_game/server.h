#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QDebug>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QVector>
#include <QString>
#include <QMap>
#include "User.h"
#include <QThreadPool>
#include "History.h"


#define PORT 8081

#define _QUESTION_FILE  "/home/repo/capstoneproject/server_game/questions.json"
#define _USER_FILE  "/home/repo/capstoneproject/server_game/users.txt"
#define _HISTORY_PATH  "/home/repo/capstoneproject/server_game/"

class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);

    void send(QTcpSocket *socket, QString action, QString data);
    QString receive(QTcpSocket *socket);
    void process(QTcpSocket* socket);
    User getByUsername(QString username);
    void handle(QTcpSocket* socket, QString message);
    bool checkLogin(User user);
    void updateScore(QString user, int score);
signals:

public slots:
    void newConnection();

protected:
    void incomingConnection(qintptr handle);

public:
    QTcpServer *server;
    QVector<User> users;
    QMap<QString, QString> waitings;
    QMap<QString, QTcpSocket*> socketMap;
    QThreadPool *pool;
    QMap<QString, History> pvpResult;
};
#endif // SERVER_H
