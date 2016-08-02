/* 
 * btga.h
 * 2016/07/29(Fri)
 * Kazuki Nagamine (145725A)
 * binary tree genetic algorythm
 *
 * 初期集団の生成->適応度の計算->スタックの保存->エリートの保存->交叉&突然変異->適応度の計算->...
 * 終了判定は...? -> とりあえず回数指定
 * http://www.obitko.com/tutorials/genetic-algorithms/japanese/recommendations.php
 */


/* Header */
#include <math.h>
#include <string.h>
#include "btc.h"


/* Struct */
// 個体の定義
struct individual {
  Tree t; // 染色体
  float fitness; // 適応度
}; typedef struct individual Indiv;

// スタックの保存用リスト
struct stock {
  char stack[8];
  struct stock *next;
}; typedef struct stock Stock;

/* Prototype */


/* Function */
// 初期個体の生成
void initIndiv(Indiv *indiv) {
  randMake(&(indiv->t));
}

// 初期集団の生成
void initPopul(Indiv *popul, int num) {
  int i;
  for (i=0; i<num; i++) {
    initIndiv(&popul[i]);
  }
}

// スタックを保存されたスタックと比較
int checkExistance(Stock **stock, char *stack) {
  if (*stock == NULL) {
    return 1;
  }
  while (*stock != NULL) {
    if (strcmp((*stock)->stack, stack) == 0) {
      return 0;
    }
    stock = &((*stock)->next);
  }
  return 1;
}

// スタックの保存
void add2Stock(Stock **stock, char *stack) {
  // 新stockの生成
  Stock *s = (Stock *)malloc(sizeof(Stock));
  strcpy(s->stack, stack);
  s->next = NULL;
  // リストへ追加
  if (*stock == NULL) {
    *stock = s;
  }
  else {
    while ((*stock)->next != NULL) stock = &((*stock)->next);
    (*stock)->next = s;
  }
}

// スタック保存リストの解放
void freeStock(Stock **stock) {
  if ((*stock)->next != NULL) {
    freeStock(&(*stock)->next);
  }
  free(*stock);
}

// スタック保存リストの出力
void printStock(Stock **stock) {
  if (*stock == NULL) {
    return;
  }
  while ((*stock)->next != NULL) {
    printf("%s, ", (*stock)->stack);
    stock = &((*stock)->next);
  }
  printf("%s\n", (*stock)->stack);
}

// 個体の適応度の計算
void indivFitness(Indiv *indiv, Stock **stock) {
  char stack[8];
  tree2stack(&(indiv->t), stack);
  if (checkExistance(stock, stack) == 0) {
    indiv->fitness = -1000;
  }
  else {
    tree2float(&(indiv->t), &(indiv->fitness));
    indiv->fitness = -fabs(10.0 - indiv->fitness);
    // 適応度最大の個体の保存
    if (indiv->fitness == 0) {
      add2Stock(stock, stack);
      indiv->fitness = -1000;
    }
  }
}

// 集団の個体すべての適応度の計算
void populFitness(Indiv *popul, int populNum, Stock **stock) {
  int i;
  for (i=0; i<populNum; i++) {
    indivFitness(&popul[i], stock);
  }
}

// 個体の適応度の出力
void printIndivFitness(Indiv *indiv) {
  printf("%f\n", indiv->fitness);
}

// 集団の個体すべての適応度の出力
void printPopulFitness(Indiv *popul, int num) {
  int i;
  for (i=0; i<num; i++) {
    printIndivFitness(&popul[i]);
  }
}

// すでに選択したかどうかの判断
int isSelected(int *selected, int select, int num) {
  int i;
  for (i=0; i<num; i++) {
    if (select == selected[i]) {
      return 1;
    }
  }
  return 0;
}

// 親の選択
void selectParent(Indiv *popul, Indiv *parent, int populNum, int parentNum) {
  int i, j, selected[parentNum];
  for(i=0; i<parentNum; i++) {
    while (1) {
      j = uRand(populNum-1);
      if (isSelected(selected, j, i) == 0) {
        break;
      }
    }
    parent[i] = popul[j];
  }
} 

// 交叉確率
int isCross(int p) {
  if (uRand(100-1) < p) {
    return 1;
  }
  return 0;
}

// 交叉 生成された子の数を返す
int crossing(Indiv *parent, Indiv *children, int parentNum, int crossp, Tree *t1, Tree *t2) {
  int i, j;
  for (i=0, j=0; i<parentNum; i+=2) {
    if (isCross(crossp) == 1) {
      *t1 = parent[i].t;
      *t2 = parent[i+1].t;
      randSwap(t1, t2);
      children[j].t = *t1;
      children[j+1].t = *t2;
      j+=2;
    }
  }
  return j;
}

// 淘汰 エリート選択
void selection(Indiv *popul, Indiv *children, int populNum, int childrenNum) {
  int i, j, k;
  Indiv temp;

  for (i=0; i<childrenNum; i++) {
    // 元の集団で適応度の最も低い個体を線形探索
    for (k=0, j=1; j<populNum; j++) {
      if (popul[j].fitness < popul[k].fitness) {
        k = j;
      }
    }
    // 探索した個体と子を比較交換
    if (children[i].fitness > popul[k].fitness) {
      temp = popul[k];
      popul[k] = children[i];
      children[i] = temp;
    }
  }
}

// 突然変異
void mutation(Indiv *popul, int populNum, int mutatep) {
  if (uRand(100-1) < mutatep) {
    randChangeNodeValue(&(popul[uRand(populNum-1)].t));
  }
}
