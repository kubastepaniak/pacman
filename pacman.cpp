#include <QApplication>
#include <QGraphicsView>
#include "scene.h"

#define FIXED_WIDTH 704
#define FIXED_HEIGHT 804

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Scene *mainScene = new Scene();

    QGraphicsView mainView(mainScene);
    mainView.setFixedSize(FIXED_WIDTH, FIXED_HEIGHT);
    mainView.show();
    
    return app.exec();
}
