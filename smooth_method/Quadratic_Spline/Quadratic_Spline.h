// 二次样条函数实现
/* 
    x0-x3共有3个区间，共需要3个二次函数，共9个未知数
    x0,x3各自有一个二次函数经过，确定2个方程
    x1,x2需满足左右两个函数，确定4个方程
    x1,x2处导数连续，可确定2个方程
    另x1处二阶导为0，共9个方程
*/

#pragma once
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/SparseQR>
#include <vector>
#include <cmath>

class Quadratic_Spline {
public:
        // 初始化x，y的系数矩阵
        Eigen::MatrixXd X;
        Eigen::MatrixXd Y;
        std::vector<double> x, y;
        Eigen::MatrixXd A;
        int col;
        int row;
        // 求解二次曲线参数
        void getPara_useQR();
        // 根据输入的x返回近似y
        double output_Y(double x);
        // 获得系数矩阵
        void getArr();
        // 初始化X，Y
        void Init();
        // 绘制图像
        void plot_image();

};

void Quadratic_Spline::Init() {
        // 确定函数个数
        int func_count = x.size() - 1;
        // 每个二次函数都有3个参数
        row = func_count * 3;
        col = row;
        X.resize(row, col);
        Y.resize(row, 1);
        X.setZero();
        Y.setZero();
        //std::cout << "X: " << X << std::endl;
        //std::cout << "Y: " << Y << std::endl;

        
        A.resize(row, 1);
        A.setZero();
}

void Quadratic_Spline::getArr() {
        
        // 定义起点和终点的方程
        Eigen::RowVectorXd x_vector(col);
        x_vector.setZero();
        x_vector(0) = pow(x[0],2);
        x_vector(1) = x[0];
        x_vector(2) = 1;
        X.row(0) = x_vector;
        Y(0) = y[0];
        X(row - 1, col - 3) = pow(x.back(), 2);
        X(row - 1, col - 2) = x.back();
        X(row - 1, col - 1) = 1;
        Y(row-1) = y.back();
        //std::cout<<X<<std::endl;
        //std::cout<<Y<<std::endl;
        
    
        // X_1满足原方程
        Eigen::MatrixXd X_1 = Eigen::MatrixXd::Zero((x.size() - 2) * 2, col);
        Eigen::MatrixXd Y_1 = Eigen::MatrixXd::Zero((x.size() - 2) * 2, 1);
        int j1 = 0;
        for (int i = 0; i < X_1.rows(); i++) {
                if (i % 2 == 0) {
                        X_1(i, j1) = pow(x[j1 / 3 + 1], 2);
                        //std::cout<<X_1(i, j1)<<std::endl;
                        X_1(i, j1 + 1) = x[j1 / 3 + 1];
                        X_1(i, j1 + 2) = 1;
                        Y_1(i) = y[j1 / 3 + 1];
                }
                else
                {
                        j1 += 3;
                        X_1(i, j1) = pow(x[j1 / 3], 2);
                        //std::cout<<X_1(i, j1)<<std::endl;
                        X_1(i, j1 + 1) = x[j1 / 3];
                        X_1(i, j1 + 2) = 1;
                        Y_1(i) = y[j1 / 3];
                }
        }

        //std::cout<<X_1<<std::endl;
        //std::cout<<Y_1<<std::endl;
        // X_d满足一阶导数
        Eigen::MatrixXd X_d = Eigen::MatrixXd::Zero(x.size() - 2, col);
        int jd = 0;
        for (int i = 0; i < X_d.rows(); i++) {
                X_d(i, jd) = x[jd / 3 + 1] * 2;
                X_d(i, jd+1) = 1;
                X_d(i, jd+3) = -1*x[jd / 3 + 1] * 2;
                X_d(i, jd+4) = -1;
                jd += 3;
        }
        // 假设x0的二阶导数为0
        Eigen::MatrixXd X_dd = Eigen::MatrixXd::Zero(1, col);
        X_dd(0, 0) = 2;

        // 将X_1,X_d,X_dd拼接到X中
        X.block(1, 0, X_1.rows(), col) = X_1;
        X.block(X_1.rows() + 1, 0, X_d.rows(), col) = X_d;
        X.block(row-2, 0, 1, col) = X_dd;

        // 将Y_1拼接到Y中
        Y.block(1, 0, Y_1.rows(), 1) = Y_1;
        //std::cout<<X<<std::endl;
        //std::cout<<Y<<std::endl;

}

void Quadratic_Spline::getPara_useQR() {
    A = X.colPivHouseholderQr().solve(Y);

}




