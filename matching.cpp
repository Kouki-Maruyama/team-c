#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //
// パターン2のみ

#include"luts.hpp"

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    // 初回のみの処理
    if( global_count == 0 ){

        // 変数の宣言
        int i, j, k, n;
        int cp_size;

        // パターン判別
        if( TMP_SIZE_W == 150 ){      
        
            // 初期化
            pattern = 1;
            cp_size = 48;
            reference_size = 3;

             // 入力画像における背景画素の決定
            for( j = 0 ; j < INPUT_SIZE_H ; j += INPUT_SIZE_H - 2 ){
                for( i = 0 ; i < INPUT_SIZE_W ; i += INPUT_SIZE_W - 2 ){
                    if( input[1][j][i] == input[1][j][i + 1] ){
                        background_pixel = input[1][j][i];

                        i = INPUT_SIZE_W;
                        j = INPUT_SIZE_H;
                    }
                }
            }

            // 同時生成行列の作成
            int TMP_SIZE_W_1 = TMP_SIZE_W - 1;

            for( j = 0 ; j < TMP_SIZE_H ; j++ ){
                for( i = 0 ; i < TMP_SIZE_W_1 ; i++ ){
                    com[temp[1][j][i + 1]][temp[1][j][i]]++;
                    com[temp[1][j][i]][temp[1][j][i + 1]]++;
                }
            }

            // 発生頻度の低い画素の座標を探索，保存
            int thin_point_p[reference_size];
            int thin_point_q[reference_size];
            int interbal = cp_size / reference_size;

            k = 0;
            n = 1;
            for( j = 0 ; j < COM_SIZE ; j++ ){
                for( i = 0 ; i < COM_SIZE ; i++ ){

                    if( com[j][i] == 1 )         // 頻度値１のペア数を記録
                        k++;
                    
                    if( k == interbal * n ){     // 選択ペアの間引き処理
                        thin_point_p[n - 1] = i;
                        thin_point_q[n - 1] = j;

                        n++;
                    }
                }
            }

            // 選択ペアのテンプレートにおける座標を探索
            for( k = 0 ; k < reference_size ; k++ ){
                for( j = 0 ; j < TMP_SIZE_H ; j++ ){
                    for( i = 0 ; i < TMP_SIZE_W_1 ; i++ ){
                        
                        if( ( temp[1][j][i] == thin_point_p[k] && temp[1][j][i + 1] == thin_point_q[k] ) || 
                            ( temp[1][j][i + 1] == thin_point_p[k] && temp[1][j][i] == thin_point_q[k] ) ){
                            
                            reference_x[k] = i;
                            reference_y[k] = j;
                        }
                    }
                }
            }

        }
        else if( TMP_SIZE_W == 280 ){

            // 初期化
            pattern = 2;
            cp_size = 3825;
            reference_size = 10;

            // 入力画像における背景画素の決定
            for( j = 0 ; j < INPUT_SIZE_H ; j += INPUT_SIZE_H - 2 ){
                for( i = 0 ; i < INPUT_SIZE_W; i += INPUT_SIZE_W - 2 ){
                    if( input[1][j][i] == input[1][j][i + 1] ){
                        background_pixel = input[1][j][i];

                        i = INPUT_SIZE_W;
                        j = INPUT_SIZE_H;
                    }
                }
            }

            // スタート位置の探索
            for(j = 0 ; j < TMP_SIZE_H ; j++){
                for(i = 0 ; i < TMP_SIZE_W ; i++){

                    if( temp[1][j][i] != background_pixel ){
                        found_x = i;
                        found_y = j;

                        i = TMP_SIZE_W;
                        j = TMP_SIZE_H;
                    }

                }
            }

            // 同時生成行列の作成
            int TMP_SIZE_W_1 = TMP_SIZE_W - 1;

            for( j = 0 ; j < TMP_SIZE_H ; j++ ){
                for( i = 0 ; i < TMP_SIZE_W_1 ; i++ ){
                    com[temp[1][j][i + 1]][temp[1][j][i]]++;
                    com[temp[1][j][i]][temp[1][j][i + 1]]++;
                }
            }
            
            // 発生頻度の低い画素の座標を探索，保存
            int thin_point_p[reference_size];
            int thin_point_q[reference_size];
            int interbal = cp_size / reference_size;

            k = 0;
            n = 1;
            for( j = 0 ; j < COM_SIZE ; j++ ){
                for( i = 0 ; i < COM_SIZE ; i++ ){

                    if( com[j][i] == 1 )           // 頻度値１のペア数を記録
                        k++;
                    
                    if( k == interbal * n ){       // 選択ペアの間引き処理
                        thin_point_p[n - 1] = i;
                        thin_point_q[n - 1] = j;

                        n++;
                    }
                }
            }

            // 選択ペアのテンプレートにおける座標を探索
            for( k = 0 ; k < reference_size ; k++ ){
                for( j = 0 ; j < TMP_SIZE_H ; j++ ){
                    for( i = 0 ; i < TMP_SIZE_W_1 ; i++ ){
                        
                        if( ( temp[1][j][i] == thin_point_p[k] && temp[1][j][i + 1] == thin_point_q[k] ) || 
                            ( temp[1][j][i + 1] == thin_point_p[k] && temp[1][j][i] == thin_point_q[k] ) ){
                            
                            reference_x[k] = i;
                            reference_y[k] = j;

                            // printf("reference[%d](%d, %d)\n", c, j, i);
                        }
                    }
                }
            }

        }
        else{                  
            
            // 初期化
            pattern = 3;
            cp_size = 4266;
            reference_size = 10;

            // 入力画像における背景画素の決定
            for( j = 0 ; j < INPUT_SIZE_H ; j += INPUT_SIZE_H - 2 ){
                for( i = 0 ; i < INPUT_SIZE_W ; i += INPUT_SIZE_W - 2 ){
                    if( input[1][j][i] == input[1][j][i + 1] ){
                        background_pixel = input[1][j][i];

                        i = INPUT_SIZE_W;
                        j = INPUT_SIZE_H;
                    }
                }
            }

            // 同時生成行列の作成
            int TMP_SIZE_W_1 = TMP_SIZE_W - 1;

            for( j = 0 ; j < TMP_SIZE_H ; j++ ){
                for( i = 0 ; i < TMP_SIZE_W_1 ; i++ ){
                    com[temp[1][j][i + 1]][temp[1][j][i]]++;
                    com[temp[1][j][i]][temp[1][j][i + 1]]++;
                }
            }

            // 発生頻度の低い画素の座標を探索，保存
            int thin_point_p[reference_size];       // 頻度値1のペアを保存(座標)
            int thin_point_q[reference_size];
            int interbal = cp_size / reference_size;

            k = 0;
            n = 1;
            for( j = 0 ; j < COM_SIZE ; j++ ){
                for( i = 0 ; i < COM_SIZE ; i++ ){

                    if( com[j][i] == 1 ){       // 頻度値１のペア数を記録
                        k++;
                    }
                    
                    if( k == interbal * n ){     // 選択ペアの間引き処理
                        thin_point_p[n - 1] = i;
                        thin_point_q[n - 1] = j;

                        n++;
                    }
                }
            }

            // 選択ペアのテンプレートにおける座標を探索
            for( k = 0 ; k < reference_size ; k++ ){
                for( j = 0 ; j < TMP_SIZE_H ; j++ ){
                    for( i = 0 ; i < TMP_SIZE_W_1 ; i++ ){     

                        if( ( temp[1][j][i] == thin_point_p[k] && temp[1][j][i + 1] == thin_point_q[k] ) || 
                            ( temp[1][j][i + 1] == thin_point_p[k] && temp[1][j][i] == thin_point_q[k] ) ){
                            
                            reference_x[k] = i;
                            reference_y[k] = j;
                        }
                    }
                }
            }

        }

    }
    global_count++;

    // SSDAを用いて探索
    if( pattern == 1 )          out_point = RSSDA_1(input, temp);
    else if( pattern == 2 )     out_point = RSSDA_2(input, temp);
    else                        out_point = RSSDA_3(input, temp);

    return out_point;
}

Point RSSDA_1(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, k, count;                                    // カウンター
    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    int found_point_x, found_point_y;
    Point min.x, min.y;                                      // 検出位置

    // 初期化
    min.x = min.y = 0;
    found_point_x = found_point_y = 0;

    // スタート位置の探索
    for( j = 0; j < loss_SIZE_H ; j++ ){
        for( i = 0; i < loss_SIZE_W ; i++ ){

            if( input[1][j][i] != background_pixel ){
                found_point_x = i;
                found_point_y = j;

                i = loss_SIZE_W;
                j = loss_SIZE_H;
            }

        }
    }

    // ラスタスキャン
    for( j = found_point_y ; j < loss_SIZE_H ; j += 116){
        for( i = found_point_x ; i < loss_SIZE_W ; i += 197){

            // 初期化
            count = 0;

            // 選択画素のみ探索
            for( k = 0 ; k < reference_size ; k++ ){

                if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                    count++;

                    if( count >= 3 ){
                        min.x = i;
                        min.y = j;

                        i = loss_SIZE_W;
                        j = loss_SIZE_H;
                        break;
                    }
                }
            }
        }
    }

    return min;
}

Point RSSDA_2(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, c, k, s;                                     // カウンター

    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    // Point start_s_point, start_f_point;                    // 探索開始位置を保存
    // Point remove_s_point, start_f_point;                   // 探索除外位置を保存
    Point min;                                             // 検出位置

    // 初期化
    /*
    s = 0;
    min.x = 0; min.y = 0;

    start_s_point.x = INPUT_CENTER_X + INPUT_CENTER_X * 0.25;
    start_s_point.y = INPUT_CENTER_Y + INPUT_CENTER_Y * 0.25;

    start_f_point.x = INPUT_CENTER_X - INPUT_CENTER_X * 0.25;
    start_f_point.y = INPUT_CENTER_Y - INPUT_CENTER_Y * 0.25;
    
    remove_s_point.x = remove_s_point.y = 0;
    remove_f_point.x = remove_f_point.y = 0;
    */

    // ラスタスキャン
    for(j = start_s_point.y; j < start_f_point.y; j++){
        for(i = start_s_point.x; i < start_f_point.x; i++){

            // 初期化
            c = 0;

            // 探索除外位置の判別
            
            // 背景画素スキップ
            if( input[1][j + found_y][i + found_x] == background_pixel ){
                continue;
            }

            // 選択画素のみ探索
            for(k = 0; k < reference_size; k++ ){

                if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                    c++;

                    if( c >= 5 ){
                        min.x = i;
                        min.y = j;

                        i = loss_SIZE_W;
                        j = loss_SIZE_H;
                        break;
                    }
                }
            }


        }
    }

    return min;
}

Point RSSDA_3(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, k, c;                                     // カウンター

    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    Point min;                                             // 検出位置

    // 初期化
    min.x = 0; min.y = 0;

    // ラスタスキャン
    for(j = 0; j < loss_SIZE_H; j++){
        for(i = 0; i < loss_SIZE_W; i++){

            // 初期化
            c = 0;

            // 背景画素スキップ
            if( !(input[1][j][i] == background_pixel && input[1][j][i + 1] == background_pixel) &&
                !(input[1][j][i + TMP_SIZE_W - 1] == background_pixel && input[1][j][i + TMP_SIZE_W] == background_pixel) &&
                !(input[1][j + TMP_SIZE_H - 1][i] == background_pixel && input[1][j + TMP_SIZE_H - 1][i + 1] == background_pixel) &&
                !(input[1][j + TMP_SIZE_H - 1][i + TMP_SIZE_W - 1] == background_pixel && input[1][j + TMP_SIZE_H - 1][i + TMP_SIZE_W]) ){

                // 選択画素のみ探索
                for(k = 0; k < reference_size; k++ ){

                    if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                        c++;

                        if( c >= 5 ){
                            min.x = i;
                            min.y = j;

                            i = loss_SIZE_W;
                            j = loss_SIZE_H;
                            break;
                        }
                    }
                }
            }
        }
    }

    return min;
}

// ============================↑↑↑編集可能↑↑↑========================== //