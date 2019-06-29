#pragma once
#include "Input.h"

#define TEXT_RATIO 0.5f
#define BASIC_COLOR Color::Yellow

class Button : public InputElement {
public:
	Button(float pos_x, float pos_y, float size_x, float size_y,RenderWindow* window);
	Button(Vector2f pos, Vector2f size, RenderWindow* window);
	~Button();
	void draw();
	virtual void update();
	bool isPointed();
	void setColor(const Color &color);
	void setBackgroundTexture(string path);
	void setBackgroundTexture(Texture* texture);
	void setBackgroundRectTexture(string path, IntRect rect);
	void setBackgroundRectTexture(Texture* texture, IntRect rect);
	void setSpecialTexture(Texture* texture) {}
	void setSpecialTexture(string path) {}
	void setSpecialRectTexture(Texture* texture, IntRect rect) {}
	void setSpecialRectTexture(string path, IntRect rect) {}
	bool isPressed(bool unpress = true);
	Vector2f getPos() { return Vector2f(_position.x-_backgroud->getOrigin().x,_position.y - _backgroud->getOrigin().y); }
	void reset();
	
	void changePos(Vector2f pos);
	void changeSize(Vector2f size);
protected:
	Vector2f _size;
	Vector2f _position;
	Vector2u _defaultWindowSize;
	RectangleShape* _backgroud = nullptr;
	Color _basicColor;
	Texture* _texture = nullptr;
	bool loadedTexture = false;
	bool PRESSED = false;
};

class DraggableButton : public Button {
public:
	DraggableButton(float size_x, float size_y, float pos_x, float pos_y, RenderWindow* window);
	DraggableButton(Vector2f size, Vector2f pos, RenderWindow* window);
	void update();
	bool FOLLOWING = false;
	void changeMod(unsigned mod) { _mod = mod; }
	void reset();
	Vector2f getLeftUpCorner() { return Vector2f(_position.x,_position.y); }
	Vector2f getRightDownCorner() { return Vector2f(_position.x + _size.x, _position.y + _size.y); }
	void setLimit(float min_x,float max_x, float min_y,float max_y);
	
private:
	//Vector2i _previousMousePos;
	unsigned _mod = 0;
	Vector2f _limit_max;
	Vector2f _limit_min;
};

class TextButton : public Button {
public:
	TextButton(float pos_x, float pos_y,float size_x,float size_y,const string &text, RenderWindow* window);
	~TextButton();
	void draw();
	void changeStyle(Uint32 style);
	void setFont(Font* font);
	void setPtr(Mouse* mouse, Event* evnt, Font* font);
	void setFont(string path);
	void getDebugInfo();
private:
	Text *_text = nullptr;
	string _str;
	bool loadedFont = false;
	Font* _font = nullptr;
};