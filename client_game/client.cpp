#include "client.h"
#include "JsonHelper.h"


Client::Client(QObject *parent) :
    QObject(parent)
{
    user = "Test_user";
}

bool Client::Connect()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress::Any, PORT);

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
        return true;
    }
    else
    {
        return false;
    }
}


void Client::send(QString user, QString action, QString data){
    QString message = action + "&" + user + "&" + data + "&\r\n";
    socket->write(message.toLocal8Bit());
    socket->waitForBytesWritten(1000    );
}

QString Client::receive(){
    socket->waitForReadyRead(60000);
    QByteArray data = socket->readAll();
    return QString(data);
}

void Client::PlayGame(int mode){
    this->currentQuestion = 0;
    this->questions.clear();
    send(user, "START_GAME", QString::number(mode));
    QString receiveData = receive();
    if(receiveData.isEmpty()) return;
    handle(receiveData);
}

void Client::register_(User user){
    send(user.username, "REGISTER", user.password);
}

bool Client::login_(User user){
    send(user.username, "LOGIN", user.password);
    QString response = receive();
    if(response.startsWith("LOGIN_SUCCESS")){
        QString scoreInfo = response.split("&")[1];
        QStringList dmm = scoreInfo.split("|");
        user.score = dmm[0];
        user.rank = dmm[1].split("\r")[0];
        this->_user = user;
        return true;
    }
    return false;
}

void Client::process(){

}

void Client::handle(QString message){
    qDebug() << message;
    QStringList elements = message.split("&");
    if(elements.size() < 2) return;
    QString action = elements[0];
    QString data = elements[1];
    if(action == "QUESION_LIST"){
        QVector<Question> questions = convertByteArrayToQuestion(data.toUtf8());
        for(int i=0; i<questions.size(); i++) questions[i].id = i;
        this->questions = questions;
        this->currentQuestion = 0;
    }
}

QVector<History> Client::getHistoryScore(){
     QVector<History> result;
     send(user, "GET_HISTORY", "Hello");
     QString response = receive();
     if(response.startsWith("GET_HISTORY_RESPONSE")){
         QStringList tmp = response.split("&");
         if(tmp.size() > 1){
             QString datas = tmp.at(1);
             QStringList tokens = datas.split("|");
             for(QString value: tokens){
                 if(value.size() > 5){
                    QStringList elements = value.split(",");
                    History h;
                    h.user = elements[0];
                    h.event = elements[1];
                    h.score = elements[2];
                    h.date = elements[3];
                    result.push_back(h);
                 }
             }
         }

     }
     return result;
}


QString Client::waitForPvPRequest(){
    socket->waitForReadyRead(30000);
    QByteArray data = socket->readAll();
    return QString(data);
}

void Client::updateScore(int score){

            int sc = _user.score.toInt();
            sc += score;
            if(sc < 0) sc = 0;
            int div = sc / 10;
            if(div == 0)
                _user.rank = "Bronze";
            if(div == 1)
                _user.rank = "Silver";
            if(div == 2)
                _user.rank = "Gold";
            if(div == 3)
                _user.rank = "PLATINUM";
            if(div == 4)
                _user.rank = "MASTER";
            _user.score = QString::number(sc);



}
