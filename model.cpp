#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "morsetranslator.h"
#include <QTimer>

model::model(QObject *parent) : QObject(parent), currentQuestion(0), continueFlashing(true)
{
    generateFieldPhrases();
}

/**
 * @brief model::generateLevel Generates a level of StudyQuestions.
 *                             Modifies the level instance
 * @param levelNumber Determines which word list the level is generated from
 */
void model::generateLevel(int levelNumber){
    currentQuestion = 0;
    QVector<StudyQuestion> newLevel;
    this->level = newLevel;
    QVector<QString> wordList = model::readWordList(levelNumber);
    generateBasics(wordList);
    generateStudyQuestion(wordList);
}

void model::generateStudyQuestion(QVector<QString> wordList){
    int numberOfQuestions = 10;
    QVector<QString> words;

    // Find all non-basic strings
    for(QString& word : wordList){
        if(word.length() != 1){
            words.push_back(word);
        }
    }
    generateRandomQuestions(numberOfQuestions, words);
}

void model::generateBasics(QVector<QString> wordList){
    int numberOfQuestions = 10;
    QVector<QString> allLetters;

    // Find all basic strings
    for(QString& word : wordList){
        if(word.length() == 1){
            allLetters.push_back(word);
        }
    }

    // Teach the new letters
    for(QString& letter : allLetters){
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
    if(allLetters.length() > 0)
        generateRandomQuestions(numberOfQuestions, allLetters);
}

void model::generateRandomQuestions(int numberOfQuestions, QVector<QString> wordList){
    int numWords = wordList.length() - 1;
    while(numberOfQuestions > 0){
        int randIndex = rand() % numWords;
        QString currWord = wordList[randIndex];
        QString currCode = translator.englishToMorse(currWord);

        int randType = rand() % 2;
        QString question;
        if(randType == 0){
            question = "What is the Morse code representation of '";
            question.append(currWord);
            question.append("'");
            StudyQuestion newQuestion(question, currCode);
            level.append(newQuestion);
        }
        else {
            if(currWord.length() == 1){
                question = "What letter does '";
            }
            else{
                question = "What sequence of letters does '";
            }
            question.append(currCode);
            question.append("' represent?");
            StudyQuestion newQuestion(question, currWord);
            level.append(newQuestion);
        }
        numberOfQuestions--;
    }
}

StudyQuestion model::getNextQuestion(){
    if(currentQuestion == level.length() - 1){
        emit goToStudyMenu();
        StudyQuestion blank("blank", "blank");
        return blank;
    }
    else{
        currentQuestion++;
        return level[currentQuestion];
    }
}

StudyQuestion model::getPreviousQuestion(){
    currentQuestion--;
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

void model::generateFieldPhrases(){
    fieldPhrases.append("sos"); // Distress signal
    fieldPhrases.append("c"); // Correct/Yes
    fieldPhrases.append("n"); // Incorrect/No
    fieldPhrases.append("hh"); // Error in sending
    fieldPhrases.append("nm"); // No more
    fieldPhrases.append("hi"); // Laugh (think lol)
    // Etc
}

QString model::generateFieldPracticeQuestion(){
//    int questionIndex = rand() % fieldPhrases.length();
//    return fieldPhrases[questionIndex];
    return QString("sos sos sos");
}

bool model::correctFieldAnswer(QString answer){
    return translator.englishToMorse(answer.trimmed()) == currentPhrase;
}

void model::retryFieldQuestion(){
    flashTextPhrase(currentPhrase);
}

void model::flashTextPhrase(QString textPhrase){
    currentPhrase = translator.englishToMorse(textPhrase);
    flashingPhrase = translator.englishToMorse(textPhrase);
    std::cout<<flashingPhrase.toStdString()<<std::endl;
    flashCharacter();
}

void model::flashCharacter(){
    int phraseLength = flashingPhrase.length();
    if(phraseLength == 0 || !continueFlashing)
        return;

    const int dahTime = 3*ditTime;
    const int wordSpaceTime = ditTime;

    QChar currChar = flashingPhrase[0];

    int waitTime;
    if(currChar == '.'){
        emit flashOn();
        waitTime = ditTime;
    }
    else if(currChar == '-'){
        emit flashOn();
        waitTime = dahTime;
    }
    else if(currChar == ' '){
        waitTime = ditTime;
    }
    else{
        waitTime = wordSpaceTime;
    }
    flashingPhrase = flashingPhrase.right(phraseLength - 1);
    QTimer::singleShot(waitTime, this, SLOT(flashOffCharacter()));
}

void model::flashOffCharacter(){
    emit flashOff();
    QTimer::singleShot(ditTime, this, SLOT(flashCharacter()));
}
