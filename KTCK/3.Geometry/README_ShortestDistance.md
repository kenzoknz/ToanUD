# Tìm Khoảng Cách Ngắn Nhất Giữa Các Đỉnh Bao Lồi

## Mô tả
Chương trình tìm khoảng cách ngắn nhất giữa các đỉnh của bao lồi (convex hull) với độ phức tạp **O(n log n)**.

## Thuật toán

### 1. Tìm Bao Lồi - Andrew's Monotone Chain (O(n log n))
- **Sắp xếp**: Sắp xếp các điểm theo tọa độ x, sau đó theo y - O(n log n)
- **Xây dựng bao lồi dưới (Lower Hull)**: Duyệt từ trái sang phải
- **Xây dựng bao lồi trên (Upper Hull)**: Duyệt từ phải sang trái
- **Kết quả**: Danh sách các đỉnh của bao lồi theo thứ tự ngược chiều kim đồng hồ

### 2. Tìm Khoảng Cách Ngắn Nhất (O(n))
Với đa giác lồi, khoảng cách nhỏ nhất giữa các đỉnh **luôn là giữa 2 đỉnh liền kề**.

**Lý do**: 
- Trong đa giác lồi, mỗi cạnh là đoạn thẳng ngắn nhất nối 2 đỉnh kế tiếp
- Khoảng cách giữa 2 đỉnh không liền kề luôn lớn hơn ít nhất một trong các cạnh nối chúng

**Cách thực hiện**:
```cpp
// Duyệt qua tất cả các cạnh của bao lồi
for (int i = 0; i < n; ++i)
{
    int j = (i + 1) % n; // Đỉnh tiếp theo
    double dist = euclidean_distance(hull[i], hull[j]);
    if (dist < min_dist)
    {
        min_dist = dist;
        closest_pair = {hull[i], hull[j]};
    }
}
```

## Độ Phức Tạp
- **Tìm bao lồi**: O(n log n)
- **Tìm khoảng cách ngắn nhất**: O(n) 
- **Tổng cộng**: **O(n log n)**

## Các Hàm Chính

### 1. `compute_convex_hull(points)` - O(n log n)
Tìm bao lồi sử dụng thuật toán Andrew's Monotone Chain.
- **Input**: Vector các điểm
- **Output**: Vector các đỉnh bao lồi (ngược chiều kim đồng hồ)

### 2. `shortest_distance_convex_hull(hull)` - O(n)
Tìm khoảng cách ngắn nhất giữa các đỉnh liền kề của bao lồi.
- **Input**: Vector các đỉnh bao lồi
- **Output**: Cặp điểm có khoảng cách ngắn nhất

### 3. `shortest_distance_all_pairs(hull)` - O(n²)
Tìm khoảng cách ngắn nhất giữa TẤT CẢ các cặp đỉnh (để kiểm tra).
- **Input**: Vector các đỉnh bao lồi
- **Output**: Cặp điểm có khoảng cách ngắn nhất

### 4. `euclidean_distance(A, B)`
Tính khoảng cách Euclid giữa 2 điểm.

### 5. `cross_product(O, A, B)`
Tính tích có hướng để xác định hướng của 3 điểm.

### 6. `polygon_area(poly)`
Tính diện tích đa giác.

## Biên Dịch và Chạy

### Biên dịch:
```bash
g++ -std=c++17 ShortestDistanceHull.cpp -o ShortestDistanceHull.exe
```

### Chạy:
```bash
.\ShortestDistanceHull.exe
```

## Ví dụ Input/Output

### Input:
```
Nhap so luong diem: 10
Nhap toa do cac diem (x y):
3 4
5 3
6 5
7 6
8 7
4 9
3 8
4 8
7 10
7 4
```

### Output:
```
========================================
CAC DIEM BAN DAU:
========================================
Diem 1: (3, 4)
Diem 2: (5, 3)
...

========================================
BAO LOI (CONVEX HULL):
========================================
So dinh bao loi: 7
Dinh 1: (3, 4)
Dinh 2: (5, 3)
Dinh 3: (7, 4)
Dinh 4: (8, 7)
Dinh 5: (7, 10)
Dinh 6: (4, 9)
Dinh 7: (3, 8)

Dien tich bao loi: 26

========================================
KHOANG CACH NGAN NHAT:
========================================
Cap dinh gan nhat: (4, 9) - (3, 8)
Khoang cach: 1.414214

========================================
KIEM TRA TAT CA CAC CAP DINH:
========================================
Cap dinh gan nhat (kiem tra tat ca): (4, 9) - (3, 8)
Khoang cach: 1.414214

========================================
DO PHUC TAP:
========================================
- Tim bao loi: O(n log n)
- Tim khoang cach ngan nhat (chi cac canh): O(n)
- Tong: O(n log n)
========================================
```

## Tối Ưu Hóa

### Tại sao chỉ cần kiểm tra các cạnh? (O(n) thay vì O(n²))
Với bao lồi, ta có tính chất:
1. **Đa giác lồi**: Mọi đoạn thẳng nối 2 điểm bất kỳ trong đa giác đều nằm trong hoặc trên biên đa giác
2. **Khoảng cách tối thiểu**: Khoảng cách ngắn nhất giữa các đỉnh luôn là một cạnh của bao lồi

Do đó, thay vì kiểm tra tất cả O(n²) cặp điểm, chỉ cần kiểm tra O(n) cạnh liền kề.

## Ứng Dụng
- Tính toán hình học
- Xử lý ảnh và nhận dạng mẫu
- Bài toán cặp điểm gần nhất trên bao lồi
- Tối ưu hóa trong thiết kế và quy hoạch
