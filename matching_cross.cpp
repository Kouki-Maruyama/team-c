#include"integration.hpp"
#include"staff_struct.hpp"
#include"matching.hpp"

// ============================↓↓↓編集可能↓↓↓========================== //
#include"luts.hpp"

Point matching(unsigned char input[CHANNEL][INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp[CHANNEL][TMP_SIZE_H][TMP_SIZE_W]){

    Point out_point ;
    int i, j, k,l;
    int halh_H = TMP_SIZE_H / 2 ;
    int halh_W = TMP_SIZE_W / 2 ;
    int count = 0 ; 
    //printf("%d",halh_H);
    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;
    k = 0 ;
    l = 0 ; 

//patern 1
    if( TMP_SIZE_W == 150 ){
        for( j = 16 ; j < loss_SIZE_H ; j+=116){
            for( i = 48 ; i < loss_SIZE_W  ; i+=197){ 
                for( k = 0; k < TMP_SIZE_W ; k+=5){
                
            //b=b+1;
            //printf("%d",b);
            if( input[0][ j+halh_H][i+k] == temp [0][ halh_H][k] && input[0][j+l][i+halh_W] == temp [0][l][halh_W]){
                count++ ; 
                //printf("counter :%d\n",count);
                if(count == 25){
                    //printf("%d\n",count);
                    out_point.x = i;
                    out_point.y = j;
                break ;
                }
            }
            l +=3 ;
            }
                l = 0 ;
            count = 0 ;
        }
            }  
            //printf("matting TMP->%d INPUT ->%d",input[0][ 50][16],temp [0][ 50 ][16]);
            return out_point ;
    }


//patern 2
    else if(TMP_SIZE_W == 280){
        for( j = 20 ; j < loss_SIZE_H ; j++){
            for( i = 20 ; i < loss_SIZE_W  ; i++){ 
                for( k = 0; k < TMP_SIZE_W ; k+=56){
                
            //b=b+1;
            //printf("%d",b);
            if( input[0][ j+halh_H][i+k] == temp [0][ halh_H][k] && input[0][j+l][i+halh_W] == temp [0][l][halh_W]){
                count++ ; 
                //printf("counter :%d\n",count);
                if(count == 4){
                    //printf("%d\n",count);
                    out_point.x = i;
                    out_point.y = j;
                break ;
                }
            }
            l +=5;
            }
                l = 0 ;
            count = 0 ;
        }
            }  
            //printf("matting TMP->%d INPUT ->%d",input[0][ 50][16],temp [0][ 50 ][16]);
            return out_point ;
    }

        //patern 3
    else {
        for( j = 50 ; j < loss_SIZE_H ; j++){
            for( i = 50 ; i < loss_SIZE_W  ; i++){ 
                for( k = 0; k < TMP_SIZE_W ; k+=20){
                
            //b=b+1;
            //printf("%d",b);
            if( input[0][ j+halh_H][i+k] == temp [0][ halh_H][k] && input[0][j+l][i+halh_W] == temp [0][l][halh_W]){
                count++ ; 
                //printf("counter :%d\n",count);
                if(count == 3){
                    //printf("%d\n",count);
                    out_point.x = i;
                    out_point.y = j;
                break ;
                }
            }
            l +=32;
            }
                l = 0 ;
            count = 0 ;
        }
            }  
            //printf("matting TMP->%d INPUT ->%d",input[0][ 50][16],temp [0][ 50 ][16]);
            return out_point ;
    }




        }



/*

    // 変数の宣言
    int i, j, c, n;                                                     // カウンター
    unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W];                  // グレースケール変換用
    unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W];                       // グレースケール変換用
    Point out_point;                                                    // 検出位置

    // 初期化
    out_point.x = out_point.y = 0;

    // グレースケール変換(入力画像)
    for( j = 0; j < INPUT_SIZE_H; j++ ){
        for( i = 0; i < INPUT_SIZE_W; i++ ){      
            input_g[j][i] = (int)(0.2126 * input[0][j][i] + 0.7152 * input[1][j][i] + 0.0722 * input[2][j][i]);
        }
    }

    // 初回のみの処理
    if( global_count == 0 ){

        // パターン判別
        int cp_size;

        if( TMP_SIZE_W == 150 ){
            pattern = 1;
            reference_size = 3;
            cp_size = 48;
        }
        else if( TMP_SIZE_W == 280 ){
            pattern = 2;
            reference_size = 12;
            cp_size = 728;
        }
        else{
            pattern = 3;
            reference_size = 25;
            cp_size = 804;
        } 

        // 入力画像における背景画素の決定(パターン1・3)
        if( pattern == 1 || pattern == 3 ){
            int histgram[256] = {0};
            int max;

            for( j = 0; j < INPUT_SIZE_H; j++ ){
                for( i = 0; i < INPUT_SIZE_W; i++ ){
                    histgram[input_g[j][i]]++;
                }
            }

            max = histgram[0];
            for( i = 0; i < 256; i++){
                if( max < histgram[i] ){
                    max = histgram[i];
                    background_pixel = i;
                }
            }
        }

        // グレースケール変換(テンプレート画像)
        for( j = 0; j < TMP_SIZE_H; j++ ){
            for( i = 0; i < TMP_SIZE_W; i++ ){
                temp_g[j][i] = (int)(0.2126 * temp[0][j][i] + 0.7152 * temp[1][j][i] + 0.0722 * temp[2][j][i]);
            }
        }

        // 担当：石川
        // 同時生成行列の作成
        int com_originai[2][COM_SIZE][COM_SIZE] = {0};

        for( j = 0; j < TMP_SIZE_H - 1; j++ ){
            for( i = 0; i < TMP_SIZE_W - 1; i++ ){
                com_originai[0][temp_g[j][i + 1]][temp_g[j][i]]++;          // 水平方向のペアを追加
                com_originai[0][temp_g[j][i]][temp_g[j][i + 1]]++;
                
                com_originai[1][temp_g[j + 1][i]][temp_g[j][i]]++;          // 垂直方向のペアを追加
                com_originai[1][temp_g[j][i]][temp_g[j + 1][i]]++;
            }
        }

        for( j = 0; j < COM_SIZE; j++ ){
            for( i = 0; i < COM_SIZE; i++ ){
                if( com_originai[0][j][i] == 1 && com_originai[1][j][i] == 1 ){
                    com[j][i] = 1;
                }
                else{
                    com[j][i] = 0;
                }
            }
        }
       
        // 担当：宇佐美
        // 発生頻度の低い画素の座標を探索，保存
        COM_POINT thin_point[reference_size];       // 頻度値1のペアを保存(座標)
        int interbal = cp_size / reference_size;

        c = 0;
        n = 0;
        for( j = 0 ; j < COM_SIZE; j++ ){
            for( i = 0 ; i < COM_SIZE; i++ ){

                if( com[j][i] == 1 ){       // 頻度値１のペア数を記録
                    c++;
                }
                
                if( c == interbal * n){     // 選択ペアの間引き処理
                    thin_point[n].p = i;
                    thin_point[n].q = j;
                    n++;
                }
            }
        }

        // 選択ペアのテンプレートにおける座標を探索
        for( c = 0; c < reference_size; c++ ){
            for( j = 0; j < TMP_SIZE_H - 1; j++ ){
                for( i = 0; i < TMP_SIZE_W - 1; i++ ){      // 領域外探索を避けている
                    
                    // 隣り合っている画素値が一致しているか否か(水平方向)
                    if( (temp_g[j][i] == thin_point[c].p && temp_g[j][i + 1] == thin_point[c].q) || 
                        (temp_g[j][i + 1] == thin_point[c].p && temp_g[j][i] == thin_point[c].q) ){
                        
                        reference_x[c] = i;
                        reference_y[c] = j;
                    }
                }
            }
        }

    }
    global_count++;

    // SSDAによる探索
    if( pattern == 1 ){
        out_point = RSSDA_1(input_g, temp_g);                 
    }
    else if( pattern == 2 ){
        out_point = RSSDA_2(input_g, temp_g);                 
    }
    else{
        out_point = RSSDA_3(input_g, temp_g);                
    }

    return out_point;
}

Point RSSDA_1(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, c, k;                                  // カウンター
    int thr, flag, flag_found;

    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    int loss[12] = {0};
    Point found_point[12];
   
    int loss_min;                                          // 相違度マップの最小値
    Point min;                                             // 検出位置

    // 初期化
    thr = 1000;
    k = 0;

    // 相違度マップの生成
    for(j = 0; j < loss_SIZE_H; j++){
        flag_found = 0;

        for(i = 0; i < loss_SIZE_W; i++){

            // 初期化
            flag = 0;
                
            // スタート位置の探索
            if( input_g[j][i] == background_pixel ){
                continue;
            }
            else{
                found_point[k].x = i;
                found_point[k].y = j;

                flag_found = 1;
            }

            // ラスタスキャン(選択画素のみ)
            for(c = 0; c < reference_size; c++){
                I = reference_x[c];
                J = reference_y[c];

                loss[k] += (int)(sqrt( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) ));

                if( thr < loss[k] ){
                    flag = 1;
                    break;
                }
            }
            // printf("%d, (%d, %d) -> %d\n", flag, j, i, loss[k]);

            if( flag == 0 ){
                thr = loss[k];
            }
            if( flag_found == 1 ){
                i += TMP_SIZE_W + 45;
                k++;
            }
        }

        if( flag_found == 1 ){
            j += TMP_SIZE_H + 15;
        }
    }

    // 相違度の最小値を求める
    // 初期化
    min.x = found_point[0].x; 
    min.y = found_point[0].y; 
    loss_min = loss[0];

    // ラスタスキャン
    for( i = 0; i < 12; i++ ){
        
        // SSDA
        if(loss_min > loss[i]){

            // 最小値の更新
            loss_min = loss[i]; 
            min.x = found_point[i].x; 
            min.y = found_point[i].y;
        }
    }

    return min;
}

Point RSSDA_2(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, c;                                     // カウンター
    int thr, flag;

    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    int loss[loss_SIZE_H][loss_SIZE_W] = {0};              // 相違度マップ
    int loss_min;                                          // 相違度マップの最小値
    Point min;                                             // 検出位置

    // 初期化
    thr = 0;

    // 相違度マップの生成
    for(j = 0; j < loss_SIZE_H; j++){
        for(i = 0; i < loss_SIZE_W; i++){

            // 初期化
            flag = 0;

            // ラスタスキャン(選択画素のみ)
            for(c = 0; c < reference_size; c++){
                I = reference_x[c];
                J = reference_y[c];

                loss[j][i] += (int)(sqrt( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) ));

                if( !(j == 0 && i == 0) && (thr < loss[j][i]) ){
                    flag = 1;
                    break;
                }
            }

            if( j == 0 && i == 0 ){
                thr = loss[j][i];
            }
            if( flag == 0 ){                   
                thr = loss[j][i];
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

            // SSD
            if(loss_min > loss[j][i]){

                // 最小値の更新
                loss_min = loss[j][i]; 
                min.x = i; min.y = j;
            }
        }
    }

    return min;
}

Point RSSDA_3(unsigned char input_g[INPUT_SIZE_H][INPUT_SIZE_W], unsigned char temp_g[TMP_SIZE_H][TMP_SIZE_W]){

    // 変数の宣言
    int i, j, I, J, c;                                     // カウンター
    int thr, flag;

    int loss_SIZE_H, loss_SIZE_W;                          // 相違度マップのサイズ
    loss_SIZE_H = INPUT_SIZE_H - TMP_SIZE_H + 1;
    loss_SIZE_W = INPUT_SIZE_W - TMP_SIZE_W + 1;

    int loss[loss_SIZE_H][loss_SIZE_W] = {0};              // 相違度マップ
    int loss_min;                                          // 相違度マップの最小値
    Point min;                                             // 検出位置

    // 初期化
    thr = 0;

    // 相違度マップの生成
    for(j = 0; j < loss_SIZE_H; j++){
        for(i = 0; i < loss_SIZE_W; i++){

            // 初期化
            flag = 0;

            // 背景画素スキップ
            if( !(j == 0 && i == 0) ){
                if( (input_g[j][i] == background_pixel && input_g[j][i + 1] == background_pixel) ||
                    (input_g[j][i + TMP_SIZE_W - 1] == background_pixel && input_g[j][i + TMP_SIZE_W] == background_pixel) ||
                    (input_g[j + TMP_SIZE_H - 1][i] == background_pixel && input_g[j + TMP_SIZE_H - 1][i + 1] == background_pixel) ||
                    (input_g[j + TMP_SIZE_H - 1][i + TMP_SIZE_W - 1] == background_pixel && input_g[j + TMP_SIZE_H - 1][i + TMP_SIZE_W]) ){
                    
                    loss[j][i] = 10000;
                    continue;
                }
            }

            // ラスタスキャン(選択画素のみ)
            for(c = 0; c < reference_size; c++){
                I = reference_x[c];
                J = reference_y[c];

                loss[j][i] += (int)(sqrt( ( input_g[J + j][I + i] - temp_g[J][I] ) * ( input_g[J + j][I + i] - temp_g[J][I] ) ));

                if( !(j == 0 && i == 0) && (thr < loss[j][i]) ){
                    flag = 1;
                    break;
                }
            }

            if( j == 0 && i == 0 ){
                thr = loss[j][i];
            }
            if( flag == 0 ){
                thr = loss[j][i];
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

            // SSD
            if(loss_min > loss[j][i]){

                // 最小値の更新
                loss_min = loss[j][i]; 
                min.x = i; min.y = j;
            }
        }
    }

    return min;
    */

// ============================↑↑↑編集可能↑↑↑========================== //