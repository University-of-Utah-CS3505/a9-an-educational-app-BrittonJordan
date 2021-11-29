#ifndef MORSETRANSLATORTESTS_H
#define MORSETRANSLATORTESTS_H

#include "morsetranslator.h"
class MorseTranslatorTests
{

private:
    MorseTranslator translator;

    // General use tests
    void englishCharToMorse();
    void morseCharToEnglish();
    void englishWordToMorse();
    void morseWordToEnglish();
    void englishSentenceToMorse();
    void morseSentenceToEnglish();

    // Edge case tests
    void leadingWhitespaceRemoved();
    void trailingWhitespaceRemoved();
    void invalidCharacterIgnored();
    void forwardSlashTreatedTheSame();
    void noSpacesSurroundingSlash();

public:
    MorseTranslatorTests();

    void runTests();

};

#endif // MORSETRANSLATORTESTS_H
