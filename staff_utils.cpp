#include"integration.hpp"
#include"staff_struct.hpp"
#include"staff_utils.hpp"

void bounding_box(Point point, int img_id, int t_H, int t_W){

    // 変数の宣言
    int i, j;
    char in_fname[256], out_fname[256];
    cv::Mat img;

    // パス文字列を作成
    sprintf(in_fname, "./data/img_%d.png", img_id);
    sprintf(out_fname, "./results/output_%d.png", img_id);

    // 画像読み込み
    img = cv::imread(in_fname,1);

    // バウンディングボックス付きの画像作成
    for( i = point.x; i < point.x + t_W; i++ ){

        img.at<cv::Vec3b>(point.y,i)[0] = 102; img.at<cv::Vec3b>(point.y,i)[1] = 0; img.at<cv::Vec3b>(point.y,i)[2] = 255;
        img.at<cv::Vec3b>(point.y+t_H-1,i)[0] = 102; img.at<cv::Vec3b>(point.y+t_H-1,i)[1] = 0; img.at<cv::Vec3b>(point.y+t_H-1,i)[2] = 255;
    }

    for( j = point.y; j < point.y + t_H; j++ ){

        img.at<cv::Vec3b>(j,point.x)[0] = 102; img.at<cv::Vec3b>(j,point.x)[1] = 0; img.at<cv::Vec3b>(j,point.x)[2] = 255;
        img.at<cv::Vec3b>(j,point.x+t_W-1)[0] = 102; img.at<cv::Vec3b>(j,point.x+t_W-1)[1] = 0; img.at<cv::Vec3b>(j,point.x+t_W-1)[2] = 255;
    }

    // 画像の保存
    cv::imwrite(out_fname,img);
}

double euclidean_distance(double x1, double y1, double x2, double y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}