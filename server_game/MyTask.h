#ifndef MYTASK_H
#define MYTASK_H
#include <QRunnable>
#include <QTcpSocket>
#include "server.h"

class MyRunnable : public QRunnable
{
public:
    MyRunnable(MyServer* server, QTcpSocket* socket);
protected:
    void run();


public:
    MyServer* server;
    QTcpSocket* socket;
};
#endif // MYTASK_H
