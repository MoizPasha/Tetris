#include <iostream>
using namespace std;
class tetrimino
{
protected:
	static int num;
	int ref_y;//start location of tetrimino
	int ref_x;
	int angle;
	int width;//width of object
	int height;
public:
	tetrimino();
	tetrimino(int, int, int, int);
	//getter & setter
	void setref_x(int);
	void setref_y(int);
	int getref_x();
	int getref_y();
	int getheight();
	int getwidth();
	int getangle();

	//polymorphism
	void setangle(int ang)
	{
		angle = ang;
		if (angle == 360)
			angle = 0;
	}
	void angleup()
	{
		angle += 90;
		if (angle == 360)
			angle = 0;
		swap(height, width);
	}
	void angledown()
	{
		angle -= 90;
		if (angle == -90)
			angle = 270;
		swap(height, width);
	}
	//rotate 90*
	virtual void drawtetrimino(int** well, int temp = num) = 0;
	virtual void deletetetrimino(int** well)
	{
		drawtetrimino(well, 0);
	}
	virtual void move(int** well)
	{
		deletetetrimino(well);
		ref_y++;
		drawtetrimino(well);
	}
	virtual bool possiblemovement(int** well, int y, int x, bool del)
	{
		return 0;
	}
	//movement 
	void left(int** well);
	virtual ~tetrimino() = default;
};
int tetrimino::num = 0;
tetrimino::tetrimino()
{
	ref_y = 0;
	ref_x = 0;
	angle = 0;
	width = 0;
	height = 0;
}
tetrimino::tetrimino(int h, int w, int ang, int n)
{
	num = n;
	angle = ang;
	width = w;
	height = h;
	ref_y = 0;
	ref_x = 0;
}

void tetrimino::setref_x(int x)
{
	ref_x = x;
}
void tetrimino::setref_y(int y)
{
	ref_y = y;
}
int tetrimino::getref_x()
{
	return ref_x;
}
int tetrimino::getref_y()
{
	return ref_y;
}
int tetrimino::getheight()
{
	return height;
}
int tetrimino::getwidth()
{
	return width;
}
int tetrimino::getangle()
{
	return angle;
}
// movement
void tetrimino::left(int** well)
{
	if (ref_x != 0 && possiblemovement(well, ref_y, ref_x - 1, 1) == 1)
	{
		deletetetrimino(well);
		ref_x--;
		drawtetrimino(well);
	}
}
//
//
//child classes
//
//
//
//
//
class i : public tetrimino
{
public:
	i();
	void drawtetrimino(int** well, int temp = num)
	{
		if (angle == 0 || angle == 180)
		{
			for (int i = 0; i < height; i++)
				well[ref_y + i][ref_x] = temp;
		}
		if (angle == 90 || angle == 270)
		{
			for (int i = 0; i < width; i++)
				well[ref_y][ref_x + i] = temp;
		}
	}
	bool possiblemovement(int** well, int y, int x, bool del)
	{
		if (del == 1)
			deletetetrimino(well);
		if (angle == 0 || angle == 180)
		{
			for (int i = 0; i < height; i++)
				if (well[y + i][x] != 0)
				{
					if (del == 1)
						drawtetrimino(well);
					return 0;
				}
		}
		if (angle == 90 || angle == 270)
		{
			for (int i = 0; i < width; i++)
				if (well[y][x + i] != 0)
				{
					if (del == 1)
						drawtetrimino(well);
					return 0;
				}
		}
		drawtetrimino(well);
		return true;

	}
	void move(int** well)
	{
		tetrimino::move(well);
	}
	~i();

private:
	//color
};

i::i() :tetrimino(4, 1, 0, 1)
{
}

i::~i()
{
}
class j : public tetrimino
{
public:
	j();
	void drawtetrimino(int** well, int temp = num)
	{
		if (angle == 0)
		{
			well[ref_y + 2][ref_x] = temp;
			for (int i = ref_y, j = 0; j < height; j++, i++)
				well[i][ref_x + 1] = temp;
		}
		else if (angle == 90)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 2] = temp;
		}
		else if (angle == 180)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 2][ref_x] = temp;
			well[ref_y][ref_x + 1] = temp;
		}
		else if (angle == 270)
		{
			well[ref_y + 1][ref_x] = temp;
			well[ref_y][ref_x] = temp;
			well[ref_y][ref_x + 1] = temp;
			well[ref_y][ref_x + 2] = temp;
		}
	}
	bool possiblemovement(int** well, int y, int x, bool del)
	{
		if (del == 1)
			deletetetrimino(well);
		if (angle == 0)
		{
			if (well[(y)+2][x] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
			for (int i = (y), j = 0; j < height; j++, i++)
				if (well[i][x + 1] != 0)
				{
					if (del == 1)
						drawtetrimino(well);
					return 0;
				}
		}
		else if (angle == 90)
		{
			if (well[y][x] != 0 ||
				well[y + 1][x] != 0 ||
				well[y + 1][x + 1] != 0 ||
				well[y + 1][x + 2] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else if (angle == 180)
		{
			if (well[y][x] != 0 ||
				well[y + 1][x] != 0 ||
				well[y + 2][x] != 0 ||
				well[y][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else if (angle == 270)
		{
			if (well[y + 1][x] != 0 ||
				well[y][x] != 0 ||
				well[y][x + 1] != 0 ||
				well[y][x + 2] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		drawtetrimino(well);
		return 1;
	}
	void move(int** well)
	{
		tetrimino::move(well);
	}
	~j();

private:

};

j::j() :tetrimino(3, 2, 0, 2)
{
}

j::~j()
{
}

class l : public tetrimino
{
public:
	l();
	void drawtetrimino(int** well, int temp = num)
	{
		if (angle == 0)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 2][ref_x] = temp;
			well[ref_y + 2][ref_x + 1] = temp;
		}
		else if (angle == 90)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y][ref_x + 1] = temp;
			well[ref_y][ref_x + 2] = temp;
			well[ref_y + 1][ref_x] = temp;
		}
		else if (angle == 180)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 2][ref_x + 1] = temp;

		}
		else if (angle == 270)
		{
			well[ref_y][ref_x + 2] = temp;
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 2] = temp;
		}
	}
	bool possiblemovement(int** well, int y, int x, bool del)
	{
		if (del == 1)
			deletetetrimino(well);
		if (angle == 0)
		{
			if (well[y][x] != 0 ||
				well[y + 1][x] != 0 ||
				well[y + 2][x] != 0 ||
				well[y + 2][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else if (angle == 90)
		{
			if (well[y][x] != 0 ||
				well[y][x + 1] != 0 ||
				well[y][x + 2] != 0 ||
				well[y + 1][x] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else if (angle == 180)
		{
			if (well[y][x] != 0 ||
				well[y][x + 1] != 0 ||
				well[y + 1][x + 1] != 0 ||
				well[y + 2][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}

		}
		else if (angle == 270)
		{
			if (well[y][x + 2] != 0 ||
				well[y + 1][x] != 0 ||
				well[y + 1][x + 1] != 0 ||
				well[y + 1][x + 2] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		drawtetrimino(well);
		return true;
	}
	void move(int** well)
	{
		tetrimino::move(well);
	}
	~l();

private:

};

l::l() :tetrimino(3, 2, 0, 3)
{
}

l::~l()
{
}

class o : public tetrimino
{
public:
	o();
	void drawtetrimino(int** well, int temp = num)
	{
		well[ref_y][ref_x] = temp;
		well[ref_y + 1][ref_x + 1] = temp;
		well[ref_y][ref_x + 1] = temp;
		well[ref_y + 1][ref_x] = temp;
	}
	bool possiblemovement(int** well, int y, int x, bool del)
	{
		if (del == 1)
			deletetetrimino(well);
		if (well[(y)][x] != 0 || well[(y)+1][x + 1] != 0 || well[(y)][x + 1] != 0 || well[(y)+1][x] != 0)
		{
			if (del == 1)
				drawtetrimino(well);
			return 0;
		}
		drawtetrimino(well);
		return 1;
	}
	void move(int** well)
	{
		tetrimino::move(well);
	}
	~o();

private:

};

o::o() :tetrimino(2, 2, 0, 4)
{
}

o::~o()
{
}

class s : public tetrimino
{
public:
	s();
	void drawtetrimino(int** well, int temp = num)
	{
		if (angle == 0 || angle == 180)
		{
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y][ref_x + 1] = temp;
			well[ref_y][ref_x + 2] = temp;
		}
		else if (angle == 90 || angle == 270)
		{
			well[ref_y + 1][ref_x] = temp;
			well[ref_y][ref_x] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 2][ref_x + 1] = temp;
		}
	}
	bool possiblemovement(int** well, int y, int x, bool del)
	{
		if (del == 1)
			deletetetrimino(well);
		if (angle == 0 || angle == 180)
		{
			if (well[y + 1][x] != 0 || well[y + 1][x + 1] != 0 || well[y][x + 1] != 0 || well[y][x + 2] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else
		{
			if (well[y + 1][x] != 0 ||
				well[y][x] != 0 ||
				well[y + 1][x + 1] != 0 ||
				well[y + 2][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		drawtetrimino(well);
		return 1;
	}
	void move(int** well)
	{
		tetrimino::move(well);
	}
	~s();

private:

};

s::s() :tetrimino(2, 3, 0, 5)
{
}

s::~s()
{
}

class t : public tetrimino
{
public:
	t();
	void drawtetrimino(int** well, int temp = num)
	{
		if (angle == 0)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y][ref_x + 1] = temp;
			well[ref_y][ref_x + 2] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
		}
		else if (angle == 90)
		{
			well[ref_y][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 2][ref_x + 1] = temp;
			well[ref_y + 1][ref_x] = temp;
		}
		else if (angle == 180)
		{
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 2] = temp;
			well[ref_y][ref_x + 1] = temp;
		}
		else if (angle == 270)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 2][ref_x] = temp;
		}
	}
	bool possiblemovement(int** well, int y, int x, bool del)
	{
		if (del == 1)
			deletetetrimino(well);
		if (angle == 0)
		{
			if (well[y][x] != 0 ||
				well[y][x + 1] != 0 ||
				well[y][x + 2] != 0 ||
				well[y + 1][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else if (angle == 90)
		{
			if (well[y][x + 1] != 0 ||
				well[y + 1][x + 1] != 0 ||
				well[y + 2][x + 1] != 0 ||
				well[y + 1][x] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else if (angle == 180)
		{
			if (well[y + 1][x] != 0 ||
				well[y + 1][x + 1] != 0 ||
				well[y + 1][x + 2] != 0 ||
				well[y][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else if (angle == 270)
		{
			if (well[y][x] != 0 ||
				well[y + 1][x] != 0 ||
				well[y + 2][x] != 0 ||
				well[y + 1][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		drawtetrimino(well);
		return 1;
	}
	void move(int** well)
	{
		tetrimino::move(well);
	}
	~t();

private:

};

t::t() :tetrimino(2, 3, 0, 6)
{
}

t::~t()
{
}

class z : public tetrimino
{
public:
	z();
	void drawtetrimino(int** well, int temp = num)
	{
		if (angle == 0 || angle == 180)
		{
			well[ref_y][ref_x] = temp;
			well[ref_y][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 2] = temp;
		}
		else
		{
			well[ref_y][ref_x + 1] = temp;
			well[ref_y + 1][ref_x + 1] = temp;
			well[ref_y + 1][ref_x] = temp;
			well[ref_y + 2][ref_x] = temp;
		}
	}
	bool possiblemovement(int** well, int y, int x, bool del)
	{
		if (del == 1)
			deletetetrimino(well);
		if (angle == 0 || angle == 180)
		{

			if (well[y][x] != 0 ||
				well[y][x + 1] != 0 ||
				well[y + 1][x + 2] != 0 ||
				well[y + 1][x + 1] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		}
		else
			if (well[y][x + 1] != 0 ||
				well[y + 1][x + 1] != 0 ||
				well[y + 1][x] != 0 ||
				well[y + 2][x] != 0)
			{
				if (del == 1)
					drawtetrimino(well);
				return 0;
			}
		drawtetrimino(well);
		return 1;
	}
	void move(int** well)
	{
		tetrimino::move(well);
	}
	~z();

private:

};

z::z() :tetrimino(2, 3, 0, 7)
{
}
z::~z()
{
}

