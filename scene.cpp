#include "rect.h"
#include "scene.h"
#include "scoreText.h"
#include "point.h"

Scene::Scene() {
    gameMap = new Map;
    collectablesMap = new Map(MapType::collectable);
    
    for (int x = 0; x < gameMap->getWidth(); x++) {
        for (int y = 0; y < gameMap->getHeight(); y++) {
            this->addItem(new Rect(x, y, gameMap));

            if((*collectablesMap)(x, y) == CollTag::point ||
               (*collectablesMap)(x, y) == CollTag::candy) {
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

void Scene::destroy() {
    Point *temp = (Point*)items(player->boundingRect()).at(1) ;
    removeItem(temp);
    delete temp;
}