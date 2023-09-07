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
      for( j = 0; j < 256 ; j++){
         for( i = 0; i < 256 ; i++){
            seiki[j][i] = 0;
         }
      }
   
    for( j = 0; j < TMP_SIZE_H; j++ ){
        for( i = 0; i < TMP_SIZE_W; i++ ){
            seiki[tmp_g[j][i]][tmp_g[j][i+1]]++;
            seiki[tmp_g[j][i+1]][tmp_g[j][i]]++;
        }
    }

   //宇佐美
   int min;          //同時生起行列の発生確率が最も低い値となる変数
   int min_j;       //minのj軸方向の画素値
   int min_i;      //minのi軸方向の画素値
   
   min = seiki[0][0];
   min_j = 0;
   min_i = 0;     //各値の初期化

   //頻度値が最も小さい（０より大きい）画素の組を求めるプログラム
   for( j = 0 ; j < 256 ; j++ ){
      for( i = 0 ; i < 256 ; i++ ){
         if( seiki[i][j] < min && seiki[i][j] > 0){   //現在保存している発生確率よりも小さい確率の場合，処理が行われる．
            min = seiki[i][j];
            min_j = j;
            min_i = i;         //全ての値の更新
         }
      }
   } 

   //求められた画素の組(min_xとmin_yが隣り合っている点）を探すプログラム
   int tokutyou_x = 0;
   int tokutyou_y = 0;   //求めたい画素の座標，及び初期化
   
   for( j = 0 ; j < TMP_SIZE_H; j++ ){
      for( i = 0; i < TMP_SIZE_W-1; i++ ){      //領域外探索を避けている
         if( tmp_g[j][i] == min_j && tmp[j][i+1] == min_i ){   //隣り合っている画素値が一致しているか否か
            tokutyou_x = i;
            tokutyou_y = j;      //一致している場合には座標を保存
         }else if(tmp[j][i+1] == min_i && tmp[j][i] == min_j){ //今回は隣り合う画素を点対称にして同時生起行列を求めているため，逆も検証
            tokutyou_x = j;
            tokutyou_y = i;     
         }
      } 
   }
   
}
