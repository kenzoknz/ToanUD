# CHƯƠNG TRÌNH PHÂN RÃ EIGEN (EIGENDECOMPOSITION)

## Mô tả
Chương trình C++ thực hiện phân rã eigen cho nhiều ma trận vuông với các cấp khác nhau (2x2, 3x3, 4x4, ..., tối đa 10x10).

## Thuật toán sử dụng
- **Phương pháp Danhilepski**: Biến đổi ma trận về dạng đồng dạng dễ tính toán
- **Giải phương trình đặc trưng**: 
  - Cấp 2: Phương trình bậc 2
  - Cấp 3: Công thức Cardano
  - Cấp 4: Phương pháp Newton-Raphson
  - Cấp cao hơn: Phương pháp số

## Công thức phân rã Eigen
```
A = S * D * S^(-1)
```
Trong đó:
- A: Ma trận gốc
- S: Ma trận eigenvector (vector riêng)
- D: Ma trận đường chéo chứa eigenvalues (trị riêng)
- S^(-1): Ma trận nghịch đảo của S

## Cách sử dụng

### 1. Compile chương trình:
```bash
g++ -o eigen eigen.cpp -std=c++11
```

### 2. Chạy chương trình:
```bash
./eigen
```

### 3. Nhập dữ liệu:
```
Number of matrices to decompose: 2    # Số lượng ma trận cần phân rã

MATRIX #1
Enter matrix size (2-10): 2           # Cấp ma trận đầu tiên
Enter matrix elements:                # Nhập các phần tử theo hàng
4 -2
1 1

MATRIX #2
Enter matrix size (2-10): 3           # Cấp ma trận thứ hai
Enter matrix elements:
1 2 3
0 1 4
0 0 1
```

### 4. Hoặc dùng file input:
```bash
./eigen < test_eigen.txt
```

## Định dạng file input
```
<số_lượng_ma_trận>
<cấp_ma_trận_1>
<phần_tử_hàng_1>
<phần_tử_hàng_2>
...
<cấp_ma_trận_2>
<phần_tử_hàng_1>
...
```

## Ví dụ
File `test_eigen2.txt`:
```
2
2
4 -2
1 1
3
1 2 3
0 1 4
0 0 1
```

## Kết quả hiển thị
Cho mỗi ma trận, chương trình hiển thị:
1. Ma trận gốc A
2. Ma trận sau biến đổi Danhilepski
3. Các eigenvalues (trị riêng)
4. Ma trận eigenvector S
5. Ma trận đường chéo D
6. Ma trận nghịch đảo S^(-1)
7. Kiểm tra độ chính xác: S * D * S^(-1) - A

## Lưu ý
- Ma trận phải khả nghịch để có thể phân rã eigen
- Ma trận tam giác hoặc đường chéo có thể gây lỗi trong thuật toán Danhilepski
- Độ chính xác: error < 1e-5 được coi là thành công
- Các eigenvalues được sắp xếp theo thứ tự giảm dần

## Điều kiện ma trận
Để phân rã eigen thành công, ma trận cần:
- ✅ Là ma trận vuông
- ✅ Khả nghịch (det ≠ 0)
- ✅ Có đầy đủ eigenvalues thực
- ✅ Có đầy đủ eigenvectors độc lập tuyến tính

## Test cases
### Test 1: Ma trận 2x2
```
Input:
4 -2
1 1

Output:
Eigenvalues: 3, 2
Verification: SUCCESS ✓
```

### Test 2: Ma trận 3x3 đường chéo
```
Input:
2 0 0
0 3 0
0 0 4

Output:
Warning: Ma trận đường chéo có thể gặp vấn đề với Danhilepski
```

## Công nghệ
- C++11
- Standard libraries: iostream, iomanip, cmath, algorithm
