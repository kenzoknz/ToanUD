#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <string>
#include <functional>

using namespace std;

const int DIMENSIONS = 10;
const int NUM_POINTS = 20;

struct Point
{
    int id;
    double coords[DIMENSIONS];
    double norm;
    double unit[DIMENSIONS];

    Point() : id(-1), norm(0.0)
    {
        for (int i = 0; i < DIMENSIONS; i++)
        {
            coords[i] = 0.0;
            unit[i] = 0.0;
        }
    }
};

struct PairResult
{
    int i, j;
    double similarity;

    PairResult() : i(-1), j(-1), similarity(-2.0) {}
    PairResult(int _i, int _j, double _sim) : i(_i), j(_j), similarity(_sim) {}
};

double calculateNorm(const double coords[])
{
    double sum = 0.0;
    for (int i = 0; i < DIMENSIONS; i++)
    {
        sum += coords[i] * coords[i];
    }
    return sqrt(sum);
}

double dotProduct(const double a[], const double b[])
{
    double sum = 0.0;
    for (int i = 0; i < DIMENSIONS; i++)
    {
        sum += a[i] * b[i];
    }
    return sum;
}

double cosineSimilarity(const Point &p1, const Point &p2)
{

    double dot = dotProduct(p1.coords, p2.coords);

    if (p1.norm < 1e-10 || p2.norm < 1e-10)
    {
        return 0.0;
    }

    return dot / (p1.norm * p2.norm);
}


bool compareByDim0(const Point &a, const Point &b)
{
    return a.coords[0] < b.coords[0];
}

PairResult divideAndConquerHelper(vector<Point> &points, int left, int right)
{
    int n = right - left + 1;

    if (n <= 3)
    {
        PairResult best(-1, -1, -2.0);
        for (int i = left; i <= right - 1; i++)
        {
            for (int j = i + 1; j <= right; j++)
            {
                double sim = cosineSimilarity(points[i], points[j]);
                if (sim > best.similarity)
                {
                    best.i = i;
                    best.j = j;
                    best.similarity = sim;
                }
            }
        }
        return best;
    }

    int mid = (left + right) / 2;

    PairResult leftBest = divideAndConquerHelper(points, left, mid);
    PairResult rightBest = divideAndConquerHelper(points, mid + 1, right);

    PairResult best = (leftBest.similarity > rightBest.similarity) ? leftBest : rightBest;

    double midValue = points[mid].coords[0];
    double threshold = 0.5;

    vector<int> strip;
    for (int i = left; i <= right; i++)
    {
        if (fabs(points[i].coords[0] - midValue) < threshold)
        {
            strip.push_back(i);
        }
    }

    for (size_t i = 0; i < strip.size() - 1; i++)
    {
        for (size_t j = i + 1; j < strip.size(); j++)
        {
            int idx1 = strip[i];
            int idx2 = strip[j];

            if ((idx1 <= mid && idx2 > mid) || (idx1 > mid && idx2 <= mid))
            {
                double sim = cosineSimilarity(points[idx1], points[idx2]);
                if (sim > best.similarity)
                {
                    best.i = idx1;
                    best.j = idx2;
                    best.similarity = sim;
                }
            }
        }
    }

    return best;
}

PairResult findMaxSimilarityDivideConquer(vector<Point> &points)
{

    int n = points.size();
    vector<int> idx(n);
    for (int i = 0; i < n; ++i)
        idx[i] = i;

    struct KDNode
    {
        int index;
        int dim;
        KDNode *left;
        KDNode *right;
        KDNode(int idx = -1, int d = 0) : index(idx), dim(d), left(nullptr), right(nullptr) {}
    };

    auto cmpDim = [&](int a, int b, int dim)
    {
        return points[a].unit[dim] < points[b].unit[dim];
    };

    function<KDNode *(int, int, int)> build = [&](int l, int r, int depth) -> KDNode *
    {
        if (l > r)
            return nullptr;
        int dim = depth % DIMENSIONS;
        int m = (l + r) / 2;
        nth_element(idx.begin() + l, idx.begin() + m, idx.begin() + r + 1,
                    [&](int a, int b)
                    { return points[a].unit[dim] < points[b].unit[dim]; });
        KDNode *node = new KDNode(idx[m], dim);
        node->left = build(l, m - 1, depth + 1);
        node->right = build(m + 1, r, depth + 1);
        return node;
    };

    auto sqDistUnit = [&](int a, int b)
    {
        double s = 0.0;
        for (int k = 0; k < DIMENSIONS; ++k)
        {
            double d = points[a].unit[k] - points[b].unit[k];
            s += d * d;
        }
        return s;
    };

    function<void(KDNode *, int, int &, double &)> nearest = [&](KDNode *node, int targetIdx, int &bestIdx, double &bestDist)
    {
        if (!node)
            return;
        int cur = node->index;
        if (cur != targetIdx)
        {
            double d = sqDistUnit(cur, targetIdx);
            if (d < bestDist)
            {
                bestDist = d;
                bestIdx = cur;
            }
        }

        int dim = node->dim;
        double diff = points[targetIdx].unit[dim] - points[cur].unit[dim];
        KDNode *first = diff <= 0 ? node->left : node->right;
        KDNode *second = diff <= 0 ? node->right : node->left;

        if (first)
            nearest(first, targetIdx, bestIdx, bestDist);
        double diff2 = diff * diff;
        if (second && diff2 < bestDist + 1e-18)
            nearest(second, targetIdx, bestIdx, bestDist);
    };

    KDNode *root = build(0, n - 1, 0);

    PairResult bestPair(-1, -1, -2.0);

    for (int i = 0; i < n; ++i)
    {
        int bestIdx = -1;
        double bestDist = numeric_limits<double>::infinity();
        nearest(root, i, bestIdx, bestDist);
        if (bestIdx != -1)
        {

            double cosine = 1.0 - 0.5 * bestDist;
            if (cosine > bestPair.similarity)
            {
                bestPair = PairResult(i, bestIdx, cosine);
            }
        }
    }

    function<void(KDNode *)> freeNode = [&](KDNode *node)
    {
        if (!node)
            return;
        freeNode(node->left);
        freeNode(node->right);
        delete node;
    };
    freeNode(root);

    return bestPair;
}

bool readDataFromCSV(const string &filename, vector<Point> &points)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Khong the mo file: " << filename << endl;
        return false;
    }

    string line;
    int pointId = 0;

    getline(file, line);

    while (getline(file, line) && pointId < NUM_POINTS)
    {
        Point p;
        p.id = pointId;

        stringstream ss(line);
        string value;
        int dim = 0;

        while (getline(ss, value, ',') && dim < DIMENSIONS)
        {
            p.coords[dim] = stod(value);
            dim++;
        }

        p.norm = calculateNorm(p.coords);

        if (p.norm > 1e-12)
        {
            for (int k = 0; k < DIMENSIONS; ++k)
                p.unit[k] = p.coords[k] / p.norm;
        }
        else
        {
            for (int k = 0; k < DIMENSIONS; ++k)
                p.unit[k] = 0.0;
        }

        points.push_back(p);
        pointId++;
    }

    file.close();
    return true;
}

void printPoint(const Point &p)
{
    cout << "Diem " << p.id << ": [";
    for (int i = 0; i < DIMENSIONS; i++)
    {
        cout << fixed << setprecision(2) << p.coords[i];
        if (i < DIMENSIONS - 1)
            cout << ", ";
    }
    cout << "]" << endl;
    cout << "  Norm: " << fixed << setprecision(6) << p.norm << endl;
}

void printResult(const PairResult &result, const vector<Point> &points)
{

    if (result.i == -1 || result.j == -1)
    {
        cout << "Khong tim thay cap diem nao!" << endl;
        return;
    }

    cout << "\nCAP DIEM CO DO TUONG DONG CUC DAI:" << endl;
    const Point &p1 = points[result.i];
    const Point &p2 = points[result.j];

    printPoint(p1);
    cout << endl;
    printPoint(p2);

    cout << "\n----------------------------------------" << endl;
    cout << "  (Cosine Similarity):" << endl;
    cout << "  " << fixed << setprecision(10) << result.similarity << endl;
}

int main()
{

    
    vector<Point> points;
    string filename = "B.scv.csv";

    if (!readDataFromCSV(filename, points))
    {
        return 1;
    }

    cout << "Da doc " << points.size() << " diem tu file " << filename << endl;
    cout << "Moi diem co " << DIMENSIONS << " chieu\n"
         << endl;

    cout << "xu ly bang phuong phap Divide and Conquer (KD-Tree)..." << endl;
    vector<Point> pointsCopy = points;
    PairResult result = findMaxSimilarityDivideConquer(pointsCopy);
    printResult(result, points);

    return 0;
}
