#include <iostream>
#include<opencv2/opencv.hpp>
#include"tools.h"
#include"energy.hpp"
#include"pso.hpp"
#include<vector>
using namespace std;
using namespace cv;


int main()
{
    Mat disp,truedisp,i1,i2;
    loadMatrix("data/disp.txt",disp);
    loadMatrix("data/truedisp.txt",truedisp);
    loadMatrix("data/i1.txt",i1);
    loadMatrix("data/i2.txt",i2);
    Energy *energy=new Energy(i1,i2,truedisp);
    PSO::gBest=disp;
    PSO::gBestCost=energy->getEnergy(disp);
    PSO::energy=energy;
    cout<<"初始能量："<<PSO::gBestCost<<endl;
    //产生10个粒子;
    vector<PSO> psovec;
    for (int i=0; i<100; i++) {
        psovec.push_back(PSO(i));
    }
    for (int iter=0; iter<1000000; iter++) {
        for (int i=0; i<psovec.size(); i++) {
            PSO& pso=psovec[i];
            pso.update();
        }
        for (int i=0; i<psovec.size(); i++) {
            PSO& pso=psovec[i];
            if (pso.pBestCost<PSO::gBestCost) {
                cout<<"粒子"<<i<<"更新全局最优"<<endl;
                PSO::gBestCost=pso.pBestCost;
                pso.pBest.copyTo(PSO::gBest);
                cout<<PSO::gBest<<endl;
            }
        }
        cout<<"迭代第"<<iter<<"次,最优能量"<<PSO::gBestCost<<endl;
        energy->print_bad_points_percentage(PSO::gBest);
    }
    delete energy;
    
    //GraphCut g("data/disp.txt","data/truedisp.txt","data/i1.txt","data/i2.txt");
    
   
  
  
    
//cout<<ncc(0,0,5)<<endl;
//cout<<ncc(100,100,5)<<endl;
//    typedef Graph<int,int,int> GraphType;
//    GraphType *g = new GraphType(/*estimated # of nodes*/ 2, /*estimated # of edges*/ 1);
//
//    g -> add_node();
//    g -> add_node();
///
    
    
//    g -> add_tweights( 0,   /* capacities */  1, 5 );
//    g -> add_tweights( 1,   /* capacities */  2, 6 );
//    g -> add_edge( 0, 1,    /* capacities */  3, 4 );
//
//    int flow = g -> maxflow();sz
//    printf("Flow = %d\n", flow);
//    printf("Minimum cut:\n");
//    if (g->what_segment(0) == GraphType::SOURCE)
//        printf("node0 is in the SOURCE set\n");
//    else
//        printf("node0 is in the SINK set\n");
//    if (g->what_segment(1) == GraphType::SOURCE)
//        printf("node1 is in the SOURCE set\n");
//    else
//        printf("node1 is in the SINK set\n");
//
//    delete g;

return 0;
}
