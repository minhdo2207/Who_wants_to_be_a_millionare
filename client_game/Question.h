#ifndef QUESTION_H
#define QUESTION_H

#include<QString>
#include<QVector>

class Question{
public:
    int id;
    QString question;
    QVector<QString> answers;
    int correctAnswer;
    int hard;

};

#endif // QUESTION_H
