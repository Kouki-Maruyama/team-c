#ifndef STAFFSTRUCT_H_
#define STAFFSTRUCT_H_

// ハイパーパラメータ
#define INPUT_SIZE_H 480
#define INPUT_SIZE_W 640
#define TMP_SIZE_H 160
#define TMP_SIZE_W 100
#define CHANNEL 3
#define TOTAL_N 5

// x,y座標を保存する構造体
typedef struct Point{
    int x;
    int y;
}Point;

#endif