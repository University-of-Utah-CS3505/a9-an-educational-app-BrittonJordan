#include "model.h"

model::model(QObject *parent) : QObject(parent)
{

}

void model::generateLevel(int level){
    // generate the levelLetters and levelCodes Stacks from the appropriate lists
    // single character strings should be added last, popped first
}

std::string model::getNextQuestion(){
    // pick randomly between levelLetters and levelCodes
    // pop from the chosen Stack
    // stores the correct answer in currentCorrectAnswer
}

bool model::isCorrectAnswer(std::string answer){
    // compares std::string currentCorrectAnswer to answer
}
