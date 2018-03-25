#include <iostream>
using namespace std;
const int row = 20;
const int column = 50;
void printMap(char map[row][column]);
void designMap(char map[row][column]);
int main() {
	char map[row][column] = {"."};
	designMap(map);
	printMap(map);
	int startX = 10;
	int startY = 10;
	int endX = 10;
	int endY = 40;
	
}

void designMap(char map[row][column]) {
	for(int i = 0; i < row; i ++) {
		for(int j = 0; j < column; j++) {
			map[i][j]='.';
		}
	}
	map[10][10] = 'S';	//start point
	map[10][40] = 'E';	//end point
	for(int i = 5; i < 15; i ++) {
		map[i][25] = 'W';
	}
	map[5][20]='W';
	map[5][21]='W';
	map[5][22]='W';
	map[5][23]='W';
	map[5][24]='W';
	map[14][20]='W';
	map[14][21]='W';
	map[14][22]='W';
	map[14][23]='W';
	map[14][24]='W';
}

void printMap(char map[row][column]) {
	for(int i = 0; i < row; i ++) {
		for(int j = 0; j < column; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}