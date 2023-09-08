#include"matching.hpp"
// ============================↓↓↓編集可能↓↓↓========================== //

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, k, n;                                               // カウンター
    double loss[INPUT_SIZE_H-TMP_SIZE_H+1][INPUT_SIZE_W-TMP_SIZE_W+1];  // 誤差保存用
    Point out_point;                                                    // 検出位置

    //seikigyouretunosakusei
    GLCM seiki;                                                         //GLCM
    static unsigned char tmp_g[TMP_SIZE_H][TMP_SIZE_W]; 
    cv::Mat tmp_gv(cv::Size(TMP_SIZE_W,TMP_SIZE_H)); 
    for( k = 1; k < CHANNEL; k++ ){
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                tmp[k][j][i] = tmp_cv.at<cv::Vec3b>(j,i)[k];
            }
            tmp_g[j][i]= 0.2126*tmp[0][j][i]+0.7152*tmp[1][j][i]+0.0722*tmp[2][j][i];
        }
    }

    if(seiki.num==0){
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                seiki.glcm[tmp_g[j][i]][tmp_g[j][i+1]]++
                seiki.glcm[tmp_g[j][i+1]][tmp_g[j][i]]++
            }
        }
    }   

    seiki.num++;



    // 初期化
    out_point.x = out_point.y = 0;

    // 全画素全探索のテンプレートマッチング SAD
    for( j = 0; j < ( INPUT_SIZE_H - TMP_SIZE_H + 1 ); j++ ){

        for( i = 0; i < ( INPUT_SIZE_W - TMP_SIZE_W + 1 ); i++ ){

            // lossの初期化
            loss[j][i] = 0.0;

            // ラスタスキャン
            for( k = 0; k < CHANNEL; k++ ){

                for( J = 0; J < TMP_SIZE_H ; J++ ){

                    for( I = 0; I < TMP_SIZE_W ; I++ ){

                        loss[j][i] += sqrt( ( input[k][J+j][I+i] - temp[k][J][I] ) * ( input[k][J+j][I+i] - temp[k][J][I] ) );
                    }
                }
            }
        }
    }

    // 相違度の最小値を求める
    out_point = get_Min(loss, (INPUT_SIZE_H-TMP_SIZE_H+1), (INPUT_SIZE_W-TMP_SIZE_W+1));

    return out_point;
}

Point get_Min(double arr[INPUT_SIZE_H-TMP_SIZE_H+1][INPUT_SIZE_W-TMP_SIZE_W+1],int h,int w){

    // 変数の宣言
    int i,j;                    // カウンター
    Point min;                  // 相違度マップの最小値を保存
    double loss;                // 相違度保存用の変数

    // 初期化
    min.x = 0; min.y = 0; loss = arr[0][0];

    // ラスタスキャン
    for(j=0;j<h;j++){

        for(i=0;i<w;i++){

            if(loss > arr[j][i]){

                // 最小値の更新
                loss = arr[j][i]; min.x = i; min.y = j;
            }
        }
    }

    return min;
}
// ============================↑↑↑編集可能↑↑↑========================== //