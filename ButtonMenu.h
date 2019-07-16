#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Slider.h"
#include <string.h>
#include <iostream>
using namespace sf;
using namespace std;
class ButtonMenu{
public:
	ButtonMenu(float pos_x, float pos_y,float size_x,float size_y,float button_height,RenderWindow *window);
	~ButtonMenu();
	void addButton(string text, Font* font);
	void update(Event *event,Mouse *mouse);
	void draw();
	bool operator[](size_t n);
	uint16_t getSize() { return _menu.size(); }
private:
	Vector2f _pos;
	Vector2f _size;
	bool _button_mod = true;
	const float _button_size;
	RenderWindow* _window = nullptr;
	vector<TextButton*> _menu;
	RectangleShape _background;
	Slider* _slider;
	View* _view;
};
