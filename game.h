#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "well.h"
using namespace std;
int extract_numbers(string h)
{
	string temp;
	for (int i = 0; h[i] != 0; i++)
	{
		if (h[i] >= '0' && h[i] <= '9')
			temp += h[i];
	}
	return stoi(temp);
}
class game
{
	
public:
	void draw();
	void namescreen();
	void checkevent();
	void highscorescreen();
	void menuscreen();
	void entername();
	void draw_highscore();
	void drawpause();
	void drawend();
	//
	game();
	game(int row, int col);
	void drawconsole();
	~game();

	//accessors
	bool running();
	//savescore
	void high();
	//Frames
	void update(); //backend
	void savedata();
private:
	int enter ;
	int select ;
	int repeat;
	well Console;
	sf::RectangleShape block;
	sf::Text text;
	sf::RenderWindow* window;
	sf::Event Event;
	sf::Clock Clock;
	sf::Font font;
	bool stop;
	float speed;
	string player;
	int score;
	int level;
	int line;
	int pause;
	fstream file;
	string highscore;
	bool top;
};
game::game() :Console(), Event()
{
	enter = 0;
	select = 1;
	repeat = 0;
	high();
	pause = 1;
	line = 0;
	Console.generator();
	font.loadFromFile("GoldenWings.ttf");
	text.setFont(font);
	level = 1;
	score = 0;
	stop = 0;
	speed = 1.0f;
	window = nullptr;
	Console.fillwell();
}
game::game(int row, int col) :Console(row, col), Event()
{
	enter = 0;
	select = 1;
	repeat = 0;
	top = 0;
	high();
	pause =1;
	line = 0;
	Console.generator();
	font.loadFromFile("GoldenWings.ttf");
	text.setFont(font);
	level = 1;
	score = 0;
	stop = 0;
	speed = 1.0f;
	Clock.restart();
	window = new sf::RenderWindow(sf::VideoMode(700, 800), "Tetris,sf::Style::Titlebar|sf::Style::Close");
	Console.fillwell();
}
void game::drawconsole()
{
	
	float x = 50;
	float y = 50;

	//big grid
	block.setPosition(sf::Vector2f(x, y));
	block.setSize(sf::Vector2f(350, 700));
	block.setOutlineColor(sf::Color::Green);
	block.setFillColor(sf::Color::White);
	block.setOutlineThickness(5);
	window->draw(block);
	//frame

	block.setSize(sf::Vector2f(35, 35));
	block.setOutlineThickness(1);
	for (int i = 0; i < Console.getHeight(); i++)
	{
		for (int j = 0; j < Console.getWidth(); j++)
		{
			block.setPosition(sf::Vector2f(x, y));
			switch (Console.getWell()[i][j])
			{
			case 1:
				block.setFillColor(sf::Color::Cyan);
				break;
			case 2:
				block.setFillColor(sf::Color::Blue);
				break;
			case 3:
				block.setFillColor(sf::Color(255, 165, 0));
				break;
			case 4:
				block.setFillColor(sf::Color(255,215,0));
				break;
			case 5:
				block.setFillColor(sf::Color(75,139,59));
				break;
			case 6:
				block.setFillColor(sf::Color(170, 0, 255));
				break;
			case 7:
				block.setFillColor(sf::Color::Red);
				break;
			case 0:
				block.setFillColor(sf::Color::White);
				break;
			}
			window->draw(block);
			x += 35;
		}
		x = 50;
		y += 35;
	}
	x = 440;
	y = 50;
	sf::Text text;
	//player name 220 text space
	text.setPosition(x, y);
	text.setString("Player Name ");
	text.setFont(font);
	text.setCharacterSize(27);
	text.setFillColor(sf::Color::Red);
	window->draw(text);
	text.setPosition(x, y + 50);
	text.setString(player);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	window->draw(text);
	//level
	text.setPosition(x, y+140);
	text.setString("Level");
	text.setFont(font);
	text.setCharacterSize(27);
	text.setFillColor(sf::Color::Blue);
	window->draw(text);
	text.setPosition(x, y + 140 + 50);
	text.setString(to_string(level));
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	window->draw(text);
	//score
	text.setPosition(x, y + 280);
	text.setString("Score");
	text.setFont(font);
	text.setCharacterSize(27);
	text.setFillColor(sf::Color::Green);
	window->draw(text);
	text.setPosition(x, y +280+ 50);
	text.setString(to_string(score));
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	window->draw(text);
	//lines
	text.setPosition(x, y + 420);
	
	text.setString("Lines");
	text.setFont(font);
	text.setCharacterSize(27);
	text.setFillColor(sf::Color::Yellow);
	window->draw(text);
	text.setPosition(x, y + 420 + 50);
	text.setString(to_string(line));
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	window->draw(text);
	//
	text.setPosition(x, y + 560);
	text.setString("Highscore");
	text.setFont(font);
	text.setCharacterSize(27);
	text.setFillColor(sf::Color::Cyan);
	if (top == 1)
	{
		text.setFillColor(sf::Color::Red);
	}
	window->draw(text);
	text.setPosition(x, y + 560+ 50);
	text.setString(highscore);
	if (top == 1)
	{
		text.setString(to_string(score));
	}
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	window->draw(text);
	if (top == 1)
	{
		text.setPosition(x, y + 660);
		text.setString("New Highscore");
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Cyan);
		window->draw(text);
	}
}
void game::high()
{
	file.open("Highscore.txt");
	string high;
	getline(file, high, ',');
	char a = high[0];
	if (high[0] > '0' && high[0] < '6')
	{
		getline(file, high, ',');
		highscore = high;
	}
	else
	{
		highscore = "0";
	}
	file.close();
}
bool game::running()
{
	return window->isOpen();
}
void game::update()
{
	bool pressed = 0;
	while (window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
		{
			window->close();
			savedata();
		}
		if (pause == 1 && stop == 0)
		{
			checkevent();
		}
		else if (pause == 0 && stop == 0)
		{
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Escape:
				{
					pause = 2;
					enter = 2;
					break;
				}
				case sf::Keyboard::Left:
				{
					Console.moveleft();
					break;
				}
				case sf::Keyboard::Up:
				{
					Console.rotate();
					break;
				}
				case sf::Keyboard::Right:
				{
					Console.moveright();
					break;
				}
				case sf::Keyboard::Down:
				{
					if (Event.type == sf::Event::KeyPressed)
						pressed = 1;
					else
						pressed = 0;
					break;
				}
				}
			}
		}
		else if (pause == 2)
		{
			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Escape)
				{
					pause = 0;
				}
				else if (Event.key.code == sf::Keyboard::Up)
				{
					select--;
					if (select < 1)
						select = 4;
				}
				else if (Event.key.code == sf::Keyboard::Down)
				{
					select++;
					if (select > 4)
						select = 1;
				}
				else if (Event.key.code == sf::Keyboard::Enter)
				{
					if (select == 1)
					{
						pause = 0;
					}
					else if (select == 2)
					{
						select = 1;
						savedata();
						top = 0;
						high();
						pause = 0;
						score = 0;
						Console.fillwell();
						Clock.restart();
						Console.generator();
					}
					else if (select == 3)
					{
						savedata();
						score = 0;
						pause = 1;
						enter = 1;
						select = 1;
						top = 0;
						Console.fillwell();
						player = "";
						Clock.restart();
						Console.generator();
						high();
					}
					else if (select == 4)
					{
						savedata();
						window->close();
					}
				}
			}

		}
		else if (stop == 1)
		{
			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				else if (Event.key.code == sf::Keyboard::Up)
				{
					select--;
					if (select < 1)
						select = 3;
				}
				else if (Event.key.code == sf::Keyboard::Down)
				{
					select++;
					if (select > 3)
						select = 1;
				}
				else if (Event.key.code == sf::Keyboard::Enter)
				{
					if (select == 1)
					{
						pause = 0;
						score = 0;
						Console.fillwell();
						Clock.restart();
						Console.generator();
						high();
						top = 0;
					}
					else if (select == 2)
					{
						score = 0;
						pause = 1;
						enter = 1;
						select = 1;
						Console.fillwell();
						Clock.restart();
						Console.generator();
						top = 0;
						player = "";
						high();
					}
					else if (select == 3)
					{
						window->close();
					}
				}
			}
		}
	}
	if (pause == 0 && stop == 0)
	{
		window->clear(sf::Color::Black);
		bool levelup = 0;
		bool once = 0;
		if (Console.stopped())
		{
			int row = Console.row();
			if (row != -1)
			{
				while (row != -1)
				{
					line++;
					score += 100;
					Console.moverowup(row);
					row = Console.row();
				}
				if (score > stoi(highscore))
					top = 1;
				if (line >= 10)
				{
					level++;
					line = 0;
					speed /= 2;
					sf::Text text;
					text.setString("Level Up!");
					text.setFont(font);
					text.setCharacterSize(50);
					text.setPosition(200, 350);
					window->draw(text);
					window->display();
					Clock.restart();
					while (Clock.getElapsedTime().asSeconds() < 1);
					Console.fillwell();
				}
			}
			if (levelup == 0)
			{
				Console.generator();
				if (Console.checkgenerator() == 0)
				{
					stop = 1;
					savedata();
				}
				else
					Console.startmovement();
			}
		}
		if (stop == 0)
		{
			if (levelup == 0)
			{
				if (pressed == 0)
					speed = 0.2f;
				else
					speed = 0.02f;
				if (Clock.getElapsedTime().asSeconds() >= speed)
				{
					Console.movetetriminodown();
					Clock.restart();
				}
			}
			drawconsole();
		}
		window->display();
	}
	else if (pause == 1 && stop == 0)
	{
		draw();
	}
	else if (pause == 2)
	{
		drawpause();
	}
	else
	{
		drawend();
		enter = 3;
	}
}

void game::savedata()
{
	file.open("Highscore.txt", ios::in);
	string a;
	file.seekg(0, ios::end);
	if (file.tellg()!=0)
	{
		file.seekg(0, ios::beg);
		getline(file, a, ',');
		int num = stoi(a);
		getline(file, a, ',');
		int max = stoi(a);
		getline(file, a);
		int minimum = stoi(a);
		string* temp;
		if (score > max)
		{
			int size;
			if (num != 5)
				size = num + 2;
			else
				size = 6;
			temp = new string[size];
			file.seekg(0, ios::beg);
			temp[1] = player + " ," + to_string(score);
			getline(file, temp[2]);
			for (int i = 2; i < size; i++)
			{
				getline(file, temp[i]);
			}
			file.close();
			minimum = extract_numbers(temp[size - 1]);
			if (num != 5)
				temp[0] = to_string(num + 1);
			else
				temp[0] = to_string(num);
			temp[0] += "," + to_string(score) + "," + to_string(minimum);
			file.open("Highscore.txt", ios::out);
			for (int i = 0; i < size; i++)
			{
				file << temp[i];
				if (i + 1 < size)
					file << endl;
			}
			delete[]temp;
			file.close();
		}
		else if (score <= minimum && num != 5)
		{
			int size = num + 2;
			temp = new string[size];
			file.seekg(0, ios::beg);
			temp[0] = to_string(num + 1);
			temp[0] += "," + to_string(max) + "," + to_string(score);
			getline(file, temp[1]);
			for (int i = 1; i <= num; i++)
			{
				getline(file, temp[i]);
			}
			temp[size - 1] = player + " ," + to_string(score);
			file.close();
			file.open("Highscore.txt", ios::out);
			for (int i = 0; i < size; i++)
			{
				file << temp[i];
				if (i + 1 < size)
					file << endl;
			}
			delete[]temp;
			file.close();
		}

		else if (score > minimum)
		{
			int _size;
			if (num == 5)
				_size = 5;
			else
				_size = num + 1;
			int* _temp = new int[_size];
			int k = 0;
			int size;
			if (num != 5)
				size = num + 2;
			else
				size = 6;
			temp = new string[size];
			file.seekg(0, ios::beg);
			getline(file, temp[1]);
			for (int i = 1; i <= num; i++)
			{
				getline(file, temp[i]);
				cout << temp[i] << endl;
				_temp[k] = extract_numbers(temp[i]);
				cout << _temp[k] << endl;
				k++;
			}
			temp[size - 1] = player + " ," + to_string(score);
			if (num == 5)
				k--;
			_temp[k] = score;
			file.close();
			k = _size;
			for (int i = 0; i < _size; i++)
			{
				int min = 0;
				for (int j = i + 1; j < k; j++)
				{
					if (_temp[j] < _temp[min])
					{
						min = j;
					}
				}
				swap(temp[min + 1], temp[k]);
				swap(_temp[min], _temp[k - 1]);
				k--;
			}
			minimum = extract_numbers(temp[size - 1]);
			if (num != 5)
				temp[0] = to_string(num + 1);
			else
				temp[0] = to_string(num);
			temp[0] += "," + to_string(max) + "," + to_string(minimum);
			delete[]_temp;
			file.open("Highscore.txt", ios::out);
			for (int i = 0; i < size; i++)
			{
				file << temp[i];
				if (i + 1 < size)
					file << endl;
			}
			delete[]temp;
			file.close();
		}
	}
	else
	{
	
		file.close();
		file.open("Highscore.txt", ios::out);
		string temp = to_string(score);
		string add = "1," + temp + "," + temp;
		file << add;
		file << endl;
		file<<(player + " ," + temp);
		file.close();
	}
}
game::~game()
{
	delete window;
}

void game::draw()
{
	text.setOutlineThickness(0);
	if (enter == 0)
	{
		window->clear(sf::Color::Black);
		//tetrimino block
		block.setSize(sf::Vector2f(50, 50));
		float x = 250;
		float y = 200;
		block.setOutlineThickness(2);
		block.setOutlineColor(sf::Color::White);
		block.setFillColor(sf::Color::Blue);
		for (int i = 0; i < 3; i++)
		{
			block.setPosition(sf::Vector2f(x + (50 * i), y));
			window->draw(block);
		}
		x = 250;
		y += 50;
		block.setFillColor(sf::Color::Yellow);
		for (int i = 0; i < 2; i++)
		{
			block.setPosition(sf::Vector2f(x + (50 * i), y));
			window->draw(block);
		}
		x = 250;
		y += 50;
		block.setFillColor(sf::Color::Yellow);
		for (int i = 0; i < 2; i++)
		{
			block.setPosition(sf::Vector2f(x + (50 * i), y));
			window->draw(block);
		}
		for (int i = 0; i < 2; i++)
		{
			block.setPosition(sf::Vector2f(x + (50 * i), y));
			window->draw(block);
		}
		x = 250;
		block.setFillColor(sf::Color::Blue);
		block.setPosition(sf::Vector2f(x + 100, y - 50));
		window->draw(block);
		block.setFillColor(sf::Color(255, 165, 0));
		block.setPosition(sf::Vector2f(x + 100, y));
		window->draw(block);
		y += 50;
		for (int i = 0; i < 3; i++)
		{
			block.setPosition(sf::Vector2f(x + (50 * i), y));
			window->draw(block);
		}
		block.setFillColor(sf::Color::Cyan);
		y = 200;
		x = 250;
		for (int i = 0; i < 4; i++)
		{
			block.setPosition(sf::Vector2f(x + 150, y + (50 * i)));
			window->draw(block);
		}
		//menu text
		text.setString("Play Game");
		text.setOutlineColor(sf::Color(235, 230, 222));
		text.setCharacterSize(50);
		text.setPosition(190, 520);
		if (select == 1)
		{
			text.setFillColor(sf::Color::White);
			text.setOutlineThickness(0);
		}
		else
		{
			text.setFillColor(sf::Color::Black);
			text.setOutlineThickness(3);
		}
		window->draw(text);
		text.setString("HighScores");
		text.setPosition(250, 620);
		text.setCharacterSize(30);
		if (select == 2)
		{
			text.setFillColor(sf::Color::White);
			text.setOutlineThickness(0);
		}
		else
		{
			text.setFillColor(sf::Color::Black);
			text.setOutlineThickness(2);
		}
		window->draw(text);
		window->display();
		text.setLetterSpacing(1);
	}
	else if (enter == 1 && select == 1)
	{

		namescreen();

	}
	else if (enter == 1 && select == 2)
	{
		draw_highscore();
	}
}
void game::namescreen()
{
	window->clear(sf::Color::Black);
	text.setPosition(50, 300);
	text.setString("Enter Your Name");
	text.setCharacterSize(27);
	if (repeat == 0)
		text.setFillColor(sf::Color::Cyan);
	else
	{
		text.setPosition(50, 285);
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(40);
	}
	window->draw(text);
	block.setSize(sf::Vector2f(590, 60));
	block.setFillColor(sf::Color::White);
	block.setPosition(50, 340);
	text.setString("Max 15 Characters");
	text.setPosition(325, 410);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Red);
	window->draw(text);
	window->draw(block);
	text.setString(player);
	text.setPosition(55, 345);
	text.setCharacterSize(35);
	text.setFillColor(sf::Color::Black);
	window->draw(text);
	window->display();
}
void game::checkevent()
{
	if (enter == 0)
	{
		menuscreen();
	}
	else if (enter = 1 && select == 1)
	{
		entername();
	}
	else if (enter = 1 && select == 2)
	{
		window->setFramerateLimit(10);
		highscorescreen();
	}
}
void game::highscorescreen()
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Escape)
		{
			enter = 0;
			select = 1;
			repeat = 0;
		}
		window->setFramerateLimit(60);
	}
}
void game::menuscreen()
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Escape)
			window->close();
		else if (Event.key.code == sf::Keyboard::Up)
		{
			select--;
			if (select < 1)
				select = 2;
		}
		else if (Event.key.code == sf::Keyboard::Down)
		{
			select++;
			if (select > 2)
				select = 1;
		}
		else if (Event.key.code == sf::Keyboard::Enter)
		{
			enter = 1;
		}
	}
}
void game::entername()
{
	if (Event.type == sf::Event::KeyPressed)
	{
		if (Event.key.code == sf::Keyboard::Escape)
		{
			enter = 0;
			select = 1;
		}
		else if (Event.key.code == sf::Keyboard::Enter)
		{
			if (player.size() != 0)
			{
				enter = 0;
				pause = 0;
				repeat = 0;
			}
			else
			{
				repeat = 1;
			}
		}
	}
	else if (Event.type == sf::Event::TextEntered)
	{

		if (Event.text.unicode == '\b' && player.size() > 0)
		{
			player[player.size() - 1] = 0;
			player.resize(player.size() - 1);
		}
		else if (((Event.text.unicode >= 48 && Event.text.unicode < 58) || (Event.text.unicode >= 65 && Event.text.unicode < 91) || (Event.text.unicode == 32) || (Event.text.unicode >= 97 && Event.text.unicode < 123)) && player.size() < 15)
		{
			player += Event.text.unicode;
		}
	}

}
void game::draw_highscore()
{
	if (repeat == 0)
	{
		window->clear(sf::Color::Black);
		file.open("Highscore.txt", ios::in);
		file.seekg(0, ios::end);
		if (file.tellg() != 0)
		{
			file.seekg(0, ios::beg);
			string line;
			getline(file, line, ',');
			char a = line[0];
			getline(file, line);
			text.setFillColor(sf::Color::Cyan);
			float i = 0;
			text.setCharacterSize(50);
			text.setString("#");
			text.setPosition(60, 190);
			window->draw(text);
			text.setCharacterSize(40);
			text.setPosition(125, 200);
			text.setString("Name");
			window->draw(text);
			text.setPosition(500, 200);
			text.setString("SCore");
			window->draw(text);
			text.setFillColor(sf::Color::White);
			while (!file.eof() && i < a - '0')
			{
				i++;
				float temp = (i * 70) + 220;
				getline(file, line, ',');
				text.setPosition(125, temp);
				text.setCharacterSize(38);
				text.setString(line);
				window->draw(text);
				string pos = to_string(static_cast<int>(i) ) + '.';
				text.setString(pos);
				text.setPosition(60, temp);
				window->draw(text);
				getline(file, line);
				text.setPosition(500, temp);
				text.setCharacterSize(35);
				text.setString(line);
				window->draw(text);
			}
		}
		else
		{
			file.seekg(0, ios::beg);
			text.setCharacterSize(45);
			text.setPosition(80, 350);
			text.setString("No Highscores Yet!");
			text.setFillColor(sf::Color::Cyan);
			window->draw(text);
		}
		window->display();
		file.close();
		repeat = 1;
	}

}
void game::drawpause()
{
	window->clear(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(145, 250);
	text.setString("Game Paused");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);
	window->draw(text);
	text.setLetterSpacing(1.5f);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setPosition(255, 330);
	text.setString("Continue");
	text.setCharacterSize(30);
	if (select == 1)
	{
		text.setCharacterSize(38);
		text.setLetterSpacing(1);
		text.setOutlineThickness(0);
		text.setFillColor(sf::Color::White);
	}
	window->draw(text);
	text.setPosition(260, 410);
	text.setString("Restart");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(2);
	if (select == 2)
	{
		text.setCharacterSize(38);
		text.setLetterSpacing(1);
		text.setOutlineThickness(0);
		text.setFillColor(sf::Color::White);
	}
	window->draw(text);
	text.setPosition(230, 490);
	text.setString("New Player");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(2);
	if (select == 3)
	{
		text.setCharacterSize(38);
		text.setLetterSpacing(1);
		text.setOutlineThickness(0);
		text.setFillColor(sf::Color::White);
	}
	window->draw(text);
	text.setPosition(305, 570);
	text.setString("Quit");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(2);
	if (select == 4)
	{
		text.setCharacterSize(38);
		text.setLetterSpacing(1);
		text.setOutlineThickness(0);
		text.setFillColor(sf::Color::White);
	}
	window->draw(text);
	window->display();
	text.setLetterSpacing(1);
}
void game::drawend()
{
	window->clear(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(185, 250);
	text.setString("Game Over");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);
	window->draw(text);
	text.setLetterSpacing(1.5f);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(2);
	text.setPosition(270, 330);
	text.setString("Restart");
	text.setCharacterSize(30);
	if (select == 1)
	{
		text.setCharacterSize(38);
		text.setLetterSpacing(1);
		text.setOutlineThickness(0);
		text.setFillColor(sf::Color::White);
	}
	window->draw(text);
	text.setPosition(240, 410);
	text.setString("New Player");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(2);
	if (select == 2)
	{
		text.setCharacterSize(38);
		text.setLetterSpacing(1);
		text.setOutlineThickness(0);
		text.setFillColor(sf::Color::White);
	}
	window->draw(text);
	text.setPosition(310, 490);
	text.setString("Quit");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(2);
	if (select == 3)
	{
		text.setCharacterSize(38);
		text.setLetterSpacing(1);
		text.setOutlineThickness(0);
		text.setFillColor(sf::Color::White);
	}
	window->draw(text);
	window->display();
	text.setLetterSpacing(1);
}