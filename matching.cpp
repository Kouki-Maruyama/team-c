#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //

#include"luts.hpp"

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    // 初回のみの処理
    if( global_count == 0 ){

        // 変数の宣言
        int i, j, c, n;
        int cp_size;

        // パターン判別
        if( TMP_SIZE_W == 150 ){      
        
            // 初期化
            pattern = 1;
            cp_size = 48;
            reference_size = 3;

             // 入力画像における背景画素の決定
            for( j = 0; j < INPUT_SIZE_H; j += INPUT_SIZE_H - 2 ){
                for( i = 0; i < INPUT_SIZE_W; i += INPUT_SIZE_W - 2 ){
                    if( input[1][j][i] == input[1][j][i + 1] ){
                        background_pixel = input[1][j][i];

                        i = INPUT_SIZE_W;
                        j = INPUT_SIZE_H;
                    }
                }
            }

            // 同時生成行列の作成
            for( j = 0; j < TMP_SIZE_H; j++ ){
                for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                    com[temp[1][j][i + 1]][temp[1][j][i]]++;
                    com[temp[1][j][i]][temp[1][j][i + 1]]++;
                }
            }

            // 発生頻度の低い画素の座標を探索，保存
            COM_POINT thin_point[reference_size];
            int interbal = cp_size / reference_size;

            c = 0;
            n = 1;
            for( j = 0 ; j < COM_SIZE; j++ ){
                for( i = 0 ; i < COM_SIZE; i++ ){

                    if( com[j][i] == 1 ){       // 頻度値１のペア数を記録
                        c++;
                    }
                    
                    if( c == interbal * n ){     // 選択ペアの間引き処理
                        thin_point[n - 1].p = i;
                        thin_point[n - 1].q = j;

                        n++;
                    }
                }
            }

            // 選択ペアのテンプレートにおける座標を探索
            for( c = 0; c < reference_size; c++ ){
                for( j = 0; j < TMP_SIZE_H; j++ ){
                    for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                        
                        if( (temp[1][j][i] == thin_point[c].p && temp[1][j][i + 1] == thin_point[c].q) || 
                            (temp[1][j][i + 1] == thin_point[c].p && temp[1][j][i] == thin_point[c].q) ){
                            
                            reference_x[c] = i;
                            reference_y[c] = j;
                        }
                    }
                }
            }

        }
        else if( TMP_SIZE_W == 280 ){

            // 初期化
            pattern = 2;
            cp_size = 3825;
            reference_size = 14;

            // 入力画像における背景画素の決定
            for( j = 0; j < INPUT_SIZE_H; j += INPUT_SIZE_H - 2 ){
                for( i = 0; i < INPUT_SIZE_W; i += INPUT_SIZE_W - 2 ){
                    if( input[1][j][i] == input[1][j][i + 1] ){
                        background_pixel = input[1][j][i];

                        i = INPUT_SIZE_W;
                        j = INPUT_SIZE_H;
                    }
                }
            }

            // 同時生成行列の作成
            for( j = 0; j < TMP_SIZE_H; j++ ){
                for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                    com[temp[1][j][i + 1]][temp[1][j][i]]++;
                    com[temp[1][j][i]][temp[1][j][i + 1]]++;
                }
            }
            
            // 発生頻度の低い画素の座標を探索，保存
            COM_POINT thin_point[reference_size];
            int interbal = cp_size / reference_size;

            c = 0;
            n = 1;
            for( j = 0 ; j < COM_SIZE; j++ ){
                for( i = 0 ; i < COM_SIZE; i++ ){

                    if( com[j][i] == 1 ){          // 頻度値１のペア数を記録
                        c++;
                    }
                    
                    if( c == interbal * n ){       // 選択ペアの間引き処理
                        thin_point[n - 1].p = i;
                        thin_point[n - 1].q = j;

                        n++;
                    }
                }
            }

            // 選択ペアのテンプレートにおける座標を探索
            for( c = 0; c < reference_size; c++ ){
                for( j = 0; j < TMP_SIZE_H; j++ ){
                    for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                        
                        if( (temp[1][j][i] == thin_point[c].p && temp[1][j][i + 1] == thin_point[c].q) || 
                            (temp[1][j][i + 1] == thin_point[c].p && temp[1][j][i] == thin_point[c].q) ){
                            
                            reference_x[c] = i;
                            reference_y[c] = j;

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
            reference_size = 20;

            // 入力画像における背景画素の決定
            for( j = 0; j < INPUT_SIZE_H; j += INPUT_SIZE_H - 2 ){
                for( i = 0; i < INPUT_SIZE_W; i += INPUT_SIZE_W - 2 ){
                    if( input[1][j][i] == input[1][j][i + 1] ){
                        background_pixel = input[1][j][i];

                        i = INPUT_SIZE_W;
                        j = INPUT_SIZE_H;
                    }
                }
            }

            // 同時生成行列の作成
            for( j = 0; j < TMP_SIZE_H; j++ ){
                for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                    com[temp[1][j][i + 1]][temp[1][j][i]]++;
                    com[temp[1][j][i]][temp[1][j][i + 1]]++;
                }
            }

            // 発生頻度の低い画素の座標を探索，保存
            COM_POINT thin_point[reference_size];       // 頻度値1のペアを保存(座標)
            int interbal = cp_size / reference_size;

            c = 0;
            n = 1;
            for( j = 0 ; j < COM_SIZE; j++ ){
                for( i = 0 ; i < COM_SIZE; i++ ){

                    if( com[j][i] == 1 ){       // 頻度値１のペア数を記録
                        c++;
                    }
                    
                    if( c == interbal * n ){     // 選択ペアの間引き処理
                        thin_point[n - 1].p = i;
                        thin_point[n - 1].q = j;

                        n++;
                    }
                }
            }

            // 選択ペアのテンプレートにおける座標を探索
            for( c = 0; c < reference_size; c++ ){
                for( j = 0; j < TMP_SIZE_H; j++ ){
                    for( i = 0; i < TMP_SIZE_W - 1; i++ ){     

                        if( (temp[1][j][i] == thin_point[c].p && temp[1][j][i + 1] == thin_point[c].q) || 
                            (temp[1][j][i + 1] == thin_point[c].p && temp[1][j][i] == thin_point[c].q) ){
                            
                            reference_x[c] = i;
                            reference_y[c] = j;
                        }
                    }
                }
            }

        }

    }
    global_count++;

    // SSDAを用いて探索
    if( pattern == 1 ){
        out_point = RSSDA_1(input, temp);
    }
    else if( pattern == 2 ){
        out_point = RSSDA_2(input, temp);
    }
    else{
        out_point = RSSDA_3(input, temp);
    }

    return out_point;
}

Point RSSDA_1(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, c, k;                                        // カウンター
    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    Point found_point;
    Point min;                                             // 検出位置

    // 初期化
    min.x = min.y = 0;
    found_point.x = found_point.y = 0;

    // スタート位置の探索
    for(j = 0; j < loss_SIZE_H; j++){
        for(i = 0; i < loss_SIZE_W; i++){

            if( input[1][j][i] == background_pixel ){
                continue;
            }
            else{
                found_point.x = i;
                found_point.y = j;

                i = loss_SIZE_W;
                j = loss_SIZE_H;
            }

        }
    }

    // ラスタスキャン
    for(j = found_point.y; j < loss_SIZE_H; j += 116){
        for(i = found_point.x; i < loss_SIZE_W; i += 197){

            // 初期化
            c = 0;

            // 選択画素のみ探索
            for(k = 0; k < reference_size; k++ ){

                if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                    c++;

                    if( c >= 3 ){
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
    int i, j, c, k;                                        // カウンター

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
            if( input[1][j + reference_y[0]][i + reference_x[0]] == background_pixel ){
                continue;
            }

            // 選択画素のみ探索
            for(k = 0; k < reference_size; k++ ){

                if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                    c++;

                    if( c >= 7 ){
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

    // 相違度マップの生成
    for(j = 0; j < loss_SIZE_H; j++){
        for(i = 0; i < loss_SIZE_W; i++){

            // 初期化
            c = 0;

            // 背景画素スキップ
            if( (input[1][j][i] == background_pixel && input[1][j][i + 1] == background_pixel) ||
                (input[1][j][i + TMP_SIZE_W - 1] == background_pixel && input[1][j][i + TMP_SIZE_W] == background_pixel) ||
                (input[1][j + TMP_SIZE_H - 1][i] == background_pixel && input[1][j + TMP_SIZE_H - 1][i + 1] == background_pixel) ||
                (input[1][j + TMP_SIZE_H - 1][i + TMP_SIZE_W - 1] == background_pixel && input[1][j + TMP_SIZE_H - 1][i + TMP_SIZE_W]) ){

                continue;
            }

            // 選択画素のみ探索
            for(k = 0; k < reference_size; k++ ){

                if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                    c++;

                    if( c >= 10 ){
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

// ============================↑↑↑編集可能↑↑↑========================== //