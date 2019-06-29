#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
class InputElement{
public:
	void setWindow(RenderWindow* window) { _window = window; }
	void setMouse(Mouse* mouse) { _mouse = mouse; }
	void setEvent(Event* evnt) { _event = evnt; }
	virtual void setPtr(Mouse* mouse, Event* evnt){ _mouse = mouse; _event = evnt;}
	virtual void draw() = 0;
	virtual void update() = 0;
	Vector2f getRatio() { return _ratio; }
	void updateRatio();
	virtual void setBackgroundTexture(Texture *texture) = 0;
	virtual void setBackgroundTexture(string path) = 0;
	virtual void setBackgroundRectTexture(Texture* texture,IntRect rect) = 0;
	virtual void setBackgroundRectTexture(string path, IntRect rect) = 0;
	virtual void setSpecialTexture(Texture* texture) = 0;
	virtual void setSpecialTexture(string path) = 0;
	virtual void setSpecialRectTexture(Texture* texture, IntRect rect) = 0;
	virtual void setSpecialRectTexture(string path, IntRect rect) = 0;
protected:
	RenderWindow* _window = nullptr;
	Mouse* _mouse = nullptr;
	Event* _event = nullptr;
	Vector2f _ratio = Vector2f(1,1);
	Vector2u _defaultWindowSize;
	bool resized = false;
};

