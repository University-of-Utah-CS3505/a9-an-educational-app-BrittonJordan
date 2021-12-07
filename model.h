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
    QString flashingPhrase;
    QString currentPhrase;
    const int ditTime = 160;
    QList<QString> fieldPhrases;
    QMap<QString, QString> fieldPhraseDescriptions;


    void generateBasics(QVector<QString> wordList);
    void generateStudyQuestion(QVector<QString> wordList);
    void generateRandomQuestions(int numberOfQuestions, QVector<QString> wordList);
    void readFieldPhrasesFile();
    void flashTextPhrase(QString phrase);

    static QVector<QString> readWordList(int levelNumber);

public:
    explicit model(QObject *parent = nullptr);
    void generateLevel(int levelNumber);
    StudyQuestion getNextQuestion();
    StudyQuestion getPreviousQuestion();
    StudyQuestion getCurrentQuestion();
    bool isCorrectAnswer(QString answer);
    QString getFieldPracticePhrase();
    QString getCurrentPhraseDescription();
    int getFieldPhrasesCount();
    bool correctFieldAnswer(QString answer);
    void retryFieldQuestion();
    void flashNewPhrase();
    void stopFlashing();
    int getDitTime();

signals:
    void goToStudyMenu();
    void rainConfetti();
    void flashOn();
    void flashOff();

private slots:
    void flashCharacter();
    void flashOffCharacter();

};

#endif // MODEL_H
