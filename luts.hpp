#ifndef LUT_H_
#define LUT_H_
// ============================↓↓↓編集可能↓↓↓========================== //

int global_count = 0;        // カウンター
int com[256][256];           // 同時生起行列を保存
int reference_x[50];         // 参照画素の座標を保存
int reference_y[50];         // 参照画素の座標を保存

// 発生頻度の低い画素を保存する構造体
typedef struct COM_POINT{
    int p;                      // 始点画素
    int q;                      // 終点画素
}COM_POINT;

// ============================↑↑↑編集可能↑↑↑========================== //
#endif