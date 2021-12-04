#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QWidget>
#include <box2d/box2d.h>
#include <QTimer>

class SceneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SceneWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void startConfetti();
    void resetConfetti();
    QTimer confettiTimer;

signals:

public slots:
    void updateWorld();

private:
    b2World world;
    b2Body* body;
    QVector<QImage> confetti;
    QImage projectile;
};

#endif // SCENEWIDGET_H
