#include <bits/stdc++.h>
#define Max 1000000000
using namespace std;

struct Point
{
    double x, y;
    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
    friend bool operator==(const Point &p1, const Point &p2)
    {
        return (p1.x == p2.x && p1.y == p2.y);
    }
    friend ostream &operator<<(ostream &output, const Point &p)
    {
        output << "(" << p.x << "," << p.y << ")";
        return output;
    }
};
double cross(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
double distance(const Point &A, const Point &B)
{
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? -1 : 1;
}
pair<Point, Point> find_min_dist_recursive(vector<Point> &Px, vector<Point> &Py)
{
    int n = Px.size();
    if (n <= 3)
    {
        double min_dist = Max;
        pair<Point, Point> res;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                double d = distance(Px[i], Px[j]);
                if (d < min_dist)
                {
                    min_dist = d;
                    res = {Px[i], Px[j]};
                }
            }
        }
        return res;
    }

    int mid = n / 2;
    Point mid_point = Px[mid];
    vector<Point> Pxl(Px.begin(), Px.begin() + mid);
    vector<Point> Pxr(Px.begin() + mid, Px.end());
    vector<Point> Pyl, Pyr;
    for (auto &p : Py)
    {
        if (p.x <= mid_point.x)
            Pyl.push_back(p);
        else
            Pyr.push_back(p);
    }
    auto d_left = find_min_dist_recursive(Pxl, Pyl);
    auto d_right = find_min_dist_recursive(Pxr, Pyr);
    double min_dist = min(distance(d_left.first, d_left.second), distance(d_right.first, d_right.second));
    pair<Point, Point> res = (distance(d_left.first, d_left.second) < distance(d_right.first, d_right.second)) ? d_left : d_right;
    vector<Point> strip;
    for (auto &p : Py)
    {
        if (abs(p.x - mid_point.x) < min_dist)
            strip.push_back(p);
    }
    int m = strip.size();
    for (int i = 0; i < m; ++i)
    {
        for (int j = i + 1; j < m && (strip[j].y - strip[i].y) < min_dist; ++j)
        {
            double d = distance(strip[i], strip[j]);
            if (d < min_dist)
            {
                min_dist = d;
                res = {strip[i], strip[j]};
            }
        }
    }

    return res;
}
pair<Point, Point> find_min_dist(vector<Point> &P)
{
    vector<Point> Px = P, Py = P;
    sort(Px.begin(), Px.end(), [](const Point &a, const Point &b)
         { return a.x < b.x; });
    sort(Py.begin(), Py.end(), [](const Point &a, const Point &b)
         { return a.y < b.y; });

    return find_min_dist_recursive(Px, Py);
}

pair<Point, Point> find_min_edge(const vector<Point> &P)
{
    double min_dist = Max;
    pair<Point, Point> res;
    int n = P.size();
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        double d = distance(P[i], P[j]);
        if (d < min_dist)
        {
            min_dist = d;
            res = {P[i], P[j]};
        }
    }
    return res;
}

vector<Point> generate_unique_points(int n, int max_range)
{
    set<pair<double, double>> points_set;
    vector<Point> points;

    while (points.size() < n)
    {
        double x = rand() % max_range;
        double y = rand() % max_range;

        if (points_set.find(make_pair(x, y)) == points_set.end())
        {
            points_set.insert(make_pair(x, y));
            Point P;
            P.x = x;
            P.y = y;
            points.push_back(P);
        }
    }
    return points;
}
vector<Point> convex_hull(vector<Point> P)
{
    int n = P.size(), k = 0;
    if (n <= 3)
        return P;
    vector<Point> res(2 * n);

    sort(P.begin(), P.end());

    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross(res[k - 2], res[k - 1], P[i]) <= 0)
            k--;
        res[k++] = P[i];
    }

    for (int i = n - 1, t = k + 1; i > 0; --i)
    {
        while (k >= t && cross(res[k - 2], res[k - 1], P[i - 1]) <= 0)
            k--;
        res[k++] = P[i - 1];
    }
    res.resize(k - 1);
    return res;
}
double poly_area(const vector<Point> &P)
{
    int n = P.size();
    double area = 0;
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        area += P[i].x * P[j].y - P[i].y * P[j].x;
    }
    return abs(area) / 2.0;
}

bool pointInConvexHull(const vector<Point> &hull, const Point &point)
{
    int n = hull.size();
    if (n < 3)
        return false;

    for (const auto &p : hull)
    {
        if (p.x == point.x && p.y == point.y)
            return false;
    }

    for (int i = 0; i < n; ++i)
    {
        int next = (i + 1) % n;
        if (cross(hull[i], hull[next], point) < 0)
        {
            return false;
        }
    }
    return true;
}
bool is_In_Vector(const vector<Point> &v, const Point &p)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        if (v[i] == p)
        {
            return true;
        }
    }
    return false;
}

vector<Point> elements_In_A_And_Not_In_B(const vector<Point> &A, const vector<Point> &B)
{
    vector<Point> result;
    for (const auto &point : A)
    {
        if (!is_In_Vector(B, point))
        {
            result.push_back(point);
        }
    }
    return result;
}

double distanceToSegment(const Point &P, const Point &A, const Point &B)
{

    double ABx = B.x - A.x;
    double ABy = B.y - A.y;

    double APx = P.x - A.x;
    double APy = P.y - A.y;

    double AB_squared = ABx * ABx + ABy * ABy;

    double AP_AB = APx * ABx + APy * ABy;

    double t = AP_AB / AB_squared;

    if (t < 0.0)
        t = 0.0;
    if (t > 1.0)
        t = 1.0;

    double nearestX = A.x + t * ABx;
    double nearestY = A.y + t * ABy;

    return sqrt((P.x - nearestX) * (P.x - nearestX) + (P.y - nearestY) * (P.y - nearestY));
}

double distanceToConvexHull(const Point &P, const vector<Point> &hull)
{
    int n = hull.size();
    double minDist = numeric_limits<double>::max();

    for (int i = 0; i < n; i++)
    {
        int next = (i + 1) % n;
        double dist = distanceToSegment(P, hull[i], hull[next]);
        minDist = min(minDist, dist);
    }

    return minDist;
}

Point findCentralPoint(const vector<Point> &insidePoints, const vector<Point> &hull)
{
    if (insidePoints.empty())
        return {0, 0};

    Point centralPoint = insidePoints[0];
    double maxMinDistance = distanceToConvexHull(insidePoints[0], hull);

    for (const auto &point : insidePoints)
    {
        double dist = distanceToConvexHull(point, hull);
        if (dist > maxMinDistance)
        {
            maxMinDistance = dist;
            centralPoint = point;
        }
    }

    return centralPoint;
}
int main()
{
    srand(time(0));

    int n = 15;
    int max_range = 20;
    vector<Point> P = generate_unique_points(n, max_range);
    // // Hoặc sử dụng tập điểm có sẵn
    // vector<Point> P = {{2,1}, {1,5}, {3,3}, {4,3}, {4,4}, {6,3}};
 

    cout << "Danh sach cac diem dau vao: \n";
    for (auto &p : P)
        cout << "(" << p.x << ", " << p.y << ")  ";
    cout << endl;

    vector<Point> hull = convex_hull(P);
    cout << "\nBao loi la: \n";
    for (auto &p : hull)
        cout << "(" << p.x << ", " << p.y << ")  ";

    cout << "\n\nDien tich cua bao loi la: " << poly_area(hull) << endl;

    vector<Point> insidePoints;
    for (const auto &point : P)
    {
        if (pointInConvexHull(hull, point))
        {
            insidePoints.push_back(point);
        }
    }

    cout << "\nCac diem nam BEN TRONG bao loi: \n";
    if (insidePoints.empty())
    {
        cout << "Khong co diem nao nam ben trong bao loi." << endl;
    }
    else
    {
        for (auto &p : insidePoints)
            cout << p << "\t";
        cout << endl;

        cout << "\nKhoang cach tu cac diem ben trong den bao loi: \n";
        for (const auto &point : insidePoints)
        {
            double dist = distanceToConvexHull(point, hull);
            cout << "Diem " << point << ": " << fixed << setprecision(4) << dist << endl;
        }

        Point centralPoint = findCentralPoint(insidePoints, hull);
        cout << "\nDiem nam o trung gian bao loi nhat la: " << centralPoint << endl;
        cout << "Khoang cach tu diem nay den canh gan nhat cua bao loi: "
             << fixed << setprecision(4) << distanceToConvexHull(centralPoint, hull) << endl;
    }

    pair<Point, Point> res_min_edge = find_min_edge(hull);
    cout << "\nCanh ngan nhat cua bao loi la: ";
    cout << "(" << res_min_edge.first.x << ", " << res_min_edge.first.y << ") va "
         << "(" << res_min_edge.second.x << ", " << res_min_edge.second.y << ")\n";
    cout << "Voi do dai: " << fixed << setprecision(4) << distance(res_min_edge.first, res_min_edge.second) << endl;

    return 0;
}
