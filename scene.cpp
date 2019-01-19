#include "rect.h"
#include "scene.h"
#include "scoreText.h"
#include <iostream>
#include <QRectF>

Scene::Scene() {
    gameMap = new Map;
    collectablesMap = new Map(MapType::collectable);
    //pointsMap = new Point**[collectablesMap->getWidth()];
    
    for (int x = 0; x < gameMap->getWidth(); x++) {
        for (int y = 0; y < gameMap->getHeight(); y++) {
            this->addItem(new Rect(x, y, gameMap));
            //pointsMap[x] = new Point*[collectablesMap->getHeight()];

            if((*collectablesMap)(x, y) == CollTag::point ||
               (*collectablesMap)(x, y) == CollTag::candy) {
                //pointsMap[x][y] = new Point(x, y, (*collectablesMap)(x, y));
                //this->addItem(pointsMap[x][y]);
                this->addItem(new Point(x, y, (*collectablesMap)(x, y)));
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
}
/* 
void Scene::destroy() {
    QRectF itemPoint(player->boundingRect().topLeft().x() + 10, player->boundingRect().topLeft().y() + 10, 5, 5);
    std::cout << items(itemPoint).size() << std::endl;
    //removeItem(items(player->boundingRect()).at(1));
    removeItem(items(itemPoint).at(1));

    //removeItem(pointsMap[player->xPos][player->yPos]);
} */