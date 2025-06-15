#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

struct Rect {
    int x, y, w, h;
    Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}

    bool contains(Point p) {
        return p.x >= x - w && p.x <= x + w && p.y >= y - h && p.y <= y + h;
    }
};

class Quadtree {
    Rect boundary;
    int capacity;
    vector<Point> points;
    bool divided;
    static int totalCells;
    Quadtree *topLeft, *topRight, *botLeft, *botRight;

public:
    Quadtree(Rect _boundary, int _capacity) : boundary(_boundary), capacity(_capacity), divided(false),
                            topLeft(nullptr), topRight(nullptr), botLeft(nullptr), botRight(nullptr) {}

    bool insert(Point p) {
        if (!boundary.contains(p)) return false;

        if (points.size() < capacity && !divided) {
            points.push_back(p);
            return true;
        }

        if (!divided) subdivide();

        if (topLeft->insert(p)) return true;
        if (topRight->insert(p)) return true;
        if (botLeft->insert(p)) return true;
        if (botRight->insert(p)) return true;

        return false;
    }

    void subdivide() {
        int x = boundary.x;
        int y = boundary.y;
        int w = boundary.w / 2;
        int h = boundary.h / 2;

        topLeft  = new Quadtree(Rect(x - w, y + h, w, h), capacity);
        topRight = new Quadtree(Rect(x + w, y + h, w, h), capacity);
        botLeft  = new Quadtree(Rect(x - w, y - h, w, h), capacity);
        botRight = new Quadtree(Rect(x + w, y - h, w, h), capacity);
        divided = true;
        totalCells += 3;

        for (Point pt : points) {
            if (topLeft->insert(pt)) continue;
            if (topRight->insert(pt)) continue;
            if (botLeft->insert(pt)) continue;
            if (botRight->insert(pt)) continue;
        }

        points.clear();
    }

    int getCellCount() {
        return totalCells;
    }
};

int Quadtree::totalCells = 1;

int main() {
    Quadtree qt(Rect(0, 0, 100, 100), 1);

    int n;
    cin >> n;

    while(n--) {
        int x, y;
        cin >> x >> y;
        qt.insert(Point(x, y));
    }

    cout << qt.getCellCount() << endl;

    return 0;
}