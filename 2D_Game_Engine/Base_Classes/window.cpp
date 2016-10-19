#include "window.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <timer.h>
#include "renderer.h"
#include "entitymanager.h"


const int CHARACTER_VELOCITY = 10;

static SDL_Renderer* m_Renderer;


Window::Window()
{

}

void Window::loadLevel(std::string levelName)
{
    std::vector<int> levelPixels;

    char ch;
    std::ifstream levelFile;
    levelFile.open("/home/milind/Pictures/"+ levelName);
    while(levelFile >> std::skipws >> ch)
    {
        levelPixels.push_back((int)ch-48);

    }
    int k=0;
    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
        {
            pixelsArray[i][j]=levelPixels[k];
            k++;
            std::cerr<<pixelsArray[i][j]<<std::endl;
        }
    }
    for(int j=0;j<height;j++)
    {
        for(int i=0;i<width;i++)
        {

            /*switch(pixelsArray[i][j])
            {
                case 0:
                    break;
                case 1:




            }*/
        }
    }
}

void Window::createWindow(int height, int width, std::string name)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        }

        SDL_Window *win = SDL_CreateWindow(name.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN);
        if (win == nullptr){
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }

        Window::loadLevel("level1.txt");

        Window::update(win);


    SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();
}

double Window::update(SDL_Window *win)
{
    Timer timer;
    Renderer* r=new Renderer(win);
    m_Renderer=r->getRenderer();



    // Background
    m_eBackground = new Entity("Background");
    m_eBackground->transform->setPosition({0,0});
    m_eBackground->transform->setScale({1, 1});

    m_sBackgroundSpriteComponent = new Sprite();
    m_sBackgroundSpriteComponent->setName("Background_Sprite");
    m_sBackgroundSpriteComponent->loadBMPFromString("/home/milind/Pictures/blah.bmp");

    m_eBackground->addComponent(m_sBackgroundSpriteComponent);

    EntityManager::addEntity(m_eBackground);

    // Character
    m_eCharacter = new Entity("Character");
    m_eCharacter->transform->setPosition({100,100});
    m_eCharacter->transform->setScale({1,1});

    m_sSpriteComponent = new Sprite();
    m_sSpriteComponent->setName("Sprite_Component");
    m_sSpriteComponent->loadBMPFromString("/home/milind/Pictures/blah.bmp");

    m_eCharacter->addComponent(m_sSpriteComponent);

    EntityManager::addEntity(m_eCharacter);

    while (!m_bQuit) {
        // Input
        double deltaTime=timer.printFPS();

        std::vector<Entity> entityList = EntityManager::getAllEntities();

        for (std::vector<Entity>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
            Entity *eachEntity = &*it;
            std::vector<Component*> components = eachEntity->getAllComponents();

            for (std::vector<Component*>::iterator it2 = components.begin(); it2 != components.end(); ++it2) {
                Component *c = *it2;
                eachEntity->transform->m_tPosition = {eachEntity->transform->m_tPosition.x, eachEntity->transform->m_tPosition.y};
                c->update(deltaTime, eachEntity->transform);
            }
        }

        while (SDL_PollEvent(&m_Event)) {
            switch (m_Event.type) {
                case SDL_QUIT:
                    m_bQuit = true;
                    break;

                case SDL_KEYUP:
                {
                    switch(m_Event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            //xVel -= CHARACTER_VELOCITY;
                            xVel=0;
                            break;
                        case SDLK_LEFT:
                            //xVel += CHARACTER_VELOCITY;
                            xVel=0;
                            break;
                        case SDLK_UP:
                            //yVel += CHARACTER_VELOCITY;
                            yVel=0;
                            break;
                        case SDLK_DOWN:
                            //yVel -= CHARACTER_VELOCITY;
                            yVel=0;
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case SDL_KEYDOWN:
                {
                switch(m_Event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        xVel += CHARACTER_VELOCITY;
                        if(xVel>2*CHARACTER_VELOCITY)
                            xVel=2*CHARACTER_VELOCITY;
                        break;

                    case SDLK_LEFT:
                        xVel -= CHARACTER_VELOCITY;
                        if(xVel<-2*CHARACTER_VELOCITY)
                            xVel=-2*CHARACTER_VELOCITY;
                        break;
                    case SDLK_UP:
                        yVel -= CHARACTER_VELOCITY;
                        if(yVel<-2*CHARACTER_VELOCITY)
                            yVel=-2*CHARACTER_VELOCITY;
                        break;
                    case SDLK_DOWN:
                        yVel += CHARACTER_VELOCITY;
                        if(yVel>2*CHARACTER_VELOCITY)
                            yVel=2*CHARACTER_VELOCITY;
                        break;

                    default:
                        break;
                }
                    break;
            }
                default:
                    break;
            }
        }
        m_eCharacter->transform->m_tPosition.x+=xVel;
        m_eCharacter->transform->m_tPosition.y+=yVel;

       SDL_RenderPresent(m_Renderer);
       SDL_RenderClear(m_Renderer);

    }
    return 0;
}

