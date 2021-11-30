#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_studyButton_clicked();
    void on_menuButton_clicked();
    void on_translateButton_clicked();
    void on_nextQuestionButton_clicked();
    void on_previousQuestionButton_clicked();
    void level1();
    void level2();
    void level3();
    void level4();
    void level5();
    void level6();
    void level7();

    void on_switchEncodeDecode_clicked();

    void updateTranslation();


private:
    Ui::MainMenu *ui;
    model morseModel;
    int scoreCounter = 0;
    int questionCounter = 1;

    MorseTranslator translate;
    bool encode;
};
#endif // MAINMENU_H
