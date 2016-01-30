//
//  energy.hpp
//  pso
//
//  Created by  刘骥 on 16/1/30.
//  Copyright © 2016年  刘骥. All rights reserved.
//

#ifndef energy_hpp
#define energy_hpp
#include <iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
struct idx{
    int row;
    int col;
    idx(int row,int col)
    {
        this->row=row;
        this->col=col;
    }
};
class Energy{
private:
    Mat i1; //左视图
    Mat i2; //右视图
    Mat truedisp;   //真实视差图
    vector<vector<vector<double> > >dmaps;
    int width; //视图宽度
    int height; //视图高度
    int r=17; //窗口半径
    int max_disparity=28; //最大视差值
    int border_size=18; //图像的边框大小（此处不计算视差）
    
    //ncc cost function
    //返回(row,col)处像素点，视差为d时的cost value
    double ncc(int row,int col,int d);
    //视差值fa和视差值fb的罚函数
    double penalty(double fp,double fq);
    //能量函数的平滑项
    double smooth(const Mat&disp,int row,int col);
    //返回(row,col)的邻居索引,默认返回周围的8邻居
    void get_neighbor(int row,int col,vector<idx>&neighbor,int s=1);
    void buildDmaps();
public:
    Energy(Mat i1,Mat i2,Mat truedisp);
    //总能量函数，即待优化的函数
    double getEnergy(const Mat&disp);
    //打印错误视差百分比
    void print_bad_points_percentage(const Mat&disp);
};

#endif /* energy_hpp */
