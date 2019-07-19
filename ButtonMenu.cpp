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
	if (_added_background_texture) delete _background_texture;
	if (_added_button_texture) delete _button_texture;
	if (_added_slider_background_texture) delete _slider_background_texture;
	if (_added_slider_texture) delete _slider_texture;
}

void ButtonMenu::addButton(string text, Font* font){
	_menu.push_back(new TextButton(0.8 * 0.9 * _size.x, _button_size, _pos.x + (_size.x * 0.1 * 0.9), _pos.y+ (_button_size * 0.2) + (_menu.size() * _button_size * 1.2), text, _window, font));
	if (_loaded_button_texture) { 
		if (_rect_button_texture) {
			_menu.back()->setBackgroundRectTexture(_button_texture,_button_rect);
		}
		else {
			_menu.back()->setBackgroundTexture(_button_texture);
		}
	}
	else _menu.back()->setColor(Color::Magenta);
	_menu.back()->changeMod(_mod);
}

void ButtonMenu::update(Event* _event, Mouse* _mouse)
{

	if (_mouse->getPosition(*_window).x>= _pos.x && _mouse->getPosition(*_window).x<= _pos.x+_size.x
		&& _mouse->getPosition(*_window).y >= _pos.y && _mouse->getPosition(*_window).y <= _pos.x + _size.y) {
		for (int i = 0; i < _menu.size(); i++) {
			_menu[i]->update(_event, _mouse);
		}
		if ((((static_cast<float>(_menu.size())) * _button_size))*1.2 >= _size.y) {
			_slider->update(_event, _mouse);
			for (int i = 0; i < _menu.size(); i++) {
				_menu[i]->changePos(Vector2f(_pos.x + (_size.x * 0.1 * 0.9), _pos.y + ((static_cast<float>(i)) * _button_size * 1.2) - ((_slider->getInput().y / 100) * ( (static_cast<float>(_menu.size()) * _button_size * 1.2) - _size.y))));
			}
		}
	}
	else _slider->release();
}

void ButtonMenu::changeMod(uint8_t mod)
{
	if (mod == 0 || mod == 1)_mod = mod;
	for (int i = 0; i < _menu.size(); i++) {
		_menu[i]->changeMod(_mod);
	}
}

void ButtonMenu::setBackgroundTexture(Texture* texture){
	if (texture != nullptr) {
		_background_texture = texture;
		_loaded_background_texture = true;
		_added_background_texture = false;
		_background.setTexture(_background_texture);
		_background.setFillColor(Color::White);
	}
}

void ButtonMenu::addBackgroundTexture(string path){
	_background_texture = new Texture;
	if (_background_texture->loadFromFile(path)) {
		_loaded_background_texture = true;
		_added_background_texture = true;
		_background.setTexture(_background_texture);
		_background.setFillColor(Color::White);
	}
	else {
		delete _background_texture;
	}
}

void ButtonMenu::setBackgroundTextureRect(Texture* texture, IntRect rect)
{
	if (texture != nullptr) {
		_background_texture = texture;
		_loaded_background_texture = true;
		_added_background_texture = false;
		_background.setTexture(_background_texture);
		_background.setTextureRect(rect);
		_background.setFillColor(Color::White);
	}
}

void ButtonMenu::addBackgroundTextureRect(string path, IntRect rect){
	_background_texture = new Texture;
	if (_background_texture->loadFromFile(path)) {
		_loaded_background_texture = true;
		_added_background_texture = true;
		_background.setTexture(_background_texture);
		_background.setTextureRect(rect);
		_background.setFillColor(Color::White);
	}
	else {
		delete _background_texture;
	}
}

void ButtonMenu::setButtonTexture(Texture* texture)
{
	if (texture != nullptr) {
		_button_texture = texture;
		_loaded_button_texture = true;
		_added_button_texture = false;
		for (int i = 0; i < _menu.size();i++)_menu[i]->setBackgroundTexture(_button_texture);
	}
}

void ButtonMenu::addButtonTexture(string path)
{
	_button_texture = new Texture;
	if (_button_texture->loadFromFile(path)) {
		_loaded_button_texture = true;
		_added_button_texture = true;
		for (int i = 0; i < _menu.size(); i++)_menu[i]->setBackgroundTexture(_button_texture);
	}
	else {
		delete _button_texture;
	}
}

void ButtonMenu::setButtonTextureRect(Texture* texture, IntRect rect)
{
	if (texture != nullptr) {
		_button_texture = texture;
		_loaded_button_texture = true;
		_added_button_texture = false;
		for (int i = 0; i < _menu.size(); i++)_menu[i]->setBackgroundRectTexture(_button_texture,rect);
		_button_rect = rect;
		_rect_button_texture = true;
	}
}

void ButtonMenu::addButtonTextureRect(string path, IntRect rect)
{
	_button_texture = new Texture;
	if (_button_texture->loadFromFile(path)) {
		_loaded_button_texture = true;
		_added_button_texture = true;
		for (int i = 0; i < _menu.size(); i++)_menu[i]->setBackgroundRectTexture(_button_texture, rect);
		_button_rect = rect;
		_rect_button_texture = true;
	}
	else {
		delete _button_texture;
	}
}

void ButtonMenu::setSliderBackgroundTexture(Texture* texture)
{
	if (texture != nullptr) {
		_slider_background_texture = texture;
		_loaded_slider_background_texture = true;
		_added_slider_background_texture = false;
		_slider->setBackgroundTexture(_slider_background_texture);
	}
}

void ButtonMenu::addSliderBackgroundTexture(string path)
{
	_slider_background_texture = new Texture;
	if (_slider_background_texture->loadFromFile(path)) {
		_loaded_slider_background_texture = true;
		_added_slider_background_texture = true;
		_slider->setBackgroundTexture(_slider_background_texture);
	}
	else {
		delete _slider_background_texture;
	}
}

void ButtonMenu::setSliderBackgroundTextureRect(Texture* texture, IntRect rect)
{
	if (texture != nullptr) {
		_slider_background_texture = texture;
		_loaded_slider_background_texture = true;
		_added_slider_background_texture = false;
		_slider->setBackgroundRectTexture(_slider_background_texture,rect);
	}
}

void ButtonMenu::addSliderBackgroundTextureRect(string path, IntRect rect)
{
	_slider_background_texture = new Texture;
	if (_slider_background_texture->loadFromFile(path)) {
		_loaded_slider_background_texture = true;
		_added_slider_background_texture = true;
		_slider->setBackgroundRectTexture(_slider_background_texture, rect);
	}
	else {
		delete _slider_background_texture;
	}
}

void ButtonMenu::setSliderTexture(Texture* texture)
{
	if (texture != nullptr) {
		_slider_texture = texture;
		_loaded_slider_texture = true;
		_added_slider_texture = false;
		_slider->setSpecialTexture(_slider_texture);
	}
}

void ButtonMenu::addSliderTexture(string path)
{
	_slider_texture = new Texture;
	if (_slider_texture->loadFromFile(path)) {
		_loaded_slider_texture = true;
		_added_slider_texture = true;
		_slider->setSpecialTexture(_slider_texture);
	}
	else {
		delete _slider_texture;
	}
}

void ButtonMenu::setSliderTextureRect(Texture* texture, IntRect rect)
{
	if (texture != nullptr) {
		_slider_texture = texture;
		_loaded_slider_texture = true;
		_added_slider_texture = false;
		_slider->setSpecialRectTexture(_slider_texture,rect);
	}
}

void ButtonMenu::addSliderTextureRect(string path, IntRect rect)
{
	_slider_texture = new Texture;
	if (_slider_texture->loadFromFile(path)) {
		_loaded_slider_texture = true;
		_added_slider_texture = true;
		_slider->setSpecialRectTexture(_slider_texture, rect);
	}
	else {
		delete _slider_texture;
	}
}

void ButtonMenu::draw(){	
	_window->setView(*_view);
	_window->draw(_background);
	if (((static_cast<float>(_menu.size()) * _button_size)) * 1.2 >= _size.y)
	_slider->draw();
	for (int i = 0; i < _menu.size(); i++)_menu[i]->draw();
	_window->setView(_window->getDefaultView());
}

bool ButtonMenu::operator[](size_t n){

	if (_menu[n]->isPressed())return true;
	return false;
}
