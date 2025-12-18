#include <bits/stdc++.h>
#define INF 1e9
using namespace std;

struct Point
{
    double x, y;

    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }

    bool operator==(const Point &p) const
    {
        return x == p.x && y == p.y;
    }

    friend ostream &operator<<(ostream &output, const Point &p)
    {
        output << "(" << p.x << "," << p.y << ")";
        return output;
    }
};

double cross_product(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

double euclidean_distance(const Point &A, const Point &B)
{
    return hypot(A.x - B.x, A.y - B.y);
}

vector<Point> compute_convex_hull(vector<Point> points)
{
    int n = points.size(), k = 0;
    if (n <= 1)
        return points;

    sort(points.begin(), points.end());
    vector<Point> hull(2 * n);

    // Lower hull
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross_product(hull[k - 2], hull[k - 1], points[i]) <= 0)
            k--;
        hull[k++] = points[i];
    }

    // Upper hull
    for (int i = n - 1, t = k + 1; i > 0; --i)
    {
        while (k >= t && cross_product(hull[k - 2], hull[k - 1], points[i - 1]) <= 0)
            k--;
        hull[k++] = points[i - 1];
    }

    hull.resize(k - 1);
    return hull;
}

double polygon_area(const vector<Point> &poly) //dien tich da giac
{
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[i].y * poly[j].x;
    }
    return abs(area) / 2.0;
}

pair<Point, Point> closest_pair_bruteforce(const vector<Point> &points)
{
    double min_dist = INF;
    pair<Point, Point> best_pair;
    int n = points.size();

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            double d = euclidean_distance(points[i], points[j]);
            if (d < min_dist)
            {
                min_dist = d;
                best_pair = {points[i], points[j]};
            }
        }
    return best_pair;
}

pair<Point, Point> shortest_edge_on_hull(const vector<Point> &hull)
{
    double min_dist = INF;
    pair<Point, Point> best_edge;
    int n = hull.size();

    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        double d = euclidean_distance(hull[i], hull[j]);
        if (d < min_dist)
        {
            min_dist = d;
            best_edge = {hull[i], hull[j]};
        }
    }
    return best_edge;
}

// bool contains_point(const vector<Point> &hull, const Point &p) {
//     int n = hull.size();
//     if (n < 3) return false;

//     for (auto &vertex : hull)
//         if (vertex == p)
//             return true;

//     for (int i = 0; i < n; ++i) {
//         int next = (i + 1) % n;
//         if (cross_product(hull[i], hull[next], p) < 0)
//             return false;
//     }
//     return true;
// }

vector<Point> points_inside_hull(const vector<Point> &all_points, const vector<Point> &hull)
{
    vector<Point> inside;
    for (auto &p : all_points)
        if (find(hull.begin(), hull.end(), p) == hull.end())
            inside.push_back(p);
    return inside;
}

double distance_point_to_segment(const Point &P, const Point &A, const Point &B)
{
    double ABx = B.x - A.x, ABy = B.y - A.y;
    double APx = P.x - A.x, APy = P.y - A.y;
    double ab2 = ABx * ABx + ABy * ABy;
    double t = max(0.0, min(1.0, (APx * ABx + APy * ABy) / ab2));
    double nearestX = A.x + t * ABx;
    double nearestY = A.y + t * ABy;
    return hypot(P.x - nearestX, P.y - nearestY);
}

double distance_point_to_hull(const Point &P, const vector<Point> &hull)
{
    double minDist = INF;
    int n = hull.size();
    for (int i = 0; i < n; ++i)
        minDist = min(minDist, distance_point_to_segment(P, hull[i], hull[(i + 1) % n]));
    return minDist;
}

int main()
{
    vector<Point> points = {
  //  {6, 2}, {8, 3}, {4, 10}, {3, 5}, {16, 5}, {9, 7}, {11, 6}, {10, 12}, {8, 9}, {7, 6}   
  {3, 4}, {5,3}, {6,5}, {7,6}, {8,7}, {4,9}, {3,8}, {4,8}, {7,10}, {7,4} 
    };

    cout << "Original Points:\n";
    for (auto p : points)
        cout << p << "\t";
    cout << "\n\n";

    vector<Point> hull = compute_convex_hull(points);

    cout << "Convex Hull:\n";
    for (auto p : hull)
        cout << p << "\t";
    cout << "\n\n";

    cout << "Polygon Area: " << polygon_area(hull) << endl;

    auto min_edge = shortest_edge_on_hull(hull);
    cout << "Shortest Edge: " << min_edge.first << " - " << min_edge.second
         << " | Length = " << euclidean_distance(min_edge.first, min_edge.second) << "\n\n";
   
    cout << "Points inside Hull:\n";
    auto inside = points_inside_hull(points, hull);
    for (auto p : inside)
        cout << p << "\t";
    cout << "\n\n";
    auto closest = closest_pair_bruteforce(points);
    cout << "Closest Pair: " << closest.first << " - " << closest.second
         << " | Distance = " << euclidean_distance(closest.first, closest.second) << "\n\n";

    // Point test = {7, 8};
    // cout << "Point " << test << (contains_point(hull, test) ? " is inside hull.\n" : " is outside hull.\n");

    return 0;
}
