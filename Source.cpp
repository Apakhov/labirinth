#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

enum type
{
		Empty,  Bombs, Player, Negr, Kek, Portal
};

vector<vector<type>> generateObjects(int height, int width, vector <pair<type, int>> types)
{
	vector<vector<type>> mapofObjects(height, vector<type>(width, Empty));

	int freeplaces = height * width;

	for (int i = 1; i < types.size(); i++) { types[i].second += types[i-1].second; }
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

int main()
{
	srand(time(0));
	freopen("input.txt", "r", stdin);

	int j, height, width, r;

	cout << "height: "; cin >> height; cout << '\n'; cout << "width: "; cin >> width; cout << '\n';
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

	for (int k = 0; k < 20; k++)
	{
		vector<vector<type>> map = generateObjects(height, width, types);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {


				if (map[i][j] == Bombs) cout << 'B';
				else if (map[i][j] == Player) cout << 'P';
				else if (map[i][j] == Empty) cout << '.';
				else if (map[i][j] == Negr) cout << 'N';
				else if (map[i][j] == Kek) cout << 'K';
				else if (map[i][j] == Portal) cout << '@';

			}
			cout << '\n';
		}
		cout << "\n\n";
	}

	return 0;
}