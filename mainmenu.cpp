#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "morsetranslatortests.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    ui->menuStack->setCurrentIndex(0); // Start on the Main Menu

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

    //Level 7 Connect
    connect(ui->level7Button, &QPushButton::clicked, this, &MainMenu::level7);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_studyButton_clicked()
{
    ui->menuStack->setCurrentIndex(1); // Switch to Study menu
}

void MainMenu::on_menuButton_clicked()
{
    ui->menuStack->setCurrentIndex(0); // Switch to Main Menu
}

void MainMenu::level1(){
    std::cout<<"Level 1 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(1);

    ui->studyLevelLabel->setText("Study Level: 1");
    //ui->studyMorseLabel->setText();
}

void MainMenu::level2(){
    std::cout<<"Level 2 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(2);

    ui->studyLevelLabel->setText("Study Level: 2");
}

void MainMenu::level3(){
    std::cout<<"Level 3 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(3);

    ui->studyLevelLabel->setText("Study Level: 3");
}

void MainMenu::level4(){
    std::cout<<"Level 4 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(4);

    ui->studyLevelLabel->setText("Study Level: 4");
}

void MainMenu::level5(){
    std::cout<<"Level 5 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(5);

    ui->studyLevelLabel->setText("Study Level: 5");
}

void MainMenu::level6(){
    std::cout<<"Level 6 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    morseModel.generateLevel(6);

    ui->studyLevelLabel->setText("Study Level: 6");
}

void MainMenu::level7(){
    std::cout<<"Level 7 Begins"<<std::endl;
    ui->menuStack->setCurrentIndex(2);
    //morseModel.generateLevel(7);

    ui->studyLevelLabel->setText("Study Level: 7");
}

