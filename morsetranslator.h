#ifndef MORSETRANSLATOR_H
#define MORSETRANSLATOR_H

#include <QMap>
#include <QString>
#include <QChar>

class MorseTranslator{

private:
    QMap<QString, QChar> toChar;
    QMap<QChar, QString> toMorse;

public:
    MorseTranslator();
    QString morseToEnglish(QString morse);
    QString englishToMorse(QString english);
};


#endif // MORSETRANSLATOR_H
