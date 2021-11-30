#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "morsetranslator.h"

model::model(QObject *parent) : QObject(parent), currentQuestion(0)
{
}

/**
 * @brief model::generateLevel Generates a level of StudyQuestions, modifying the level instance
 * @param levelNumber
 */
void model::generateLevel(int levelNumber){
    QVector<StudyQuestion> newLevel;
    this->level = newLevel;
    QVector<QString> wordList = model::readWordList(levelNumber);
    generateBasics(wordList);
    generateStudyQuestion(wordList);
}

void model::generateStudyQuestion(QVector<QString> wordList){
    int numberOfQuestions = 10;

    // Remove basic strings from word list
    for(QString& word : wordList){
        if(word.length() == 1){
            wordList.removeAll(word);
        }
    }
    generateRandomQuestions(numberOfQuestions, wordList);
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
        QString question = "The letter '";
        question.append(letter);
        question.append("' is represented by ");

        QString answer = translator.englishToMorse(letter);

        StudyQuestion newQuestion(question, answer);
        QString title = "Learn new letters:";
        newQuestion.setTitle(title);
        level.append(newQuestion);
        numberOfQuestions--;
    }

    // Create random single-character questions
    generateRandomQuestions(numberOfQuestions, wordList);
}

void model::generateRandomQuestions(int numberOfQuestions, QVector<QString> wordList){
    int numWords = wordList.length() - 1;
    while(numberOfQuestions > 0){
        int randIndex = rand() % numWords;
        QString currWord = wordList[randIndex];
        QString currCode = translator.englishToMorse(currWord);

        int randType = rand() % 2;
        if(randType == 0){
            QString question = "What is the Morse code representation of '";
            question.append(currWord);
            question.append("'");
            StudyQuestion newQuestion(question, currCode);
            level.append(newQuestion);
        }
        else {
            QString question = "What sequence of letters does '";
            question.append(currCode);
            question.append("' represent?");
            StudyQuestion newQuestion(question, currWord);
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
