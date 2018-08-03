#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Point {
public:
    Point(int x, int y){this->x=x; this->y=y;};
    int x;
    int y;
    int f;
    Point* parent;
    bool operator>(const Point& p);
    bool operator<(const Point& p);
    bool operator==(const Point& p);
    void setF(int f);
    friend ostream& operator<<(ostream& out, Point& point);
};

//жиди>=
bool Point::operator>(const Point& p) {
    if(f > p.f) {
        return false;
    } else {
        return true;
    }
}

bool Point::operator<(const Point& p) {
    if(f <= p.f) {
        return true;
    } else {
        return false;
    }
}

//жиди==
bool Point::operator==(const Point& p) {
    if(x == p.x && y == p.y) {
        return true;
    } else {
        return false;
    }
}

void Point::setF(int f) {
    this->f = f;
}

ostream& operator<<(ostream& out, Point& point) {
    out << "x=" << point.x << ",y=" << point.y << ",f=" << point.f << endl;
    return out;
}

const int row = 20;
const int column = 50;
vector<Point> openList;
map<int, int> closeList;
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
	Point p2(3,4);
	p2.setF(20);
	Point p1(1,2);
	p1.setF(10);
	openList.push_back(p2);
	openList.push_back(p1);
    sort(openList.begin(), openList.end());
    vector<Point>::iterator iter;
    for(iter = openList.begin(); iter != openList.end(); iter++) {
        cout << (*iter);
    }
}

void findPath(Point& startPoint, Point& endPoint, int endY, char map[row][column]) {
    int minX = startPoint.x - 1;
    int minY = startPoint.y - 1;
    int maxX = startPoint.x + 1;
    int maxY = startPoint.y + 1;
    for(int i = minX; i <= maxX; i ++) {
        for(int j = minY; j <= maxY; j ++) {
            Point point(i, j);
            int diffX = endPoint.x - i;
            int diffY = endPoint.y - j;
            if(i != startPoint.x && j != startPoint.y) {
                int f = 14 + (diffX + diffY)*14;
                point.setF(f);
            } else {
                int f = 10 + (diffX + diffY)*10;
                point.setF(f);
            }
            point.parent = &startPoint;
            vector<Point>::iterator it = find(openList.begin(), openList.end(), point);
            if(it == openList.end()) {
                openList.push_back(point);
            }
        }
    }
    openList.erase(startPoint);
    sort(openList.begin(), openList.end());
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
