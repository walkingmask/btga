/* 
 * btga.h
 * 2016/07/29(Fri)
 * Kazuki Nagamine (145725A)
 * binary tree genetic algorythm
 */

/* Header */
#include "btc.h"

/* Struct */
// 個体
struct individual {
  Tree t;
  Node nodes[7];
  float fitness;
}; typedef struct individual Indiv;

// スタックの保存用リスト
struct stock {
  int treeType;
  char stack[8];
  struct stock *next;
}; typedef struct stock Stock;

/* Prototype */
// init 
void initIndiv(Indiv *indiv);
void initPopul(Indiv *popul, int populNum);

// check
int checkExistance(Stock **stock, char *stack);
int checkSelected(int *selected, int select, int num);

// stock
void add2Stock(Stock **stock, char *stack, int treeType);
void freeStock(Stock **stock);
void printStock(Stock **stock);
void printStockNum(Stock **stock);
void printStockFomula(Stock **stock);

// fitness
void indivFitness(Indiv *indiv, Stock **stock);
void populFitness(Indiv *popul, int populNum, Stock **stock);
void printIndivFitness(Indiv *indiv);
void printPopulFitness(Indiv *popul, int populNum);
void printPopulFitnessAve(Indiv *popul, int populNum);
void printPopulFitnessMax(Indiv *popul, int populNum);
void printPopulFitnessMin(Indiv *popul, int populNum);

// copy
void copyIndiv(Indiv *from, Indiv *to);

// main
void selectParents(Indiv *popul, Indiv *parents, int populNum, int parentsNum);
int crossing(Indiv *parents, Indiv *children, int parentsNum, int crossp);
void selection(Indiv *popul, Indiv *children, int populNum, int childrenNum);
void mutation(Indiv *popul, int populNum, int mutatep);

/* Function */
// 1つの個体の初期化
void initIndiv(Indiv *indiv) {
  randMakeTree(&(indiv->t), indiv->nodes);
}

// 初期集団の生成
void initPopul(Indiv *popul, int populNum) {
  int i;
  for (i=0; i<populNum; i++) {
    initIndiv(&popul[i]);
  }
}

// 指定されたstackがStockにあるか確認
// あれば0 ないまたはStockが空ならば1を返す
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

// Stockに新しいstackを追加
void add2Stock(Stock **stock, char *stack, int treeType) {
  Stock *s = (Stock *)malloc(sizeof(Stock));
  strcpy(s->stack, stack);
  s->treeType = treeType;
  s->next = NULL;
  if (*stock == NULL) {
    *stock = s;
  }
  else {
    while ((*stock)->next != NULL) stock = &((*stock)->next);
    (*stock)->next = s;
  }
}

// Stockのメモリを解放する
void freeStock(Stock **stock) {
  if ((*stock)->next != NULL) {
    freeStock(&(*stock)->next);
  }
  free(*stock);
}

// Stockに含まれるstackを全て出力
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

// Stockに含まれるstackの数を出力
void printStockNum(Stock **stock) {
  if (*stock == NULL) {
    printf("0\n");
    return;
  }
  int count = 0;
  while ((*stock)->next != NULL) {
    count++;
    stock = &((*stock)->next);
  }
  printf("%d\n", count);
}

void printStockFomula(Stock **stock) {
  char fomula[16];
  if (*stock == NULL) {
    return;
  }
  while ((*stock)->next != NULL) {
    stack2fomula((*stock)->treeType, (*stock)->stack, fomula);
    printf("%s, ", fomula);
    stock = &((*stock)->next);
  }
  stack2fomula((*stock)->treeType, (*stock)->stack, fomula);
  printf("%s\n", fomula);
}

// 1つの個体の適応度の計算
// 個体の木を小数に変換して10.0に近いほど適応度が高い
// 10.0丁度だとStockに木をstackに変換したものが存在するか確認
// なければStockに追加し，その個体の適応度を大きく下げる
// あれば単純に適応度を大きく下げる
void indivFitness(Indiv *indiv, Stock **stock) {
  char stack[8];
  tree2stack(&(indiv->t), stack);
  if (checkExistance(stock, stack) == 0) {
    indiv->fitness = -1000;
  }
  else {
    tree2float(&(indiv->t), &(indiv->fitness));
    indiv->fitness = -fabs(10.0 - indiv->fitness);
    if (indiv->fitness == 0) {
      add2Stock(stock, stack, indiv->t.treeType);
      indiv->fitness = -1000;
    }
  }
}

// 集団の全ての個体の適応度の計算
void populFitness(Indiv *popul, int populNum, Stock **stock) {
  int i;
  for (i=0; i<populNum; i++) {
    indivFitness(&popul[i], stock);
  }
}

// 1つの個体の適応度の出力
void printIndivFitness(Indiv *indiv) {
  printf("%f\n", indiv->fitness);
}

// 集団の全個体の適応度の出力
void printPopulFitness(Indiv *popul, int populNum) {
  int i;
  for (i=0; i<populNum; i++) {
    printIndivFitness(&popul[i]);
  }
}

// 集団の平均適応度を出力
void printPopulFitnessAve(Indiv *popul, int populNum) {
  float ave;
  int i;
  for (ave=.0, i=0; i<populNum; i++) {
    ave += popul[i].fitness;
  }
  printf("%f\n", ave/populNum);
}

// 集団の最大適応度を出力
void printPopulFitnessMax(Indiv *popul, int populNum) {
  float max;
  int i;
  max = popul[0].fitness;
  for (i=1; i<populNum; i++) {
    max = (popul[i].fitness > max)? popul[i].fitness : max;
  }
  printf("%f\n", max);
}

// 集団の最小適応度を出力
void printPopulFitnessMin(Indiv *popul, int populNum) {
  float min;
  int i;
  min = popul[0].fitness;
  for (i=1; i<populNum; i++) {
    min = (popul[i].fitness < min)? popul[i].fitness : min;
  }
  printf("%f\n", min);
}

// 個体をコピーする
void copyIndiv(Indiv *from, Indiv *to) {
  copyTree(&(from->t), &(to->t), to->nodes);
  to->fitness = from->fitness;
}

// 指定された値selectがすでに選択された値の配列selectedのnumまでに存在するか確認
int checkSelected(int *selected, int select, int num) {
  int i;
  for (i=0; i<num; i++) {
    if (select == selected[i]) {
      return 1;
    }
  }
  return 0;
}

// 集団から親となる個体の選択
void selectParents(Indiv *popul, Indiv *parents, int populNum, int parentsNum) {
  int i, j, selected[parentsNum];
  for(i=0; i<parentsNum; i++) {
    while (1) {
      j = uRand(populNum-1);
      if (checkSelected(selected, j, i) == 0) {
        break;
      }
    }
    copyIndiv(&(popul[j]), &(parents[i]));
  }
}

// 親の集団から交叉確率crosspに従って交叉を行い子の集団を生成する
// 生成された子の数を返す
int crossing(Indiv *parents, Indiv *children, int parentsNum, int crossp) {
  int i, j;
  for (i=0, j=0; i<parentsNum; i+=2) {
    if (uRand(100)-1 < crossp) {
      copyIndiv( &(parents[i]), &(children[j]) );
      copyIndiv( &(parents[i+1]), &(children[j+1]) );
      randSwap( &(children[j].t), &(children[j+1].t) );
      j+=2;
    }
  }
  return j;
}

// 淘汰
// 元の集団で最も適応度の低い個体を線形探索し子の個体と比較して適応度の高い方を元の集団に残す
void selection(Indiv *popul, Indiv *children, int populNum, int childrenNum) {
  int i, j, k;

  for (i=0; i<childrenNum; i++) {
    for (k=0, j=1; j<populNum; j++) {
      if (popul[j].fitness < popul[k].fitness) {
        k = j;
      }
    }
    if (children[i].fitness > popul[k].fitness) {
      copyIndiv(&(children[i]), &(popul[k]));
    }
  }
}

// 突然変異確率mutepに従って突然変異を起こす
void mutation(Indiv *popul, int populNum, int mutatep) {
  if (uRand(100)-1 < mutatep) {
    randChangeNodeValue(&(popul[uRand(populNum-1)].t));
  }
}
