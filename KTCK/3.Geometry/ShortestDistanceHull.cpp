#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
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
        output << "(" << p.x << ", " << p.y << ")";
        return output;
    }
};

// Tính tích có hướng (cross product)
double cross_product(const Point &O, const Point &A, const Point &B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Tính khoảng cách Euclid giữa 2 điểm
double euclidean_distance(const Point &A, const Point &B)
{
    return hypot(A.x - B.x, A.y - B.y);
}

// Thuật toán Andrew's Monotone Chain để tìm bao lồi - O(n log n)
vector<Point> compute_convex_hull(vector<Point> points)
{
    int n = points.size(), k = 0;
    if (n <= 1)
        return points;

    // Sắp xếp các điểm theo tọa độ x, sau đó theo y - O(n log n)
    sort(points.begin(), points.end());
    vector<Point> hull(2 * n);

    // Xây dựng bao lồi dưới (Lower hull)
    for (int i = 0; i < n; ++i)
    {
        while (k >= 2 && cross_product(hull[k - 2], hull[k - 1], points[i]) <= 0)
            k--;
        hull[k++] = points[i];
    }

    // Xây dựng bao lồi trên (Upper hull)
    for (int i = n - 1, t = k + 1; i > 0; --i)
    {
        while (k >= t && cross_product(hull[k - 2], hull[k - 1], points[i - 1]) <= 0)
            k--;
        hull[k++] = points[i - 1];
    }

    hull.resize(k - 1);
    return hull;
}

// Tìm khoảng cách ngắn nhất giữa các đỉnh bao lồi - O(n)
// Chỉ kiểm tra các cạnh liền kề vì đây là đa giác lồi
pair<Point, Point> shortest_distance_convex_hull(const vector<Point> &hull)
{
    int n = hull.size();
    
    if (n < 2)
    {
        cout << "Bao loi khong co du dinh!\n";
        return {{0, 0}, {0, 0}};
    }
    
    double min_dist = INFINITY;
    pair<Point, Point> closest_pair;

    // Duyệt qua tất cả các cạnh của bao lồi
    // Với đa giác lồi, khoảng cách nhỏ nhất GIỮA CÁC ĐỈNH BAO LỒI luôn là giữa 2 đỉnh liền kề
    for (int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n; // Đỉnh tiếp theo (quay vòng)
        double dist = euclidean_distance(hull[i], hull[j]);
        
        if (dist < min_dist)
        {
            min_dist = dist;
            closest_pair = {hull[i], hull[j]};
        }
    }

    return closest_pair;
}

// Tìm khoảng cách ngắn nhất giữa TẤT CẢ các điểm ban đầu - O(n²)
// Đây là cách chính xác để tìm cặp điểm gần nhất trong tập điểm
pair<Point, Point> shortest_distance_all_points(const vector<Point> &points)
{
    int n = points.size();
    
    if (n < 2)
    {
        cout << "Khong co du diem!\n";
        return {{0, 0}, {0, 0}};
    }
    
    double min_dist = INFINITY;
    pair<Point, Point> closest_pair;

    // Kiểm tra tất cả các cặp điểm
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            double dist = euclidean_distance(points[i], points[j]);
            
            if (dist < min_dist)
            {
                min_dist = dist;
                closest_pair = {points[i], points[j]};
            }
        }
    }

    return closest_pair;
}

// Tìm khoảng cách ngắn nhất giữa TẤT CẢ các cặp đỉnh bao lồi (không chỉ liền kề) - O(n²)
// Hàm này để so sánh và kiểm tra
pair<Point, Point> shortest_distance_all_pairs(const vector<Point> &hull)
{
    int n = hull.size();
    
    if (n < 2)
    {
        cout << "Bao loi khong co du dinh!\n";
        return {{0, 0}, {0, 0}};
    }
    
    double min_dist = INFINITY;
    pair<Point, Point> closest_pair;

    // Kiểm tra tất cả các cặp đỉnh
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            double dist = euclidean_distance(hull[i], hull[j]);
            
            if (dist < min_dist)
            {
                min_dist = dist;
                closest_pair = {hull[i], hull[j]};
            }
        }
    }

    return closest_pair;
}

// Tính diện tích đa giác
double polygon_area(const vector<Point> &poly)
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

int main()
{
    // Nhập dữ liệu
    int n;
    cout << "Nhap so luong diem: ";
    cin >> n;

    vector<Point> points(n);
    cout << "Nhap toa do cac diem (x y):\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }

    cout << "\n========================================\n";
    cout << "CAC DIEM BAN DAU:\n";
    cout << "========================================\n";
    for (int i = 0; i < n; ++i)
        cout << "Diem " << i + 1 << ": " << points[i] << "\n";

    // Tìm bao lồi - O(n log n)
    vector<Point> hull = compute_convex_hull(points);

    cout << "\n========================================\n";
    cout << "BAO LOI (CONVEX HULL):\n";
    cout << "========================================\n";
    cout << "So dinh bao loi: " << hull.size() << "\n";
    for (int i = 0; i < hull.size(); ++i)
        cout << "Dinh " << i + 1 << ": " << hull[i] << "\n";

    cout << "\nDien tich bao loi: " << polygon_area(hull) << "\n";

    // Tìm khoảng cách ngắn nhất giữa TẤT CẢ các điểm ban đầu - O(n²)
    auto result_all_points = shortest_distance_all_points(points);
    double min_dist_all_points = euclidean_distance(result_all_points.first, result_all_points.second);

    cout << "\n========================================\n";
    cout << "KHOANG CACH NGAN NHAT (TAT CA CAC DIEM):\n";
    cout << "========================================\n";
    cout << "Cap diem gan nhat: " << result_all_points.first << " - " << result_all_points.second << "\n";
    cout << "Khoang cach: " << fixed << setprecision(6) << min_dist_all_points << "\n";

    // Tìm khoảng cách ngắn nhất chỉ giữa các đỉnh bao lồi - O(n)
    auto result_hull = shortest_distance_convex_hull(hull);
    double min_dist_hull = euclidean_distance(result_hull.first, result_hull.second);

    cout << "\n========================================\n";
    cout << "KHOANG CACH NGAN NHAT (CHI DINH BAO LOI):\n";
    cout << "========================================\n";
    cout << "Cap dinh bao loi gan nhat: " << result_hull.first << " - " << result_hull.second << "\n";
    cout << "Khoang cach: " << fixed << setprecision(6) << min_dist_hull << "\n";

    // So sánh tất cả các cặp đỉnh bao lồi (để kiểm tra)
    cout << "\n========================================\n";
    cout << "KIEM TRA TAT CA CAC CAP DINH BAO LOI:\n";
    cout << "========================================\n";
    auto result_all = shortest_distance_all_pairs(hull);
    double min_dist_all = euclidean_distance(result_all.first, result_all.second);
    
    cout << "Cap dinh gan nhat (kiem tra tat ca cap): " << result_all.first << " - " << result_all.second << "\n";
    cout << "Khoang cach: " << fixed << setprecision(6) << min_dist_all << "\n";

    cout << "\n========================================\n";
    cout << "DO PHUC TAP:\n";
    cout << "========================================\n";
    cout << "- Tim bao loi: O(n log n)\n";
    cout << "- Tim khoang cach ngan nhat (tat ca diem): O(n^2)\n";
    cout << "- Tim khoang cach ngan nhat (chi dinh bao loi): O(n)\n";
    cout << "========================================\n";
    cout << "\nLUU Y: Khoang cach ngan nhat co the nam giua cac diem\n";
    cout << "       BEN TRONG bao loi, khong chi giua cac dinh bao loi!\n";
    cout << "========================================\n";

    return 0;
}
