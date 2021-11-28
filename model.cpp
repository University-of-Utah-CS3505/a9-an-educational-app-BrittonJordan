#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "morsetranslator.h"

model::model(QObject *parent) : QObject(parent), currentQuestion(0)
{
}

void model::generateLevel(int levelNumber){
    QVector<QString> wordList = model::readWordList(levelNumber);
    generateBasics(wordList);
    // Then increase word size

    // etc.
}

void model::generateBasics(QVector<QString> wordList){
    int numberOfQuestions = 10;

    // Remove non-basic strings from the word list
    for(QString& word : wordList){
        if(word.length() != 1){
            wordList.removeAll(word);
        }
    }

    // Teach the new letters
    for(QString& letter : wordList){
        QString question = "The letter ";
        question.append(letter);
        question.append(" is represented by ");

        QString answer = translator.englishToMorse(letter);

        StudyQuestion newQuestion(question, answer);
        QString title = "Learn new letters:";
        newQuestion.setTitle(title);
        level.append(newQuestion);
        numberOfQuestions--;
    }

    // Create random questions for the new letters
    int numLetters = wordList.length() - 1;
    while(numberOfQuestions > 0){
        int randIndex = rand() % numLetters;
        QString currLetter = wordList[randIndex];
        QString currCode = translator.englishToMorse(currLetter);

        int randType = rand() % 2;
        if(randType == 0){
            QString question = "What is the Morse code representation of '";
            question.append(currLetter);
            question.append("'");
            StudyQuestion newQuestion(question, currCode);
            level.append(newQuestion);
        }
        else {
            QString question = "What letter does '";
            question.append(currCode);
            question.append("' represent?");
            StudyQuestion newQuestion(question, currLetter);
            level.append(newQuestion);
        }
        numberOfQuestions--;
    }
}

StudyQuestion model::getNextQuestion(){
    currentQuestion++;
    return level[currentQuestion];
}

StudyQuestion model::getCurrentQuestion(){
    return level[currentQuestion];
}

bool model::isCorrectAnswer(QString answer){
    return level[currentQuestion].checkIsCorrect(answer);
}

QVector<QString> model::readWordList(int levelNumber){
    QVector<QString> wordList;

    QString filename = ":/levelLists/Level";
    filename.append(QString::number(levelNumber));
    filename.append(".txt");
    QFile file(filename);

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            QString line = stream.readLine();
            if(line != "")
                wordList.push_back(line);
        }
    }
    else{
        qDebug() <<"File could not be opened";
    }

    return wordList;
}
