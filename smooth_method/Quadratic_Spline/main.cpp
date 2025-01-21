#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include </home/edy/scy/cppTest/Lattice/smooth_method/Quadratic_Spline/Quadratic_Spline.h>

using namespace std;
using namespace Eigen;
int n;
int main(){
    Quadratic_Spline qs;
    qs.x = {3,4.5,7,9};
    qs.y = {2.5,1,2.5,0.5};
    qs.Init();
    qs.getArr();
    qs.getPara_useQR();
    cout<<qs.A<<endl;
    return 0;
}
    

