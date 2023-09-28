#ifndef LUTS_H_
#define LUTS_H_

// ============================↓↓↓編集可能↓↓↓========================== //

#define COM_SIZE 256              // 同時生起行列のサイズ
#define SAVE_SIZE 50              // 保存サイズ 
#define INPUT_CENTER_X 320        // 入力画像の中心位置
#define INPUT_CENTER_Y 240        // 入力画像の中心位置


int global_count;                 // カウンター
int pattern;                      // パターン判別用
int reference_size;               // TMの参照画素数
int background_pixel;             // 背景画素
int found_x, found_y;             // スタート位置（パターン2）
int com[COM_SIZE][COM_SIZE];      // 同時生起行列を保存
int reference_x[SAVE_SIZE];       // 参照画素の座標を保存
int reference_y[SAVE_SIZE];       // 参照画素の座標を保存

// ============================↑↑↑編集可能↑↑↑========================== //

#endif