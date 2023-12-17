#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "server.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(MyServer* server, QTcpSocket *socket){
        this->myserver = server;
        this->socket = socket;
    }
    void run(){
        qDebug() << "Running";
//        myserver->process(this->socket);
    }



private:
    MyServer* myserver;
    QTcpSocket* socket;
};
#endif // MYTHREAD_H
