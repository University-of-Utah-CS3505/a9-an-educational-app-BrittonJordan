#include "scenewidget.h"
#include <QPainter>

SceneWidget::SceneWidget(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 2.5f))
{
//    //Creating initial position of ground body
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.0f, -10.0f);

//    //Passing body def to world to create the ground
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);

//    b2PolygonShape groundBox;
//    groundBox.SetAsBox(50.0f, 10.0f);

//    //Creating the ground shape fixture
//    groundBody->CreateFixture(&groundBox, 0.0f);


    //Creating dynamic body
    b2BodyDef mainBodyDef;
    mainBodyDef.type = b2_dynamicBody;
    mainBodyDef.position.Set(-5.0f, -10.0f);
    body = world.CreateBody(&mainBodyDef);

    //Creating shape fixture and adding to mainBody
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixDef;
    fixDef.shape = &dynamicBox;
    fixDef.density = 1.0f;
    fixDef.friction = 0.3f;
    fixDef.restitution = 0.9;

    //Creating the body fixture
    body->CreateFixture(&fixDef);

    connect(&timer, &QTimer::timeout, this, &SceneWidget::updateWorld);
    timer.start(50);
}

void SceneWidget::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();

    QImage image(":/Images/confetti.png");

    painter.drawImage((int)(position.x*20), (int)(position.y*20), image);

    painter.end();
}

void SceneWidget::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);

    update();
}
