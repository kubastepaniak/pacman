#pragma once
#include <QGraphicsTextItem>
#include <QGraphicsItem>

//#define TEXT_DEFAULT_X 410
#define TEXT_DEFAULT_X 340
#define TEXT_DEFAULT_Y 0

class ScoreText : public QGraphicsTextItem {
    Q_OBJECT
private:
    int score;
    void display();
public:
    ScoreText(QGraphicsItem *parent = nullptr);
public slots:
    void pointEaten(int value);
};