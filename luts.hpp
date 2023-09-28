#ifndef LUTS_H_
#define LUTS_H_

// ============================↓↓↓編集可能↓↓↓========================== //

#define COM_SIZE 256              // 同時生起行列のサイズ
#define SAVE_SIZE 20              // 保存サイズ

int global_count ;                 // カウンター
int pattern ;                      // パターン判別用
int reference_size ;               // TMの参照画素数
int reference_x[SAVE_SIZE] ;       // 参照画素の座標を保存
int reference_y[SAVE_SIZE] ;       // 参照画素の座標を保存

// ============================↑↑↑編集可能↑↑↑========================== //

#endif