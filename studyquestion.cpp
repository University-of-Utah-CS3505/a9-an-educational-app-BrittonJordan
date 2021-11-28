#include "studyquestion.h"
#include <QString>

StudyQuestion::StudyQuestion()
{
}

StudyQuestion::StudyQuestion(QString question, QString answer):question(question), answer(answer){

}

QString StudyQuestion::getTitle(){
    return title;
}

QString StudyQuestion::getQuestion(){
    return question;
}

QString StudyQuestion::getAnswer(){
    return answer;
}

void StudyQuestion::setTitle(QString title){
    this->title = title;
}

bool StudyQuestion::checkIsCorrect(QString answer){
    return this->answer == answer;
}
