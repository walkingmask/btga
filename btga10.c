/* 
 * btga10.c
 * 2016/07/29(Fri)
 * Kazuki Nagamine (145725A)
 * binary tree genetic algorythm for 10 puzzle
 */

#include "btga.h"

#define POPULN 1000
#define PARENTN 100*2
#define CHILDRENN PARENTN
#define MAXGEN 10000

int main(int argc, char *argv[])
{
  // uRandの初期化
  initRand();

  // 個体群
  Indiv popul[POPULN];
  Indiv parent[PARENTN];
  Indiv children[CHILDRENN];

  // 交叉用変数
  Tree temp1, temp2;

  // 式保存用リスト
  Stock *stock = NULL;

  // 生成された新個体の数を保存する
  int childrenNum;

  // 初期集団の生成
  initPopul(popul, POPULN);
  // 適応度の計算
  populFitness(popul, POPULN, &stock);

  // 世代交代 指定回数で終了
  int gen;
  for (gen=0; gen<100; gen++) {
    printf("gen%d\n", gen);
    // 親の選択
    selectParent(popul, parent, POPULN, PARENTN);
    // 交叉
    childrenNum = crossing(parent, children, PARENTN, 80, &temp1, &temp2);
    // 新個体の適応度の計算
    //populFitness(children, childrenNum, &stock);
    // 淘汰
    //selection(popul, children, POPULN, childrenNum);
    // 突然変異
    mutation(popul, POPULN, 1);
    // 見つかった式の出力
    printStock(&stock);
  }

	return 0;
}
