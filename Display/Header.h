#pragma once
#include "QGraphicsPixmapItem"
#include "QObject"

class  Player :public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public: void keyPressEvent(QKeyEvent* event);
public: void move(char c);
};

class Boss : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT
};

class Item : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT
public: bool checkitem(int x, int y);
};

class Stone : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT
};

class Point : public QGraphicsTextItem {
public: void checkpoint(bool x);
public: int getpoint();
private: int point;
};