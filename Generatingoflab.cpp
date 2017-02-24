// #define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include<queue>

using namespace std;

enum type
{
	Empty, Bombs, Player, Negr, Kek, Portal
};

vector<vector<type>> generateObjects(int height, int width, vector <pair<type, int>> types)
{
	vector<vector<type>> mapofObjects(height, vector<type>(width, Empty));

	int freeplaces = height * width;

	for (int i = 1; i < types.size(); i++) { types[i].second += types[i - 1].second; }
	types.push_back(make_pair(Empty, freeplaces));

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int s = rand() % freeplaces + 1;
			freeplaces--;
			int l = 0;
			while (types[l].second < s) l++;
			mapofObjects[i][j] = types[l].first;
			for (int d = l; d < types.size(); d++) {
				types[d].second--;
			}

		}
	return mapofObjects;
}

enum Wall
{
	None, Right, Down, Both
};

vector<vector<Wall>> generateWalls(int height, int width, int amount)
{
	vector<vector<Wall>> mapofWalls(height, vector<Wall>(width, None));

	int freeplaces = (height)* (width);
	vector<pair<Wall, int>> Walls(4);
	int percent_of_Both = 20;
	Walls[0].first = Both;
	Walls[0].second = (amount*percent_of_Both) / 100;
	int s = ((rand() % 20 + 1)*(amount)) / 100;
	Walls[1].first = Right;
	switch (rand() % 2 + 1) {
	case 1:
		Walls[1].second = amount / 2 + s - Walls[0].second;
		break;
	case 2:
		Walls[1].second = amount / 2 - s - Walls[0].second;
		break;
	}
	Walls[2].first = Down;
	Walls[2].second = amount - Walls[0].second * 2 - Walls[1].second;
	Walls[3].first = None;
	Walls[3].second = freeplaces - Walls[0].second - Walls[1].second - Walls[2].second;

	for (int i = 1; i < Walls.size(); i++) { Walls[i].second += Walls[i - 1].second; }
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int s = rand() % freeplaces + 1;
			freeplaces--;
			int l = 0;
			while (Walls[l].second < s) l++;
			mapofWalls[i][j] = Walls[l].first;
			for (int d = l; d < Walls.size(); d++) {
				Walls[d].second--;
			}

		}
	for (int i = 0; i < height - 1; i++) { if (mapofWalls[i][width - 1] != None) mapofWalls[i][width - 1] = Down; }
	for (int i = 0; i < width - 1; i++) { if (mapofWalls[height - 1][i] != None) mapofWalls[height - 1][i] = Right; }
	mapofWalls[height - 1][width - 1] = None;
	//return mapofWalls;
	queue<pair<int, int>> ToCheck;
	ToCheck.push(make_pair(0, 0));
	//ToCheck.pop();
	//ToCheck.front().first;
	vector<vector<bool>> mapofchecking(height, vector<bool>(width, 0));
	mapofchecking[0][0] = 1;
	int lefttocheck = height*width;
	bool trigger = 0;
	while (true)
	{
		if (ToCheck.size() != 0) {
			int f = ToCheck.front().first, s = ToCheck.front().second;
			if (mapofWalls[f][s] != Both) {
				if ((mapofWalls[f][s] != Down) && (f + 1 < height))
					if ((f < height - 1) && (!mapofchecking[f + 1][s])) {
						ToCheck.push(make_pair(f + 1, s));
						mapofchecking[f + 1][s] = 1;
					}

				if ((mapofWalls[f][s] != Right) && (s + 1 < width))
					if ((s < width - 1) && (!mapofchecking[f][s + 1])) {
						ToCheck.push(make_pair(f, s + 1));
						mapofchecking[f][s + 1] = 1;
					}

			}
			if ((f > 0) && (mapofWalls[f - 1][s] != Down) &&
				(mapofWalls[f - 1][s] != Both) &&
				(!mapofchecking[f - 1][s]))
			{
				ToCheck.push(make_pair(f - 1, s));
				mapofchecking[f - 1][s] = 1;
			}
			if ((s > 0) && (mapofWalls[f][s - 1] != Right) &&
				(mapofWalls[f][s - 1] != Both) &&
				(!mapofchecking[f][s - 1]))
			{
				ToCheck.push(make_pair(f, s - 1));
				mapofchecking[f][s - 1] = 1;
			}

			ToCheck.pop();
			lefttocheck = lefttocheck-- ;
		}
		

		if (ToCheck.size() == 0){
			if (lefttocheck != 0)
			{
				for (int i = 0; i < height; i++)
					for (int j = 0; j < width; j++)
						if (trigger == 0)
							if (mapofchecking[i][j] == 1)
							{
								if ((i < height - 1) && (!mapofchecking[i + 1][j])){
									trigger = 1;
									mapofchecking[i + 1][j] = 1;
									ToCheck.push(make_pair(i + 1, j));
									if (mapofWalls[i][j] == Both){
										mapofWalls[i][j] = Right;
									} else
									mapofWalls[i][j] = None;
								} else
								if ((j < width - 1) && (!mapofchecking[i][j + 1])){
									trigger = 1;
									mapofchecking[i][j + 1] = 1;
									ToCheck.push(make_pair(i, j + 1));
									if (mapofWalls[i][j] == Both){
										mapofWalls[i][j] = Down;
									}
									else
									mapofWalls[i][j] = None;
								} else
								if ((i > 0) && (!mapofchecking[i - 1][j])){
									trigger = 1;
									mapofchecking[i - 1][j] = 1;
									ToCheck.push(make_pair(i - 1, j));
									if (mapofWalls[i - 1][j] == Both){
										mapofWalls[i - 1][j] = Right;
									}
									else
									mapofWalls[i - 1][j] = None;
								} else
								if ((j > 0) && (!mapofchecking[i][j - 1])){
									trigger = 1;
									mapofchecking[i][j - 1] = 1;
									ToCheck.push(make_pair(i, j - 1));
									if (mapofWalls[i][j - 1] == Both){
										mapofWalls[i][j - 1] = Down;
									}
									else
									mapofWalls[i][j - 1] = None;
								}
							}
				trigger = 0;
			}
			else{
				return mapofWalls;
			}
		}
	}
}

int main()
{
	srand(time(0));
	int  height, width, r, amount;

	cout << "height: "; cin >> height; cout << '\n'; cout << "width: "; cin >> width; cout << '\n';
	cout << "num of Walls:"; cin >> amount; cout << '\n';

	vector<vector<Wall>> mapofWalls = generateWalls(height, width, amount);

	vector<vector<char>> realmap(height * 2 + 2, vector<char>(width * 2 + 2, ' '));
	for (int i = 0; i < height; i++) { 
		for (int j = 0; j < width; j++) {
			realmap[i * 2][j * 2] = ' ';
			if (mapofWalls[i][j] == Right) { realmap[i * 2][j * 2 + 1] = '|'; }
			else
				if (mapofWalls[i][j] == Down) realmap[i * 2 + 1][j * 2] = '-'; else
					if (mapofWalls[i][j] == Both) {
						realmap[i * 2 + 1][j * 2] = '-';
						realmap[i * 2][j * 2 + 1] = '|';
					}

		}

	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((realmap[i * 2 + 1][j * 2] == '-') || (realmap[i * 2 + 1][j * 2] == '|') || (realmap[i * 2][j * 2 + 1] == '-') || (realmap[i * 2][j * 2 + 1] == '|'))
				realmap[i * 2 + 1][j * 2 + 1] = '+';
			if ((i> 0) && (j>0))
				if ((realmap[i * 2 - 1][j * 2] == '-') || (realmap[i * 2 - 1][j * 2] == '|') || (realmap[i * 2][j * 2 - 1] == '-') || (realmap[i * 2][j * 2 - 1] == '|'))
					realmap[i * 2 -
					1][j * 2 - 1] = '+';
		}

	}



	cout << "num of types:"; cin >> r; cout << '\n';

	vector<pair<type, int>> types(r);
	for (int i = 0; i < r; i++) {
		string a;
		cout << "type: ";
		cin >> a;

		if (a == "Bombs")  types[i].first = Bombs;
		else if (a == "Player") types[i].first = Player;
		else if (a == "Negr") types[i].first = Negr;
		else if (a == "Kek") types[i].first = Kek;
		else if (a == "Portal") types[i].first = Portal;
		else { cout << "Unknown type!\n"; i--; continue; }

		cout << " amount: ";
		cin >> types[i].second;
		cout << "\n";
	}




	vector<vector<type>> map = generateObjects(height, width, types);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {


			if (map[i][j] == Bombs) realmap[i*2][j*2] = 'B';
			else if (map[i][j] == Player) realmap[i * 2][j * 2] = 'P';
			else if (map[i][j] == Empty) realmap[i * 2][j * 2] = ' ';
			else if (map[i][j] == Negr) realmap[i * 2][j * 2] = 'N';
			else if (map[i][j] == Kek) realmap[i * 2][j * 2] = 'K';
			else if (map[i][j] == Portal) realmap[i * 2][j * 2] = '@';

		}
		cout << '\n';
	}
	cout << "\n\n";



	for (int i = 0; i < height * 2 + 2; i++) {
		for (int j = 0; j < width * 2 + 2; j++) {
			cout << realmap[i][j];

		}
		cout << '\n';
	}
	system("pause");
	return 0;
}