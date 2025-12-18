# Gradient Descent với Momentum - Cross-Entropy Loss

## Hàm Mất Mát (Loss Function)

Hàm Cross-Entropy Loss cho Logistic Regression:

```
f(x,y) = { -log₁₀(1/(1+e⁻ˣ))           nếu y = 1
         { -log₁₀(1 - 1/(1+e⁻ˣ))       nếu y = 0
```

Hay viết gọn hơn với sigmoid σ(x) = 1/(1+e⁻ˣ):

```
f(x,y) = { -log₁₀(σ(x))         nếu y = 1
         { -log₁₀(1 - σ(x))     nếu y = 0
```

## Đạo Hàm

### Đạo hàm của sigmoid:
```
σ'(x) = σ(x) · (1 - σ(x))
```

### Đạo hàm của Cross-Entropy:

**Khi y = 1:**
```
∂f/∂x = ∂/∂x[-log₁₀(σ(x))]
      = -1/(σ(x)·ln(10)) · σ'(x)
      = -σ'(x)/(σ(x)·ln(10))
      = -(1 - σ(x))/ln(10)
```

**Khi y = 0:**
```
∂f/∂x = ∂/∂x[-log₁₀(1 - σ(x))]
      = 1/((1-σ(x))·ln(10)) · σ'(x)
      = σ(x)/ln(10)
```

## Thuật Toán Gradient Descent với Momentum

### Mô hình: z = w·x + b

Với:
- w: weight (trọng số)
- b: bias (độ lệch)
- x: input (đầu vào)
- y: label (nhãn: 0 hoặc 1)

### Công Thức Cập Nhật:

```
1. Tính gradient:
   grad_w = (1/n) · Σ[∂L/∂x · x]
   grad_b = (1/n) · Σ[∂L/∂x]

2. Cập nhật velocity (vận tốc):
   v_w = α · v_w + γ · grad_w
   v_b = α · v_b + γ · grad_b

3. Cập nhật tham số:
   w = w - v_w
   b = b - v_b
```

Trong đó:
- γ (gamma): learning rate (tốc độ học)
- α (alpha): momentum coefficient (hệ số động lượng)
- n: số mẫu dữ liệu

## Kết Quả Thực Nghiệm

### Dữ liệu:
- 60 mẫu huấn luyện
- Class 0: 30 mẫu (X < 0)
- Class 1: 30 mẫu (X > 0)

### Tham số tối ưu hóa:
- Learning rate (γ): 0.1
- Momentum (α): 0.9
- Hội tụ sau: 583 iterations
- Độ chính xác: 85%

### Kết quả cuối cùng:
```
Optimal w = 2.338345
Optimal b = -1.282633
Final Loss = 0.128081
```

### Mô hình học được:
```
Decision boundary: w·x + b = 0
                  2.338·x - 1.283 = 0
                  x ≈ 0.548
```

**Quy tắc phân loại:**
- Nếu x > 0.548 → Dự đoán y = 1 (xác suất > 50%)
- Nếu x < 0.548 → Dự đoán y = 0 (xác suất < 50%)

## Ví Dụ Dự Đoán

| X    | z = w·x + b | σ(z) = P(Y=1) | Dự đoán |
|------|-------------|---------------|---------|
| -2.0 | -5.96       | 0.26%         | 0       |
| -1.0 | -3.62       | 2.61%         | 0       |
|  0.0 | -1.28       | 21.71%        | 0       |
|  1.0 |  1.06       | 74.19%        | 1       |
|  2.0 |  3.39       | 96.75%        | 1       |

## Lợi Ích của Momentum

1. **Tăng tốc hội tụ**: Tích lũy vận tốc giúp di chuyển nhanh hơn theo hướng giảm gradient
2. **Vượt qua local minima**: Động lượng giúp vượt qua các cực tiểu địa phương
3. **Giảm dao động**: Smooth hóa quá trình cập nhật, giảm dao động khi gradient thay đổi
4. **Ổn định hơn**: Ít bị ảnh hưởng bởi nhiễu trong gradient

## So Sánh với Gradient Descent Thông Thường

| Đặc điểm              | GD Thường | GD + Momentum |
|-----------------------|-----------|---------------|
| Tốc độ hội tụ         | Chậm      | Nhanh hơn     |
| Dao động              | Nhiều     | Ít hơn        |
| Vượt local minima     | Khó       | Dễ hơn        |
| Số tham số            | 1 (γ)     | 2 (γ, α)      |
| Độ phức tạp           | Thấp      | Trung bình    |

## Công Thức Toán Học Chi Tiết

### Cross-Entropy Loss (Binary):
```
L(w,b) = -(1/n) · Σᵢ[yᵢ·log₁₀(σ(zᵢ)) + (1-yᵢ)·log₁₀(1-σ(zᵢ))]
```

Với: zᵢ = w·xᵢ + b

### Gradient theo w và b:
```
∂L/∂w = (1/n) · Σᵢ[(σ(zᵢ) - yᵢ)·xᵢ] / ln(10)
∂L/∂b = (1/n) · Σᵢ[(σ(zᵢ) - yᵢ)] / ln(10)
```

### Momentum Update:
```
vₜ = α·vₜ₋₁ + γ·∇L
θₜ = θₜ₋₁ - vₜ
```

## Biên Dịch và Chạy

### Biên dịch:
```bash
g++ -std=c++17 CrossEntropy_GradientMomentum.cpp -o CrossEntropy_GradientMomentum.exe
```

### Chạy:
```bash
.\CrossEntropy_GradientMomentum.exe
```

## Ứng Dụng Thực Tế

1. **Phân loại nhị phân**: Email spam/not spam, bệnh/khỏe mạnh
2. **Dự đoán xác suất**: Khả năng khách hàng mua hàng
3. **Nhận dạng mẫu**: Phát hiện đối tượng trong ảnh
4. **Machine Learning**: Nền tảng cho Neural Networks
5. **Regression**: Dự đoán kết quả 0/1

## Tham Số Tối Ưu

### Learning Rate (γ):
- Quá lớn (>1): Không hội tụ, dao động
- Quá nhỏ (<0.001): Hội tụ chậm
- Tốt: 0.01 - 0.5

### Momentum (α):
- α = 0: Gradient Descent thông thường
- α = 0.5: Momentum vừa phải
- α = 0.9: Momentum cao (thường dùng)
- α = 0.99: Momentum rất cao

### Tổng Hợp:
- Bắt đầu: γ = 0.1, α = 0.9
- Fine-tuning: Điều chỉnh dựa trên kết quả
- Validation: Kiểm tra trên tập test

## Độ Phức Tạp

- **Không gian**: O(p) với p là số tham số
- **Thời gian mỗi iteration**: O(n·p) với n là số mẫu
- **Tổng thời gian**: O(k·n·p) với k là số iterations

Trong bài này:
- p = 2 (w và b)
- n = 60 (mẫu)
- k = 583 (iterations)
