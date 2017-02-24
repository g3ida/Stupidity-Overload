#include "../include/MenuState.h"
#include "../include/logging/Log.h"
#include "../include/input/InputManager.h"
#include "../include/input/Action.h"

void
MenuState::onEnter(SDL_Renderer* renderer)
{

	t.load(renderer, "sprites/adv_chara.png");
	s.setNumRows(4);
	s.setNumCols(12);
	s.setFps(20);
	s.reverse(true);
	s.restart();
	s.loop(false);

    l.setNumRows(4);
	l.setNumCols(12);
	l.setStartFrame(15);
	l.setEndFrame(23);
	l.setCurrentFrame(20);
	l.setFps(20);
	l.restart();
	l.pause();
	l.loop(true);

    r.setNumRows(4);
	r.setNumCols(12);
	r.setStartFrame(4);
	r.setEndFrame(11);
	r.setCurrentFrame(20);
	r.setFps(20);
	r.restart();
	r.pause();
	r.loop(true);

    LOG( "menu state entred\n");

    InputManager::getInstance().bind(State::MoveLeft, SDL_SCANCODE_LEFT);
    InputManager::getInstance().registerCommand(State::MoveLeft,
    [&]()
    {
        LOG("left fired !\n");
        isleft = true;
        x-=3;
        l.resume();
    }
    );


    InputManager::getInstance().bind(State::MoveRight, SDL_SCANCODE_RIGHT);
    InputManager::getInstance().registerCommand(State::MoveRight,
    [&]()
    {
        LOG("right fired !\n");
        isleft = false;
        x+=3;
        r.resume();
    }
    );

}

AbstractGameState*
MenuState::handleEvent(SDL_Event& event)
{
    /*
    mouse.process(event);
    if(mouse.leftButtonDown()) LOG("left button down\n");
    if(mouse.leftButtonPressed()) LOG("left button pressed\n");
    if(mouse.leftButtonReleased()) LOG("left button released\n");
    LOG(mouse.getX(), " ", mouse.getY(), "\n");

    keyboard.process(event);
    if(keyboard.keyPressed(SDL_SCANCODE_A))
        LOG("A pressed !\n");

    if(keyboard.keyReleased(SDL_SCANCODE_A))
        LOG("A released !\n");

    if(keyboard.keyDown(SDL_SCANCODE_A))
        LOG("A down !\n");
    */

    InputManager::getInstance().process(event);
    return nullptr;
}

AbstractGameState*
MenuState::update(Uint32 ms)
{
    //s.update(ms);
    l.update(ms);
    r.update(ms);

    r.pause();
    l.pause();
    return nullptr;
}

AbstractGameState*
MenuState::render(SDL_Renderer* m_renderer)
{
    if(isleft)
        drawSprite(x, 100, l, t);
    else
        drawSprite(x, 100, r, t);

	return nullptr;
}

void
MenuState::onExit()
{
    //m_sprite.free();
	LOG("menu state exited\n");
}
