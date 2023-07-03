#include <iostream>
#include"tetrimino.h"
using namespace std;
//
//
//
class well
{
private:
	tetrimino* object;
	int** Well;
	const int Height;
	const int Width;
public:
	well();
	well(int h, int w);
	//getters
	int getHeight() const;
	int getWidth()const;
	int** getWell();
	//
	bool stopped();
	void fillwell();
	void generator();
	bool checkgenerator();
	void startmovement();
	void movetetriminodown();
	int returnelements(int row);//return how much row has been filled
	int row(); // if a row has been filled checker
	bool checkup(int row);
	void moverowup(int row);
	void rotate();
	void moveleft();
	void moveright();
	~well();
};
well::well():Height(0),Width(0)
{
	Well = nullptr;
	object = nullptr;
}
int well::getHeight() const
{
	return Height;
}
int well::getWidth() const
{
	return Width;
}
int** well::getWell()
{
	return Well;
}
void well::startmovement()
{
	object->drawtetrimino(Well);
}
void well::movetetriminodown()
{
	object->move(Well);
}
bool well::checkgenerator()
{
	if (object->possiblemovement(Well, 0, 5, 0) == 1)
		return 1;
	return 0;
}
void well::rotate()
{

	object->deletetetrimino(Well);
	object->angleup();
	if (object->getref_y() + object->getheight() > Height)
	{
		object->angledown();
	}
	else if (object->getref_x() + object->getwidth() > Width)
	{
		bool done = 0;
		bool rev = 0;
		for (int i = 1; i < object->getwidth() && done == 0; i++)
		{
			if (!((object->getref_x() - i + object->getwidth()) > Width))
			{
				object->setref_x(object->getref_x() - i);
				done = 1;
				if (object->possiblemovement(Well, object->getref_y(), object->getref_x(), 0) == 0)
				{
					object->setref_x(object->getref_x() + i);
					rev = 1;
				}
			}
		}
		if (done == 0 || rev == 1)
			object->angledown();
	}
	else if (object->possiblemovement(Well, object->getref_y(), object->getref_x(), 0) == 0)
	{
		object->angledown();;
	}
}
void well::moverowup(int row)
{
	bool stop = 0;
	for (int j = 0; j < Width; j++)
	{
		Well[row][j] = 0;
	}
	for (int i = row; i > 0 && stop == 0; i--)
	{
		if (checkup(i) == 0)
		{
			stop = 1;
		}
		else
		{
			for (int j = 0; j < Width; j++)
			{
				Well[i][j] = Well[i - 1][j];
				Well[i - 1][j] = 0;
			}
		}
	}
}
bool well::checkup(int row)
{
	for (int i = 0; i < Width; i++)
		if (Well[row - 1][i] != 0)
			return 1;
	return 0;
}
bool well::stopped()
{
	if (object->getref_y() + object->getheight() < Height&&object->possiblemovement(Well,object->getref_y()+1,object->getref_x(),1)==1)
		return false;

	return true;
}
well::well(int h, int w) :Height(h), Width(w)
{
	object = nullptr;
	if (Height != 0)
	{
		Well = new int* [Height];
		for (int i = 0; i < Height; i++)
		{
			Well[i] = new int[Width];
		}
		fillwell();
	}
	else
		Well = nullptr;
}
void well::fillwell()
{
	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
			Well[i][j] = 0;
}
int well::returnelements(int row)
{
	int count = 0;
	for (int i = 0; i < Width; i++)
		if (Well[row][i] != 0)
			count++;
	return count;
}
int well::row()
{
	for (int i = Height - 1; i > 0; i--)
	{
		if (returnelements(i) == Width)
		{
			return i;
		}
	}
	return -1;
	
}
void well::moveleft()
{
	object->left(Well);
}
void well::moveright()
{
	if (!((object->getref_x() + object->getwidth()) > Width) && object->possiblemovement(Well, object->getref_y(), object->getref_x() + 1, 1) == 1)
	{
		object->deletetetrimino(Well);
		object->setref_x(object->getref_x() + 1);
		object->drawtetrimino(Well);
	}
}
void well::generator()
{
	srand((unsigned int)time(NULL));
	int r = rand() % 7 + 1;
	if (object != nullptr)
	{
		delete object;
	}
	switch (r)
	{
		case 1:
		{
			object = new i;
			break;
		}
		case 2:
		{
			object = new j;
			break;
		}
		case 3:
		{
			object = new l;
			break;
		}
		case 4:
		{
			object = new o;
			break;
		}
		case 5:
		{
			object = new s;
			break;
		}
		case 6:
		{
			object = new t;
			break;

		}
		case 7:
		{
			object = new z;
			break;
		}
	}
	object->setref_x(4);
	object->setref_y(0);
	object->setangle(0);

}
well::~well()
{	
	for (int i = 0; i < Height; i++)
	{
		delete[]Well[i];
	}
	delete[]Well;

	delete object;
	object = nullptr;
}

