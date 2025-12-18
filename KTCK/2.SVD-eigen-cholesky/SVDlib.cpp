#include <iostream>
#include <Eigen/Dense>

int main() {
    // Khởi tạo ma trận ví dụ 3x2
    Eigen::MatrixXd A(3, 3);
    A << 5,7,9,3,6,9,2,4,6;

    // Phân rã SVD
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeFullU | Eigen::ComputeFullV);

    // Lấy các ma trận U, S, V
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::VectorXd S = svd.singularValues();
    Eigen::MatrixXd V = svd.matrixV();

    // In kết quả
    std::cout << "Ma tran U:\n" << U << "\n\n";
    std::cout << "Gia tri rieng (S):\n" << S << "\n\n";
    std::cout << "Ma tran V^t:\n" << V.transpose() << "\n";

    return 0;
}