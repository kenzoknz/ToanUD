#include <bits/stdc++.h>

using namespace std;

struct Point
{
    double x, y;

    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    void print() const
    {
        cout << "(" << x << ", " << y << ")";
    }
};

double distance(const Point &p1, const Point &p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareByX(const Point &p1, const Point &p2)
{
    return p1.x < p2.x;
}

bool compareByY(const Point &p1, const Point &p2)
{
    return p1.y < p2.y;
}

double stripClosest(vector<Point> &strip, double d)
{
    double min_dist = d;

    sort(strip.begin(), strip.end(), compareByY);

    for (size_t i = 0; i < strip.size(); i++)
    {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_dist; j++)
        {
            if (distance(strip[i], strip[j]) < min_dist)
            {
                min_dist = distance(strip[i], strip[j]);
            }
        }
    }

    return min_dist;
}

double closestPairDistance(vector<Point> &points, int start, int end, vector<pair<Point, Point>> &closestPairs)
{

    if (end - start <= 3)
    {
        double min_dist = DBL_MAX;
        for (int i = start; i < end; i++)
        {
            for (int j = i + 1; j < end; j++)
            {
                double dist = distance(points[i], points[j]);
                if (dist < min_dist)
                {
                    min_dist = dist;

                    if (!closestPairs.empty() && abs(closestPairs[0].first.x - closestPairs[0].second.x) > dist)
                    {
                        closestPairs.clear();
                    }
                    closestPairs.push_back({points[i], points[j]});
                }
                else if (!closestPairs.empty() && abs(dist - min_dist) < 1e-9)
                {

                    closestPairs.push_back({points[i], points[j]});
                }
            }
        }
        return min_dist;
    }

    int mid = (start + end) / 2;
    Point midPoint = points[mid];

    double dl = closestPairDistance(points, start, mid, closestPairs);
    double dr = closestPairDistance(points, mid, end, closestPairs);

    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = start; i < end; i++)
    {
        if (abs(points[i].x - midPoint.x) < d)
        {
            strip.push_back(points[i]);
        }
    }

    double stripDist = stripClosest(strip, d);

    if (stripDist < d)
    {
        closestPairs.clear();
        for (size_t i = 0; i < strip.size(); i++)
        {
            for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < stripDist; j++)
            {
                if (abs(distance(strip[i], strip[j]) - stripDist) < 1e-9)
                {
                    closestPairs.push_back({strip[i], strip[j]});
                }
            }
        }
        return stripDist;
    }

    return d;
}

double findClosestPair(vector<Point> &points, vector<pair<Point, Point>> &closestPairs)
{
    sort(points.begin(), points.end(), compareByX);
    return closestPairDistance(points, 0, points.size(), closestPairs);
}

int main()
{
    int n;
    cout << "Nhap so luong diem: ";
    cin >> n;

    if (n < 2)
    {
        cout << "Can it nhat 2 diem de tim khoang cach!" << endl;
        return 1;
    }

    vector<Point> points(n);

    cout << "Nhap toa do cac diem (x y):" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Diem " << i + 1 << ": ";
        cin >> points[i].x >> points[i].y;
    }

    vector<pair<Point, Point>> closestPairs;
    double minDistance = findClosestPair(points, closestPairs);

    cout << "\nKhoang cach ngan nhat: " << minDistance << endl;
    cout << "Cac cap diem gan nhat:" << endl;

    for (const auto &pair : closestPairs)
    {
        pair.first.print();
        cout << " - ";
        pair.second.print();
        cout << endl;
    }

    return 0;
}