#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //

#include"luts.hpp"

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, k, n ;                                                // カウンター
    Point out_point ;                                               // 検出位置

    // 初期化
    out_point.x = out_point.y = 0 ;


    // --------------------- 特徴点の抽出（初回のみの処理）--------------------
    if( global_count == 0 ){

        // パターン判別
        if( TMP_SIZE_W == 150 ){

            // 初期化
            pattern = 1 ;
            reference_size = 3 ;

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
            int p, q ;
            int com[COM_SIZE][COM_SIZE] ;
            int com_point_x[COM_SIZE][COM_SIZE] ;
            int com_point_y[COM_SIZE][COM_SIZE] ;
            int TMP_SIZE_W_1 = TMP_SIZE_W - 1 ;

            for( j = 0 ; j < TMP_SIZE_H ; ++j ){
                for( i = 0 ; i < TMP_SIZE_W_1 ; ++i ){

                    // 初期化
                    p = temp[1][j][i] ;
                    q = temp[1][j][i + 1] ;

                    // 同時生成行列を作成
                    com[q][p]++ ;
                    com[p][q]++ ;

                    // 同時生成行列に対応する座標ペアを保存
                    if( com[p][q] == 1 ){
                        com_point_x[q][p] = i ;
                        com_point_y[q][p] = j ;

                        com_point_x[p][q] = i ;
                        com_point_y[p][q] = j ;
                    }
                }
            }
        
            // 発生頻度の低い画素のテンプレートにおける座標を探索，保存
            int interbal = 16 ;

            k = 0 ;
            n = 1 ;
            for( j = 0 ; j < COM_SIZE ; ++j ){
                for( i = 0 ; i < COM_SIZE ; ++i ){

                    if( com[j][i] == 1 )                            // 頻度値１のペア数を記録
                        k++ ;
                        
                    if( k == interbal * n ){                        // 選択ペアの間引き処理
                        reference_x[n - 1] = com_point_x[j][i] ;
                        reference_y[n - 1] = com_point_y[j][i] ;

                        n++ ;
                    }
                }
            }
        }
        else if( TMP_SIZE_W == 280 ){

            // 初期化
            pattern = 2 ;
            reference_size = 10 ;

            // 同時生成行列の作成
            int p, q ;
            int com[COM_SIZE][COM_SIZE] ;
            int com_point_x[COM_SIZE][COM_SIZE] ;
            int com_point_y[COM_SIZE][COM_SIZE] ;
            int TMP_SIZE_W_1 = TMP_SIZE_W - 1 ;

            for( j = 0 ; j < TMP_SIZE_H ; ++j ){
                for( i = 0 ; i < TMP_SIZE_W_1 ; ++i ){

                    // 初期化
                    p = temp[1][j][i] ;
                    q = temp[1][j][i + 1] ;

                    // 同時生成行列を作成
                    com[q][p]++ ;
                    com[p][q]++ ;

                    // 同時生成行列に対応する座標ペアを保存
                    if( com[p][q] == 1 ){
                        com_point_x[q][p] = i ;
                        com_point_y[q][p] = j ;

                        com_point_x[p][q] = i ;
                        com_point_y[p][q] = j ;
                    }
                }
            }
        
            // 発生頻度の低い画素のテンプレートにおける座標を探索，保存
            int interbal = 382 ;

            k = 0 ;
            n = 1 ;
            for( j = 0 ; j < COM_SIZE ; ++j ){
                for( i = 0 ; i < COM_SIZE ; ++i ){

                    if( com[j][i] == 1 )                            // 頻度値１のペア数を記録
                        k++ ;
                        
                    if( k == interbal * n ){                        // 選択ペアの間引き処理
                        reference_x[n - 1] = com_point_x[j][i] ;
                        reference_y[n - 1] = com_point_y[j][i] ;

                        n++ ;
                    }
                }
            }
        }   
        else{

            // 初期化
            pattern = 3 ;
            reference_size = 10 ;

            // 同時生成行列の作成
            int p, q ;
            int com[COM_SIZE][COM_SIZE] ;
            int com_point_x[COM_SIZE][COM_SIZE] ;
            int com_point_y[COM_SIZE][COM_SIZE] ;
            int TMP_SIZE_W_1 = TMP_SIZE_W - 1 ;

            for( j = 0 ; j < TMP_SIZE_H ; ++j ){
                for( i = 0 ; i < TMP_SIZE_W_1 ; ++i ){

                    // 初期化
                    p = temp[1][j][i] ;
                    q = temp[1][j][i + 1] ;

                    // 同時生成行列を作成
                    com[q][p]++ ;
                    com[p][q]++ ;

                    // 同時生成行列に対応する座標ペアを保存
                    if( com[p][q] == 1 ){
                        com_point_x[q][p] = i ;
                        com_point_y[q][p] = j ;

                        com_point_x[p][q] = i ;
                        com_point_y[p][q] = j ;
                    }
                }
            }   
        
            // 発生頻度の低い画素のテンプレートにおける座標を探索，保存
            int interbal = 426 ;

            k = 0 ;
            n = 1 ;
            for( j = 0 ; j < COM_SIZE ; ++j ){
                for( i = 0 ; i < COM_SIZE ; ++i ){

                    if( com[j][i] == 1 )                            // 頻度値１のペア数を記録
                        k++ ;
                        
                    if( k == interbal * n ){                        // 選択ペアの間引き処理
                        reference_x[n - 1] = com_point_x[j][i] ;
                        reference_y[n - 1] = com_point_y[j][i] ;

                        n++ ;
                    }
                }
            }
        }

    }
    global_count++ ;


    // // -------------------- 探索アルゴリズム --------------------

    if( pattern == 1 ){
        
        // 変数の宣言
        int count ;
        int loss_SIZE_H, loss_SIZE_W ;
        int found_point_x, found_point_y ;

        // 初期化
        loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1 ;
        loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1 ;

        found_point_x = found_point_y = 0 ;

        // スタート位置の探索
        for( j = 0 ; j < loss_SIZE_H ; j++ ){
            for( i = 0 ; i < loss_SIZE_W ; i++ ){

                if( input[1][j][i] != background_pixel ){
                    found_point_x = i;
                    found_point_y = j;

                    i = loss_SIZE_W;
                    j = loss_SIZE_H;
                }
            }
        }

        // ラスタスキャン
        for( j = found_point_y ; j < loss_SIZE_H ; j += 116 ){
            for( i = found_point_x ; i < loss_SIZE_W ; i += 197 ){

                // 初期化
                count = 0 ;

                // 選択画素のみ探索
                for( k = 0 ; k < reference_size ; k++ ){

                    if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                        count++;

                        if( count >= 3 ){
                            out_point.x = i;
                            out_point.y = j;

                            return out_point ;
                        }
                    }
                }
            }
        }
    }
    else{

        // 変数の宣言
        int count ;
        int loss_SIZE_H, loss_SIZE_W ;

        // 初期化
        loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1 ;
        loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1 ;

        // ラスタスキャン
        for( n = 0 ; n < reference_size ; ++n ){
            for( j = 0 ; j < loss_SIZE_H ; ++j ){
                for( i = 0 ; i < loss_SIZE_W ; ++i ){

                    // 初期化
                    count = 0 ;

                    // 背景画素スキップ
                    if( input[1][j + reference_y[n]][i + reference_x[n]] == temp[1][reference_y[n]][reference_x[n]] ){

                        // 選択画素のみ探索
                        for( k = 0 ; k < reference_size ; ++k ){

                            if( input[1][j + reference_y[k]][i + reference_x[k]] == temp[1][reference_y[k]][reference_x[k]] ){
                                count++;

                                if( count >= 5 ){
                                    out_point.x = i ;
                                    out_point.y = j ;

                                    return out_point ;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return out_point ;
}

// ============================↑↑↑編集可能↑↑↑========================== //