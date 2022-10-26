#include "Object.h"


Object::Object() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}
Object::Object(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


int Object::GetX() {return x;}
int Object::GetY() {return y;}
int Object::GetWidth() { return width; }
int Object::GetHeight() { return height; }
void Object::SetCollisionMatrix(CrossingRoadGame& game) {

}
void Object::Update(CrossingRoadGame&, float fElapsedTime) {

}

bool Object::Move(int xDir, int yDir) {
	x += xDir;
	y += yDir;
	return true;
}
bool Object::SetPosition(int x, int y) {
	this->x = x;
	this->y = y;
	return true;
}

void Object::Draw(CrossingRoadGame& game) {

}

bool Object::CheckCollided(CrossingRoadGame& game) {
	int xTemp = x;
	int yTemp = y;
	bool tl = game.CheckCollision(xTemp, yTemp);

	xTemp = x + width;
	yTemp = y;
	bool tr = game.CheckCollision(xTemp, yTemp);

	xTemp = x;
	yTemp = y + height;
	bool bl = game.CheckCollision(xTemp, yTemp);

	xTemp = x + width;	
	yTemp = y + height;
	bool br = game.CheckCollision(xTemp, yTemp);

	return tl || tr || bl || br;
}