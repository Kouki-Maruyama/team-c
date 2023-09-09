#include"matching.hpp"
// ============================↓↓↓編集可能↓↓↓========================== //

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j;                                                           // カウンター
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

        // 初期化

        // 同時生成行列の作成
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                com[temp_g[j][i]][temp_g[j][i + 1]]++;
                com[temp_g[j][i + 1]][temp_g[j][i]]++;
            }
        }

        /* 担当：宇佐美 */

        /*new(20230909)--------------------------------------------------*/
        /*同時生起行列で求めた座標をプロットする画像の生成
        /*create new templete-images*/
        
        cv::Mat im_out = cv::Mat<uchar>(TMP_SIZE_H,TMP_SIZE_W);　      //画像の生成

        for( j = 1; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                im_out.at<uchar>[j][i] = temp_g[j][i];                //さきにGSのテンプレートと同じものにする
        }
    }
    /*--------------------------------------------------------------------*/

        /* 発生頻度の低い画素の座標を探索，保存 */

        int CP_SIZE = 100;
        COM_POINT com_point[CP_SIZE];

        // 頻度値1の画素画素対を求めるプログラム
        int c = 0;
        for( j = 0 ; j < COM_SIZE; j++ ){
            for( i = 0 ; i < COM_SIZE; i++ ){

                if( c >= CP_SIZE )
                    break;

                if( com[j][i] == 1 ){   // 頻度値１の場合の画素対を保存
                    com_point[c].p = i;
                    com_point[c].q = j;
                    c++;
                }
            }
        }

        // 求められた画素の組を探すプログラム
        c = 0;
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W - 1; i++ ){      // 領域外探索を避けている
                
                if( c >= REFERENCE_SIZE )
                    break;

                if( temp_g[j][i] == com_point[c].p && temp_g[j][i + 1] == com_point[c].q ){   // 隣り合っている画素値が一致しているか否か
                    reference_x[c] = i;
                    reference_y[c] = j;

                    /* new 20230909--------------------------------*/
                    im_out.at<uchar>[j][i] = 255;       //ここで求められた画素ペアの始点を255の白画素に変換
                    /*---------------------------------------------*/

                    c++;
                }
            }
        }
    //save image
    cv::imwrite("Feature point extraction image.png", im_out);　//同時生起行列の全てのプログラムが終了した際に画像を出力

    }
    global_count++;

    // SSDAによる探索                              
    out_point = SSDA_R(input_g, temp_g);                 // 参照画素を用いたSSDA

    return out_point;
}

Point SSDA_R(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W]){

    int TMAP_SIZE_H, TMAP_SIZE_W;               // 相違度マップのサイズ
    TMAP_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    TMAP_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    int TMAP[TMAP_SIZE_H][TMAP_SIZE_W];         // 相違度マップ
    int i, j, J, I, c;                          // カウンター
    int Smin, thr, flag;                        // カウンター
    Point min;                                  // 相違度マップの最小値を保存
    
    // 相違度マップの初期化
    TMAP[j][i] = {0};

    // 相違度マップの生成
    for(j = 0; j < TMAP_SIZE_H; j++){
        for(i = 0; i < TMAP_SIZE_W; i++){

            flag = 0;

            // 画素選択型マッチング
            for(c = 0; c < REFERENCE_SIZE; c++){

                I = reference_x[c];
                J = reference_y[c];

                TMAP[j][i] += ( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) )
                            * ( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) );

                if( thr < TMAP[j][i] ){
                    flag = 1;
                    break;
                }
            }

            if( j == 0 && i == 0 ){
                thr = TMAP[j][i];
            }
            else if( flag == 0 ){
                thr = TMAP[j][i];
            }
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
    
    return min;
}
// ============================↑↑↑編集可能↑↑↑========================== //
