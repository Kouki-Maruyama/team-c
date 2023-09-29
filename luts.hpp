#ifndef LUTS_H_
#define LUTS_H_

// ============================↓↓↓編集可能↓↓↓========================== //

#define COM_SIZE 256              // 同時生起行列のサイズ
#define SAVE_SIZE 20              // 保存サイズ

#define loss1_SIZE_H 380          // 入力画像のサイズとテンプレート画像のサイズの差分
#define loss1_SIZE_W 490
#define loss2_SIZE_H 318
#define loss2_SIZE_W 360
#define loss3_SIZE_H 320
#define loss3_SIZE_W 540

int global_count ;                 // カウンター
int pattern ;                      // パターン判別用
int found_point_x ;                // 探索開始位置
int found_point_y ;                // 探索開始位置
int reference_size ;               // TMの参照画素数
int reference_x[SAVE_SIZE] ;       // 参照画素の座標を保存
int reference_y[SAVE_SIZE] ;       // 参照画素の座標を保存

// ============================↑↑↑編集可能↑↑↑========================== //

#endif