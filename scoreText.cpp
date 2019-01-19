#include "scoreText.h"
#include <string>

ScoreText::ScoreText(QGraphicsItem * parent) : QGraphicsTextItem(parent) {
    score = 0;
    setDefaultTextColor(Qt::yellow);
    setPos(TEXT_DEFAULT_X, TEXT_DEFAULT_Y);
    display();
}

void ScoreText::display() {
    std::string text = std::to_string(score);
    setPlainText(QString(text.c_str()));
}

void ScoreText::pointEaten(int value) {
    score += (value - 5);
    display();
}