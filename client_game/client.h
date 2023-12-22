#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QDebug>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QMainWindow>
#include "Question.h"
#include <QVector>
#include "User.h"
#include "History.h"
#define PORT 8081

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    bool Connect();

    void PlayGame(int mode);

    void send(QString user, QString action, QString data);
    void process();
    QString receive();
    void register_(User user);
    bool login_(User user);
    void handle(QString message);
    QVector<History> getHistoryScore();
    QString waitForPvPRequest();
    void updateScore(int score);
signals:

public slots:

public:
    QTcpSocket *socket;
    QString user;
    User _user;
    bool isReady = false;
    QVector<Question> questions;
    int currentQuestion;
};
#endif // CLIENT_H
