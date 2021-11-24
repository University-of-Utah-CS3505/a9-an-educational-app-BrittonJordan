#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QStack>

class model : public QObject
{
    Q_OBJECT
    QStack<std::string> levelLetters;
    QStack<std::string> levelCodes;
    std::string currentCorrectAnswer;

public:
    explicit model(QObject *parent = nullptr);

    void generateLevel(int level);
    std::string getNextQuestion();
    bool isCorrectAnswer(std::string answer);

signals:


};

#endif // MODEL_H
