---------------------------- -
/* 課題：[C]をfor文で回すか回さないか（Cを変数の宣言するべきか）
		点１を左上，点２を日の丸右下，点３を右下にしているが、順番を変えるべきか
		（もし左上に白の国旗が多い場合には点２を先に回した方が高速になるかもしれない）*/

//最終編集：20230820

//課題１を動かすための処理
int N;//変数の宣言
int i;//変数の宣言
int j;//変数の宣言
if (template[0][0][0] ==0&& template[1][0][0] == 0 && template[2][0][0] == 0 ) {//もし入力画像の左上が白色のときに実行する
	//処理開始
	for (N = 0; N < 10; N++) {
		for (i = 16; i < im_in.cols; i += 116) {//116は国旗の縦の画素
			for (j = 49; j < im_in.rows; j += 196) {//196は国旗の横の画素
				if (input[N][0][i][j] == 0 && input[N][1][i][j] == 0 && input[N][2][i][j] == 0) {//国旗の左上の色が白のとき
					 if (input[N][0][i+64][j+92] == 0 && input[N][1][i+64][j+92] == 0 && input[N][2][i+64][j+92] == 255) {//国旗の左上の色が赤のとき（大雑把のため改良の余地あり）
						 if (input[N][0][i+100][j+150] == 0 && input[N][1][i+100][j+150] == 0 && input[N][2][i+100][j+150] == 0) {//国旗の左上の色が白のとき
							 printf("matting=(%d,%d)", j, i);//出力
						 }

					 }

				}
			}
		}

	}
}//それ以外（課題２、課題３）は下のプログラムへ↓


-----------------------------