#include "morsetranslator.h"

#include <QMap>
#include <QString>
#include <QChar>
#include <iostream>

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
    english = removeWhitespace(english.toLower());
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
        }
    }
    return morse;
}


QString MorseTranslator::morseToEnglish(QString morse) {
    morse = removeWhitespace(morse);
    QString english = "";
    QString currentMorseCharacter = "";
    for (int i = 0; i < morse.length(); i++){
        if (morse[i] == ' ' || morse[i] == '/' || morse[i] == '\\'){
            if (toChar.find(currentMorseCharacter) != toChar.end())
                english.append(toChar[currentMorseCharacter]);
            currentMorseCharacter = "";

            // Check if the user intends to input any spaces.
            int ii = i;
            while (ii < morse.length() && (morse[ii] == ' ' || morse[ii] == '/' || morse[ii] == '\\')){
                if (morse[ii] == '/' || morse[ii] == '\\'){
                    english.append(' ');
                }
                ii++;
            }

            // To prevent skipping unintended characters, only jump forward
            // in the string if more spaces or slashes were detected.
            if (ii > i + 1)
                i = ii - 1;
        } else
            currentMorseCharacter.append(morse[i]);
    }
    if (toChar.find(currentMorseCharacter) != toChar.end())
        english.append(toChar[currentMorseCharacter]);
    return english;
}


QString MorseTranslator::removeWhitespace(QString str){
    // Remove leading whitespace
    if (str.length() > 0){
        QChar currChar = str.at(0);
        int whitespaceCount = 0;
        while (currChar == ' '){
           whitespaceCount++;
           if (whitespaceCount == str.length())
               break;
           else
               currChar = str.at(whitespaceCount);
        }
        if (whitespaceCount > 0)
            str.remove(0, whitespaceCount);
    }

    // Remove trailing whitespace
    if (str.length() > 0){
        QChar currChar = str.at(str.length() - 1);
        int whitespaceCount = 0;
        while (currChar == ' '){
           whitespaceCount++;
           if (str.length() - whitespaceCount == 0)
               break;
           else
               currChar = str.at(str.length() - 1 - whitespaceCount);
        }
        if (whitespaceCount > 0)
            str.remove(str.length() - whitespaceCount, whitespaceCount);
    }
    return str;
}
