#include "ButtonMenu.h"

ButtonMenu::ButtonMenu(float pos_x, float pos_y, float size_x, float size_y, float button_height, RenderWindow* window)
: _button_size(button_height)
{
	_window = window;
	_pos.x = pos_x;
	_pos.y = pos_y;
	_size.x = size_x;
	_size.y = size_y;
	_background.setPosition(_pos);
	_background.setSize(_size);
	_background.setFillColor(Color::Blue);
	_slider = new Slider(_size.x * 0.1, _size.y, _pos.x + (_size.x * 0.9), _pos.y, _window);
	_view = new View(FloatRect(_pos.x /*+ (_size.x / 2)*/, _pos.y /*+ (_size.y / 2)*/, _size.x, _size.y));
	_view->setViewport(FloatRect(_pos.x / _window->getSize().x, _pos.y / _window->getSize().y, _size.x/_window->getSize().x, _size.y / _window->getSize().y));
}

ButtonMenu::~ButtonMenu(){
	for (int i = 0; i < _menu.size(); i++)delete _menu[i];
	delete _slider;
	delete _view;
}

void ButtonMenu::addButton(string text, Font* font){
	_menu.push_back(new TextButton(0.8 * 0.9 * _size.x, _button_size, _pos.x + (_size.x * 0.1 * 0.9), _pos.y+ (_button_size * 0.2) + (_menu.size() * _button_size * 1.2), text, _window, font));
	_menu.back()->setColor(Color::Magenta);
}

void ButtonMenu::update(Event* _event, Mouse* _mouse)
{
	//_background.setPosition(_pos);
	//_background.setSize(_size);
	if (_mouse->getPosition(*_window).x>= _pos.x && _mouse->getPosition(*_window).x<= _pos.x+_size.x
		&& _mouse->getPosition(*_window).y >= _pos.y && _mouse->getPosition(*_window).y <= _pos.x + _size.y) {
		for (int i = 0; i < _menu.size(); i++) {
			_menu[i]->update(_event, _mouse);
		}
		_slider->update(_event, _mouse);
	
		for (int i = 0; i < _menu.size(); i++) {
			_menu[i]->changePos(Vector2f(_pos.x + (_size.x * 0.1 * 0.9), _pos.y + (_button_size * 0.2) + (static_cast<float>(i) * _button_size * 1.2) - ((_slider->getInput().y / 100) * (_pos.y + (_button_size * 0.2) + (_menu.size() * _button_size * 1.2)-_size.y))));
		}
	}



}

void ButtonMenu::draw(){	
	_window->setView(*_view);
	_window->draw(_background);
	_slider->draw();
	for (int i = 0; i < _menu.size(); i++)_menu[i]->draw();
	_window->setView(_window->getDefaultView());
}

bool ButtonMenu::operator[](size_t n){

	if (_menu[n]->isPressed(_button_mod))return true;
	return false;
}
