/*
* https://www.qoosky.io/techs/2798a45608  -> バウンディングボックス、最小内包円 例がある。
* https://docs.opencv.org/3.4/df/d0d/tutorial_find_contours.html
* https://tora-k.com/2019/06/23/binary-opencv/  -> 【C++】OpenCVを用いた画像の二値化プログラム【画像処理】
* http://cvwww.ee.ous.ac.jp/opencv_practice4/  -> OpenCV 画像処理演習 ― 図形描画編
*
* main.cpp
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::Mat  binary,blur;
    //cv::Mat src = cv::imread("aaa.png", cv::IMREAD_COLOR);
    cv::Mat gray = cv::imread("../house_map.pgm", cv::IMREAD_GRAYSCALE);
    //cv::Mat gray = cv::imread("../house_map-alt.pgm", cv::IMREAD_GRAYSCALE);

    // エッジ検出はノイズの影響を受けやすいため平滑化しておきます。
    cv::blur(gray, blur, cv::Size(3,3));
    //cv::blur(gray, blur, cv::Size(2,2));

    // 2値化データを使います。
    //cv::threshold(gray,binary,250,255,cv::THRESH_BINARY);
    cv::threshold(blur,binary,250,255,cv::THRESH_BINARY);


    // cv::findContours は第一引数を破壊的に利用するため imshow 用に別変数を用意しておきます。
    cv::Mat binary2 = binary.clone();

    // cv::Point の配列として、輪郭を計算します。
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    //cv::findContours(canny, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);


    std::cout << contours.size() << std::endl; //=> 36


    //std::cout << contours[contours.size() - 1][0] << std::endl; //=> [154, 10]


    //printf("%s",contours[0]);
    //auto ss = contours[0];
    //print(ss);
    //std::vector<cv::Point_<int>> v = contours[0];
    //printf("%ld",v.size());

    int pi=0;
    long int max_cnt=0;

    for( size_t i = 0; i< contours.size(); i++ ) {
        std::vector<cv::Point_<int>> v = contours[i];
        long int j=v.size();
        if(j > max_cnt){
            pi=i;
            max_cnt = j;
        }
    }

    std::cout << "pi:"<< pi<<" max_cnt:"<<  max_cnt << std::endl; //=> 36

    // 輪郭を可視化してみます。分かりやすさのため、乱数を利用して色付けします。
    cv::Mat drawing = cv::Mat::zeros(gray.size(), CV_8UC3);
    cv::RNG rng(12345);

    cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256));

    //#define TEST1
    #if defined(TEST1)
        cv::imshow("gray", gray);
        for( size_t i = 0; i< contours.size(); i++ ) {
            cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256));
            cv::drawContours(drawing, contours, (int)i, color);
            cv::imshow("drawing", drawing);
            cv::waitKey(300);
        }
        cv::imshow("drawing", drawing);
        cv::waitKey(0);
    #endif


    //#define TEST2
    #if defined(TEST2)
        // http://cvwww.ee.ous.ac.jp/opencv_practice4/
        cv::fillPoly(drawing, contours[pi], cv::Scalar(0, 255, 255), cv::LINE_AA);
        cv::imshow("gray", gray);
        //cv::imshow("blur", blur);
        //cv::imshow("canny", canny2);
        cv::imshow("drawing", drawing);
        cv::waitKey(0);
    #endif

    #define TEST3
    #if defined(TEST3)
        cv::imshow("gray", gray);
        cv::imshow("blur", blur);
        for( size_t i = 0; i< contours.size(); i++ ) {
            cv::Scalar color = cv::Scalar(rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256));
            // http://cvwww.ee.ous.ac.jp/opencv_practice4/
            //cv::fillPoly(drawing, contours[i], cv::Scalar(0, 255, 255), cv::LINE_AA);
            long int j=contours[i].size();
            std::cout << "i:"<< i <<" cnt:"<<  j << std::endl; //=> 36
            cv::fillPoly(drawing, contours[i], color, cv::LINE_AA);
            cv::imshow("drawing", drawing);
            cv::waitKey(300);
        }
        cv::imshow("drawing", drawing);
        cv::waitKey(0);
    #endif

	gray.release();
	binary.release();
    blur.release();

    return 0;
}


