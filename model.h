#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QStack>
#include "studyquestion.h"
#include "morsetranslator.h"

class model : public QObject
{
    Q_OBJECT
    QVector<StudyQuestion> level;
    int currentQuestion;
    MorseTranslator translator;
    bool continueFlashing;

    void generateBasics(QVector<QString> wordList);
    void generateStudyQuestion(QVector<QString> wordList);
    void generateRandomQuestions(int numberOfQuestions, QVector<QString> wordList);
    static QVector<QString> readWordList(int levelNumber);

//    void flashMorsePhrase(QString phrase);

public:
    explicit model(QObject *parent = nullptr);

    void generateLevel(int levelNumber);
    StudyQuestion getNextQuestion();
    StudyQuestion getPreviousQuestion();
    StudyQuestion getCurrentQuestion();
    bool isCorrectAnswer(QString answer);
    void flashTextPhrase(QString phrase);

signals:
    void goToStudyMenu();
    void flashOn();
    void flashOff();

private slots:
    void flashCharacter(QString phrase);

};

#endif // MODEL_H
