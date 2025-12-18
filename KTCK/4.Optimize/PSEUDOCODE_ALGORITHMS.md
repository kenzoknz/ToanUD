# PSEUDOCODE - CÁC THUẬT TOÁN TỐI ƯU HÓA

## 1. GRADIENT DESCENT (Không có Momentum)

### Mô tả
Thuật toán tối ưu hóa cơ bản sử dụng gradient để di chuyển theo hướng giảm dần của hàm mục tiêu.

### Pseudocode

```
Algorithm GradientDescent(x_init, learning_rate, max_epochs, f, f'):
    Input: 
        - x_init: Điểm khởi đầu
        - learning_rate (γ): Tốc độ học (learning rate)
        - max_epochs: Số vòng lặp tối đa
        - f: Hàm mục tiêu cần tối ưu
        - f': Đạo hàm của hàm mục tiêu
    Output: 
        - x_optimal: Điểm cực tiểu của hàm f
        - f(x_optimal): Giá trị nhỏ nhất của hàm

    1. Initialize:
        x ← x_init                                  // Khởi tạo điểm bắt đầu
        epoch ← 0                                   // Số vòng lặp hiện tại

    2. While epoch < max_epochs:
        epoch ← epoch + 1

        x_prev ← x                                  // Lưu giá trị x trước đó
        
        grad ← f'(x)                                // Tính gradient tại x
        
        x ← x - learning_rate × grad                // Cập nhật x theo hướng ngược gradient
        
        Print "Iteration", epoch, ": x =", x, ", f(x) =", f(x)

        // Kiểm tra điều kiện hội tụ
        If |x - x_prev| < ε:                        // ε = 1e-5
            Print "Convergence reached after", epoch, "iterations."
            Print "Minimum value:", f(x)
            Print "At point: x =", x
            Return x, f(x)

    3. Print "Maximum iterations reached without convergence."
    Return x, f(x)
```

### Ưu điểm
- Đơn giản, dễ cài đặt
- Luôn đi theo hướng giảm dần

### Nhược điểm
- Có thể dao động quanh điểm cực tiểu
- Hội tụ chậm
- Nhạy cảm với learning rate

---

## 1.5. GRADIENT DESCENT WITH MOMENTUM

### Mô tả
Cải tiến của Gradient Descent, sử dụng "vận tốc" (velocity) để tăng tốc hội tụ và giảm dao động. Momentum giúp vượt qua các vùng phẳng và local minima.

### Pseudocode (Classical Momentum - Standard Form)

```
Algorithm GradientDescentMomentum(x_init, gamma, alpha, max_iter, f, f'):
    Input: 
        - x_init: Điểm khởi đầu
        - gamma (γ): Learning rate (tốc độ học)
        - alpha (α): Momentum coefficient (thường 0.9 - 0.99)
        - max_iter: Số vòng lặp tối đa
        - f: Hàm mục tiêu cần tối ưu
        - f': Đạo hàm của hàm mục tiêu
    Output: 
        - x_optimal: Điểm cực tiểu
        - f(x_optimal): Giá trị nhỏ nhất

    1. Initialize:
        x ← x_init                                  // Điểm khởi đầu
        v ← 0                                       // Velocity ban đầu = 0
        iterations ← 0

    2. While iterations < max_iter:
        iterations ← iterations + 1
        x_prev ← x                                  // Lưu x trước đó
        
        grad ← f'(x)                                // Tính gradient tại x
        
        // Cập nhật velocity (tích lũy momentum)
        v ← alpha × v + gamma × grad                // Standard form
        
        // Cập nhật x
        x ← x - v                                   // Di chuyển theo hướng ngược v
        
        // In thông tin (mỗi 100 vòng hoặc 5 vòng đầu)
        If (iterations % 100 == 0) OR (iterations ≤ 5):
            Print "Iter", iterations, ": x =", x, 
                  ", f(x) =", f(x), ", f'(x) =", grad

        // Kiểm tra hội tụ
        If |x - x_prev| < ε:                        // ε = 1e-5
            Print "Convergence reached after", iterations, "iterations."
            Print "Optimal x =", x, ", f(x) =", f(x)
            Return x, f(x)

    3. Print "Maximum iterations reached without convergence."
       Return x, f(x)
```

### Pseudocode (Alternative Form - Cùng kết quả)

```
// Cách viết tương đương, chỉ khác dấu:
v ← alpha × v - gamma × grad                    // Velocity âm
x ← x + v                                       // Cộng velocity
```

**Lưu ý:** Cả hai cách đều cho kết quả giống nhau vì:
- `x - (α·v + γ·∇f)` ≡ `x + (α·v - γ·∇f)`

### So sánh với Gradient Descent thường

| Thuật toán | Công thức | Đặc điểm |
|------------|-----------|----------|
| **GD thường** | `x ← x - γ·∇f` | Không nhớ quá khứ |
| **GD + Momentum** | `v ← α·v + γ·∇f`<br>`x ← x - v` | Tích lũy hướng di chuyển |

### Tham số quan trọng

**Alpha (α) - Momentum coefficient:**
- **Giá trị khuyến nghị**: 0.9 - 0.99
- α = 0: Trở về Gradient Descent thường
- α = 0.9: Giữ lại 90% velocity cũ (chuẩn)
- α = 0.99: Momentum mạnh hơn, hội tụ nhanh nhưng có thể vọt lố
- **❌ α = 0.1 quá nhỏ** → momentum yếu

**Gamma (γ) - Learning rate:**
- **Giá trị khuyến nghị**: 0.001 - 0.1
- Nhỏ hơn GD thường vì có momentum tăng tốc

### Ưu điểm
- Hội tụ nhanh hơn Gradient Descent thường
- Giảm dao động (oscillation)
- Vượt qua vùng phẳng dễ dàng hơn
- Có thể thoát khỏi local minima nông

### Nhược điểm
- Thêm hyperparameter (alpha) cần điều chỉnh
- Có thể vọt qua (overshoot) điểm cực tiểu nếu α quá lớn
- Phức tạp hơn GD thường một chút

---

## 2. NEWTON-RAPHSON METHOD

### Mô tả
Thuật toán tìm nghiệm của phương trình f(x) = 0 hoặc tìm cực trị (khi f'(x) = 0) sử dụng đạo hàm bậc hai (Hessian).

### Pseudocode

```
Algorithm NewtonRaphson(f, f', x_init):
    Input:
        - f: Hàm mục tiêu (hoặc đạo hàm bậc nhất nếu tìm cực trị)
        - f': Đạo hàm của f (hoặc đạo hàm bậc hai nếu tìm cực trị)
        - x_init: Điểm khởi đầu
    Output:
        - x_root: Nghiệm của phương trình f(x) = 0

    1. Initialize:
        x ← x_init                                  // Điểm bắt đầu
        iterations ← 0
        MAX_ITERATIONS ← 1000
        EPSILON ← 1e-5

    2. Print "Starting Newton-Raphson with initial guess:", x
       Print "Initial f(x) =", f(x)
       Print "Initial f'(x) =", f'(x)

    3. While iterations < MAX_ITERATIONS:
        fx ← f(x)                                   // Tính f(x)
        dfx ← f'(x)                                 // Tính f'(x)
        
        // Kiểm tra đạo hàm gần 0
        If |dfx| < 1e-12:
            Print "Derivative too small. Method may not converge."
            Break
        
        h ← fx / dfx                                // Bước di chuyển
        x_new ← x - h                               // Công thức Newton-Raphson
        iterations ← iterations + 1
        
        Print "Iteration", iterations, ": x =", x_new, 
              ", f(x) =", fx, ", f'(x) =", dfx, ", step h =", h

        // Kiểm tra hội tụ theo bước di chuyển
        If |h| < EPSILON:
            Print "Convergence achieved after", iterations, "iterations."
            Print "Root approximately:", x_new
            Return x_new
        
        // Kiểm tra hội tụ theo giá trị hàm
        If |fx| < EPSILON:
            Print "Function value close to zero after", iterations, "iterations."
            Print "Root approximately:", x_new
            Return x_new
        
        x ← x_new                                   // Cập nhật x

    4. Print "Did not converge within", MAX_ITERATIONS, "iterations."
       Print "Final approximation:", x
       Return x
```

### Ưu điểm
- Hội tụ rất nhanh (quadratic convergence) khi gần nghiệm
- Chính xác cao

### Nhược điểm
- Cần tính đạo hàm bậc hai
- Có thể phân kỳ nếu khởi tạo xa nghiệm
- Yêu cầu f'(x) ≠ 0

---

## 3. AUGMENTED LAGRANGIAN METHOD (ALM)

### Mô tả
Thuật toán tối ưu hóa có ràng buộc, kết hợp phương pháp Lagrange với hàm phạt (penalty).

### Bài toán
```
Minimize: f(x, y, z) = x² + y² + z² - (1/2)·ln(1 + x² + y² + z²)
Subject to: h(x, y, z) = x² + y + z - 2 = 0
```

### Pseudocode chính

```
Algorithm AugmentedLagrangianMethod():
    Input:
        - f(x,y,z): Hàm mục tiêu
        - h(x,y,z): Ràng buộc đẳng thức (h = 0)
    Output:
        - (x*, y*, z*): Điểm tối ưu thỏa mãn ràng buộc

    1. Initialize:
        λ ← 0.0                                     // Nhân tử Lagrange
        r ← 1.0                                     // Hệ số phạt (penalty parameter)
        x ← 1.0, y ← 1.0, z ← 1.0                  // Điểm khởi đầu
        tol ← 1e-5                                  // Ngưỡng hội tụ
        maxIter ← 100

    2. Print "Starting Augmented Lagrangian Method"
       Print "Objective: f(x,y,z) = x² + y² + z² - (1/2)·ln(1+x²+y²+z²)"
       Print "Constraint: h(x,y,z) = x² + y + z - 2 = 0"

    3. For iteration = 1 to maxIter:
        
        // Bước 3a: Xây dựng hàm Augmented Lagrangian
        Define A(x,y,z) = f(x,y,z) + λ·h(x,y,z) + (r/2)·[h(x,y,z)]²
        
        // Bước 3b: Tối ưu hóa hàm A không ràng buộc (dùng Powell Method)
        (x, y, z) ← PowellMethod(A, (x,y,z), tolerance=1e-6)
        
        // Bước 3c: Tính vi phạm ràng buộc
        h_val ← h(x, y, z)
        
        Print "Iter", iteration, ": λ =", λ, ", r =", r,
              ", (x,y,z) = (", x, ",", y, ",", z, "), h =", h_val
        
        // Bước 3d: Kiểm tra hội tụ
        If |h_val| < tol:
            Print "Converged after", iteration, "iterations."
            Print "Optimal point: (", x, ",", y, ",", z, ")"
            Print "Constraint violation:", h_val
            Print "Objective value:", f(x, y, z)
            Return (x, y, z)
        
        // Bước 3e: Cập nhật nhân tử Lagrange
        λ ← λ + r × h_val
        
        // Bước 3f: Tăng hệ số phạt
        γ_r ← 10.0                                  // Hệ số tăng penalty
        r ← r × γ_r
        If r > 1e6:                                 // Giới hạn r
            r ← 1e6

    4. Print "Reached max iterations without convergence."
       Return (x, y, z)
```

### Thuật toán phụ: Powell Method (tối ưu không ràng buộc)

```
Algorithm PowellMethod(func, initial_guess, tol):
    Input:
        - func(x,y,z): Hàm cần tối ưu
        - initial_guess: Điểm khởi đầu [x₀, y₀, z₀]
        - tol: Ngưỡng hội tụ
    Output:
        - X*: Điểm cực tiểu của func

    1. Initialize:
        directions ← [[1,0,0], [0,1,0], [0,0,1]]   // Hướng tìm kiếm ban đầu
        X ← initial_guess
        n ← 3                                       // Số biến
        maxIter ← 100

    2. For iter = 0 to maxIter:
        X_prev ← X
        
        // Bước 2a: Tìm kiếm theo từng hướng
        For q = 0 to n-1:
            // Định nghĩa hàm 1 biến theo hướng q
            Define func_1D(α) = func(X[0] + α·directions[q][0],
                                     X[1] + α·directions[q][1],
                                     X[2] + α·directions[q][2])
            
            // Tìm α tối ưu bằng Golden Section Search
            α_opt ← GoldenSectionSearch(func_1D, -5, 5)
            
            // Cập nhật X theo hướng q
            For i = 0 to 2:
                X[i] ← X[i] + α_opt × directions[q][i]
        
        // Bước 2b: Tạo hướng tìm kiếm mới (Powell)
        newDir ← [X[0]-X_prev[0], X[1]-X_prev[1], X[2]-X_prev[2]]
        normNew ← √(newDir[0]² + newDir[1]² + newDir[2]²)
        
        If normNew > 0:
            // Chuẩn hóa hướng mới
            For i = 0 to 2:
                newDir[i] ← newDir[i] / normNew
            
            // Xóa hướng cũ nhất, thêm hướng mới
            Remove directions[0]
            Append newDir to directions
        
        // Bước 2c: Kiểm tra hội tụ
        diffNorm ← √((X[0]-X_prev[0])² + (X[1]-X_prev[1])² + (X[2]-X_prev[2])²)
        If diffNorm < tol:
            Break

    3. Return X
```

### Thuật toán phụ: Golden Section Search

```
Algorithm GoldenSectionSearch(func, a, b, tol):
    Input:
        - func: Hàm 1 biến cần tối ưu
        - [a, b]: Khoảng tìm kiếm
        - tol: Ngưỡng hội tụ (default 1e-6)
    Output:
        - x*: Điểm cực tiểu trong [a, b]

    1. Initialize:
        gr ← (√5 + 1) / 2                          // Golden ratio ≈ 1.618
        c ← b - (b - a) / gr
        d ← a + (b - a) / gr

    2. While |c - d| > tol:
        If func(c) < func(d):
            b ← d                                   // Thu hẹp về bên trái
        Else:
            a ← c                                   // Thu hẹp về bên phải
        
        c ← b - (b - a) / gr
        d ← a + (b - a) / gr

    3. Return (b + a) / 2
```

### Ưu điểm của ALM
- Xử lý tốt ràng buộc đẳng thức
- Kết hợp ưu điểm của Lagrange và Penalty Method
- Không cần r → ∞ như Penalty Method thuần túy

### Nhược điểm
- Phức tạp hơn các phương pháp khác
- Cần điều chỉnh nhiều tham số (λ, r, γ_r)
- Yêu cầu giải bài toán tối ưu không ràng buộc ở mỗi vòng lặp

---

## SO SÁNH CÁC THUẬT TOÁN

| Tiêu chí | Gradient Descent | Newton-Raphson | ALM |
|----------|-----------------|----------------|-----|
| **Đạo hàm cần** | Bậc 1 | Bậc 2 | Bậc 1 (qua Powell) |
| **Tốc độ hội tụ** | Chậm (linear) | Rất nhanh (quadratic) | Trung bình |
| **Ràng buộc** | Không | Không | Có |
| **Độ phức tạp** | Thấp | Trung bình | Cao |
| **Số biến** | Đơn/Đa biến | Đơn/Đa biến | Đa biến |
| **Use case** | Tối ưu đơn giản | Tìm nghiệm chính xác | Tối ưu có ràng buộc |

---

## FLOWCHART TỔNG QUAN

### Gradient Descent
```
Start → Initialize x, γ → Loop: x ← x - γ·f'(x) → Check convergence → End
```

### Newton-Raphson
```
Start → Initialize x → Loop: x ← x - f(x)/f'(x) → Check |f(x)| or |step| → End
```

### ALM
```
Start → Initialize λ, r, x → Loop {
    Minimize A(x) = f(x) + λ·h(x) + (r/2)·h²(x)
    Update λ ← λ + r·h(x)
    Increase r
    Check |h(x)| < ε
} → End
```

---

## GHI CHÚ QUAN TRỌNG

1. **Learning Rate (γ)**: 
   - Quá lớn → dao động, không hội tụ
   - Quá nhỏ → hội tụ chậm
   - Thường chọn: 0.001 - 0.1

2. **Penalty Parameter (r)**:
   - Bắt đầu nhỏ (r = 1.0)
   - Tăng dần mỗi vòng (γ_r = 10)
   - Giới hạn trên để tránh ill-conditioning

3. **Convergence Check**:
   - Gradient Descent: |x_new - x_old| < ε
   - Newton-Raphson: |f(x)| < ε hoặc |step| < ε
   - ALM: |h(x)| < ε (vi phạm ràng buộc)
