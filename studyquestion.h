#ifndef STUDYQUESTION_H
#define STUDYQUESTION_H

#include <iostream>
#include <QString>

class StudyQuestion
{
    QString title;
    QString question;
    QString answer;

public:
    StudyQuestion();
    StudyQuestion(QString question, QString answer);

    QString getTitle();
    QString getQuestion();
    QString getAnswer();

    bool checkIsCorrect(QString answer);
    void setTitle(QString title);
};

#endif // STUDYQUESTION_H
