#include <iostream>
#include <Eigen/Dense>

int main() {
    // Khởi tạo ma trận vuông thực
    Eigen::MatrixXd A(3, 3);
    A << -7, 9, 20,
         9, -7, 18,
         20, 18, -7;

    // Phân rã eigen
    Eigen::EigenSolver<Eigen::MatrixXd> es(A);

    // Lấy giá trị riêng và vector riêng
    Eigen::VectorXcd eigenvalues = es.eigenvalues();
    Eigen::MatrixXcd eigenvectors = es.eigenvectors();

    std::cout << "Ma tran A:\n" << A << "\n\n";
    std::cout << "Gia tri rieng:\n" << eigenvalues << "\n\n";
    std::cout << "Vector rieng:\n" << eigenvectors << "\n\n";

    // Tạo ma trận đường chéo D từ eigenvalues
    Eigen::MatrixXcd D = eigenvalues.asDiagonal();

    // Tính P * D * P^-1
    Eigen::MatrixXcd PDPinv = eigenvectors * D * eigenvectors.inverse();

    std::cout << "Ma tran P*D*P^-1:\n" << PDPinv << "\n";

    return 0;
}