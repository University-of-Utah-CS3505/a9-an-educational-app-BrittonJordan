#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QWidget>
#include <box2d/box2d.h>
#include <QTimer>
#include <QMap>
#include <QPair>

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

    QMap<int, QPair<QImage, int>> confettiMap;
    QPair<QImage, int> confettiInformation;
    QVector<b2Body*> confettiBodies;
};

#endif // SCENEWIDGET_H
