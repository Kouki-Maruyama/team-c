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
------------------------------------------------------------------------------------------------------------
   //宇佐美
   //int CoM_min_point;          //同時生起行列の発生確率が最も低い値となる変数→頻度値１のみを探すように変更したため，改良
   int COM_MINE_SIZE;
   point Com_min[COM_MINE_SIZE];    //頻度値１の画素の組み合わせの座標を取り出す配列
   int reference_x[100];
   int reference_y[100];
  
  
   COM_POINT[100];    //構造体宣言

   //頻度値1の画素の組を求めるプログラム
  for( No = 0 ; No < 100 ; No++){
   for( j = 0 ; j < 256 ; j++ ){
      for( i = 0 ; i < 256 ; i++ ){
         if( seiki[j][i] == 1){   //頻度値が１の場合にプログラムが始まる
            COM_POINT[No].p = i;
            COM_POINT[No].q = j;
     }
    }
   } 
  }

   //求められた画素の組を探すプログラム
  for( No = 0 ; No < 100; No++){
   for( j = 0 ; j < TMP_SIZE_H; j++ ){
      for( i = 0; i < TMP_SIZE_W-1; i++ ){      //領域外探索を避けている
         if( tmp_g[j][i] == COM_POINT[No].p && tmp[j][i+1] == COM_POINT[No].q ){   //隣り合っている画素値が一致しているか否か
             reference_x[No] = i;
             reference_y[No] = j;
                  //一致している場合には座標を保存
         }else if(tmp[j][i+1] == COM_POINT[No].q && tmp[j][i] == COM_POINT[No].p){ //今回は隣り合う画素を点対称にして同時生起行列を求めているため，逆も検証
             reference_x = j;
             reference_y = i;  
         }
      } 
     }
  }
  ----------------------------------------------------------------------------------------------------------------
}
