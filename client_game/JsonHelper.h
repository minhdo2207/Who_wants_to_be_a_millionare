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

#include "Question.h"

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
#endif // JSONHELPER_H
