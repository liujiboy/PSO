//
//  pso.hpp
//  pso
//
//  Created by  刘骥 on 16/1/30.
//  Copyright © 2016年  刘骥. All rights reserved.
//

#ifndef pso_hpp
#define pso_hpp

#include <iostream>
#include<opencv2/opencv.hpp>
#include<vector>
#include "energy.hpp"
using namespace std;
using namespace cv;

class PSO{
public:
    int id; //粒子id
    Mat present; //粒子当前位置
    Mat v;//粒子速度
    Mat pBest; //取得局部最大值时的粒子位置
    double pBestCost;   //局部最大值
    int max_v;  //最大速度
    int min_v;  //最小速度
    int max_p;  //最大位置
    int min_p;  //最小位置
    //以下数据所有粒子相同
    static Mat gBest; //指向全局最大值的位置
    static double gBestCost; //全局最大值
    static Energy *energy; //能量函数
public:
    PSO(int id,int min_v=-5,int max_v=5,int min_p=0,int max_p=28);
    void update();
};

#endif /* pso_hpp */
