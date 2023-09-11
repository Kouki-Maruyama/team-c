#ifndef LUTS_H_
#define LUTS_H_

// ============================↓↓↓編集可能↓↓↓========================== //

#define COM_SIZE 256                     // 同時生起行列のサイズ
#define REFERENCE_SIZE 100                // TMの参照画素数

extern int global_count;                 // カウンター
extern int pattern;                      // パターン判別用
// extern int REFERENCE_SIZE;               // TMの参照画素数
extern int com[COM_SIZE][COM_SIZE];      // 同時生起行列を保存
extern int reference_x[REFERENCE_SIZE];  // 参照画素の座標を保存
extern int reference_y[REFERENCE_SIZE];  // 参照画素の座標を保存

// 発生頻度の低い画素を保存する構造体
typedef struct COM_POINT{
    int p;                        // 始点画素
    int q;                        // 終点画素
}COM_POINT;

// ============================↑↑↑編集可能↑↑↑========================== //
#endif