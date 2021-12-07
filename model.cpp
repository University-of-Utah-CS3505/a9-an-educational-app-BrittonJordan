#include "model.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "morsetranslator.h"
#include <QTimer>

model::model(QObject *parent) : QObject(parent), currentQuestion(0), continueFlashing(true)
{
   readFieldPhrasesFile();
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
        emit rainConfetti();
        StudyQuestion blank("blank", "blank");
        return blank;
    }
    else{
        emit rainConfetti();
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

void model::readFieldPhrasesFile(){

    QFile phraseFile(":/levelLists/FieldPhrases.txt");
    if (!phraseFile.open(QIODevice::ReadOnly)){
        qWarning("Field Practice phrase file not found.");
        return;
    }


    QTextStream phrases(&phraseFile);
    while (!phrases.atEnd()){
        QString phraseAndDescription = phrases.readLine();
        int i = 0;

        // Read line until end of phrase found
        QString phrase = "";
        while (i < phraseAndDescription.length()){
            QChar currentChar = phraseAndDescription.at(i);
            if (currentChar == ':'){
                i++;
                break;
            }
            else
                phrase.append(currentChar);
            i++;
        }

        // Read the rest of the line to retrieve description.
        QString description = "";
        while (i < phraseAndDescription.length()){
            description.append(phraseAndDescription.at(i));
            i++;
        }

        fieldPhrases.push_back(phrase);
        fieldPhraseDescriptions[phrase] = description;
    }
}

QString model::getFieldPracticePhrase(){
    int index = rand() % fieldPhrases.length();
    return fieldPhrases[index];
}

QString model::getCurrentPhraseDescription(){
    QString phrase = translator.morseToEnglish(currentPhrase);
    return fieldPhraseDescriptions[phrase];
}

int model::getFieldPhrasesCount(){
    return fieldPhrases.length();
}

bool model::correctFieldAnswer(QString answer){
    return answer.trimmed() == currentPhrase;
}

void model::retryFieldQuestion(){
    flashTextPhrase(currentPhrase);
}

void model::flashNewPhrase(){
    QString newPhrase = getFieldPracticePhrase();
    flashTextPhrase(newPhrase);
}

void model::flashTextPhrase(QString textPhrase){
    currentPhrase = textPhrase;
    flashingPhrase = translator.englishToMorse(textPhrase);

    std::cout<<"Flashing: " << textPhrase.toStdString() <<std::endl;
    continueFlashing = true;
    flashCharacter();
}

void model::stopFlashing(){
    continueFlashing = false;
}

void model::flashCharacter(){
    int phraseLength = flashingPhrase.length();
    if(phraseLength == 0)
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
    if(!continueFlashing){
        emit flashOff();
        return;
    }
    QTimer::singleShot(waitTime, this, SLOT(flashOffCharacter()));
}

void model::flashOffCharacter(){
    emit flashOff();
    QTimer::singleShot(ditTime, this, SLOT(flashCharacter()));
}

int model::getDitTime(){
    return ditTime;
}

