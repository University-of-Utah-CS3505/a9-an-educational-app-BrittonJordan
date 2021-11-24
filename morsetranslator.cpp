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

    toMorse = {{'a',".-"},{'b', "-..."},{'c', "-.-."},{'d',"-.."},{'e', "."},{'f', "..-."}};
            // Fill in the rest of this

}




QString MorseTranslator::englishToMorse(QString english){

}


QString MorseTranslator::morseToEnglish(QString morse) {

}
