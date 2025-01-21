#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

class discreateArr{
    public:
        MatrixXd A;
        MatrixXd L;
        void Cholesky(MatrixXd& A, MatrixXd& L, int N, int k);
};
void Cholesky(MatrixXd& A, MatrixXd& L, int N, int k) {
    // 将L初始化为N*N的矩阵
    if (N-k == 2) {
        L(k, k) = A(0,0);

        return;
    } 

    L(k,k) = sqrt(A(0,0));
    cout<<L(k,k)<<endl;

    MatrixXd L_col(N-k-1,1);
    //MatrixXd A_part = A(seq(k+1,N-1), seq(k+1,N-1));
    MatrixXd A_part = A.block(k+1, k+1, N-1, N-k-1);
    cout<<A_part<<endl;
    for (int i = 1; i < A.rows(); i++) {
        L(i,k) = A(i,k) / L(k,k);
        L_col(i-1,0) = L(i,k);
    }

    A_part = A_part - L_col * L_col.transpose();
    cout<<A_part<<endl;

    k++;
    Cholesky(A_part,L,N,k);

    cout<<L<<endl;
}

