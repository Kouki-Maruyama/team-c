#include"matching.hpp"
// ============================↓↓↓編集可能↓↓↓========================== //

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, k;                                                  // カウンター
    int R_SIZE;                                                         // カウンター
    unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W];                  // グレースケール変換用
    unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W];                       // グレースケール変換用
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    // グレースケール変換
    for( j = 1; j < CHANNEL; j++ ){
        for( i = 0; i < TMP_SIZE_H; i++ ){
            input_g[j][i] = 0.2126 * input[0][j][i] + 0.7152 * input[1][j][i] + 0.0722 * input[2][j][i];
            temp_g[j][i] = 0.2126 * temp[0][j][i] + 0.7152 * temp[1][j][i] + 0.0722 * temp[2][j][i];
        }
    }

    // 初回のみの処理
    if(global_count == 0){
        
        /* 担当：石川 */
        /* 同時生成行列の作成 */

        com = {0};

        // 同時生成行列の作成
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                com[tmp_g[j][i]][tmp_g[j][i+1]]++;
                com[tmp_g[j][i+1]][tmp_g[j][i]]++;
            }
        }

        /* 担当：宇佐美 */
        /* 発生頻度の低い画素の座標を探索，保存 */

        int C_SIZE = 100;
        COM_POINT com_point[C_SIZE];

        // 頻度値1の画素の組を求めるプログラム
        for( k = 0 ; k < C_SIZE; k++ ){
            for( j = 0 ; j < 256; j++ ){
                for( i = 0 ; i < 256 ; i++ ){
                    if( seiki[j][i] == 1 ){   // 頻度値が１の場合にプログラムが始まる
                        com_point[k].p = i;
                        com_point[k].q = j;
                    }
                }
            } 
        }

        // 求められた画素の組を探すプログラム
        for( k = 0; k < C_SIZE; k++ ){
            for( j = 0; j < TMP_SIZE_H; j++ ){
                for( i = 0; i < TMP_SIZE_W-1; i++ ){      // 領域外探索を避けている

                    if( tmp_g[j][i] == COM_POINT[k].p && tmp[j][i+1] == COM_POINT[k].q ){   // 隣り合っている画素値が一致しているか否か
                        reference_x[k] = i;
                        reference_y[k] = j;

                    // 一致している場合には座標を保存
                    }else if(tmp[j][i+1] == COM_POINT[k].q && tmp[j][i] == COM_POINT[k].p){ // 今回は隣り合う画素を点対称にして同時生起行列を求めているため，逆も検証
                        reference_x = j;
                        reference_y = i;  
                    }
                } 
            }
        }
    }
    global_count++;

    // SSDAによる探索
    out_point = SSDA(input_g, temp_g);                                    
    out_point = SSDA_R(input_g, temp_g);                 // 参照画素を用いたSSDA


    return out_point;
}

Point SSDA(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W]){

    int TMAP_SIZE_H, TMAP_SIZE_W;               // 相違度マップのサイズ
    TMAP_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    TMAP_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    int TMAP[TMAP_SIZE_H][TMAP_SIZE_W];         // 相違度マップ
    int i, j, J, I;                             // カウンター
    int Smin, thr, flag;                        // カウンター
    Point min;                                  // 相違度マップの最小値を保存
    
    // 相違度マップの初期化
    for(j = 0; j < TMAP_SIZE_H; j++){
        for(i = 0; i < TMAP_SIZE_W; i++){
            TMAP[j][i] = 0;
        }
    }

    // 相違度マップの生成
    for(j = 0; j < TMAP_SIZE_H; j++){
        for(i = 0; i < TMAP_SIZE_W; i++){

            flag = 0;

            for(J = 0; J < TMP_SIZE_H; J++){
                for(I = 0; I < TMP_SIZE_W; I++){

                    TMAP[j][i] += ( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) )
                                * ( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) );

                    if( thr < TMAP[j][i] ){
                        flag = 1;
                        break;
                    }
                }
            }

            if( j == 0 && i == 0 )
                thr = TMAP[j][i];
            else if( flag == 0 )
                thr = TMAP[j][i];
        }
    }

    Smin = TMAP[0][0];
    min.x = min.y = 0;

    // 相違度マップの最小値を算出
    for(j = 0; j < TMAP_SIZE_H; j++){
        for(i = 0; i < TMAP_SIZE_W; i++){

            if( Smin > TMAP[j][i] ){
                Smin = TMAP[j][i];
                min.x = i;
                min.y = j;
            }
        }
    }
    
    return min
}


Point SSDA_R(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W], Point refernse_point[R_SIZE]){


}
// ============================↑↑↑編集可能↑↑↑========================== //