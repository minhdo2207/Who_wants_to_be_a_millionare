#ifndef JSONHELPER_H
#define JSONHELPER_H
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "User.h"
#include "Question.h"
#include "History.h"

QString convert(QString data){
    return data;
}

QVector<Question> readJson(QString fileName){
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument jsonDocs;
    QByteArray tmp = file.readAll();
    QJsonParseError error;
    jsonDocs = QJsonDocument::fromJson(tmp, &error);
    file.close();


    QVector<Question> result;
    if(jsonDocs.isNull()) return result;

    QJsonArray jsonArray = jsonDocs.array();

    for(int i=0; i<jsonArray.size(); i++){
        QJsonValue jsonValue = jsonArray.at(i);
        QJsonObject obj = jsonValue.toObject();
        //qDebug() << obj.value(QString("name"));

        // convert
        Question q;
        q.question = convert(obj["question"].toString());
        QJsonArray answerArray = obj.value(QString("answers")).toArray();
        for(int j=0; j<answerArray.size(); j++){
            q.answers.append(answerArray.at(j).toString());
        }
        q.correctAnswer = obj.value(QString("correctAnswer")).toInt();
        q.hard = obj.value(QString("hard")).toInt();

        result.append(q);
    }

    return result;
}

void print(QVector<Question> result){
        for(int i=0; i<result.size(); i++){
            qDebug() << result.at(i).question << " ";
            for(int j=0; j<result.at(i).answers.size(); j++){
                qDebug() << result.at(i).answers.at(j) << " ";

            }
        }
}


QVector<Question> convertByteArrayToQuestion(QByteArray tmp){
    QJsonParseError error;
    QJsonDocument jsonDocs = QJsonDocument::fromJson(tmp, &error);


    QVector<Question> result;
    if(jsonDocs.isNull()) return result;

    QJsonArray jsonArray = jsonDocs.array();

    for(int i=0; i<jsonArray.size(); i++){
        QJsonValue jsonValue = jsonArray.at(i);
        QJsonObject obj = jsonValue.toObject();
        //qDebug() << obj.value(QString("name"));

        // convert
        Question q;
        q.question = convert(obj["question"].toString());
        QJsonArray answerArray = obj.value(QString("answers")).toArray();
        for(int j=0; j<answerArray.size(); j++){
            q.answers.append(answerArray.at(j).toString());
        }
        q.correctAnswer = obj.value(QString("correctAnswer")).toInt();
        q.hard = obj.value(QString("hard")).toInt();

        result.append(q);
    }

    return result;
}

QByteArray toJson(QVector<Question> datas){
    QJsonArray arr;
    for(int i=0; i<datas.size(); i++){
        QJsonObject object;
        object.insert("question", datas[i].question);

        QJsonArray jsonAnswerArr;
        for(QString d: datas[i].answers){
            jsonAnswerArr.append(d);
        }
        object.insert("answers", jsonAnswerArr);
        object.insert("correctAnswer", datas[i].correctAnswer);
        object.insert("hard", datas[i].hard);

        arr.append(object);
    }

    QJsonDocument jsonDoc;
    jsonDoc.setArray(arr);
    return jsonDoc.toJson();

}

QVector<User> readUser(QString fileName){
    QVector<User> result;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return result;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        if(line.isEmpty()) continue;
        QStringList fields = line.split(",");
        if(fields.size() < 4) continue;
        User u;
        u.username = fields[0];
        u.password = fields[1];
        u.score = fields[2];
        u.rank = fields[3];
        result.push_back(u);
    }
    file.close();
    return result;
}

void fflushUserData(QString fileName, QVector<User> users){
        QFile file(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    for(User user: users){
        out << user.username << "," << user.password << "," << user.score << "," << user.rank << "\n";
        qDebug() << user.score;
    }
    file.close();
}

void addUser(QString fileName, User user){
        QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return;
    }

    QTextStream out(&file);

    out << user.username << "," << user.password << "," << user.score << "," << user.rank << "\n";

    file.close();
}

QVector<History> readHistory(QString fileName){
    QVector<History> result;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return result;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        if(line.isEmpty()) continue;
        QStringList fields = line.split(",");
        if(fields.size() < 4) continue;
        History u;
        u.user = fields[0];
        u.event = fields[1];
        u.score = fields[2];
        u.date = fields[3];
        result.push_back(u);
    }
    file.close();
    return result;
}


void addHistory(QString fileName, History history){

        QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return;
    }

    QTextStream out(&file);

    out << history.user << "," << history.event << "," << history.score << "," << history.date << "\n";

    file.close();
}
#endif // JSONHELPER_H
