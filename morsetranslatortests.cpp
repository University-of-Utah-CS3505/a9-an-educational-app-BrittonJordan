#include "morsetranslatortests.h"
#include "morsetranslator.h"
#include <iostream>

MorseTranslatorTests::MorseTranslatorTests()
{
}


void MorseTranslatorTests::runTests(){
    std::cout << "-----------------" << std::endl;
    std::cout << "GENERAL USE TESTS" << std::endl;
    std::cout << "-----------------" << std::endl;
    englishCharToMorse();
    morseCharToEnglish();
    englishWordToMorse();
    morseWordToEnglish();
    englishSentenceToMorse();
    morseSentenceToEnglish();
    std::cout << std::endl;

    std::cout << "-----------------" << std::endl;
    std::cout << "EDGE CASE TESTS" << std::endl;
    std::cout << "-----------------" << std::endl;
    leadingWhitespaceRemoved();
    trailingWhitespaceRemoved();
    invalidCharacterIgnored();
    forwardSlashTreatedTheSame();
    noSpacesSurroundingSlash();
}

void MorseTranslatorTests::englishCharToMorse(){
    QString morseChar = translator.englishToMorse("a");
    if (morseChar == ".-")
        std::cout << "englishCharToMorse: \nPASS" << std::endl;
    else {
        std::cout << "englishCharToMorse: \nFAIL" << std::endl;
        std::cout << "Expected: \".-\" actual: \"" << morseChar.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}


void MorseTranslatorTests::morseCharToEnglish(){
    QString englishChar = translator.morseToEnglish("-.--");
    if (englishChar == "y")
        std::cout << "morseCharToEnglish: \nPASS" << std::endl;
    else {
        std::cout << "morseCharToEnglish: \nFAIL" << std::endl;
        std::cout << "Expected: \"y\" actual: \"" << englishChar.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}

void MorseTranslatorTests::englishWordToMorse(){
    QString morseWord = translator.englishToMorse("xylophone");
    if (morseWord == "-..- -.-- .-.. --- .--. .... --- -. .")
        std::cout << "englishWordToMorse: \nPASS" << std::endl;
    else {
        std::cout << "englishWordToMorse: \nFAIL" << std::endl;
        std::cout << "Expected: \"-..- -.-- .-.. --- .--. .... --- -. .\" actual: \"" << morseWord.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}

void MorseTranslatorTests::morseWordToEnglish(){
    QString englishWord = translator.morseToEnglish("--. ..- .. - .- .-.");
    if (englishWord == "guitar")
        std::cout << "morseWordToEnglish: \nPASS" << std::endl;
    else {
        std::cout << "morseWordToEnglish: \nFAIL" << std::endl;
        std::cout << "Expected: \"guitar\" actual: \"" << englishWord.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}


void MorseTranslatorTests::englishSentenceToMorse(){
    QString morseSentence = translator.englishToMorse("the quick brown fox jumped over the lazy dog");
    if (morseSentence == "- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / ..-. --- -..- / .--- ..- -- .--. . -.. / --- ...- . .-. / - .... . / .-.. .- --.. -.-- / -.. --- --.")
        std::cout << "englishSentenceToMorse: \nPASS" << std::endl;
    else {
        std::cout << "englishSentenceToMorse: \nFAIL" << std::endl;
        std::cout << "Expected: \"- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / ..-. --- -..- / .--- ..- -- .--. . -.. / --- ...- . .-. / - .... . / .-.. .- --.. -.-- / -.. --- --.\" actual: \"" << morseSentence.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}

void MorseTranslatorTests::morseSentenceToEnglish(){
    QString englishSentence = translator.morseToEnglish("- .... . / --.- ..- .. -.-. -.- / -... .-. --- .-- -. / ..-. --- -..- / .--- ..- -- .--. . -.. / --- ...- . .-. / - .... . / .-.. .- --.. -.-- / -.. --- --.");
    if (englishSentence == "the quick brown fox jumped over the lazy dog")
        std::cout << "morseSentenceToEnglish: \nPASS" << std::endl;
    else {
        std::cout << "morseSentenceToEnglish: \nFAIL" << std::endl;
        std::cout << "Expected: \"the quick brown fox jumped over the lazy dog\" actual: \"" << englishSentence.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}


void MorseTranslatorTests::leadingWhitespaceRemoved(){
    QString english = " apple";
    QString morse = "   .- .--. .--. .-.. .";
    QString englishResult = translator.morseToEnglish(morse);
    QString morseResult = translator.englishToMorse(english);
    if ("apple" == englishResult && ".- .--. .--. .-.. ." == morseResult)
        std::cout << "leadingWhitespaceRemoved: \nPASS" << std::endl;
    else {
        std::cout << "leadingWhitespaceRemoved: \nFAIL" << std::endl;
        std::cout << "Expected Morse: \".- .--. .--. .-.. .\" actual: \"" << morseResult.toStdString() << "\"" << std::endl;
        std::cout << "Expected English: \"apple\" actual: \"" << englishResult.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}

void MorseTranslatorTests::trailingWhitespaceRemoved(){
    QString english = "apple ";
    QString morse = ".- .--. .--. .-.. .  ";
    QString englishResult = translator.morseToEnglish(morse);
    QString morseResult = translator.englishToMorse(english);
    if ("apple" == englishResult && ".- .--. .--. .-.. ." == morseResult)
        std::cout << "trailingWhitespaceRemoved: \nPASS" << std::endl;
    else {
        std::cout << "trailingWhitespaceRemoved: \nFAIL" << std::endl;
        std::cout << "Expected Morse: \".- .--. .--. .-.. .\" actual: \"" << morseResult.toStdString() << "\"" << std::endl;
        std::cout << "Expected English: \"apple\" actual: \"" << englishResult.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}

void MorseTranslatorTests::invalidCharacterIgnored(){
    QString morse = ".- .--. ----- .--. .-.. .";
    QString englishResult = translator.morseToEnglish(morse);
    if (englishResult == "apple")
        std::cout << "invalidCharacterIgnored: \nPASS" << std::endl;
    else {
        std::cout << " invalidCharacterIgnored: \nFAIL" << std::endl;
        std::cout << "Expected English: \"apple\"" << " actual: \"" << englishResult.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}


void MorseTranslatorTests::forwardSlashTreatedTheSame(){
    QString englishSentence = translator.morseToEnglish("- .... . \\ --.- ..- .. -.-. -.- \\ -... .-. --- .-- -. \\ ..-. --- -..- \\ .--- ..- -- .--. . -.. \\ --- ...- . .-. \\ - .... . \\ .-.. .- --.. -.-- \\ -.. --- --.");
    if (englishSentence == "the quick brown fox jumped over the lazy dog")
        std::cout << "noSpacesSurroundingSlash: \nPASS" << std::endl;
    else {
        std::cout << "noSpacesSurroundingSlash: \nFAIL" << std::endl;
        std::cout << "Expected: \"the quick brown fox jumped over the lazy dog\" actual: \"" << englishSentence.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}

void MorseTranslatorTests::noSpacesSurroundingSlash(){
    QString englishSentence = translator.morseToEnglish("- .... ./ --.- ..- .. -.-. -.- /-... .-. --- .-- -./..-. --- -..- / .--- ..- -- .--. . -.. / --- ...- . .-. / - .... . / .-.. .- --.. -.-- / -.. --- --.");
    if (englishSentence == "the quick brown fox jumped over the lazy dog")
        std::cout << "noSpacesSurroundingSlash: \nPASS" << std::endl;
    else {
        std::cout << "noSpacesSurroundingSlash: \nFAIL" << std::endl;
        std::cout << "Expected: \"the quick brown fox jumped over the lazy dog\" actual: \"" << englishSentence.toStdString() << "\"" << std::endl;
        std::cout << std::endl;
    }
}
