//
//  energy.cpp
//  pso
//
//  Created by  刘骥 on 16/1/30.
//  Copyright © 2016年  刘骥. All rights reserved.
//

#include "energy.hpp"
//ncc cost function
//返回(row,col)处像素点，视差为d时的cost value
double Energy::ncc(int row,int col,int d)
{
    int col1 = col;
    int row1 = row;
    int col2 = col1 - d;
    int row2 = row1;
    if (col1 - r >= 0 && col1 + r < width && col2 - r >= 0 && col2 + r < width
        && row1 - r >= 0 && row1 + r < height && row2 - r >= 0 && row2 + r < height)
    {
        Mat cl;
        i1(Rect(col1-r,row1-r,2*r+1,2*r+1)).copyTo(cl);
        cl=cl.reshape(1,1);
        Mat cr;
        i2(Rect(col2-r,row2-r,2*r+1,2*r+1)).copyTo(cr);
        cr=cr.reshape(1,1);
        cl=cl-mean(cl);
        cr=cr-mean(cr);
        return 1-cl.dot(cr)/(norm(cl)*norm(cr));
    }else
    {
        return 2;
    }
}
//视差值fa和视差值fb的罚函数
double Energy::penalty(double fp,double fq)
{
    double e=abs(fp-fq);
    return e>1?1:e;
}
//能量函数的平滑项
double Energy::smooth(const Mat&disp,int row,int col)
{
    vector<idx> neighbor;
    get_neighbor(col,row,neighbor);
    double fp=disp.at<double>(row,col);
    double sum=0;
    for(vector<idx>::iterator q=neighbor.begin();q!=neighbor.end();q++)
    {
        
        double fq=disp.at<double>(q->row,q->col);
        sum+=penalty(fp, fq);
    }
    return sum;
}
//返回(row,col)的邻居索引,默认返回周围的8邻居
void Energy::get_neighbor(int row,int col,vector<idx>&neighbor,int s)
{
    for (int i = -s; i <= s; i++)
        for (int j = -s; j <= s; j++)
        {
            int col1=col+j;
            int row1=row+i;
            if (row1!=row&&col1!=col) {
                if(col1>=0&&col1<width&&row1>=0&&row1<height)
                {
                    
                    neighbor.push_back(idx(row1, col1));
                }
            }
        }
}
void Energy::buildDmaps()
{
    dmaps.resize(height,vector<vector<double> >(width,vector<double>(max_disparity+1,0)));
    for(int row=0;row<height;row++)
        for(int col=0;col<width;col++)
            for(int d=0;d<=max_disparity;d++)
            {
                dmaps[row][col][d]=ncc(row,col,d);
            }
}
Energy::Energy(Mat i1,Mat i2,Mat truedisp)
{
    this->i1=i1;
    this->i2=i2;
    this->truedisp=truedisp;
    width=i1.cols;
    height=i1.rows;
    cout<<"创建DSI"<<endl;
    buildDmaps();
    
}
//总能量函数，即待优化的函数
double Energy::getEnergy(const Mat&disp)
{
    double e=0;
    //由于测试好数据存在宽度18的边框，故此略过这个边框
    for(int row=border_size;row<height-border_size;row++)
        for(int col=border_size;col<width-border_size;col++)
        {
            e+=dmaps[row][col][disp.at<double>(row,col)]+smooth(disp,row,col);
        }
    return e;
}
//打印错误视差百分比
void Energy::print_bad_points_percentage(const Mat&disp)
{
    double n=width*height;
    Rect roi(border_size,border_size,width-2*border_size,height-2*border_size);
    double bad_points=countNonZero(abs(truedisp(roi)-disp(roi))>1);
    cout<<"错误视差百分比:"<<bad_points/n*100<<endl;
}
