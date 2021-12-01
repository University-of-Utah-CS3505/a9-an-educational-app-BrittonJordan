#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "morsetranslatortests.h"
#include <QFontDatabase>

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ui->menuStack->setCurrentIndex(0); // Start on the Main Menu
    ui->helpPicture->setVisible(false);

    //Font stuff
    int id = QFontDatabase::addApplicationFont(":/Fonts/armalite.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont armyStyle(family);

    QFont armyStyle28(family);
    armyStyle28.setPointSize(28);
    QFont armyStyle22(family);
    armyStyle22.setPointSize(22);
    QFont armyStyle14(family);
    armyStyle14.setPointSize(14);

    //Set font for buttons
    ui->level1Button->setFont(armyStyle);
    ui->level2Button->setFont(armyStyle);
    ui->level3Button->setFont(armyStyle);
    ui->level4Button->setFont(armyStyle);
    ui->level5Button->setFont(armyStyle);
    ui->level6Button->setFont(armyStyle);
    ui->menuButton->setFont(armyStyle14);
    ui->studyButton->setFont(armyStyle14);
    ui->translateButton->setFont(armyStyle14);
    ui->fieldPracticeButton->setFont(armyStyle14);
    ui->helpButton->setFont(armyStyle);
    ui->nextQuestionButton->setFont(armyStyle);
    ui->previousQuestionButton->setFont(armyStyle);

    // Set font for labels
    ui->gameTitleLabel->setFont(armyStyle28);
    ui->studyLabel->setFont(armyStyle22);
    ui->studyLevelLabel->setFont(armyStyle22);
    ui->questionNumber->setFont(armyStyle22);
    ui->translateLabel->setFont(armyStyle22);
    ui->toTranslateLanguageLabel->setFont(armyStyle14);
    ui->resultLanguageLabel->setFont(armyStyle14);

    // When translating, default to English -> Morse
    encode = true;

    ui->inputToTranslate->setStyleSheet("background-color: #f5e9d7");
    ui->translateResult->setStyleSheet("background-color: #f5e9d7");

    MorseTranslatorTests test;
    test.runTests();

    //Level 1 Connect
    connect(ui->level1Button, &QPushButton::clicked, this, &MainMenu::level1);

    //Level 2 Connect
    connect(ui->level2Button, &QPushButton::clicked, this, &MainMenu::level2);

    //Level 3 Connect
    connect(ui->level3Button, &QPushButton::clicked, this, &MainMenu::level3);

    //Level 4 Connect
    connect(ui->level4Button, &QPushButton::clicked, this, &MainMenu::level4);

    //Level 5 Connect
    connect(ui->level5Button, &QPushButton::clicked, this, &MainMenu::level5);

    //Level 6 Connect
    connect(ui->level6Button, &QPushButton::clicked, this, &MainMenu::level6);

    //isNextQuestion
    connect(&morseModel, &model::goToStudyMenu, this, &MainMenu::on_studyButton_clicked);

    connect(ui->inputToTranslate, &QTextEdit::textChanged, this, &MainMenu::updateTranslation);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_studyButton_clicked()
{
    ui->menuStack->setCurrentIndex(1); // Switch to Study menu
    ui->studyMorseLabel->clear();

    questionCounter = 1;
}

void MainMenu::on_menuButton_clicked()
{
    ui->menuStack->setCurrentIndex(0); // Switch to Main Menu
    ui->studyMorseLabel->clear();

    questionCounter = 1;
}

void MainMenu::on_translateButton_clicked(){
    ui->menuStack->setCurrentIndex(3); // Switch to Translate menu
    ui->studyMorseLabel->clear();

    questionCounter = 1;
}

void MainMenu::on_fieldPracticeButton_clicked()
{
    ui->menuStack->setCurrentIndex(4); // Switch to Field Practice menu
    ui->studyMorseLabel->clear();
}

void MainMenu::on_nextQuestionButton_clicked(){
    if(morseModel.isCorrectAnswer(ui->userInput->toPlainText())){
        std::cout << "correct" << std::endl;

        questionCounter++;
        ui->questionNumber->setText("Question Number: " +QString::number(questionCounter));

        ui->userInput->clear();

        morseModel.getNextQuestion();
        StudyQuestion question = morseModel.getCurrentQuestion();
        ui->studyMorseLabel->setText(question.getQuestion());
    }
    else{
        std::cout << "wrong" << std::endl;
    }

//    morseModel.getNextQuestion();
//    StudyQuestion question = morseModel.getCurrentQuestion();
//    ui->studyMorseLabel->setText(question.getQuestion());
//    ui->userInput->clear();
}

void MainMenu::on_previousQuestionButton_clicked(){
    if(questionCounter-1 != 0){
        morseModel.getPreviousQuestion();
        StudyQuestion question = morseModel.getCurrentQuestion();
        ui->studyMorseLabel->setText(question.getQuestion());

        questionCounter--;
        ui->questionNumber->setText("Question Number: " +QString::number(questionCounter));

        ui->userInput->clear();
    }
}

void MainMenu::on_helpButton_clicked(){
    if(ui->helpPicture->isVisible())
        ui->helpPicture->setVisible(false);
    else
        ui->helpPicture->setVisible(true);
}

void MainMenu::level1(){
    std::cout<<"Level 1 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(1);

    ui->studyLevelLabel->setText("Study Level: 1");

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level2(){
    std::cout<<"Level 2 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(2);

    ui->studyLevelLabel->setText("Study Level: 2");

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level3(){
    std::cout<<"Level 3 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(3);

    ui->studyLevelLabel->setText("Study Level: 3");

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level4(){
    std::cout<<"Level 4 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(4);

    ui->studyLevelLabel->setText("Study Level: 4");

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level5(){
    std::cout<<"Level 5 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(5);

    ui->studyLevelLabel->setText("Study Level: 5");

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level6(){
    std::cout<<"Level 6 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(6);

    ui->studyLevelLabel->setText("Study Level: 6");

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}


void MainMenu::on_switchEncodeDecode_clicked()
{
    if (encode){
        encode = false;
        ui->toTranslateLanguageLabel->setText("Morse code");
        ui->resultLanguageLabel->setText("Text");
    }
    else {
        encode = true;
        ui->toTranslateLanguageLabel->setText("Text");
        ui->resultLanguageLabel->setText("Morse code");
    }

    QString untranslated = ui->inputToTranslate->toPlainText();
    QString translated = ui->translateResult->toPlainText();
    ui->inputToTranslate->setText(translated);
}

void MainMenu::updateTranslation(){
    QString toTranslate = ui->inputToTranslate->toPlainText();
    if (encode)
        ui->translateResult->setText(translate.englishToMorse(toTranslate));
    else
        ui->translateResult->setText(translate.morseToEnglish(toTranslate));
}
