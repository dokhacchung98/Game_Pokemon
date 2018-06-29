#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include<Windows.h>
#include<string>

using namespace std;
using namespace sf;

class Button {
private:
	int x;
	int y;
	Texture tx;
	Sprite sp;
public:
	Button(int x, int y, Texture tx, Sprite sp) {
		this->x = x;
		this->y = y;
		this->tx = tx;
		this->sp = sp;
	}

	void setTexture(Texture tx) {
		this->tx = tx;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void draw(RenderWindow &window) {
		sp.setTexture(tx);
		sp.setPosition((float)x, (float)y);
		window.draw(sp);
	}
};

class Pokemon {
private:
	int id;
	int x;
	int y;
	Texture texture;
	Sprite sprite;
	String path;
public:
	Pokemon(int id, int x, int y) {
		this->id = id;
		this->x = x;
		this->y = y;
	}

	Pokemon() {

	}

	int getId() {
		return id;
	}

	int getX() { return x; }

	int getY() { return y; }

	Texture getTexture() {
		return texture;
	}

	Sprite getSprite() {
		return sprite;
	}

	void setId(int id) {
		this->id = id;
	}

	void setX(int x) {
		this->x = x;
	}

	void setY(int y) {
		this->y = y;
	}

	void setTexture(Texture texture) {
		this->texture = texture;
	}

	void setSprite(Sprite sprite) {
		this->sprite = sprite;
	}

	void drawSprite(RenderWindow &win) {
		path = "Images/image" + to_string(id) + ".png";
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setPosition((float)x, (float)y);
		if (id != 0) {
			win.draw(sprite);
		}
	}
};

void newGmae();


int const countPikachu = 15;
int const numberW = 16;
int const numberH = 10;
Pokemon matrix[numberH][numberW];
int spaceX = 10;
int spaceY = 10;


void setTexture();
/*Tạo matrix mới*/
void createNewMatric();
int countElementPikachu(int t);
/*Kiểm tra matrix có số phần tử đúng chưa*/
void checkMatrix();
bool checkBoolPokemon(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw);
bool checkLineX(int x1, int x2, int y1, int y2, bool check, RenderWindow &window);
bool checkLineY(int x1, int x2, int y1, int y2, bool check, RenderWindow &window);
bool check3Line1(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw);
bool check3Line2(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw);
bool check3Line31(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw);
bool check3Line32(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw);
bool check3Line41(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw);
bool check3Line42(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw);
/*Đếm số phân từ còn lại*/
int checkCout();
/*Kiểm tra trong matrix còn có đôi nào có thể chọn không*/
bool checkDouble(RenderWindow &window, bool hd);
/*Nếu matrix không có cái nào có thể chọn thì thay đổi để có thể chọn lại*/
void changeMatrix(RenderWindow &window);
Texture texture;
Sprite sprite1;
Sprite sprite2;
int tempX1, tempX2, tempY1, tempY2;
int coutClick = 0;
int timeMax = 180;
int timeNow;
/*in matrix trong cửa sổ console*/
void printMatrix();
void threadTime();
int checkTrue = 0;
/*vẽ đường thẳng*/
void drawLine(RenderWindow &window, int x1, int y1, int x2, int y2);
Music msClick;
Music msBg;
Music msSuccess;
Music msWin;
Music msLose;
Texture txWinner;
Texture txLoser;
Sprite spWinner;
Sprite spLoser;
bool clickMouse = true;
bool music = true;
int eye = 3;

int getMin(int a, int b) {
	if (a > b) {
		return b;
	}
	else {
		return a;
	}
}

void a() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Pikachu Game");
	msClick.openFromFile("Audio/click.wav");
	msBg.openFromFile("Audio/bg.wav");
	msSuccess.openFromFile("Audio/success.wav");
	msWin.openFromFile("Audio/winner.wav");
	msLose.openFromFile("Audio/loser.wav");
	msBg.setLoop(true);
	msBg.play();
	texture.loadFromFile("Images/frame.png");
	sprite1.setTexture(texture);
	sprite2.setTexture(texture);
	Texture txBg;
	Texture txPr1;
	Texture txPr2;
	Texture txTime;
	txWinner.loadFromFile("Images/win.png");
	txLoser.loadFromFile("Images/lose.png");
	txTime.loadFromFile("Images/time.png");
	spWinner.setTexture(txWinner);
	spLoser.setTexture(txLoser);
	txPr1.loadFromFile("Images/pr.png");
	txPr2.loadFromFile("Images/pr2.png");
	txBg.loadFromFile("Images/bgpokemon1.png");
	Sprite bg(txBg);
	Sprite spPr1(txPr1);
	Sprite spPr2(txPr2);
	Sprite spTime(txTime);
	spPr1.setPosition(990, 330);
	spPr2.setPosition(992, 332);
	spTime.setPosition(1000, 270);
	Thread thread(&threadTime);
	thread.launch();
	Texture txSound;
	Texture txScore;
	txScore.loadFromFile("Images/score.png");
	txSound.loadFromFile("Images/btnSound1.png");
	Sprite spSound;
	Sprite spScore(txScore);
	spScore.setPosition(1020, 400);
	Texture txEye;
	txEye.loadFromFile("Images/eye3.png");
	Sprite spEye;
	Texture txAgain;
	txAgain.loadFromFile("Images/playAgain.png");
	Sprite spAgain(txAgain);
	Button btnSound(1020, 580, txSound, spSound);
	Button btnEye(1140, 580, txEye, spEye);
	Button btnAgain(500, 500, txAgain, spAgain);

	Font f;
	f.loadFromFile("Font/font.ttf");
	Text t;
	t.setFont(f);
	t.setFillColor(Color::Yellow);
	t.setPosition(1070, 480);
	t.setString("00");
	t.setCharacterSize(40);
	string score;

	while (window.isOpen())
	{
		int x = Mouse::getPosition(window).x;
		int y = Mouse::getPosition(window).y;
		window.draw(bg);
		window.draw(spPr1);
		window.draw(spTime);
		int pr = (int)(246 * ((float)timeNow / timeMax));
		spPr2.setTextureRect(IntRect(0, 0, pr, 36));
		window.draw(spPr2);
		window.draw(spScore);
		Event event;

		btnEye.draw(window);
		btnSound.draw(window);
		if (music) {
			txSound.loadFromFile("Images/btnSound1.png");
			btnSound.setTexture(txSound);
			msBg.setVolume(100.f);
		}
		else {
			txSound.loadFromFile("Images/btnSound2.png");
			btnSound.setTexture(txSound);
			msBg.setVolume(0.f);
		}
		window.draw(t);
		for (int i = 1; i < numberH - 1; i++) {
			for (int j = 1; j < numberW - 1; j++) {
				if (matrix[i][j].getId() != 0) {
					matrix[i][j].drawSprite(window);
				}
			}
		}


		if (tempX1 > 0 && tempY1 > 0 && tempX1 < numberW - 1 && tempY1 < numberH - 1 && matrix[tempY1][tempX1].getId() != 0) {
			sprite1.setPosition((float)tempX1 * 60 + spaceX, (float)tempY1 * 70 + spaceY);
			window.draw(sprite1);
		}

		if (tempX2 > 0 && tempY2 > 0 && tempX2 < numberW - 1 && tempY2 < numberH - 1 && matrix[tempY2][tempX2].getId() != 0) {
			sprite2.setPosition((float)tempX2 * 60 + spaceX, (float)tempY2 * 70 + spaceY);
			window.draw(sprite2);
		}while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				int tX = (x - spaceX) / 60;
				int tY = (y - spaceY) / 70;
				if (tX > 0 && tY > 0 && tX < numberW - 1 && tY < numberH - 1 && matrix[tY][tX].getId() != 0 && clickMouse) {
					if (coutClick == 0) {
						tempX1 = tX;
						tempY1 = tY;
						coutClick++;
						if (music) {
							msClick.play();
						}
						cout << matrix[tempY1][tempX1].getId() << " -- ";
					}
					else if (coutClick == 1) {
						if (tX == tempX1 && tY == tempY1) {
							tempX1 = 0;
							tempY1 = 0;
							coutClick = 0;
							if (music) {
								msClick.play();
							}
						}
						else {
							tempX2 = tX;
							tempY2 = tY;
							coutClick = 0;
							cout << matrix[tempY2][tempX2].getId() << endl;
							if (music) {
								msClick.play();
							}
							if (matrix[tempY1][tempX1].getId() == matrix[tempY2][tempX2].getId()) {
								if (checkBoolPokemon(tempX1, tempX2, tempY1, tempY2, window, true)) {
									sprite2.setPosition((float)tempX2 * 60 + spaceX, (float)tempY2 * 70 + spaceY);
									window.draw(sprite2);
									window.display();
									if (music) {
										msSuccess.play();
									}
									checkTrue++;
									Sleep(500);
									matrix[tempY1][tempX1].setId(0);
									matrix[tempY2][tempX2].setId(0);
									if (checkTrue < 10) {
										score = "0" + to_string(checkTrue);
									}
									else {
										score = to_string(checkTrue);
									}
									t.setString(score);
									printMatrix();
									if (checkDouble(window, false)) {
										cout << "Van co" << endl;
									}
									else if(!checkDouble(window, false) && checkCout()>0){
										changeMatrix(window);
										cout << "Het roi, phai lam lai" << endl;
									}
								}
							}
						}
						tempX1 = 0;
						tempX2 = 0;
						tempY1 = 0;
						tempY2 = 0;
					}
				}
				else if (x >= btnSound.getX() && y >= btnSound.getY() && x <= (btnSound.getX() + 64) && y <= (btnSound.getY() + 64) && clickMouse) {
					music = !music;
					if (music) {
						msClick.play();
					}
				}
				else if (x >= btnEye.getX() && y >= btnEye.getY() && x <= (btnEye.getX() + 64) && y <= (btnEye.getY() + 64) && clickMouse && eye > 0) {
					if (music) {
						msClick.play();
					}
					eye--;
					string path = "Images/eye" + to_string(eye) + ".png";
					txEye.loadFromFile(path);
					btnEye.setTexture(txEye);
					if (checkDouble(window, true)) {
					}
					else if (!checkDouble(window, false) && checkCout()>0) {
						changeMatrix(window);
					}
				}
				else if (!clickMouse && x >= btnAgain.getX() && y >= btnAgain.getY() && x <= (btnAgain.getX() + 218) && y <= (btnAgain.getY() + 108)) {
					newGmae();
				}
			}
		}
		//window.clear();
		if (checkCout() == 0) {
			/*Xu ly thang cuoc*/
			clickMouse = false;
			msBg.stop();
			window.draw(spWinner);
			thread.terminate();
			if (!clickMouse) {
				btnAgain.draw(window);
			}

		}
		if (timeNow <= 0) {
			/*Xu ly thua cuoc*/
			clickMouse = false;
			msBg.stop();
			window.draw(spLoser);
			thread.terminate();
			if (!clickMouse) {
				btnAgain.draw(window);
			}
		}

		window.display();
	}
}

int checkSum() {
	int dem = 0;
	for (int n = 0; n <= countPikachu; n++) {
		dem = 0;
		for (int i = 0; i < numberH; i++) {
			for (int j = 0; j < numberW; j++) {
				if (matrix[i][j].getId() == n) {
					dem++;
				}
			}
		}
		cout << "Phan tu " << n << " co " << dem << endl;
		if (dem % 2 != 0) {
			return n;
		}
	}
	return 0;
}

int main()
{
	createNewMatric();
	a();
	return 0;
}


void createNewMatric() {
	srand(time(NULL));
	for (int i = 0; i < numberH; i++) {
		for (int j = 0; j < numberW; j++) {
			matrix[i][j] = Pokemon::Pokemon(0, j * 60 + spaceX, i * 70 + spaceY);
		}
	}


	for (int i = 1; i < numberH - 1; i++) {
		for (int j = 1; j < numberW - 1; j++) {
			matrix[i][j].setId((rand() % countPikachu) + 1);
		}
	}
	while (checkSum() != 0) {
		checkMatrix();
	}
	printMatrix();
}

void printMatrix() {
	for (int i = 0; i < numberH; i++) {
		for (int j = 0; j < numberW; j++) {
			cout << matrix[i][j].getId() << " ";
		}
		cout << endl;
	}
}

int countElementPikachu(int t) {
	int d = 0;
	for (int i = 1; i < numberH - 1; i++) {
		for (int j = 1; j < numberW - 1; j++) {
			if (matrix[i][j].getId() == t) {
				d++;
			}
		}
	}
	return d;
}

void checkMatrix() {
	for (int i = 1; i < numberH - 1; i++) {
		for (int j = 1; j < numberW - 1; j++) {
			if (matrix[i][j].getId() != countPikachu)
				if (countElementPikachu(matrix[i][j].getId()) % 2 != 0) {
					matrix[i][j].setId(matrix[i][j].getId() + 1);
				}
		}
	}
}

bool checkBoolPokemon(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw) {
	if (x1 == x2) {
		if (checkLineY(x1, x2, y1, y2, false, window)) {
			if (draw) {
				drawLine(window, x1, y1, x2, y2);
				cout << "Check theo x=x" << endl;
			}
			return true;
		}
	}

	if (y1 == y2) {
		if (checkLineX(x1, x2, y1, y2, false, window)) {
			if (draw) {
				cout << "Check theo y=y" << endl;
				drawLine(window, x1, y1, x2, y2);
			}
			return true;
		}
	}

	if (check3Line1(x1, x2, y1, y2, window, draw)) {
		cout << "Check theo loai 1" << endl;
		return true;
	}

	if (check3Line2(x1, x2, y1, y2, window, draw)) {
		cout << "Check theo loai 2" << endl;
		return true;
	}

	if (check3Line31(x1, x2, y1, y2, window, draw)) {
		cout << "Check theo loai 3 1" << endl;
		return true;
	}

	if (check3Line32(x1, x2, y1, y2, window, draw)) {
		cout << "Check theo loai 3 2" << endl;
		return true;
	}

	if (check3Line41(x1, x2, y1, y2, window, draw)) {
		cout << "Check theo loai 4 1" << endl;
		return true;
	}

	if (check3Line42(x1, x2, y1, y2, window, draw)) {
		cout << "Check theo loai 4 2" << endl;
		return true;
	}

	return false;
}


bool checkLineX(int x1, int x2, int y1, int y2, bool check, RenderWindow &window) {
	/*Check theo _________________  */
	int max, min;
	if (x1 == x2) {
		return false;
	}
	if (x1 > x2) {
		max = x1;
		min = x2;
	}
	else {
		max = x2;
		min = x1;
	}

	if (min + 1 == max && !check) {
		return true;
	}
	if (check) {
		for (int i = min; i <= max; i++) {
			if (matrix[y1][i].getId() != 0) {
				return false;
			}
		}
	}
	else {
		for (int i = min + 1; i < max; i++) {
			if (matrix[y1][i].getId() != 0) {
				return false;
			}
		}
	}
	return true;
}

bool checkLineY(int x1, int x2, int y1, int y2, bool check, RenderWindow &window) {
	/*Check loai    |
					|
					|
					|*/
	int max, min;
	if (y1 == y2) {
		return false;
	}
	if (y1 > y2) {
		max = y1;
		min = y2;
	}
	else {
		max = y2;
		min = y1;
	}
	if (min + 1 == max && !check) {
		return true;
	}
	if (check) {
		for (int i = min; i <= max; i++) {
			if (matrix[i][x1].getId() != 0) {
				return false;
			}
		}
	}
	else {
		for (int i = min + 1; i < max; i++) {
			if (matrix[i][x1].getId() != 0) {
				return false;
			}
		}
	}
	return true;
}

bool check3Line1(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw) {
	/*Check loai  ________				va			__________
						  |							|
						  |_________		________|*/
	if (x1 == x2 || y1 == y2) {
		return false;
	}
	int minX, maxX, minY, maxY;
	if (y2 > y1) {
		minX = x1;
		minY = y1;
		maxX = x2;
		maxY = y2;
	}
	else {
		minX = x2;
		minY = y2;
		maxX = x1;
		maxY = y1;
	}
	if (minX < maxX) {
		/*Loai 1 truoc*/
		for (int i = minX + 1; i <= maxX; i++) {
			if (matrix[minY][i].getId() != 0) {
				return false;
			}
			else {
				if (i == maxX && checkLineY(i, maxX, minY, maxY, false, window)) {
					if (draw) {
						drawLine(window, minX, minY, i, minY);
						drawLine(window, i, minY, maxX, maxY);
					}
					return true;
				}
				else if (i < maxX && checkLineY(i, i, minY, maxY, true, window) && checkLineX(i, maxX, maxY, maxY, false, window)) {
					if (draw) {
						drawLine(window, minX, minY, i, minY);
						drawLine(window, i, minY, i, maxY);
						drawLine(window, i, maxY, maxX, maxY);
					}
					return true;
				}
			}
		}
	}
	else if (minX > maxX) {
		/* Check loai 2*/
		for (int i = minX - 1; i >= maxX; i--) {
			if (matrix[minY][i].getId() != 0) {
				return false;
			}
			else {
				if (i == maxX && checkLineY(i, maxX, minY, maxY, false, window)) {
					if (draw) {
						drawLine(window, minX, minY, i, minY);
						drawLine(window, i, minY, maxX, maxY);
					}
					return true;
				}
				else if (i > maxX && checkLineY(i, i, minY, maxY, true, window) && checkLineX(i, maxX, maxY, maxY, false, window)) {
					if (draw) {
						drawLine(window, minX, minY, i, minY);
						drawLine(window, i, minY, i, maxY);
						drawLine(window, i, maxY, maxX, maxY);
					}
					return true;
				}
			}
		}
	}

	return false;
}

bool check3Line2(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw) {
	/*check loai |				 va				  |
				 |_______				__________|
						 |				|
						 |				|	*/
	if (x1 == x2 || y1 == y2) {
		return false;
	}
	int minX, minY, maxX, maxY;
	if (y2 > y1) {
		minX = x1;
		minY = y1;
		maxX = x2;
		maxY = y2;
	}
	else {
		minX = x2;
		minY = y2;
		maxX = x1;
		maxY = y1;
	}
	for (int i = minY + 1; i <= maxY; i++) {
		if (matrix[i][minX].getId() != 0) {
			return false;
		}
		else {
			if (i == maxY && checkLineX(minX, maxX, i, maxY, false, window)) {
				if (draw) {
					drawLine(window, minX, minY, minX, i);
					drawLine(window, minX, i, maxX, maxY);
				}
				return true;
			}
			else if (i < maxY && checkLineX(minX, maxX, i, i, true, window) && checkLineY(maxX, maxX, i, maxY, false, window)) {
				if (draw) {
					drawLine(window, minX, minY, minX, i);
					drawLine(window, minX, i, maxX, i);
					drawLine(window, maxX, i, maxX, maxY);
				}
				return true;
			}
		}
	}
	return false;
}

bool check3Line31(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw) {
	/*Check loai |        |
				 |        |
				 |________|	*/
	if (x1 == x2) {
		return false;
	}
	int minX, minY, maxX, maxY;
	if (x2 > x1) {
		minX = x1;
		minY = y1;
		maxX = x2;
		maxY = y2;
	}
	else {
		minX = x2;
		minY = y2;
		maxX = x1;
		maxY = y1;
	}

	for (int i = minY + 1; i <= numberH; i++) {
		if (matrix[i][minX].getId() != 0) {
			return false;
		}
		else
		{
			if (checkLineX(minX, maxX, i, i, true, window) && checkLineY(maxX, maxX, i, maxY, false, window)) {
				if (draw) {
					drawLine(window, maxX, i, maxX, maxY);
					drawLine(window, minX, i, maxX, i);
					drawLine(window, minX, minY, minX, i);
				}
				return true;
			}
		}
	}

	return false;
}

bool check3Line32(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw) {
	/*Check loai   _________
				  |        |
				  |        |*/
	if (x1 == x2) {
		return false;
	}
	int minX, minY, maxX, maxY;
	if (x2 > x1) {
		minX = x1;
		minY = y1;
		maxX = x2;
		maxY = y2;
	}
	else {
		minX = x2;
		minY = y2;
		maxX = x1;
		maxY = y1;
	}

	/*Check loai 2*/
	for (int i = minY - 1; i >= 0; i--) {
		if (matrix[i][minX].getId() != 0) {
			return false;
		}
		else
		{
			if (checkLineX(minX, maxX, i, i, true, window) && checkLineY(maxX, maxX, i, maxY, false, window)) {
				if (draw) {
					drawLine(window, maxX, i, maxX, maxY);
					drawLine(window, minX, i, maxX, i);
					drawLine(window, minX, minY, minX, i);
				}
				return true;
			}
		}
	}
	return false;
}

bool check3Line41(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw) {
	/*Check loai    __________
				   |
				   |__________*/
	if (y1 == y2) {
		return false;
	}
	int minX, minY, maxX, maxY;
	if (y2 > y1) {
		minX = x1;
		minY = y1;
		maxX = x2;
		maxY = y2;
	}
	else {
		minX = x2;
		minY = y2;
		maxX = x1;
		maxY = y1;
	}

	for (int i = minX - 1; i >= 0; i--) {
		if (matrix[minY][i].getId() != 0) {
			return false;
		}
		else
		{
			if (checkLineX(maxX, i, maxY, maxY, false, window) && checkLineY(i, i, minY, maxY, true, window)) {
				if (draw) {
					drawLine(window, minX, minY, i, minY);
					drawLine(window, i, minY, i, maxY);
					drawLine(window, i, maxY, maxX, maxY);
				}
				return true;
			}
		}
	}
	return false;
}

bool check3Line42(int x1, int x2, int y1, int y2, RenderWindow &window, bool draw) {
	/*Check loai    __________
							  |
					__________|*/
	if (y1 == y2) {
		return false;
	}
	int minX, minY, maxX, maxY;
	if (y2 > y1) {
		minX = x1;
		minY = y1;
		maxX = x2;
		maxY = y2;
	}
	else {
		minX = x2;
		minY = y2;
		maxX = x1;
		maxY = y1;
	}

	for (int i = minX + 1; i <= numberW; i++) {
		if (matrix[minY][i].getId() != 0) {
			return false;
		}
		else
		{
			if (checkLineX(maxX, i, maxY, maxY, false, window) && checkLineY(i, i, minY, maxY, true, window)) {
				if (draw) {
					drawLine(window, minX, minY, i, minY);
					drawLine(window, i, minY, i, maxY);
					drawLine(window, i, maxY, maxX, maxY);
				}
				return true;
			}
		}
	}
	return false;
}

void threadTime() {
	timeNow = timeMax;
	while (timeNow > 0) {
		//cout << "Time : " << timeNow << endl;
		timeNow--;
		Sleep(1000);
	}
}

void drawLine(RenderWindow &window, int x1, int y1, int x2, int y2) {
	//window.draw()
	RectangleShape line;
	line.setFillColor(Color::Red);
	if (x1 == x2) {
		line.setSize(Vector2f(4.f, abs(y1 - y2)*70.f + 2));
		line.setPosition((float)(x1) * 60 + 28 + spaceX, (float)getMin(y1, y2) * 70 + 35 + spaceY);
	}
	else if (y1 == y2) {
		line.setSize(Vector2f(abs(x1 - x2)*60.f + 2, 4.f));
		line.setPosition(getMin(x1, x2) * 60.f + 30 + spaceX, (y1) * 70.f + 33 + spaceY);
	}
	window.draw(line);
}

int checkCout() {
	int dem = 0;
	for (int i = 1; i < numberH - 1; i++) {
		for (int j = 1; j < numberW - 1; j++) {
			if (matrix[i][j].getId() != 0)
				dem++;
		}
	}
	return dem;
}

bool checkDouble(RenderWindow &window, bool hd) {
	for (int i = 1; i < numberH - 1; i++) {
		for (int j = 1; j < numberW - 1; j++) {
			if (matrix[i][j].getId() != 0) {
				for (int n = i; n < numberH - 1; n++) {
					for (int m = 1; m < numberW - 1; m++) {
						if (matrix[n][m].getId() == matrix[i][j].getId()) {
							if (checkBoolPokemon(j, m, i, n, window, false)) {
								if (hd) {
									checkBoolPokemon(j, m, i, n, window, true);
									cout << j << " - " << i << " - " << m << " - " << n << endl;
									window.display();
									Sleep(500);
								}
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

void changeMatrix(RenderWindow &window) {
	while (!checkDouble(window, false)) {
		srand(time(NULL));
		for (int i = 1; i < numberH - 1; i++) {
			for (int j = 1; j < numberW - 1; j++) {
				if (matrix[i][j].getId() != 0) {
					matrix[i][j].setId((rand() % countPikachu) + 1);
				}
			}
			while (checkSum() != 0) {
				checkMatrix();
			}
		}
	}
}

void newGmae() {
	createNewMatric();
	clickMouse = true;
	checkTrue = 0;
	eye = 3;
	msBg.play();
	a();
}