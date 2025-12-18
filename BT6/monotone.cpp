#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

bool ccw(const Point &A, const Point &B, const Point &C)
{
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (C.x - A.x) * (B.y - A.y) >0;
}

vector<Point> convexHull(vector<Point> p, int n)
{

    sort(p.begin(), p.end(), [](const Point &A, const Point &B)
         {
        if (A.x != B.x) return A.x < B.x;
        return A.y < B.y; });

    vector<Point> hull;
    hull.push_back(p[0]);

    for (int i = 1; i < n; ++i)
    {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i]))
        {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    for (int i = n - 2; i >= 0; --i)
    {
        while (hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), p[i]))
        {
            hull.pop_back();
        }
        hull.push_back(p[i]);
    }

    if (n > 1)
        hull.pop_back();

    return hull;
}
double area(const vector<Point> &poly)
{
    long long A = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        A += 1LL * poly[i].x * poly[j].y - 1LL * poly[j].x * poly[i].y;
    }
    return fabs(A) / 2.0;
}
vector<Point> lietKeNamTrongBaoLoi(const vector<Point> &allPoints, const vector<Point> &hull)
{
    vector<Point> inside;
    int m = hull.size();

    if (m < 3)
    {
        return inside;
    }

    for (const auto &p : allPoints)
    {
        bool isStrictlyInside = true;
        for (int i = 0; i < m; ++i)
        {
            int j = (i + 1) % m;
            Point A = hull[i];
            Point B = hull[j];

            long long cross_product = 1LL * (B.x - A.x) * (p.y - A.y) - 1LL * (p.x - A.x) * (B.y - A.y);

            if (cross_product >= 0)
            {
                isStrictlyInside = false;
                break;
            }
        }
        if (isStrictlyInside)
        {
            inside.push_back(p);
        }
    }
    return inside;
}

double distance(const vector<Point> &inside)
{
    double minDist = 1e18;
    int m = inside.size();
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            double dist = sqrt(1LL * (inside[i].x - inside[j].x) * (inside[i].x - inside[j].x) +
                               1LL * (inside[i].y - inside[j].y) * (inside[i].y - inside[j].y));
            minDist = min(minDist, dist);
        }
    }
    return minDist == 1e18 ? 0.0 : minDist;
}

Point trungGian(const vector<Point> &inside)
{
    Point midPoint = inside[0];
    int m = inside.size();
    double sumX = 0, sumY = 0;

    for (auto &p : inside)
    {
        sumX += p.x;
        sumY += p.y;
    }

    double cx = sumX / m;
    double cy = sumY / m;

    Point best = inside[0];
    double bestDist = (best.x - cx) * (best.x - cx) + (best.y - cy) * (best.y - cy);
    for (auto &p : inside)
    {
        double dist = (p.x - cx) * (p.x - cx) + (p.y - cy) * (p.y - cy);
        if (dist < bestDist)
        {
            bestDist = dist;
            best = p;
        }
    }
    return best;
}
int main()
{

    vector<Point> p = {{2, 1}, {2, 5}, {3, 3}, {4, 3}, {4, 4}, {6, 3}};
    int n = p.size();
    vector<Point> hull = convexHull(p, n);
    cout << "Cac diem bao loi la:" << endl;
    for (Point p : hull)
    {
        cout << "(" << p.x << ", " << p.y << ")\t";
    }
    cout << endl;
    cout << "Dien tich bao loi: " << fixed << setprecision(2) << area(hull) << '\n';
    vector<Point> inside = lietKeNamTrongBaoLoi(p, hull);
    cout << "Cac diem nam trong bao loi: \n";
    for (Point pt : inside)
    {
        cout << "(" << pt.x << ", " << pt.y << ")\t";
    }
    cout << "Khoang cach nho nhat giua hai diem nam trong bao loi: " << fixed << setprecision(2) << distance(inside) << '\n';
    // Point mid = trungGian(inside);
    // cout << "Diem trung gian nhat la: " << mid.x << ' ' << mid.y << '\n';
    return 0;
}