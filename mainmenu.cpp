#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "morsetranslatortests.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ui->menuStack->setCurrentIndex(0); // Start on the Main Menu
    ui->helpPicture->setVisible(false);

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
    ui->menuStack->setCurrentIndex(3);
    ui->studyMorseLabel->clear();

    questionCounter = 1;
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
    if (encode)
        encode = false;
    else
        encode = true;

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

