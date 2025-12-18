# Chuỗi Markov - Phân Tích Thói Quen Ăn Sáng

## Kết Quả Phân Tích

### Dữ liệu lịch sử ăn sáng (16 ngày):
```
Banh my -> Pho -> Bun -> Pizza -> Banh my -> Pho -> Bun -> Pizza 
-> Pizza -> Banh my -> Banh my -> Pho -> Pho -> Pho -> Bun -> Pho
```

### Ma Trận Chuyển Trạng Thái P:

```
   From \ To     Banh my      Pho        Bun      Pizza
----------------------------------------------------------
     Banh my      0.2500     0.7500     0.0000    0.0000
         Pho      0.0000     0.4000     0.6000    0.0000
         Bun      0.0000     0.3333     0.0000    0.6667
       Pizza      0.6667     0.0000     0.0000    0.3333
```

### Câu trả lời:

**Xác suất ăn 'Banh my' hôm nay biết hôm qua đã ăn 'Pho':**

**P(Banh my | Pho) = 0.0000 = 0%**

**Giải thích:** Trong dữ liệu lịch sử, sau khi ăn Phở thì KHÔNG BAO GIỜ ăn Bánh mì vào ngày hôm sau. Thay vào đó:
- Sau Pho → Pho: 40% (2/5 lần)
- Sau Pho → Bun: 60% (3/5 lần)

## Cách Xây Dựng Ma Trận P

### Bước 1: Đếm số lần chuyển trạng thái

Từ dữ liệu, ta đếm:
- **Banh my → ?**: 
  - Banh my → Pho: 3 lần
  - Banh my → Banh my: 1 lần
  - Tổng: 4 lần

- **Pho → ?**:
  - Pho → Pho: 2 lần
  - Pho → Bun: 3 lần
  - Tổng: 5 lần

- **Bun → ?**:
  - Bun → Pizza: 2 lần
  - Bun → Pho: 1 lần
  - Tổng: 3 lần

- **Pizza → ?**:
  - Pizza → Banh my: 2 lần
  - Pizza → Pizza: 1 lần
  - Tổng: 3 lần

### Bước 2: Tính xác suất

```
P[i][j] = (Số lần chuyển từ i sang j) / (Tổng số lần xuất phát từ i)
```

Ví dụ:
- P(Pho | Banh my) = 3/4 = 0.75 = 75%
- P(Banh my | Banh my) = 1/4 = 0.25 = 25%
- P(Pho | Pho) = 2/5 = 0.40 = 40%
- P(Bun | Pho) = 3/5 = 0.60 = 60%

## Tính Chất Chuỗi Markov

1. **Tính chất không nhớ (Memoryless)**: 
   - Xác suất ăn món hôm nay CHỈ phụ thuộc vào món ăn hôm qua
   - KHÔNG phụ thuộc vào các ngày trước đó

2. **Tổng xác suất mỗi hàng = 1**:
   ```
   P(Banh my | Banh my) + P(Pho | Banh my) + P(Bun | Banh my) + P(Pizza | Banh my) 
   = 0.25 + 0.75 + 0 + 0 = 1.0
   ```

3. **Ma trận ngẫu nhiên (Stochastic Matrix)**:
   - Mỗi phần tử ≥ 0
   - Tổng mỗi hàng = 1

## Phân Tích Thú Vị

### Các xác suất đặc biệt:

1. **Sau khi ăn Bánh mì**:
   - 75% sẽ ăn Phở
   - 25% tiếp tục ăn Bánh mì
   - 0% ăn Bún hoặc Pizza

2. **Sau khi ăn Phở**:
   - 60% sẽ ăn Bún
   - 40% tiếp tục ăn Phở
   - **0% ăn Bánh mì hoặc Pizza**

3. **Sau khi ăn Bún**:
   - 66.7% sẽ ăn Pizza
   - 33.3% ăn Phở
   - 0% ăn Bánh mì hoặc tiếp tục Bún

4. **Sau khi ăn Pizza**:
   - 66.7% sẽ ăn Bánh mì
   - 33.3% tiếp tục ăn Pizza
   - 0% ăn Phở hoặc Bún

### Chu trình phổ biến:
- **Banh my → Pho → Bun → Pizza → Banh my** (lặp lại)
- Pho có xu hướng được ăn liên tiếp (40% tự chuyển)

## Các Hàm Chính

### 1. `buildTransitionMatrix(data, states, P)`
Xây dựng ma trận chuyển trạng thái từ dữ liệu lịch sử.

**Input:**
- `data`: Vector chứa lịch sử ăn sáng
- `states`: Vector lưu các trạng thái (output)
- `P`: Ma trận xác suất chuyển (output)

**Output:**
- Ma trận P[i][j] = xác suất chuyển từ trạng thái i sang j

### 2. `getProbability(states, P, from, to)`
Tính xác suất chuyển từ trạng thái `from` sang `to`.

**Input:**
- `states`: Danh sách các trạng thái
- `P`: Ma trận chuyển trạng thái
- `from`: Trạng thái xuất phát (hôm qua)
- `to`: Trạng thái đích (hôm nay)

**Output:**
- Xác suất P(to | from)

### 3. `printTransitionMatrix(states, P)`
In ma trận chuyển trạng thái dạng bảng.

### 4. `printStatistics(data, states, P)`
In thống kê tần suất xuất hiện của các món ăn.

## Biên Dịch và Chạy

### Biên dịch:
```bash
g++ -std=c++17 MarkovChain_AnSang.cpp -o MarkovChain_AnSang.exe
```

### Chạy:
```bash
.\MarkovChain_AnSang.exe
```

## Ứng Dụng Thực Tế

1. **Dự đoán hành vi**: Dự đoán món ăn tiếp theo dựa trên lịch sử
2. **Phân tích thói quen**: Hiểu xu hướng ăn uống của người dùng
3. **Tối ưu kho**: Chuẩn bị nguyên liệu dựa trên xác suất
4. **Gợi ý món ăn**: Đề xuất món phù hợp với lịch sử

## Công Thức Toán Học

### Xác suất chuyển trạng thái:
```
P(X_t = j | X_{t-1} = i) = P[i][j]
```

### Tính xác suất sau n bước:
```
P^n = P × P × ... × P (n lần)
```

### Phân phối ổn định (nếu tồn tại):
```
π × P = π
```
Trong đó π là vector xác suất ổn định.
