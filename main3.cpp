/*
* https://www.qoosky.io/techs/2798a45608  -> バウンディングボックス、最小内包円 例がある。
* https://docs.opencv.org/3.4/df/d0d/tutorial_find_contours.html
* https://tora-k.com/2019/06/23/binary-opencv/  -> 【C++】OpenCVを用いた画像の二値化プログラム【画像処理】
* http://cvwww.ee.ous.ac.jp/opencv_practice4/  -> OpenCV 画像処理演習 ― 図形描画編
* https://cvtech.cc/centroid/ -> 重心の求め方
*
* main3.cpp
*/

#include <string>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "conto_builder.hpp"

bool compare_Cource_Plan_dist_min(Cource_Plan &s1,Cource_Plan &s2){
    return s1.dist < s2.dist;
}

int main() {

    //std::string img_path="../house_map.pgm";
    //std::string img_path="../house_map-alt.pgm";
    //std::string img_path="../my_map.pgm";
    //std::string img_path="/home/nishi/map_builder.pgm";

    ContoBuilder cbuilder;

    bool isCourceDisp=true;
    #define USE_RGBD
    #if defined(USE_RGBD)
        // RGBD Camera Mapping
        std::string img_path="../house_map-alt.pgm";
        int px = 87 ;
        int py = 94;
        double threshold=250;      // white RGDカメラの場合、白領域(自由領域)が残るので、250
    #else
        // Stero Camera Mapping
        std::string img_path="../my_map.pgm";
        int px = 60;
        int py = 30;
        double threshold=200;       // gray
    #endif

    cbuilder.init(img_path,threshold);


    //cbuilder.get_bolb(100,100);

    cbuilder.get_bolb(px,py,isCourceDisp);   //  .yaml から原点の位置を持ってこないと、 .pgm 毎に異なる。
    //cbuilder.get_bolb(py,px);   // .yaml から原点の位置を持ってこないと、 .pgm 毎に異なる。

    //cbuilder.get_bolb(400,100);

    while(1){
        sleep(1);
        std::cout << " loop" << std::endl;
    }

    return 0;
}


