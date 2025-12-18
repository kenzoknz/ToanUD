# THUẬT TOÁN MONOTONE CHAIN (Andrew's Algorithm)

## Mô tả
- **Mục đích**: Tìm bao lồi (Convex Hull) của tập điểm trên mặt phẳng
- **Độ phức tạp**: O(n log n)
- **Ưu điểm**: Đơn giản, hiệu quả, dễ cài đặt

## Mã giả thuật toán

```
Algorithm MonotoneChain(points):
    Input: Mảng points[] gồm n điểm trên mặt phẳng
    Output: Mảng hull[] chứa các đỉnh của bao lồi theo thứ tự ngược chiều kim đồng hồ

    1. Nếu n <= 1:
          Trả về points                            // Không cần xử lý

    2. Sắp xếp points[] theo tọa độ x tăng dần    // O(n log n)
       (Nếu x bằng nhau thì sắp xếp theo y tăng dần)

    3. Khởi tạo:
          hull[] = mảng rỗng với kích thước tối đa 2n
          k = 0                                     // Chỉ số hiện tại trong hull[]

    4. XÂY DỰNG LOWER HULL (chuỗi dưới):          // O(n)
       For i = 0 to n-1:
           While (k >= 2) AND (CrossProduct(hull[k-2], hull[k-1], points[i]) <= 0):
               k = k - 1                            // Loại bỏ điểm cuối vì không tạo góc lồi
           hull[k] = points[i]
           k = k + 1

    5. XÂY DỰNG UPPER HULL (chuỗi trên):          // O(n)
       t = k + 1                                    // Lưu số điểm của lower hull
       For i = n-2 down to 0:
           While (k >= t) AND (CrossProduct(hull[k-2], hull[k-1], points[i]) <= 0):
               k = k - 1                            // Loại bỏ điểm cuối vì không tạo góc lồi
           hull[k] = points[i]
           k = k + 1

    6. Loại bỏ điểm cuối (trùng với điểm đầu):
       hull.resize(k - 1)

    7. Trả về hull[]
```

## Hàm phụ trợ

### Cross Product (Tích có hướng)
```
Function CrossProduct(O, A, B):
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x)
```

**Ý nghĩa**:
- `> 0`: B nằm bên trái đường thẳng OA (rẽ trái) ✓
- `< 0`: B nằm bên phải đường thẳng OA (rẽ phải)
- `= 0`: O, A, B thẳng hàng

**Lưu ý**: Điều kiện `<= 0` chấp nhận cả điểm thẳng hàng

## Minh họa thuật toán

### Bước 1: Sắp xếp điểm
```
Points ban đầu: (3,5), (11,2), (6,8), (4,9), ...
Points sau sắp xếp: (3,5), (4,9), (6,8), (7,8), (9,9), (9,10), (10,3), ...
                     ↑                                                    ↑
                   Trái nhất                                          Phải nhất
```

### Bước 2: Xây dựng Lower Hull
```
Duyệt từ trái → phải:
(3,5) → (4,9) → (6,8)
            ↑ Loại bỏ vì rẽ phải
(3,5) → (6,8) → (7,8)
            ↑ Loại bỏ vì rẽ phải
(3,5) → (7,8) → (9,10) → ...
```

### Bước 3: Xây dựng Upper Hull
```
Duyệt từ phải → trái:
(34,5) → (32,1) → (25,10) → ...
```

### Bước 4: Kết hợp
```
Lower Hull + Upper Hull = Convex Hull hoàn chỉnh
```

## So sánh với Chan's Algorithm

| Tiêu chí | Monotone Chain | Chan's Algorithm |
|----------|---------------|------------------|
| Độ phức tạp | O(n log n) | O(n log h) |
| Phù hợp | Mọi trường hợp | h << n |
| Độ phức tạp code | Đơn giản | Phức tạp |
| Ổn định | Cao | Trung bình |

Trong đó: n = số điểm, h = số đỉnh bao lồi

---

# THUẬT TOÁN CHAN (Chan's Algorithm)

## Mô tả
- **Mục đích**: Tìm bao lồi của tập điểm trên mặt phẳng
- **Độ phức tạp**: O(n log h) - optimal output-sensitive
- **Ưu điểm**: Tối ưu khi h << n (số đỉnh bao lồi nhỏ hơn rất nhiều so với số điểm)

## Mã giả thuật toán

```
Algorithm ChansAlgorithm(points):
    Input: Mảng points[] gồm n điểm trên mặt phẳng
    Output: Mảng hull[] chứa các đỉnh của bao lồi

    For t = 0 to infinity:                          // Tăng dần số lần thử nghiệm
        max_hulls = 2^(2^t)                         // Số phân đoạn tối đa
        
        For m = 1 to max_hulls:                     // Số điểm trong mỗi phân đoạn
            hulls = []                              // Danh sách các hull con
            
            For i = 0 to size(points) step m:       // Chia tập hợp thành các phân đoạn
                If i + m <= size(points):
                    chunk = points[i to i + m]      // Lấy phân đoạn m điểm
                Else:
                    chunk = points[i to end]        // Lấy phần còn lại
                
                hulls.append(GrahamScan(chunk))     // Tìm hull của phân đoạn và thêm vào hulls
            
            hull = []                               // Hull cuối cùng
            hull.append(ExtremeHullPtPair(hulls))   // Tìm điểm cực trị ban đầu
            
            For i = 0 to m:                         // Tìm tối đa m điểm trong hull
                p = NextHullPtPair(hulls, hull[last]) // Tìm điểm tiếp theo trên hull
                
                If p == hull[0]:                    // Nếu điểm tiếp theo quay về điểm đầu
                    output = []
                    For j = 0 to size(hull):
                        output.append(hulls[hull[j].first][hull[j].second]) // Thêm điểm vào output
                    output.pop_back()               // Loại bỏ điểm cuối (trùng điểm đầu)
                    return output                   // Trả về hull cuối cùng
                
                hull.append(p)                      // Thêm điểm tiếp theo vào hull
    
    return []                                       // Trả về rỗng nếu không tìm thấy
```

## Hàm phụ trợ

### Graham Scan (Tìm hull của phân đoạn nhỏ)
```
Function GrahamScan(points):
    // Thuật toán Graham Scan chuẩn để tìm bao lồi
    // Độ phức tạp: O(m log m) với m là số điểm
    ...
    return convex_hull
```

### Tìm điểm cực trị ban đầu
```
Function ExtremeHullPtPair(hulls):
    // Tìm điểm có tọa độ y nhỏ nhất (hoặc x nhỏ nhất nếu y bằng nhau)
    min_point = hulls[0][0]
    min_index = (0, 0)
    
    For i = 0 to size(hulls):
        For j = 0 to size(hulls[i]):
            If hulls[i][j].y < min_point.y OR 
               (hulls[i][j].y == min_point.y AND hulls[i][j].x < min_point.x):
                min_point = hulls[i][j]
                min_index = (i, j)
    
    return min_index
```

### Tìm điểm tiếp theo trên hull
```
Function NextHullPtPair(hulls, current):
    // Tìm điểm tạo góc lớn nhất (rẽ trái nhất) so với điểm hiện tại
    next = null
    max_angle = -infinity
    
    For i = 0 to size(hulls):
        For j = 0 to size(hulls[i]):
            angle = ComputeAngle(current, hulls[i][j])
            If angle > max_angle:
                max_angle = angle
                next = (i, j)
    
    return next
```

## Ý tưởng chính

1. **Chia để trị**: Chia n điểm thành các nhóm nhỏ, mỗi nhóm m điểm
2. **Tìm hull con**: Dùng Graham Scan tìm bao lồi cho từng nhóm nhỏ
3. **Gộp hull**: Kết hợp các hull con để tạo hull cuối cùng
4. **Thử nghiệm**: Tăng dần m = 2^(2^t) cho đến khi tìm được hull hoàn chỉnh

## Phân tích độ phức tạp

- **Số nhóm**: n/m
- **Tìm hull mỗi nhóm**: O(m log m) × n/m = O(n log m)
- **Gộp hull**: O(n/m × m) = O(n)
- **Tổng mỗi vòng lặp**: O(n log m)
- **Số vòng lặp**: O(log h)
- **Tổng**: O(n log h)

## Khi nào sử dụng Chan's Algorithm?

✓ **Nên dùng khi**:
- Số đỉnh bao lồi h << n
- Ví dụ: n = 1,000,000 điểm nhưng chỉ có h = 10 đỉnh bao lồi

✗ **Không nên dùng khi**:
- h ≈ n (hầu hết điểm đều là đỉnh bao lồi)
- Cần code đơn giản, dễ cài đặt

## Ví dụ minh họa

```
Cho n = 16 điểm, h = 4 đỉnh bao lồi

Vòng t = 0: m = 2^(2^0) = 2
  - Chia thành 8 nhóm, mỗi nhóm 2 điểm
  - Thử tìm hull với tối đa 2 điểm → Thất bại

Vòng t = 1: m = 2^(2^1) = 4
  - Chia thành 4 nhóm, mỗi nhóm 4 điểm
  - Thử tìm hull với tối đa 4 điểm → Thành công!
  - Trả về hull với 4 đỉnh

Monotone Chain: O(16 log 16) = O(64)
Chan's Algorithm: O(16 log 4) = O(32)
```

## Kết luận

Chan's Algorithm là thuật toán **output-sensitive** tối ưu cho bài toán tìm bao lồi khi số đỉnh bao lồi nhỏ hơn đáng kể so với tổng số điểm. Tuy nhiên, trong thực tế, Monotone Chain thường được ưa chuộng hơn do tính đơn giản và hiệu quả ổn định.
