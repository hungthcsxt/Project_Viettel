#include "QApplication"
#include "QGraphicsScene"
#include "Header.h"
#include "QGraphicsView"
#include "QObject"
#include "QKeyEvent"
#include  "QPixmap"
int flag = 1;

#include <winsock2.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <WS2tcpip.h>
#define SERVER_PORT 5500
#define SERVER_ADDR "10.0.0.1"
#define BUFF_SIZE 2048
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

// point
Point* point = new Point();
void Point::checkpoint(bool x) {
	if (x == 0) {
		point = 0;
		setPlainText(QString("Point: ") + QString::number(point));
	}
	else {
		point = point + 2000;
		setPlainText(QString("Point: ") + QString::number(point));
	}
}
int Point::getpoint() {
	return point;
}

// move
void Player::move(char c) {
	if (c == 'a') {
		if (pos().x() >= 50)	setPos(x() - 50, y());
	}
	else if (c == 'd') {
		if (pos().x() <= 400) setPos(x() + 50, y());
	}
	else if (c == 'w') {
		if (pos().y() >= 50) setPos(x(), y() - 50);
	}
	else if (c == 's') {
		if (pos().y() <= 400) setPos(x(), y() + 50);
	}
}

// check stone
bool checkstone(int x, int y, Stone stone1, Stone stone2, Stone stone3, Stone stone4) {
	if (x == stone1.pos().x() && y == stone1.pos().y()) return 0;
	if (x == stone2.pos().x() && y == stone2.pos().y()) return 0;
	if (x == stone3.pos().x() && y == stone3.pos().y()) return 0;
	if (x == stone4.pos().x() && y == stone4.pos().y()) return 0;
	else return 1;
}

// check boss
bool checkboss(int x, int y, Boss boss1, Boss boss2, Boss boss3) {
	if (x == boss1.pos().x() && y == boss1.pos().y())  return 1;
	if (x == boss2.pos().x() && y == boss2.pos().y())  return 1;
	if (x == boss3.pos().x() && y == boss3.pos().y())  return 1;
	else return 0;
}

// check item
int checkitem(int x, int y, Item item1, Item item2, Item item3, Item item4, Item item5) {
	if (x == item1.pos().x() && y == item1.pos().y()) return 1;
	if (x == item2.pos().x() && y == item2.pos().y()) return 2;
	if (x == item3.pos().x() && y == item3.pos().y()) return 3;
	if (x == item4.pos().x() && y == item4.pos().y()) return 4;
	if (x == item5.pos().x() && y == item5.pos().y()) return 5;
	else return 0;
}

// control player
void Player::keyPressEvent(QKeyEvent* event) {

	if (event->key() == Qt::Key_Left) {
		if (pos().x() >= 50)	setPos(x() - 50, y());
	}
	else if (event->key() == Qt::Key_Right) {
		if (pos().x() <= 400) setPos(x() + 50, y());
	}
	else if (event->key() == Qt::Key_Up) {
		if (pos().y() >= 50) setPos(x(), y() - 50);
	}
	else if (event->key() == Qt::Key_Down) {
		if (pos().y() <= 400) setPos(x(), y() + 50);
	}
}


int main(int argc, char* argv[])
{
	//step 1:
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		cout << "winsock 2.2 is not supported";
		//return 0;
	}

	//step 2:
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET) {
		cout << "error " << WSAGetLastError() << ": cannot creat server socket";
		//return 0;
	}

	// step 3
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	/*if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
		cout << "error " << WSAGetLastError() << ": cannot associate a local address whit srver socket ";
		return 0;
	}
	*/

	// step 4:
	if (listen(listenSock, 10)) {
		cout << "error " << WSAGetLastError() << ": cannot place server socket in state LISTEN.";
		//return 0;
	}

	cout << "server started! " << endl;

	// step 5:
	sockaddr_in clientAddr;
	char buff[BUFF_SIZE], clientIP[INET_ADDRSTRLEN];
	int ret, clientAddrLen = sizeof(clientAddr), clientPort;
	SOCKET connSock;
	// accept request
	connSock = accept(listenSock, (sockaddr*)&clientAddr, &clientAddrLen);
	if (connSock == SOCKET_ERROR) {
		cout << "error " << WSAGetLastError() << ": cannot permit incoming connection";
		//return 0;
	}
	else {
		inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
		clientPort = ntohs(clientAddr.sin_port);
		cout << "accept incoming connection from " << clientIP << " " << clientPort << endl;
	}

	// Application
	QApplication a(argc, argv);
	QGraphicsScene* scene = new QGraphicsScene();

	// add boss
	Boss* boss1 = new Boss();
	boss1->setPixmap(QPixmap(":/images/boss.jpg"));
	boss1->setPos(350, 250);
	scene->addItem(boss1);

	Boss* boss2 = new Boss();
	boss2->setPixmap(QPixmap(":/images/boss2.jpg"));
	boss2->setPos(100, 300);
	scene->addItem(boss2);

	Boss* boss3 = new Boss();
	boss3->setPixmap(QPixmap(":/images/boss3.jpg"));
	boss3->setPos(450, 100);
	scene->addItem(boss3);

	//add stone
	Stone* stone1 = new Stone();
	stone1->setPixmap(QPixmap(":/images/stone.jpg"));
	stone1->setPos(100, 100);
	scene->addItem(stone1);

	Stone* stone2 = new Stone();
	stone2->setPixmap(QPixmap(":/images/stone.jpg"));
	stone2->setPos(200, 150);
	scene->addItem(stone2);

	Stone* stone3 = new Stone();
	stone3->setPixmap(QPixmap(":/images/stone.jpg"));
	stone3->setPos(450, 400);
	scene->addItem(stone3);

	Stone* stone4 = new Stone();
	stone4->setPixmap(QPixmap(":/images/stone.jpg"));
	stone4->setPos(300, 50);
	scene->addItem(stone4);

	Stone* stone5 = new Stone();
	stone5->setPixmap(QPixmap(":/images/tuongngang.jpg"));
	stone5->setPos(0, 500);
	scene->addItem(stone5);

	Stone* stone6 = new Stone();
	stone6->setPixmap(QPixmap(":/images/tuongdoc.jpg"));
	stone6->setPos(500, 0);
	scene->addItem(stone6);

	// add item
	Item* item1 = new Item();
	item1->setPixmap(QPixmap(":/images/item.jpg"));
	item1->setPos(100, 0);
	scene->addItem(item1);

	Item* item2 = new Item();
	item2->setPixmap(QPixmap(":/images/item.jpg"));
	item2->setPos(450, 450);
	scene->addItem(item2);

	Item* item3 = new Item();
	item3->setPixmap(QPixmap(":/images/item.jpg"));
	item3->setPos(0, 400);
	scene->addItem(item3);

	Item* item4 = new Item();
	item4->setPixmap(QPixmap(":/images/item.jpg"));
	item4->setPos(450, 0);
	scene->addItem(item4);

	Item* item5 = new Item();
	item5->setPixmap(QPixmap(":/images/item.jpg"));
	item5->setPos(250, 200);
	scene->addItem(item5);

	//add point
	point->setPlainText(QString("Point: ") + QString::number(0));
	point->setDefaultTextColor(Qt::red);
	point->setFont(QFont("times", 16));
	point->setPos(550, 0);
	scene->addItem(point);

	//add player
	Player* player = new Player();
	player->setPixmap(QPixmap(":/images/player.jpg"));
	player->setPos(0, 0);
	scene->addItem(player);



	QGraphicsView* view = new QGraphicsView(scene);
	view->show();
	view->setFixedSize(700, 700);
	scene->setSceneRect(0, 0, 700, 700);

	//player->setFlag(QGraphicsItem::ItemIsFocusable);
	//player->setFocus();

	return a.exec();
	while (1) {
		ret = recv(connSock, buff, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR) {
			cout << "error " << WSAGetLastError() << ": cannot receive data";
			break;
		}
		else if (ret == 0) {
			cout << "client disconnects " << endl;
			break;
		}
		else {
			buff[ret] = 0;
			player->move(buff[0]);
		}
	}

	return 0;
}

