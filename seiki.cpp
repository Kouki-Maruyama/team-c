#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<chrono>
#include<string.h>
#include<opencv2/opencv.hpp>

int main(void){
   int i, j, k, n;
   double d;      
   char tmp_path[256]; 
   static unsigned char tmp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W];  
   cv::Mat tmp_cv(cv::Size(TMP_SIZE_W,TMP_SIZE_H),CV_8UC3); 
   static unsigned char tmp_g[TMP_SIZE_H][TMP_SIZE_W]; 
   cv::Mat tmp_gv(cv::Size(TMP_SIZE_W,TMP_SIZE_H)); 


   sprintf( tmp_path, "./data/tmp.png");
   tmp_cv = cv::imread(tmp_path, 1);
   for( k = 1; k < CHANNEL; k++ ){
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                tmp[k][j][i] = tmp_cv.at<cv::Vec3b>(j,i)[k];
            }
            tmp_g[j][i]= 0.2126*tmp[0][j][i]+0.7152*tmp[1][j][i]+0.0722*tmp[2][j][i];
        }
    }

    int seiki[256][256];
    for( j = 0; j < TMP_SIZE_H; j++ ){
        for( i = 0; i < TMP_SIZE_W; i++ ){
            seiki[tmp_g[j][i]][tmp_g[j][i+1]]++;
            seiki[tmp_g[j][i+1]][tmp_g[j][i]]++;
        }
    }
    

}