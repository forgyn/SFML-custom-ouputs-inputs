#include "TextInput.h"


TextInput::TextInput(float size_x, float size_y, float pos_x, float pos_y, RenderWindow* window)
	:_size(Vector2f(size_x,size_y)),_position(Vector2f(pos_x,pos_y)){
	_window = window;
	_button = new Button(_size, _position,_window);
	_button->setColor(Color::Transparent);

	_background = new RectangleShape(_size);
	_background->setPosition(_position);
	_background->setFillColor(Color::Yellow);

	_cursor = new RectangleShape(Vector2f(5, _size.y * 0.8));
	_cursor->setPosition(_position.x + (_size.x * OFFSET_X), _position.y + (_size.y * 0.1));
	_cursor->setFillColor(Color::Black);

	_inputText = new Text;
	_inputText->setString(_input);
	_inputText->setCharacterSize(_size.y * 0.8);
	_inputText->setPosition(_position.x + (_size.x * OFFSET_X),_position.y);
	_inputText->setFillColor(Color::Black);
}

TextInput::TextInput(Vector2f size, Vector2f pos, RenderWindow* window)
	:_size(size), _position(pos) {
	_window = window;
	_button = new Button(_size, _position,_window);
	_button->setColor(Color::Transparent);

	_background = new RectangleShape(_size);
	_background->setPosition(_position);
	_background->setFillColor(Color::Yellow);

	_cursor = new RectangleShape(Vector2f(5, _size.y * 0.8));
	_cursor->setPosition(_position.x + (_size.x * OFFSET_X), _position.y + (_size.y * 0.1));
	_cursor->setFillColor(Color::Black);

	_inputText = new Text;
	_inputText->setString(_input);
	_inputText->setCharacterSize(_size.y * 0.8);
	_inputText->setPosition(_position.x + (_size.x * OFFSET_X), _position.y);
	_inputText->setFillColor(Color::Black);
}

void TextInput::draw(){
	if (_clock.getElapsedTime().asSeconds() >= 0.5 && ACTIVATED) {
		_clock.restart();
		if (_cursor->getFillColor() == Color::Black)_cursor->setFillColor(Color::Transparent);
		else _cursor->setFillColor(Color::Black);
	}
	_button->draw();
	_window->draw(*_background);
	_window->draw(*_cursor);
	_window->draw(*_inputText);
}

void TextInput::update(){
	_button->update();
	
	if (_button->isPressed()) {
		_button->reset();
		ACTIVATED = true;
	}
	if (_event->type == Event::MouseButtonPressed && !_button->isPointed()) {
		_button->reset();
		ACTIVATED = false;
	}
	if (ACTIVATED) {
		if (_event->type == Event::TextEntered)addChar();
	}
	else {
		_cursor->setFillColor(Color::Transparent);
	}
	_inputText->setString(_input);
	_cursor->setPosition(_inputText->getLocalBounds().width + (_position.x + _size.x* OFFSET_X) + 5, _cursor->getPosition().y);
}

void TextInput::addChar()
{
		if (_event->text.unicode == '\b') {
			if(_input.size() > 0)
			_input.erase(_input.size() - 1, 1);
		}
		else { 
			char newChar = static_cast<char>(_event->text.unicode);
			_input += newChar;
			_inputText->setString(_input);
			if (_inputText->getLocalBounds().width > _size.x) {
				_input.erase(_input.size() - 1, 1);
				_inputText->setString(_input);
			}
		}

}

void TextInput::setPtr(Mouse* mouse, Event* evnt, Font* font)
{
	_mouse = mouse; 
	_event = evnt;
	_font = font;
	_inputText->setFont(*_font);
	_button->setPtr(_mouse, _event);
	loadedFont = true;
}

void TextInput::setBackgroundTexture(string path){
	_texture = new Texture();
	_texture->loadFromFile(path);
	_background->setTexture(_texture);
	_background->setFillColor(Color::White);
}

void TextInput::setBackgroundTexture(Texture* texture){
	_texture = texture;
	_background->setTexture(_texture);
	loadedTexture = true;
	_background->setFillColor(Color::White);
}

void TextInput::setBackgroundRectTexture(string path, IntRect rect){
	_texture = new Texture();
	_texture->loadFromFile(path);
	_background->setTexture(_texture);
	_background->setTextureRect(rect);
	_background->setFillColor(Color::White);
}

void TextInput::setBackgroundRectTexture(Texture* texture, IntRect rect){
	_texture = texture;
	_background->setTexture(_texture);
	loadedTexture = true;
	_background->setTextureRect(rect);
	_background->setFillColor(Color::White);
}

TextInput::~TextInput(){
	delete _button;
	delete _background;
	delete _cursor;
	delete _inputText;
	if (!loadedTexture)delete _texture;
	if (!loadedFont)delete _font;
}

void TextInput::setFont(Font* font)
{
	_font = font;
	_inputText->setFont(*_font);
	loadedFont = true;
}

void TextInput::setFont(string path)
{
	_font = new Font();
	_font->loadFromFile(path);
	_inputText->setFont(*_font);
	loadedFont = false;
}