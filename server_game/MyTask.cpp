#include "MyTask.h"

MyRunnable::MyRunnable(MyServer* server, QTcpSocket* socket){
    this->server = server;
    this->socket = socket;
}

void MyRunnable::run(){
    qDebug() << "Running...";
    server->process(socket);
}
