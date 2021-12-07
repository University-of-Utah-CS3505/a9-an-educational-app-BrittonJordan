#include "scenewidget.h"
#include <QPainter>
#include <QDebug>

SceneWidget::SceneWidget(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 20.0f))
{
    QImage purple(":/Confetti/purple.png");
    QImage blue(":/Confetti/blue.png");
    QImage green(":/Confetti/green.png");
    QImage orange(":/Confetti/orange.png");
    QImage red(":/Confetti/red.png");
    QImage yellow(":/Confetti/yellow.png");

    //Populating confetti QMap
    for(int i = 0; i < 150; i++){
        int randomConfettiColor = rand() % 6 + 1;
        int randRotation = rand() % 15 + -10;
        QPair<QImage, int> confetti;

        switch(randomConfettiColor){
            case 1:
            confetti.first = purple;
            confetti.second = randRotation;

            confettiMap.insert(i, confetti);
            break;

            case 2:
            confetti.first = blue;
            confetti.second = randRotation;

            confettiMap.insert(i, confetti);
            break;

            case 3:
            confetti.first = green;
            confetti.second = randRotation;

            confettiMap.insert(i, confetti);
            break;

            case 4:
            confetti.first = orange;
            confetti.second = randRotation;

            confettiMap.insert(i, confetti);
            break;

            case 5:
            confetti.first = red;
            confetti.second = randRotation;

            confettiMap.insert(i, confetti);
            break;

            case 6:
            confetti.first = yellow;
            confetti.second = randRotation;

            confettiMap.insert(i, confetti);
            break;
        }
    }

    for(int i = 0; i < confettiMap.size(); i++){
        b2Body* confetti;
        confettiBodies.insert(i, confetti);
    }
}

void SceneWidget::paintEvent(QPaintEvent *) {
    //Paints individual confettis
    for(int i = 0; i < confettiBodies.size(); i++){
        QPainter painter(this);

        b2Vec2 position = confettiBodies.at(i)->GetPosition();

        QImage image = confettiMap.value(i).first.scaled(5, 5);

        painter.rotate(confettiMap.value(i).second);

        painter.drawImage((int)(position.x*20), (int)(position.y*20), image);
        painter.end();
    }
}

void SceneWidget::updateWorld() {
    world.Step(1.0/60.0, 6, 2);

    update();
}

void SceneWidget::startConfetti(){
    confettiTimer.start(50);
}

void SceneWidget::resetConfetti(){
    //Individual Confettis
    //Resetting dynamic bodies
    for(int i = 0; i < confettiBodies.size(); i++){
        b2Body* confettiBody = confettiBodies.at(i);

        //Reseting dynamic body
        b2BodyDef mainBodyDef;
        mainBodyDef.type = b2_dynamicBody;

        mainBodyDef.position.Set(15.0f, 1.0f);
        confettiBody = world.CreateBody(&mainBodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f, 1.0f);

        b2FixtureDef fixDef;
        fixDef.shape = &dynamicBox;

        int randDensity = rand() % 10 + 1;
        fixDef.density = randDensity;

        int randFriction = rand() % 1 + 0;
        fixDef.friction = randFriction;

        int randRestitution = rand() % 1 + 0;
        fixDef.restitution = randRestitution;

        confettiBody->CreateFixture(&fixDef);

        int randAngularVelocity = rand() % 5 + -5;
        confettiBody->SetAngularVelocity(randAngularVelocity);

        confettiBodies.removeAt(i);
        confettiBodies.insert(i, confettiBody);
    }
}
