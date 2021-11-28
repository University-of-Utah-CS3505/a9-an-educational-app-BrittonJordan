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
    morseModel.generateLevel(1);
}

void MainMenu::level2(){

}

void MainMenu::level3(){

}

void MainMenu::level4(){

}

void MainMenu::level5(){

}

void MainMenu::level6(){

}

void MainMenu::level7(){

}

