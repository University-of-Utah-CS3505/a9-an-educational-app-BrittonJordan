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

    ui->animationWidgetStudy->hide();
    ui->animationWidgetStudy->setDisabled(true);

    ui->animationWidgetFieldPractice->hide();
    ui->animationWidgetFieldPractice->setDisabled(true);

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
    QFont armyStyle12(family);
    armyStyle12.setPointSize(12);
    QFont armyStyle10(family);
    armyStyle10.setPointSize(10);

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
    ui->fieldPracticeButton->setFont(armyStyle12);
    ui->helpButton->setFont(armyStyle);
    ui->nextQuestionButton->setFont(armyStyle);
    ui->previousQuestionButton->setFont(armyStyle);
    ui->checkAnswerButton->setFont(armyStyle);
    ui->nextPhraseButton->setFont(armyStyle);
    ui->goButton->setFont(armyStyle14);
    ui->skipQuestionButton->setFont(armyStyle10);
    ui->startOverButton->setFont(armyStyle10);

    // Set font for labels
    ui->gameTitleLabel->setFont(armyStyle28);
    ui->studyLabel->setFont(armyStyle22);
    ui->studyLevelLabel->setFont(armyStyle22);
    ui->questionNumber->setFont(armyStyle22);
    ui->translateLabel->setFont(armyStyle22);
    ui->toTranslateLanguageLabel->setFont(armyStyle14);
    ui->resultLanguageLabel->setFont(armyStyle14);
    ui->fieldPracticeLabel->setFont(armyStyle22);
    ui->userAnswerLabel->setFont(armyStyle10);

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

    //Translate text
    connect(ui->inputToTranslate, &QTextEdit::textChanged, this, &MainMenu::updateTranslation);

    connect(&morseModel, &model::flashOn, this, &MainMenu::flashOnLabel);
    connect(&morseModel, &model::flashOff, this, &MainMenu::flashOffLabel);

    //Rain conffeti
    connect(&morseModel, &model::rainConfetti, this, &MainMenu::handleConfettiFallingStudy);

    //Handle Study Confetti Timer
    connect(&ui->animationWidgetStudy->confettiTimer, &QTimer::timeout, ui->animationWidgetStudy, &SceneWidget::updateWorld);

    //Handle Field Practice Confetti Timer
    connect(&ui->animationWidgetFieldPractice->confettiTimer, &QTimer::timeout, ui->animationWidgetFieldPractice, &SceneWidget::updateWorld);
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
    ui->animationWidgetStudy->hide();
    ui->animationWidgetStudy->setDisabled(true);

    ui->animationWidgetFieldPractice->hide();
    ui->animationWidgetFieldPractice->setDisabled(true);
}

void MainMenu::on_menuButton_clicked()
{
    ui->menuStack->setCurrentIndex(0); // Switch to Main Menu
    ui->studyMorseLabel->clear();

    questionCounter = 1;
    ui->animationWidgetStudy->hide();
    ui->animationWidgetStudy->setDisabled(true);

    ui->animationWidgetFieldPractice->hide();
    ui->animationWidgetFieldPractice->setDisabled(true);
}

void MainMenu::on_translateButton_clicked(){
    ui->menuStack->setCurrentIndex(3); // Switch to Translate menu
    ui->studyMorseLabel->clear();

    questionCounter = 1;
    ui->animationWidgetStudy->hide();
    ui->animationWidgetStudy->setDisabled(true);

    ui->animationWidgetFieldPractice->hide();
    ui->animationWidgetFieldPractice->setDisabled(true);
}

void MainMenu::on_fieldPracticeButton_clicked()
{
    ui->menuStack->setCurrentIndex(4); // Switch to Field Practice menu
    ui->studyMorseLabel->clear();

    displayFieldPracticeInstructions();
    questionCounter = 1;
    morseModel.stopFlashing();

    ui->animationWidgetStudy->hide();
    ui->animationWidgetStudy->setDisabled(true);

    ui->animationWidgetFieldPractice->hide();
    ui->animationWidgetFieldPractice->setDisabled(true);
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

void MainMenu::handleConfettiFallingStudy(){
    ui->animationWidgetStudy->setDisabled(false);
    ui->animationWidgetStudy->show();

    ui->animationWidgetStudy->resetConfetti();
    ui->animationWidgetStudy->startConfetti();
}

void MainMenu::handleConfettiFallingFieldPractice(){
    ui->animationWidgetFieldPractice->setDisabled(false);
    ui->animationWidgetFieldPractice->show();

    ui->animationWidgetFieldPractice->resetConfetti();
    ui->animationWidgetFieldPractice->startConfetti();
}

void MainMenu::level1(){
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(1);

    ui->studyLevelLabel->setText("Study Level: 1");

    ui->helpButton->setVisible(true);
    QPixmap pixmap(":/Images/A-EMorse.png");
    ui->helpPicture->setPixmap(pixmap);
    int w = ui->helpPicture->width();
    int h = ui->helpPicture->height();
    ui->helpPicture->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level2(){
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(2);

    ui->studyLevelLabel->setText("Study Level: 2");

    ui->helpButton->setVisible(true);
    QPixmap pixmap(":/Images/F-JMorse.png");
    ui->helpPicture->setPixmap(pixmap);
    int w = ui->helpPicture->width();
    int h = ui->helpPicture->height();
    ui->helpPicture->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level3(){
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(3);

    ui->studyLevelLabel->setText("Study Level: 3");

    ui->helpButton->setVisible(true);
    QPixmap pixmap(":/Images/K-PMorse.png");
    ui->helpPicture->setPixmap(pixmap);
    int w = ui->helpPicture->width();
    int h = ui->helpPicture->height();
    ui->helpPicture->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level4(){
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(4);

    ui->studyLevelLabel->setText("Study Level: 4");

    ui->helpButton->setVisible(true);
    QPixmap pixmap(":/Images/Q-UMorse.png");
    ui->helpPicture->setPixmap(pixmap);
    int w = ui->helpPicture->width();
    int h = ui->helpPicture->height();
    ui->helpPicture->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level5(){
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(5);

    ui->studyLevelLabel->setText("Study Level: 5");

    ui->helpButton->setVisible(true);
    QPixmap pixmap(":/Images/V-ZMorse.png");
    ui->helpPicture->setPixmap(pixmap);
    int w = ui->helpPicture->width();
    int h = ui->helpPicture->height();
    ui->helpPicture->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    StudyQuestion question = morseModel.getCurrentQuestion();
    ui->studyMorseLabel->setText(question.getQuestion());
}

void MainMenu::level6(){
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(6);

    ui->studyLevelLabel->setText("Study Level: 6");
    ui->helpButton->setVisible(false);
    ui->helpPicture->setVisible(false);

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

void MainMenu::flashOnLabel(){
    ui->flashLabel->setStyleSheet(QString("background-color: rgb(255, 255, 255);"));
}

void MainMenu::flashOffLabel(){
    ui->flashLabel->setStyleSheet(QString("background-color: rgb(180, 170, 156);"));
}


void MainMenu::displayFieldPracticeInstructions(){
    ui->goButton->setEnabled(true);
    ui->goButton->setVisible(true);

    ui->instructionLabel->setEnabled(true);
    ui->instructionLabel->setVisible(true);

    ui->checkAnswerButton->setEnabled(false);
    ui->checkAnswerButton->setVisible(false);

    ui->userAnswerLabel->setEnabled(false);
    ui->userAnswerLabel->setVisible(false);

    ui->userAnswerBox->setEnabled(false);
    ui->userAnswerBox->setVisible(false);

    ui->nextPhraseButton->setEnabled(false);
    ui->nextPhraseButton->setVisible(false);

    ui->skipQuestionButton->setEnabled(false);
    ui->skipQuestionButton->setVisible(false);

    ui->startOverButton->setEnabled(false);
    ui->startOverButton->setVisible(false);
}
void MainMenu::on_goButton_clicked()
{
    ui->goButton->setEnabled(false);
    ui->goButton->setVisible(false);

    ui->instructionLabel->setEnabled(false);
    ui->instructionLabel->setVisible(false);

    ui->checkAnswerButton->setEnabled(true);
    ui->checkAnswerButton->setVisible(true);

    ui->userAnswerLabel->setEnabled(true);
    ui->userAnswerLabel->setVisible(true);

    ui->userAnswerBox->setEnabled(true);
    ui->userAnswerBox->setVisible(true);

    ui->skipQuestionButton->setEnabled(true);
    ui->skipQuestionButton->setVisible(true);

    ui->startOverButton->setEnabled(true);
    ui->startOverButton->setVisible(true);

   QTimer::singleShot(1250, this, &MainMenu::nextFieldQuestion);

}

void MainMenu::on_checkAnswerButton_clicked()
{
    if (morseModel.correctFieldAnswer(ui->userAnswerBox->toPlainText())){
        QString reportCorrect = "Correct!\n";
        reportCorrect.append(morseModel.getCurrentPhraseDescription());
        ui->reportCorrectLabel->setText(reportCorrect);
        ui->nextPhraseButton->setEnabled(true);
        ui->nextPhraseButton->setVisible(true);

        handleConfettiFallingFieldPractice();

    } else {
        ui->reportCorrectLabel->setText("Try again!");
        QTimer::singleShot(2000, this, &MainMenu::retryFieldQuestion);
    }
}

void MainMenu::nextFieldQuestion(){
    ui->reportCorrectLabel->setText("");
    ui->userAnswerBox->setText("");
    morseModel.stopFlashing();
    QTimer::singleShot(1000, &morseModel, &model::flashNewPhrase);
}

void MainMenu::retryFieldQuestion(){
    ui->reportCorrectLabel->setText("");
    ui->userAnswerBox->setText("");
    morseModel.stopFlashing();
    QTimer::singleShot(1000, &morseModel, &model::retryFieldQuestion);
}

void MainMenu::on_nextPhraseButton_clicked()
{
    ui->nextPhraseButton->setEnabled(false);
    ui->nextPhraseButton->setVisible(false);
    nextFieldQuestion();
}


void MainMenu::on_skipQuestionButton_clicked()
{
    morseModel.stopFlashing();
    QTimer::singleShot(1000, this, &MainMenu::nextFieldQuestion);
}


void MainMenu::on_userAnswerBox_textChanged()
{
    QString text = ui->userAnswerBox->toPlainText();
    if (text.endsWith('\n')){
        ui->userAnswerBox->setText(text.chopped(1));
        on_checkAnswerButton_clicked();
    }
}


void MainMenu::on_startOverButton_clicked()
{
    morseModel.stopFlashing();
    QTimer::singleShot(1500, &morseModel, &model::retryFieldQuestion);
}

