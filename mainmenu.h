#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <box2d/box2d.h>
#include "model.h"
#include "scenewidget.h"

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
    void on_fieldPracticeButton_clicked();
    void on_helpButton_clicked();
    void on_switchEncodeDecode_clicked();
    void on_userInput_textChanged();
    void level1();
    void level2();
    void level3();
    void level4();
    void level5();
    void level6();
    void updateTranslation();
    void flashOnLabel();
    void flashOffLabel();
    void handleConfettiFallingStudy();
    void handleConfettiFallingFieldPractice();
    void on_goButton_clicked();
    void on_checkAnswerButton_clicked();
    void nextFieldQuestion();
    void retryFieldQuestion();
    void on_nextPhraseButton_clicked();
    void on_skipQuestionButton_clicked();
    void on_userAnswerBox_textChanged();
    void on_startOverButton_clicked();

private:
    Ui::MainMenu *ui;
    model morseModel;
    MorseTranslator translate;
    SceneWidget sceneWidget;

    int questionCounter = 1;
    bool encode;

    void displayFieldPracticeInstructions();
};
#endif // MAINMENU_H
