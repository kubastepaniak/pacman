#include "rect.h"
#include "scene.h"
#include "scoreText.h"
#include "point.h"
#include "candy.h"
#include "redGhost.h"

Scene::Scene() {
    gameMap = new Map;
    collectablesMap = new Map(MapType::collectable);
    
    for (int x = 0; x < gameMap->getWidth(); x++) {
        for (int y = 0; y < gameMap->getHeight(); y++) {
            this->addItem(new Rect(x, y, gameMap));

            if((*collectablesMap)(x, y) == CollTag::point) {
                this->addItem(new Point(x, y, (*collectablesMap)(x, y)));
            } else if ((*collectablesMap)(x, y) == CollTag::candy) {
                this->addItem(new Candy(x, y, (*collectablesMap)(x, y)));
            }
        }
    }
    player = new Player(collectablesMap, gameMap);
    this->addItem(player);
    player->setFocus();

    ScoreText *score = new ScoreText;
    this->addItem(score);

    connect(player, &Player::itemCollected,
            score, &ScoreText::pointEaten);
    connect(player, &Player::itemCollected,
            this, &Scene::destroy);
    
    //ghosts
    RedGhost *red = new RedGhost(gameMap, player);
    this->addItem(red);
    connect(player, &Player::start,
            red, &RedGhost::go);
    connect(player, &Player::changeGhostState,
            red, &RedGhost::changeState);
    connect(red, &RedGhost::playerCaught,
            this, &Scene::gameOver);
}

void Scene::destroy() {
    Point *temp = (Point*)items(player->boundingRect()).at(1) ;
    removeItem(temp);
    delete temp;
}

void Scene::gameOver() {
    player->timer->stop();

    QFont *gameOverTextFont = new QFont;
    gameOverTextFont->setBold(true);
    gameOverTextFont->setItalic(true);
    gameOverTextFont->setWeight(20);

    QGraphicsTextItem *gameOverText = new QGraphicsTextItem("Game Over");
    gameOverText->setPos(315, 425);
    gameOverText->setDefaultTextColor(Qt::white);
    gameOverText->setFont(QFont(*gameOverTextFont));
    
    this->addItem(gameOverText);
}