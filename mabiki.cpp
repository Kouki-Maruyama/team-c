//候補点を等価間隔で求めるプログラム

int reference_x[C_SIZE/2];    //絞った際のx座標の配列
int reference_y[C_SIZE/2];    //絞った際のy座標の配列
//※注意！！C_SIZEが偶数であることを確認しておくこと（奇数の場合小数点の問題が発生）

int count = 0;
for( i = 0; i < C_SIZE-2; i+=2 ){
    reference_x[count] = point_x[i];
    reference_y[count] = point_y[i];
    count += 1;
} 
