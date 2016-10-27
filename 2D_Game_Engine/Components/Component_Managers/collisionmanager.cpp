#include "collisionmanager.h"
#include <string>

std::vector<Collision> CollisionManager::m_vCollisionComponents;

void CollisionManager::addCollision(Collision *collision) {
    CollisionManager::m_vCollisionComponents.push_back(*collision);
}

std::vector<Collision> &CollisionManager::getAllCollisions() {
    return CollisionManager::m_vCollisionComponents;
}

void CollisionManager::checkCollision(Collision *collision) {

    for (int i = 0; i < (int) m_vCollisionComponents.size(); i++) {
        Collision currentCollision = m_vCollisionComponents[i];

        if (strcmp(collision->name().c_str(), currentCollision.name().c_str()) != 0) {

            // AABB Test

            SDL_Rect rect1 = collision->rect();
            SDL_Rect rect2 = currentCollision.rect();

            if (rect1.w > 0 && rect2.w > 0) {
                if (rect1.x < rect2.x + (rect2.w * 2) &&
                    rect1.x + (rect1.w * 2) > rect2.x &&
                    rect1.y < rect2.y + (rect2.h * 2) &&
                    (rect1.h * 2) + rect1.y > rect2.y) {

                    // Collision detected

                    if((rect1.w * 2 )+rect1.x >= rect2.x && rect1.x + (rect1.w * 2 )<rect2.x+(rect2.w * 2 )) {
                        collision->setLeft(true);
                        collision->setContactPoint({rect2.x - (rect1.w * 2), rect2.y});
//                        std::cerr<<"HIt from left "<< collision->name() <<"\n";
                    }

                    if(rect1.y+(rect1.h * 2) >=rect2.y && rect1.y+(rect1.h * 2)<rect2.y+(rect2.h * 2))
                        collision->setTop(true);
//                        std::cerr<<"HIt from top\n";

                    if(rect1.x<=rect2.x+(rect2.w * 2) && rect1.x>rect2.x)
                        collision->setRight(true);
//                        std::cerr<<"HIt from right\n";

                    if(rect1.y<=rect2.y+(rect2.h * 2) && rect1.y>rect2.y)
                        collision->setBottom(true);
//                        std::cerr<<"HIt from bottom\n";


//                    std::cerr<<"Collided"<< (rect1.x + rect1.w);
                    collision->setCollide(true);
                    currentCollision.setCollide(true);
                }
                else {
                    collision->setLeft(false);
                    collision->setRight(false);
                    collision->setBottom(false);
                    collision->setTop(false);
                }
            }
        }

    }
}