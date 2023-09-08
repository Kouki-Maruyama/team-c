// ======================================= //
// 使用するライブラリをまとめたライブラリ  //
// ======================================= //
#ifndef INTEGRATION_H_
#define INTEGRATION_H_

// 標準ライブラリ
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<chrono>
#include<string.h>
#include<opencv2/opencv.hpp>

// スタッフ用ライブラリ(編集禁止・使用は可能)
#include"staff_struct.hpp"        // 構造体やハイパーパラメータを管理
#include"staff_utils.hpp"         // 運営が用意した関数

// 自作ライブラリ(新規ファイル・ライブラリを追加可能)
// ============================↓↓↓編集可能↓↓↓========================== //
#include"matching.hpp"
#include"luts.hpp"


// ============================↑↑↑編集可能↑↑↑========================== //
#endif