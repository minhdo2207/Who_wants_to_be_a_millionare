#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyServer myserver;
//    QVector<Question> q = readJson("/home/canngocbinh/Documents/server_game/questions.json");
//    QByteArray response = toJson(q);

//    QVector<Question> q2 = convertByteArrayToQuestion(response);
//    print(q2);


    return a.exec();
}
