#include "morsetranslator.h"

#include <QMap>
#include <QString>
#include <QChar>

MorseTranslator::MorseTranslator(){
    toChar = {{".-", 'a'},{"-...", 'b'},{"-.-.", 'c'},{"-..", 'd'},{".", 'e'},{"..-.", 'f'},
              {"--.", 'g'},{"....", 'h'},{"..", 'i'},{".---", 'j'},{"-.-", 'k'},{".-..", 'l'},
              {"--", 'm'},{"-.", 'n'},{"---", 'o'},{".--.", 'p'},{"--.-", 'q'},{".-.", 'r'},
              {"...", 's'},{"-", 't'},{"..-", 'u'},{"...-", 'v'},{".--", 'w'},{"-..-", 'x'},
              {"-.--", 'y'},{"--..", 'z'}};

    toMorse = {{'a',".-"},{'b', "-..."},{'c', "-.-."},{'d',"-.."},{'e', "."},{'f', "..-."},
               {'g', "--."},{'h', "...."},{'i', ".."},{'j', ".---"},{'k', "-.-"},{'l', ".-.."},
               {'m', "--"},{'n', "-."},{'o', "---"},{'p', ".--."},{'q', "--.-"},{'r', ".-."},
               {'s', "..."},{'t', "-"},{'u', "..-"},{'v', "...-"},{'w', ".--"},{'x', "-..-"},
               {'y', "-.--"},{'z', "--.."}};
}

QString MorseTranslator::englishToMorse(QString english){
    english = english.toLower();
    QString morse = "";
    for (int i = 0; i < english.length(); i++){
        if (english[i] == ' '){
            morse.append("/ ");
        } else {
            if (toMorse.find(english[i]) != toMorse.end()) {
                morse.append(toMorse[english[i]]);
                if (i+1 != english.length())
                    morse.append(" ");
            }
            else
                qWarning("Invalid character.");
        }
    }
    return morse;
}


QString MorseTranslator::morseToEnglish(QString morse) {
    QString english = "";
    QString currentMorseCharacter = "";
    for (int i = 0; i < morse.length(); i++){
        if (morse[i] == ' '){
            if (toChar.find(currentMorseCharacter) != toChar.end())
                english.append(toChar[currentMorseCharacter]);
            else
                qWarning("Invalid morse character.");

            currentMorseCharacter = "";

            // Check next char for another space, short circuiting first if end of string reached.
            if(i+1 != morse.length() && morse[i+1] == '/'){
                i += 2;
                english.append(' ');
            }
        } else
            currentMorseCharacter.append(morse[i]);
    }
    if (toChar.find(currentMorseCharacter) != toChar.end())
        english.append(toChar[currentMorseCharacter]);
    else
        qWarning("Invalid morse character.");
    return english;
}
