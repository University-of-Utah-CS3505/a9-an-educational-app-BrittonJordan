#ifndef MORSETRANSLATOR_H
#define MORSETRANSLATOR_H

#include <QMap>
#include <QString>
#include <QChar>

class MorseTranslator{

private:
    static QMap<QString, QChar> toChar;
    static QMap<QChar, QString> toMorse;

public:
    MorseTranslator();

    QString morseToEnglish(QString morse);

    QString englishToMorse(QString english);





};


#endif // MORSETRANSLATOR_H
