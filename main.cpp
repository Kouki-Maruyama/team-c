// ライブラリのインクルード
#include"integration.hpp"

// メイン関数
int main(void){

    // 変数の宣言
    int i, j, k, n;                                                         // カウント用の関数
    double d;                                                               // 検出位置とGT間のユークリッド距離
    char input_path[256];                                                   // 入力画像へのパスを格納する文字列
    char tmp_path[256];                                                     // テンプレート画像へのパスを格納する文字列
    static unsigned char tmp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W];                     // テンプレート画像用の3次元配列
    cv::Mat tmp_cv(cv::Size(TMP_SIZE_W,TMP_SIZE_H),CV_8UC3);                // テンプレート画像読み込み用のMat型配列
    static unsigned char input [TOTAL_N][CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W];     // 入力画像用の3次元配列
    cv::Mat img_cv(cv::Size(INPUT_SIZE_W,INPUT_SIZE_H),CV_8UC3);            // 入力画像読み込み用のMat型配列
    Point out_point[TOTAL_N];                                               // 検出位置(座標)を保存する構造体配列
    std::chrono::system_clock::time_point start, end;                       // 時間計測用
    double time;                                                            // 実行時間

    // ======================================================================================= //
    Point gt[TOTAL_N];                                                      // GT格納用
    gt[0].x = 0;  gt[0].y = 0;
    gt[1].x = 0;  gt[1].y = 0;
    gt[2].x = 0;  gt[2].y = 0;
    gt[3].x = 0;  gt[3].y = 0;
    gt[4].x = 0;  gt[4].y = 0;
    gt[5].x = 0;  gt[5].y = 0;
    gt[6].x = 0;  gt[6].y = 0;
    gt[7].x = 0;  gt[7].y = 0;
    gt[8].x = 0;  gt[8].y = 0;
    gt[9].x = 0;  gt[9].y = 0;
    // ======================================================================================= //

    // テンプレート画像・入力画像の読み込み
    for( n = 0; n < TOTAL_N; n++ ){

        // パスの設定,Mat型(opencv)で画像を読み込み
        sprintf(input_path, "./data/img_%d.png", n);
        img_cv = cv::imread(input_path, 1);

        // uchar型(配列)へ変換・配列へ格納
        for( k = 0; k < CHANNEL; k++ ){
            for( j = 0; j < INPUT_SIZE_H; j++ ){
                for( i = 0; i < INPUT_SIZE_W; i++ ){
                    input[n][k][j][i] = img_cv.at<cv::Vec3b>(j,i)[k];
                }
            }
        }
    }
    sprintf( tmp_path, "./data/tmp.png");
    tmp_cv = cv::imread(tmp_path, 1);
    for( k = 0; k < CHANNEL; k++ ){
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                tmp[k][j][i] = tmp_cv.at<cv::Vec3b>(j,i)[k];
            }
        }
    }

    // 処理時間計測スタート
    start = std::chrono::system_clock::now();

    for( n = 0; n < TOTAL_N; n++ ){

        // マッチング処理
        out_point[n] = matching(input[n],tmp);

        // ======================================================================================= //
        // 検出位置とGT間のユークリッド距離を算出
        d = euclidean_distance((double)gt[n].x,(double)gt[n].y,(double)out_point[n].x,(double)out_point[n].y);
        // 結果を表示
        printf("<img_%d.png> : x = %d y = %d d = %f\n",n,out_point[n].x,out_point[n].y,d);
        //printf("<img_%d.png> : x = %d y = %d\n",n,out_point[n].x,out_point[n].y);
        // ======================================================================================= //
    }

    // 処理時間計測終了
    end = std::chrono::system_clock::now();
    time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0);
    printf("<time> : %lf[ms]\n", time);
    
    // 結果の出力(バウンディングボックスの描画)
    for( n = 0; n < TOTAL_N; n++ ){
        bounding_box(out_point[n], n, TMP_SIZE_H, TMP_SIZE_W);
    }

    // プログラム終了
    return 0;
}