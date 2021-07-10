#include <iostream>
#include <unordered_map>
#include <list>
#include <random>
using namespace std;
struct cell
{
	int x;
	int y;
	cell(int X, int Y)

	{
		x = X;
		y = Y;

	}
	
	bool operator==(const cell& p) const;
	
};
bool cell::operator==(const cell& p) const
{
	return x == p.x and y == p.y;
}
/*bool cell::operator<(const cell& var)
{
	if (x != var.x)
		return x < var.x;
	else return y < var.y;
}*/
class MyHashFunction {
	public:

		size_t operator()(const cell& var) const
		{
		   return (hash<int>()(var.x)) ^ (hash<int>()(var.y));
		}

};

class life
{
	private:
		int height, width;
		unordered_map<cell,bool, MyHashFunction> planet;
		unordered_map<cell,bool, MyHashFunction>::iterator it;
	public:
		life(int, int);
		const unordered_map<cell, bool, MyHashFunction>& access_planet() const;
		void update_planet(const unordered_map<cell, bool, MyHashFunction>& newBrd);
		void new_iteration();
		void addPoint(cell&);
		void display();
		list<cell>neighbors(const cell& var);
};


const unordered_map<cell, bool, MyHashFunction>& life::access_planet() const
{
	return planet;
}

void life::update_planet(const unordered_map<cell, bool, MyHashFunction>& new_planet)
{
	planet = new_planet;
}
list<cell> life::neighbors(const cell& var)
{
	list<cell> points;
	int x,y;

	for (int i = var.x - 1;i <=var.x + 1;++i)
	{
		for (int j = var.y - 1;j <=var.y + 1;++j)
		{
			if (!(var.x == i && var.y == j))
			{

				if (i == -1) x = width - 1;
				else if (i == width ) x = 0;
				else x = i;

				if (j == -1) y = height - 1;
				else if (j == height ) y = 0;
				else y = j;

				 points.push_back(cell(x, y));
			}
		}
	}
	//for (auto i : points) cout << i.x <<i.y<<" ";
	return points;
}
void life::new_iteration()
{

	list<cell> neig;
	unsigned int alive_neighbors = 0;
	list<cell> alive;

	for (auto& item : planet)
	{

		neig = neighbors(item.first);
		for (const auto& i : neig)
		{
			
			if  ((*planet.find(i)).second == true)
			{
				++alive_neighbors;
				
			}
		}
		
		if (alive_neighbors ==3 ) alive.push_back(item.first);
		else if(item.second == true && (alive_neighbors == 2 || alive_neighbors ==3))  alive.push_back(item.first);;

		alive_neighbors = 0;
	}
	for (auto& item : planet)
	{
		item.second = false;
	}


	for (auto& item : alive)
	{
		(*planet.find(item)).second = true;
	}

}


void life::display()
{

	for (int i = 0;i < width;++i)
	{
		for (int j = 0;j < height;++j)
		{
			it = planet.find({ i,j });
			cout << (*it).second;
		}
		cout << endl;
	}
}
			
life::life(int h, int w)
{
	height = h;
	width = w;
	//random_device rd;
	//mt19937 gen(rd());
	//uniform_int_distribution<> dis(1, 10000);
	for (int i = 0;i < width;++i)
		for (int j = 0;j < height;++j)
		{
			if (i == 3 && j == 2) planet[{i, j}] = true;
			else if (i == 3 && j == 3) planet[{i, j}] = true;
			else if (i == 3 && j == 4) planet[{i, j}] = true;
			else
				planet[{i, j}] = false;
			/*unsigned int num = dis(gen);
			if (num % 2 == 0)
				planet[{i,j}]=true;

			else
				planet[{i, j}]=false;
`			*/
		}
}
int main()
{
	life a(7,7);
	a.display();
	cout << endl;
	a.new_iteration();
	a.display();
	cout << endl;
	a.new_iteration();
	a.display();
	a.neighbors({ 2,2 });
	return 0;
};

