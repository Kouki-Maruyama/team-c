#include"matching.hpp"
// ============================↓↓↓編集可能↓↓↓========================== //

// グローバル変数の宣言
int global_count = 0;
int pattern = 0;
// int REFERNCE_SIZE = 50;           
int com[COM_SIZE][COM_SIZE];      
int reference_x[REFERENCE_SIZE];  
int reference_y[REFERENCE_SIZE]; 


Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, c;                                                        // カウンター
    unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W];                  // グレースケール変換用
    unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W];                       // グレースケール変換用
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    // グレースケール変換(入力画像)
    for( j = 0; j < INPUT_SIZE_H; j++ ){
        for( i = 0; i < INPUT_SIZE_W; i++ ){      
            input_g[j][i] = 0.2126 * input[0][j][i] + 0.7152 * input[1][j][i] + 0.0722 * input[2][j][i];
        }
    }

    // 初回のみの処理
    printf("\nglobal_count -> %d\n", global_count);
    if(global_count == 0){

        // パターン判別
        if( TMP_SIZE_W == 150 )
            pattern = 1;
        else if ( TMP_SIZE_W == 160 )
            pattern = 2;
        else
            pattern = 3;

        // グレースケール変換(テンプレート画像)
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                temp_g[j][i] = 0.2126 * temp[0][j][i] + 0.7152 * temp[1][j][i] + 0.0722 * temp[2][j][i];
            }
        }
        
        // 担当：石川
        // 同時生成行列の作成
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                com[temp_g[j][i + 1]][temp_g[j][i]]++;      // 水平方向のペアを追加
                com[temp_g[j][i]][temp_g[j][i + 1]]++;
            }
        }

        /*
        printf("check temp_g\n");
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                if( temp_g[j][i] == 13 && temp_g[j][i + 1] == 1 )
                    printf("temp_g[%d][%d] -> %d\n",j, i, temp_g[j][i]);
                // printf("%d ", temp_g[j][i]);
            }
            // printf("\n");
        }
        */

        /*
        printf("check com\n");
        c = 0;
        for( j = 0; j < COM_SIZE; j++ ){
            for( i = 0; i < COM_SIZE; i++ ){
                if( com[j][i] == 1 )
                    c++;
                // printf("%d ", com[j][i]);       
            }
            // printf("\n");
        }
        printf("sum of com 1 : %d\n", c);
        */

        // 担当：宇佐美
        // 発生頻度の低い画素の座標を探索，保存

        int CP_SIZE = 4314;         // 頻度値1のペア数
        COM_POINT com_point[CP_SIZE];

        // 同時世起行列から頻度値1のペアを探索
        c = 0;
        for( j = 0 ; j < COM_SIZE; j++ ){
            for( i = 0 ; i < COM_SIZE; i++ ){

                if( c >= CP_SIZE )
                    break;

                if( com[j][i] == 1 ){   // 頻度値１の場合のペアを保存
                    com_point[c].p = i;
                    com_point[c].q = j;
                    c++;
                }
            }
        }
        
        /*
        printf("check com_point\n");
        for( i = 0; i < CP_SIZE; i++ ){
            printf("(%d, %d)\n", com_point[i].p, com_point[i].q);
        }
        */
        
        // 選択ペアの間引き処理
        int interbal = CP_SIZE / REFERENCE_SIZE;
        COM_POINT thin_point[REFERENCE_SIZE];

        for(i = 0; i < REFERENCE_SIZE; i++){
            thin_point[i].p = com_point[i + (interbal * i)].p;
            thin_point[i].q = com_point[i + (interbal * i)].q;
        } 

        /*
        printf("check thin_point\n");
        for( i = 0; i < REFERENCE_SIZE; i++ ){
            printf("(%d, %d)\n", thin_point[i].p, thin_point[i].q);
        }
        */

        // 選択ペアのテンプレートにおける座標を探索
        for( c = 0; c < REFERENCE_SIZE; c++ ){
            for( j = 0; j < TMP_SIZE_H; j++ ){
                for( i = 0; i < TMP_SIZE_W - 1; i++ ){      // 領域外探索を避けている

                    // 隣り合っている画素値が一致しているか否か(水平方向)
                    if( (temp_g[j][i] == thin_point[c].p && temp_g[j][i + 1] == thin_point[c].q) || (temp_g[j][i + 1] == thin_point[c].p && temp_g[j][i] == thin_point[c].q) ){ 
                        reference_x[c] = i;
                        reference_y[c] = j;
                        
                        // printf("reference_point[%d] -> (%d, %d)\n", c, reference_x[c], reference_y[c]);
                    }
                }
            }
        }

        /*
        printf("check reference_point\n");
        for( i = 0; i < REFERENCE_SIZE; i++ ){
            printf("(%d, %d)\n", reference_x[i], reference_y[i]);
        }
        */

        /*
        // 参照画素の座標を描画, 表示
        cv::Mat im_out(cv::Size(TMP_SIZE_W, TMP_SIZE_H), CV_8UC1);

        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                im_out.at<uchar>(j, i) = temp_g[j][i];
            }
        }
        
        for( c = 0; c < REFERENCE_SIZE; c++ ){
            for( j = 0; j < TMP_SIZE_H; j++ ){
                for( i = 0; i < TMP_SIZE_W; i++ ){

                    if( i == reference_x[c] && j == reference_y[c] )
                        im_out.at<uchar>(j, i) = 0;
                }
            }   
        }
        cv::imwrite("img_temp.png", im_out);
        */

    }
    global_count++;

    // SSDAによる探索                              
    out_point = SSDA_R(input_g, temp_g);                 // 画素選択型SSDA
    // out_point = SAD_R(input_g, temp_g);                     // 画素選択型SAD

    return out_point;
}

Point SSDA_R(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, c;                                     // カウンター
    // int thr, flag;

    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    int loss[loss_SIZE_H][loss_SIZE_W];                    // 相違度マップ
    int loss_min;                                          // 相違度マップの最小値
    Point min;                                             // 検出位置
    
    // 初期化
    // thr = 1000000;

    // 相違度マップの生成
    for(j = 0; j < loss_SIZE_H; j++){
        for(i = 0; i < loss_SIZE_W; i++){

            // 初期化
            loss[j][i] = 0;
            // flag = 0;

            // ラスタスキャン(選択画素のみ)
            for(c = 0; c < REFERENCE_SIZE; c++){

                I = reference_x[c];
                J = reference_y[c];

                /*
                // 一致している個数を記憶
                if( input_g[J + j][I + i]  == temp_g[J][I]){
                    loss[j][i]++;
                }
                */

                loss[j][i] += ( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) )
                            + ( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) );

                // if( thr < loss[j][i] ){
                //     flag = 1;
                //     break;
                // }
            }

            // if( flag == 0 ){
            //     thr = loss[j][i];
            // }
        }
    }

    /*
    printf("check loss\n");
    for( j = 0; j < loss_SIZE_H; j++ ){
        for ( i = 0; i < loss_SIZE_W; i++ ){
            printf("%d ", loss[j][i]);
        }
        printf("\n");
    }
    */

    // 相違度の最小値を求める
    // 初期化
    min.x = 0; min.y = 0; 
    loss_min = loss[0][0];

    // ラスタスキャン
    for( j = 0; j < loss_SIZE_H; j++ ){
        for( i = 0; i < loss_SIZE_W; i++ ){

            // SSD
            if(loss_min > loss[j][i]){

                // 最小値の更新
                loss_min = loss[j][i]; 
                min.x = i; min.y = j;
            }
            
            /*
            // 一致した個数
            if(loss_min < loss[j][i]){

                // 最大値の更新
                loss_min = loss[j][i]; 
                min.x = i; min.y = j;
            }
            */
        }
    }
    
    return min;
}


Point SAD_R(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, c;                                        // カウンター

    int loss_SIZE_H, loss_SIZE_W;                             // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;
    double loss[loss_SIZE_H][loss_SIZE_W];                    // 相違度マップ
    double loss_min;                                          // 相違度マップの最小値
    Point min;                                                // 検出位置

    // 全画素全探索のテンプレートマッチング SAD
    /*
    for( j = 0; j < loss_SIZE_H; j++ ){
        for( i = 0; i < loss_SIZE_W; i++ ){

            // lossの初期化
            loss[j][i] = 0.0;

            // ラスタスキャン
            for( J = 0; J < TMP_SIZE_H ; J++ ){
                for( I = 0; I < TMP_SIZE_W ; I++ ){

                    loss[j][i] += sqrt( ( input_g[J+j][I+i] - temp_g[J][I] ) * ( input_g[J+j][I+i] - temp_g[J][I] ) );
                }
            }
        }
    }
    */

    // 選択画素探索のテンプレートマッチング SAD_R
    for( j = 0; j < loss_SIZE_H; j++ ){
        for( i = 0; i < loss_SIZE_W; i++ ){

            // lossの初期化
            loss[j][i] = 0.0;

            // ラスタスキャン(選択画素のみ)
            for(c = 0; c < REFERENCE_SIZE; c++){

                I = reference_x[c];
                J = reference_y[c];

                loss[j][i] += sqrt( ( input_g[J+j][I+i] - temp_g[J][I] ) * ( input_g[J+j][I+i] - temp_g[J][I] ) );
            }
        }
    }

    // 相違度の最小値を求める
    // 初期化
    min.x = 0; min.y = 0; 
    loss_min = loss[0][0];

    // ラスタスキャン
    for( j = 0; j < loss_SIZE_H; j++ ){
        for( i = 0; i < loss_SIZE_W; i++ ){

            if(loss_min > loss[j][i]){

                // 最小値の更新
                loss_min = loss[j][i]; 
                min.x = i; min.y = j;
            }
        }
    }

    return min;
}

// ============================↑↑↑編集可能↑↑↑========================== //