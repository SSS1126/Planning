#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include </home/edy/scy/cppTest/smooth_method/cubic_spline/cubic_spline.h>

using namespace std;
using namespace Eigen;

int main() {
    cubic_Spline cs;
    cs.x = {3, 4.5, 7, 9};
    cs.y = {2.5, 1, 2.5, 0.5};
    int N = cs.x.size();
    cs.Init(N);
    cs.GetArr(N);
    cout<<cs.X<<endl;
    cout<<cs.Y<<endl;
    cs.GetPara(N);
    return 0;
}
