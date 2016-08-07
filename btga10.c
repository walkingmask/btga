/* 
 * btga10.c
 * 2016/07/29(Fri)
 * Kazuki Nagamine (145725A)
 * binary tree genetic algorythm for 10 puzzle
 *
 * referenced
 * https://www.sist.ac.jp/~suganuma/kougi/other_lecture/SE/opt/GA/GA.htm
 * http://www.obitko.com/tutorials/genetic-algorithms/japanese/recommendations.php
 *
 * TODO
 * 少し複雑な適応度関数の実装 Stock内のstackとの類似度を利用する
 */

#include <unistd.h>
#include "btga.h"

#define POPULN 100          // 集団の個体数
#define PARENTSN 10*2       // 選択する親の数
#define CHILDRENN PARENTSN  // 生成される子の最大数
#define MAXGEN 10000        // 最大世代交代数

int main(int argc, char *argv[]) {
  // uRandの初期化
  initRand();

  // 個体群
  Indiv popul[POPULN];
  Indiv parents[PARENTSN];
  Indiv children[PARENTSN];

  // 式保存用リスト
  Stock *stock = NULL;

  // 世代数，生成された新個体の数
  int gen, childrenNum;

  // 初期集団
  initPopul(popul, POPULN);
  populFitness(popul, POPULN, &stock);

  // 世代交代
  for (gen=0; gen<MAXGEN; gen++) {
    // 親の選択
    selectParents(popul, parents, POPULN, PARENTSN);
    // 交叉
    childrenNum = crossing(parents, children, PARENTSN, 80);
    // 新個体の適応度の計算
    populFitness(children, childrenNum, &stock);
    // 淘汰
    selection(popul, children, POPULN, childrenNum);
    // 突然変異
    mutation(popul, POPULN, 1);
    // 中間結果の出力
    printf("gen:%05d --------------------\n", gen);
    printf("fitness ave: ");printPopulFitnessAve(popul, POPULN);
    printf("fitness max: ");printPopulFitnessMax(popul, POPULN);
    printf("fitness min: ");printPopulFitnessMin(popul, POPULN);
    printf("found num  : ");printStockNum(&stock);
    // ワンクッション
    sleep(1);
  }

  // 見つかった全ての10パズルを出力
  printf("result -------------------------\n");
  printStock(&stock);

  return 0;
}
