#ifndef LUTS_H_
#define LUTS_H_

// ============================↓↓↓編集可能↓↓↓========================== //
#define COM_SIZE 256              // 同時生起行列のサイズ
#define SAVE_SIZE 100             // 保存サイズ

int global_count;                 // カウンター
int pattern;                      // パターン判別用
int reference_size;               // TMの参照画素数
int background_pixel;             // 背景画素
int com[COM_SIZE][COM_SIZE];      // 同時生起行列を保存
int reference_x[SAVE_SIZE];       // 参照画素の座標を保存
int reference_y[SAVE_SIZE];       // 参照画素の座標を保存

// 発生頻度の低い画素を保存する構造体
typedef struct COM_POINT{
    int p;                        // 始点画素
    int q;                        // 終点画素
}COM_POINT;
// ============================↑↑↑編集可能↑↑↑========================== //

#endif