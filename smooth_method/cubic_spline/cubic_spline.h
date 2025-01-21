#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SparseQR>
#include <vector>
#include <cmath>

using namespace std;
using namespace Eigen;

class cubic_Spline {
    public:
        MatrixXd X;
        MatrixXd Y;
        VectorXd Res;
        vector<double> x, y;

        int row, col;

        void Init(int N);
        void GetArr(int N);
        void GetPara(int N);
};


void cubic_Spline::Init(int N) {
    // 三次多项式共有4个参数，需要4N-4个方程
    row = (N-1) * 4;
    col = row;
    X.resize(row, col);
    X.setZero();
    Y.resize(row, 1);
    Y.setZero();

    Res.resize(row);
    Res.setZero();
}


void cubic_Spline::GetArr(int N) {
    // 定义起点和终点的方程，共2个方程
    X(0, 0) = pow(x[0], 3);
    X(0, 1) = pow(x[0], 2);
    X(0, 2) = x[0];
    X(0, 3) = 1;
    Y(0) = y[0];

    X(row - 1, col-4) = pow(x.back(), 3);
    X(row - 1, col-3) = pow(x.back(), 2);
    X(row - 1, col-2) = x.back();
    X(row - 1, col-1) = 1;
    Y(row - 1) = y.back();

    //X_1满足原方程，共N-2个点，2N-4个方程
    MatrixXd X_1 = MatrixXd::Zero((N-2)*2, col);
    MatrixXd Y_1 = MatrixXd::Zero((N-2)*2, 1);
    int j1 = 0;
    for (int i = 0; i < X_1.rows(); i++) {
        if (i % 2 == 0) {
            X_1(i, j1) = pow(x[j1 / 4 + 1], 3);
            X_1(i, j1 + 1) = pow(x[j1 / 4 + 1], 2);
            X_1(i, j1 + 2) = x[j1 / 4 + 1];
            X_1(i, j1 + 3) = 1;
            Y_1(i) = y[j1 / 4 + 1];
        } else {
            j1 += 4;
            X_1(i, j1) = pow(x[j1 / 4], 3);
            X_1(i, j1 + 1) = pow(x[j1 / 4], 2);
            X_1(i, j1 + 2) = x[j1 / 4];
            X_1(i, j1 + 3) = 1;
            Y_1(i) = y[j1 / 4];
        }
    }

    // X_d满足左右两个一阶导数，共N-2个点，N-2个方程
    MatrixXd X_d = MatrixXd::Zero(N-2,col);
    MatrixXd Y_d = MatrixXd::Zero(N-2, 1);
    int j_d = 0;
    for (int i = 0; i < X_d.rows(); i++) {
        X_d(i,j_d) = 3 * pow(x[j_d / 4 + 1], 2);
        X_d(i, j_d + 1) = 2 * x[j_d / 4 + 1];
        X_d(i, j_d + 2) = 1;
        X_d(i, j_d + 4) = -3 * pow(x[j_d / 4 + 1], 2);
        X_d(i, j_d + 5) = -2 * x[j_d / 4 + 1];
        X_d(i, j_d + 6) = -1;
        j_d += 4;
    }

    // X_dd在连接点处二阶导数连续，共N-2个点，共N-2个方程
    MatrixXd X_dd = MatrixXd::Zero(N-2,col);
    MatrixXd Y_dd = MatrixXd::Zero(N-2, 1);
    int j_dd = 0;
    for (int i = 0; i < X_dd.rows(); i++) {
        X_dd(i, j_dd) = 6 * x[j_dd / 4 + 1];
        X_dd(i, j_dd + 1) = 2;
        X_dd(i, j_dd + 4) = -6 * x[j_dd / 4 + 1];
        X_dd(i, j_dd + 5) = -2;
        j_dd += 4;
    }

    // 根据两个端点的自然边界条件，三阶导数为0，即a1 = 0,an = 0;
    X(row - 3, 0) = 6;
    X(row - 2, col - 4) = 6;

    // 将矩阵进行拼接
    
    X.block(1,0,X_1.rows(),col) = X_1;//1-4
    X.block(X_1.rows() + 1, 0, X_d.rows(), col) = X_d;//5-6
    X.block(X_1.rows() + X_d.rows() + 1, 0, X_dd.rows(),col) = X_dd;//7-8
    Y.block(1,0,Y_1.rows(),1) = Y_1;
}


void cubic_Spline::GetPara(int N) {
    // 采用QR分解求解参数
    Res = X.colPivHouseholderQr().solve(Y);
    cout<<"参数："<<Res<<endl;
}