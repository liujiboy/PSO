//
//  pso.cpp
//  pso
//
//  Created by  刘骥 on 16/1/30.
//  Copyright © 2016年  刘骥. All rights reserved.
//

#include "pso.hpp"
//静态成员变量必须按照以下方式初始化
Mat PSO::gBest;

double PSO::gBestCost=0;

Energy* PSO::energy=NULL;

PSO::PSO(int id,int min_v,int max_v,int min_p,int max_p)
{
    this->id=id;
    this->min_v=min_v;
    this->max_v=max_v;
    this->min_p=min_p;
    this->max_p=max_p;
    //gBest.copyTo(this->pBest);
    //this->pBestCost=gBestCost;
    //初始值用随机
    present.create(gBest.rows, gBest.cols, gBest.type());
    for (int row=0; row<present.rows;row++) {
        for(int col=0;col<present.cols;col++)
        {
            int p=rand()%this->max_p;
            present.at<double>(row,col)=p<this->min_p?min_p:p;
        }
    }
    present.copyTo(pBest);
    pBestCost=energy->getEnergy(present);
    //初始化速度
    this->v.create(gBest.rows, gBest.cols, gBest.type());
    for (int row=0; row<v.rows;row++) {
        for(int col=0;col<v.cols;col++)
        {
            int v=rand()%this->max_v;
            this->v.at<double>(row,col)=v<this->min_v?min_v:v;
        }
    }
}
void PSO::update()
{
    
    double w=1;
    double c1=2;
    double c2=3;
    //更新速度
    v = w * v + c1 * rand()/(RAND_MAX+0.0) * (pBest - present) + c2 * rand()/(RAND_MAX+0.0) * (gBest - present);
    //速度转换为[min_v,max_v]以内且为整数
    for (int row=0; row<v.rows;row++) {
        for(int col=0;col<v.cols;col++)
        {
            if (v.at<double>(row, col)>max_v) {
                v.at<double>(row, col)=max_v;
            }else if(v.at<double>(row, col)<min_v)
            {
                v.at<double>(row, col)=min_v;
            }
            v.at<double>(row, col)=int(v.at<double>(row, col));
        }
    }
  //  cout<<v<<endl;
    //更新位置
    present=present+v;
    for (int row=0; row<present.rows;row++) {
        for(int col=0;col<present.cols;col++)
        {
            if (present.at<double>(row, col)>max_p) {
                present.at<double>(row, col)=max_p;
            }else if(present.at<double>(row, col)<min_p)
            {
                present.at<double>(row, col)=min_p;
            }
        }
    }
    //cout<<present<<endl;
    double cost=energy->getEnergy(present);
   // cout<<cost<<endl;
    if(cost<pBestCost)
    {
        present.copyTo(pBest);
        pBestCost=cost;
        cout<<"粒子"<<id<<"更新了局部最优，新能量是"<<pBestCost<<endl;
    }
}
