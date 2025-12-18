#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
using namespace std;

// Hàm Cross-Entropy Loss cho Logistic Regression
// f(x,y) = -log10(1/(1+e^(-x)))           nếu y = 1
//        = -log10(1 - 1/(1+e^(-x)))       nếu y = 0
// Hay:   = -log10(sigmoid(x))             nếu y = 1
//        = -log10(1 - sigmoid(x))         nếu y = 0

// Hàm sigmoid
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Hàm Cross-Entropy Loss cho một điểm dữ liệu
double crossEntropyLoss(double x, int y) {
    const double LOG10 = log(10.0); // chuyển từ ln sang log10
    
    if (y == 1) {
        // f(x,1) = -log10(1/(1+e^(-x))) = -log10(sigmoid(x))
        double sig = sigmoid(x);
        if (sig < 1e-15) sig = 1e-15; // tránh log(0)
        return -log(sig) / LOG10;
    } else {
        // f(x,0) = -log10(1 - 1/(1+e^(-x))) = -log10(1 - sigmoid(x))
        double sig = sigmoid(x);
        if (sig > 1.0 - 1e-15) sig = 1.0 - 1e-15; // tránh log(0)
        return -log(1.0 - sig) / LOG10;
    }
}

// Hàm mất mát trung bình cho tập dữ liệu
double totalLoss(const vector<double>& X, const vector<int>& Y, double w, double b) {
    double loss = 0.0;
    int n = X.size();
    
    for (int i = 0; i < n; i++) {
        double x = w * X[i] + b; // tính z = w*x + b
        loss += crossEntropyLoss(x, Y[i]);
    }
    
    return loss / n; // trung bình
}

// Đạo hàm của Cross-Entropy Loss theo x
double gradCrossEntropy(double x, int y) {
    const double LOG10 = log(10.0);
    double sig = sigmoid(x);
    
    if (y == 1) {
        // d/dx[-log10(sigmoid(x))] = -1/(sigmoid(x) * ln(10)) * sigmoid'(x)
        //                          = -sigmoid'(x)/(sigmoid(x) * ln(10))
        //                          = -(1 - sigmoid(x))/ln(10)
        return -(1.0 - sig) / LOG10;
    } else {
        // d/dx[-log10(1-sigmoid(x))] = 1/(1-sigmoid(x) * ln(10)) * sigmoid'(x)
        //                             = sigmoid(x)/ln(10)
        return sig / LOG10;
    }
}

// Tính gradient của loss theo w và b
void computeGradients(const vector<double>& X, const vector<int>& Y, 
                     double w, double b, double& grad_w, double& grad_b) {
    int n = X.size();
    grad_w = 0.0;
    grad_b = 0.0;
    
    for (int i = 0; i < n; i++) {
        double x = w * X[i] + b;
        double grad_x = gradCrossEntropy(x, Y[i]);
        
        // Chain rule: dL/dw = dL/dx * dx/dw = grad_x * X[i]
        grad_w += grad_x * X[i];
        // Chain rule: dL/db = dL/dx * dx/db = grad_x * 1
        grad_b += grad_x;
    }
    
    grad_w /= n;
    grad_b /= n;
}

// Gradient Descent với Momentum
void gradientDescentMomentum(const vector<double>& X, const vector<int>& Y,
                            double& w, double& b,
                            double learning_rate, double momentum,
                            int max_iterations, double tolerance) {
    int n = X.size();
    
    // Khởi tạo vận tốc (velocity) cho momentum
    double v_w = 0.0;
    double v_b = 0.0;
    
    cout << "\n===============================================\n";
    cout << "GRADIENT DESCENT WITH MOMENTUM\n";
    cout << "===============================================\n";
    cout << "Learning rate (gamma): " << learning_rate << "\n";
    cout << "Momentum (alpha): " << momentum << "\n";
    cout << "Max iterations: " << max_iterations << "\n";
    cout << "Tolerance: " << tolerance << "\n";
    cout << "Training samples: " << n << "\n";
    cout << "===============================================\n\n";
    
    for (int iter = 1; iter <= max_iterations; iter++) {
        // Tính gradient
        double grad_w, grad_b;
        computeGradients(X, Y, w, b, grad_w, grad_b);
        
        // Lưu giá trị cũ
        double w_old = w;
        double b_old = b;
        
        // Cập nhật vận tốc với momentum
        v_w = momentum * v_w + learning_rate * grad_w;
        v_b = momentum * v_b + learning_rate * grad_b;
        
        // Cập nhật tham số
        w = w - v_w;
        b = b - v_b;
        
        // Tính loss hiện tại
        double current_loss = totalLoss(X, Y, w, b);
        
        // In thông tin
        if (iter <= 5 || iter % 100 == 0 || iter == max_iterations) {
            cout << "Iter " << setw(4) << iter 
                 << ": w = " << setw(10) << fixed << setprecision(6) << w
                 << ", b = " << setw(10) << fixed << setprecision(6) << b
                 << ", Loss = " << setw(10) << fixed << setprecision(6) << current_loss
                 << ", grad_w = " << setw(10) << fixed << setprecision(6) << grad_w
                 << ", grad_b = " << setw(10) << fixed << setprecision(6) << grad_b << "\n";
        }
        
        // Kiểm tra hội tụ
        double delta = sqrt(pow(w - w_old, 2) + pow(b - b_old, 2));
        if (delta < tolerance) {
            cout << "\n>>> Converged after " << iter << " iterations!\n";
            cout << ">>> Delta = " << scientific << delta << "\n";
            break;
        }
        
        if (iter == max_iterations) {
            cout << "\n>>> Reached maximum iterations.\n";
        }
    }
    
    cout << "\n===============================================\n";
    cout << "FINAL RESULTS\n";
    cout << "===============================================\n";
    cout << "Optimal w = " << fixed << setprecision(6) << w << "\n";
    cout << "Optimal b = " << fixed << setprecision(6) << b << "\n";
    cout << "Final Loss = " << fixed << setprecision(6) << totalLoss(X, Y, w, b) << "\n";
    cout << "===============================================\n";
}

// Hàm dự đoán
int predict(double x, double w, double b) {
    double z = w * x + b;
    double prob = sigmoid(z);
    return (prob >= 0.5) ? 1 : 0;
}

// Đánh giá độ chính xác
double accuracy(const vector<double>& X, const vector<int>& Y, double w, double b) {
    int correct = 0;
    for (int i = 0; i < X.size(); i++) {
        if (predict(X[i], w, b) == Y[i]) {
            correct++;
        }
    }
    return (double)correct / X.size() * 100.0;
}

int main() {
    // Tạo dữ liệu mẫu cho bài toán phân loại nhị phân
    // Y = 1 nếu X > 0, Y = 0 nếu X <= 0 (với một chút nhiễu)
    
    vector<double> X_train;
    vector<int> Y_train;
    
    // Tạo dữ liệu huấn luyện
    random_device rd;
    mt19937 gen(42); // seed cố định để tái tạo
    normal_distribution<> noise(0.0, 0.3);
    
    // Class 0: X âm
    for (int i = 0; i < 30; i++) {
        X_train.push_back(-2.0 + i * 0.1 + noise(gen));
        Y_train.push_back(0);
    }
    
    // Class 1: X dương
    for (int i = 0; i < 30; i++) {
        X_train.push_back(0.2 + i * 0.1 + noise(gen));
        Y_train.push_back(1);
    }
    
    cout << "===============================================\n";
    cout << "LOGISTIC REGRESSION - CROSS ENTROPY LOSS\n";
    cout << "===============================================\n";
    cout << "Ham mat mat: f(x,y) = {-log10(sigmoid(x))     if y=1\n";
    cout << "                      {-log10(1-sigmoid(x))   if y=0\n";
    cout << "Voi sigmoid(x) = 1/(1+e^(-x))\n";
    cout << "===============================================\n";
    
    // In một số mẫu dữ liệu
    cout << "\nMot so mau du lieu:\n";
    cout << "-----------------------------------------------\n";
    for (int i = 0; i < 5; i++) {
        cout << "X[" << i << "] = " << setw(8) << fixed << setprecision(3) 
             << X_train[i] << ", Y[" << i << "] = " << Y_train[i] << "\n";
    }
    cout << "...\n";
    for (int i = 55; i < 60; i++) {
        cout << "X[" << i << "] = " << setw(8) << fixed << setprecision(3) 
             << X_train[i] << ", Y[" << i << "] = " << Y_train[i] << "\n";
    }
    
    // Khởi tạo tham số
    double w = 0.0;  // weight
    double b = 0.0;  // bias
    
    // Tham số tối ưu hóa
    double learning_rate = 0.1;
    double momentum = 0.9;
    int max_iterations = 1000;
    double tolerance = 1e-6;
    
    // Chạy Gradient Descent với Momentum
    gradientDescentMomentum(X_train, Y_train, w, b, 
                           learning_rate, momentum, 
                           max_iterations, tolerance);
    
    // Đánh giá kết quả
    cout << "\n===============================================\n";
    cout << "EVALUATION\n";
    cout << "===============================================\n";
    
    double acc = accuracy(X_train, Y_train, w, b);
    cout << "Accuracy on training set: " << fixed << setprecision(2) << acc << "%\n";
    
    // Test một số điểm
    cout << "\nMot so du doan:\n";
    cout << "-----------------------------------------------\n";
    vector<double> test_points = {-2.0, -1.0, 0.0, 1.0, 2.0};
    for (double x : test_points) {
        double z = w * x + b;
        double prob = sigmoid(z);
        int pred = predict(x, w, b);
        cout << "X = " << setw(6) << fixed << setprecision(2) << x
             << " => z = " << setw(8) << fixed << setprecision(4) << z
             << ", P(Y=1) = " << setw(6) << fixed << setprecision(4) << prob
             << ", Predict: " << pred << "\n";
    }
    cout << "===============================================\n";
    
    return 0;
}
