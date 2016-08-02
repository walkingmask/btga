/*
 * btc.h
 * 2016/07/29(Fri)
 * Kazuki Nagamine (145725A)
 * 二分木型染色体ライブラリ
 */

/* Header */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
// 分数計算ライブラリ
#include "frac.h"


/* Struct */
// Node型構造体 二分木型染色体の二分木の各ノードの定義
struct node {
  int nodeType; // 0:root, 1:grandparent, 2:parent, 3:reaf
  char ope; int num; // value
  struct node *el, *er; // edge
}; typedef struct node Node;

// 二分木型染色体の定義
struct tree {
  int treeType; // 1 ~ 5
  Node *r; // root node
}; typedef struct tree Tree;


/* Variable */
// uRand用のtimeval変数
struct timeval myTime;


/* Prototype */
// uRand関連
void initRand();
int uRand(int range);

// Node定義
void setNode(Node *n, int nodeType, char ope, int num, Node *el, Node *er);
void freeNode(Node *n);

// Tree定義
void makeTree(Tree *t, char opes[3], int nums[4]);
void setTreeType(Tree *t, int treeType);
void initTree(Tree *t, int treeType, char opes[3], int nums[4]);
void freeTree(Tree *t);

// NodeやTreeの状態取得
void getNodeValue(Node *n, int *pos, char *buf);
void tree2stack(Tree *t, char *stack);
void printTreeStack(Tree *t);

// NodeやTreeを操作
void swapNode(Node **n1, Node **n2);
Node **searchNodeType(Node **n, int nodeType, int *passCount);
void changeTreeType(Tree *t, int newType);
void swapTreeType(Tree *t1, Tree *t2);
void swapTree(Tree *t1, Tree *t2, int depth, int direct[3], int *passCount);

// uRandを用いたTreeの操作
void randNums(int *nums);
void randOpes(char *opes);
void randMake(Tree *t);
void randSwap(Tree *t1, Tree *t2);

// 二分木型染色体の表現型の計算
void stack2fomula(int treeType, char *stack, char *fomula);
void tree2fomula(Tree *t, char *fomula);
void printTreeFomula(Tree *t);
void stack2frac(char *stack, int treeType, char *r);
float frac2float(char *num);
void tree2float(Tree *t, float *res);


/* Function */
// uRand用にseedをμsで初期化
void initRand() {
  gettimeofday(&myTime, NULL);
  srand((unsigned) myTime.tv_usec);
}

// μsを使ったrand関数 1~rangeの範囲の値を返す
int uRand(int range) {
  gettimeofday(&myTime, NULL);
  return (rand()%(RAND_MAX-1000000)+myTime.tv_usec)%range+1;
}

// Nodeの初期化
void setNode(Node *n, int nodeType, char ope, int num, Node *el, Node *er) {
  n->nodeType = nodeType;
  n->ope = ope;
  n->num = num;
  n->el = el;
  n->er = er;
}

// Nodeの解放
void freeNode(Node *n) {
  if (n == NULL) return;
  freeNode(n->el);
  freeNode(n->er);
  free(n);
  return;
}

// treeTypeに応じてNodeの関係を構造化してTreeを作成する
void makeTree(Tree *t, char opes[3], int nums[4]) {

  Node *root = (Node *)malloc(sizeof(Node));
  Node *n1 = (Node *)malloc(sizeof(Node));
  Node *n2 = (Node *)malloc(sizeof(Node));
  Node *n3 = (Node *)malloc(sizeof(Node));
  Node *n4 = (Node *)malloc(sizeof(Node));
  Node *n5 = (Node *)malloc(sizeof(Node));
  Node *n6 = (Node *)malloc(sizeof(Node));

  switch(t->treeType) {
    case 1:
      setNode(root, 0, opes[0], -1, n2, n5);
      setNode(n1, 3, 0, nums[0], NULL, NULL);
      setNode(n2, 2, opes[1], -1, n1, n3);
      setNode(n3, 3, 0, nums[1], NULL, NULL);
      setNode(n4, 3, 0, nums[2], NULL, NULL);
      setNode(n5, 2, opes[2], -1, n4, n6);
      setNode(n6, 3, 0, nums[3], NULL, NULL);
      break;
    case 2:
      setNode(root, 0, opes[0], -1, n4, n6);
      setNode(n1, 3, 0, nums[0], NULL, NULL);
      setNode(n2, 2, opes[1], -1, n1, n3);
      setNode(n3, 3, 0, nums[1], NULL, NULL);
      setNode(n4, 1, opes[2], -1, n2, n5);
      setNode(n5, 3, 0, nums[2], NULL, NULL);
      setNode(n6, 3, 0, nums[3], NULL, NULL);
      break;
    case 3:
      setNode(root, 0, opes[0], -1, n2, n6);
      setNode(n1, 3, 0, nums[0], NULL, NULL);
      setNode(n2, 1, opes[1], -1, n1, n4);
      setNode(n3, 3, 0, nums[1], NULL, NULL);
      setNode(n4, 2, opes[2], -1, n3, n5);
      setNode(n5, 3, 0, nums[2], NULL, NULL);
      setNode(n6, 3, 0, nums[3], NULL, NULL);
      break;
    case 4:
      setNode(root, 0, opes[0], -1, n1, n5);
      setNode(n1, 3, 0, nums[0], NULL, NULL);
      setNode(n2, 3, 0, nums[1], NULL, NULL);
      setNode(n3, 2, opes[1], -1, n2, n4);
      setNode(n4, 3, 0, nums[2], NULL, NULL);
      setNode(n5, 1, opes[2], -1, n3, n6);
      setNode(n6, 3, 0, nums[3], NULL, NULL);
      break;
    case 5:
      setNode(root, 0, opes[0], -1, n1, n3);
      setNode(n1, 3, 0, nums[0], NULL, NULL);
      setNode(n2, 3, 0, nums[1], NULL, NULL);
      setNode(n3, 1, opes[1], -1, n2, n5);
      setNode(n4, 3, 0, nums[2], NULL, NULL);
      setNode(n5, 2, opes[2], -1, n4, n6);
      setNode(n6, 3, 0, nums[3], NULL, NULL);
      break;
    default:
      exit(1);
      break;
  }
  t->r = root;
}

// treeTypeの初期化
void setTreeType(Tree *t, int treeType) {
  t->treeType = treeType;
  t->r = NULL;
}

// Treeの初期化処理
void initTree(Tree *t, int treeType, char opes[3], int nums[4]) {
  setTreeType(t, treeType);
  makeTree(t, opes, nums);
}

// Treeの解放
void freeTree(Tree *t) {
  freeNode(t->r);
}

// 深さ優先探索で二分木を探索してそれぞれのNodeのValueをbufに格納する
void getNodeValue(Node *n, int *pos, char *buf) {
  if(n == NULL) return;
  getNodeValue(n->el, pos, buf);
  getNodeValue(n->er, pos, buf);
  buf[*pos] = (n->nodeType != 3)? n->ope : (char)(n->num+48);
  (*pos)++;
  return;
}

// Treeの各NodeのValueをstackに格納する
void tree2stack(Tree *t, char *stack) {
  int pos = 0;
  getNodeValue(t->r, &pos, stack);
  stack[7] = '\0';
}

// 二分木をStackの状態にして出力する
void printTreeStack(Tree *t) {
  //printf("%d: ", t->treeType); //D
  char stack[8];
  tree2stack(t, stack);
  printf("%s\n", stack);
}

// Nodeを入れ替える
void swapNode(Node **n1, Node **n2) {
  Node *temp;
  temp = *n1;
  *n1 = *n2;
  *n2 = temp;
}

// nodeTypeのNodeを探索する 探索して見つけてもpassCount分だけ無視する
Node **searchNodeType(Node **n, int nodeType, int *passCount) {
  if (n == NULL) return NULL;

  if ((*n)->nodeType == nodeType) {
    if (*passCount == 0) {
      return n;
    }
    else {
      (*passCount)--;
    }
  }

  Node **temp = NULL;

  if ((*n)->el != NULL) {
    temp = searchNodeType(&((*n)->el), nodeType, passCount);
    if (temp != NULL) return temp;
  }
  if ((*n)->er != NULL) {
    temp = searchNodeType(&((*n)->er), nodeType, passCount);
    if (temp != NULL) return temp;
  }

  return temp;
}

// 二分木のtreeTypeを変更する
void changeTreeType(Tree *t, int newType) {
  t->treeType = newType;
}

// 二つの二分木のtreeTypeを入れ替える
void swapTreeType(Tree *t1, Tree *t2) {
  int temp = t1->treeType;
  changeTreeType(t1, t2->treeType);
  changeTreeType(t2, temp);
}

// 二つの二分木をあるNode点において入れ替える
// 点の指定には木の深さとそれぞれの深さにおける方向で指定する
// 指定された二つの木の組み合わせ次第ではswapした後にtreeTypeを変更する
void swapTree(Tree *t1, Tree *t2, int depth, int direct[3], int *passCount) {
  //printf("b t1: treetype: %d , stack: ", t1->treeType);printTreeStack(t1);
  //printf("b t2: treetype: %d , stack: ", t2->treeType);printTreeStack(t2);
  Node **temp1, **temp2;
  int i;
  for (i=0, temp1=&(t1->r); i<depth; i++) {
    if (direct[i] == 0)
      temp1 = ((*temp1)->el != NULL)? &((*temp1)->el) : temp1;
    else
      temp1 = ((*temp1)->er != NULL)? &((*temp1)->er) : temp1;
  }
  // be safety
  if ((*temp1)->nodeType == 0 || (*temp1)->nodeType == 1) *passCount = 0;
  if ((*temp1)->nodeType == 2 && *passCount > 1) *passCount = 1;
  if ((*temp1)->nodeType == 2 && t2->treeType != 1) *passCount = 0;

  /*if ((*temp1)->ope != 0) printf("sNodeValue: %c, ", (*temp1)->ope); //D
  if ((*temp1)->num != -1) printf("sNodeValue: %d, ", (*temp1)->num); //D
  printf("nodeType: %d, passCount: %d\n", (*temp1)->nodeType, *passCount); //D*/

  // change treeType
  if ((*temp1)->nodeType == 1) {
    //printf("**********test: t1type: %d, t2type: %d\n", t1->treeType, t2->treeType);
    if ( (t1->treeType == 2 && t2->treeType == 3) || (t1->treeType == 3 && t2->treeType == 2) ){
      swapTreeType(t1, t2);
    }
    else if (t1->treeType == 3 && t2->treeType == 4) {
      changeTreeType(t1, 2);
      changeTreeType(t2, 5);
    }
    else if (t1->treeType == 4 && t2->treeType == 3) {
      changeTreeType(t1, 5);
      changeTreeType(t2, 2);
    }
    else if ( (t1->treeType == 4 && t2->treeType == 5) || (t1->treeType == 5 && t2->treeType == 4) ){
      swapTreeType(t1, t2);
    }
    else if (t1->treeType == 2 && t2->treeType == 5) {
      changeTreeType(t1, 3);
      changeTreeType(t2, 4);
    }
    else if (t1->treeType == 5 && t2->treeType == 2) {
      changeTreeType(t1, 4);
      changeTreeType(t2, 3);
    }
  }

  temp2 = searchNodeType(&(t2->r), (*temp1)->nodeType, passCount);
  if (temp2 != NULL) {
    swapNode(temp1, temp2);
  }
  else {
    randSwap(t1, t2);
  }
  //printf("a t1: treetype: %d , stack: ", t1->treeType);printTreeStack(t1);
  //printf("a t2: treetype: %d , stack: ", t2->treeType);printTreeStack(t2);
}

// uRandを使ってランダムな4つの数字を生成する
void randNums(int *nums) {
  int i;
  for (i=0; i<4; i++) {
    nums[i] = uRand(9);
  }
}

// uRandを使ってランダムな3つの演算子を生成する
void randOpes(char *opes) {
  int i;
  for (i=0; i<3; i++) {
    switch (uRand(4)) {
      case 1:
        opes[i] = '+';
        break;
      case 2:
        opes[i] = '-';
        break;
      case 3:
        opes[i] = '*';
        break;
      case 4:
        opes[i] = '/';
        break;
    }
  }
}

// uRandを使ったランダムな二分木の生成
void randMake(Tree *t) {
  int treeType;
  char opes[3];
  int nums[4];
  treeType = uRand(5);
  randOpes(opes);
  randNums(nums);
  initTree(t, treeType, opes, nums);
}

// uRandを使ったランダムな木のswap
void randSwap(Tree *t1, Tree *t2) {
  int depth = uRand(3);
  int direct[3] = { uRand(2)-1, uRand(2)-1, uRand(2)-1 };
  int passCount = uRand(4)-1;
  swapTree(t1, t2, depth, direct, &passCount);
}

// ランダムにTreeの適当なNodeのValueを変える
void randChangeNodeValue(Tree *t) {
  int depth = uRand(3);
  int direct[3] = { uRand(2)-1, uRand(2)-1, uRand(2)-1 };
  Node **temp;
  int i;
  for (i=0, temp=&(t->r); i<depth; i++) {
    if (direct[i] == 0)
      temp = ((*temp)->el != NULL)? &((*temp)->el) : temp;
    else
      temp = ((*temp)->er != NULL)? &((*temp)->er) : temp;
  }
  if ((*temp)->ope != 0) {
    switch (uRand(4)) {
      case 1:
        (*temp)->ope = '+';
        break;
      case 2:
        (*temp)->ope = '-';
        break;
      case 3:
        (*temp)->ope = '*';
        break;
      case 4:
        (*temp)->ope = '/';
        break;
    }
  }
  else {
    (*temp)->num = uRand(9);
  }
}

// stackに入った数字と演算子を逆ポーランド記法を使って数式に変換する
void stack2fomula(int treeType, char *stack, char *fomula) {
  switch (treeType) {
    case 1:
      sprintf(fomula, "((%c%c%c)%c(%c%c%c))", stack[0],stack[2],stack[1],stack[6],stack[3],stack[5],stack[4]);
      break;
    case 2:
      sprintf(fomula, "(((%c%c%c)%c%c)%c%c)", stack[0],stack[2],stack[1],stack[4],stack[3],stack[6],stack[5]);
      break;
    case 3:
      sprintf(fomula, "((%c%c(%c%c%c))%c%c)", stack[0],stack[4],stack[1],stack[3],stack[2],stack[6],stack[5]);
      break;
    case 4:
      sprintf(fomula, "(%c%c((%c%c%c)%c%c))", stack[0],stack[6],stack[1],stack[3],stack[2],stack[5],stack[4]);
      break;
    case 5:
      sprintf(fomula, "(%c%c(%c%c(%c%c%c)))", stack[0],stack[6],stack[1],stack[5],stack[2],stack[4],stack[3]);
      break;
  }
}

// 二分木を数式に変換する
void tree2fomula(Tree *t, char *fomula) {
  char stack[8];
  tree2stack(t, stack);
  stack2fomula(t->treeType, stack, fomula);
}

// 二分木を数式に変換して出力する
void printTreeFomula(Tree *t) {
  char fomula[16];
  tree2fomula(t, fomula);
  printf("%s\n", fomula);
}

// スタックを分数に変換する
void stack2frac(char *stack, int treeType, char *res) {
  char buf[32], res1[8], res2[8];
  switch (treeType) {
    case 1:
      sprintf(buf, "%c %c %c", stack[0], stack[2], stack[1]);
      //printf("%s, ", buf); //D
      frac(buf, res1);
      sprintf(buf, "%c %c %c", stack[3], stack[5], stack[4]);
      //printf("%s, ", buf); //D
      frac(buf, res2);
      sprintf(buf, "%s %c %s", res1, stack[6], res2);
      //printf("%s, ", buf); //D
      frac(buf, res);
      break;
    case 2:
      sprintf(buf, "%c %c %c", stack[0], stack[2], stack[1]);
      //printf("%s, ", buf); //D
      frac(buf, res1);
      sprintf(buf, "%s %c %c", res1, stack[4], stack[3]);
      //printf("%s, ", buf); //D
      frac(buf, res2);
      sprintf(buf, "%s %c %c", res2, stack[6], stack[5]);
      //printf("%s, ", buf); //D
      frac(buf, res);
      break;
    case 3:
      sprintf(buf, "%c %c %c", stack[1], stack[3], stack[2]);
      //printf("%s, ", buf); //D
      frac(buf, res1);
      sprintf(buf, "%c %c %s", stack[0], stack[4], res1);
      //printf("%s, ", buf); //D
      frac(buf, res2);
      sprintf(buf, "%s %c %c", res2, stack[6], stack[5]);
      //printf("%s, ", buf); //D
      frac(buf, res);
      break;
    case 4:
      sprintf(buf, "%c %c %c", stack[1], stack[3], stack[2]);
      //printf("%s, ", buf); //D
      frac(buf, res1);
      sprintf(buf, "%s %c %c", res1, stack[5], stack[4]);
      //printf("%s, ", buf); //D
      frac(buf, res2);
      sprintf(buf, "%c %c %s", stack[0], stack[6], res2);
      //printf("%s, ", buf); //D
      frac(buf, res);
      break;
    case 5:
      sprintf(buf, "%c %c %c", stack[2], stack[4], stack[3]);
      //printf("%s, ", buf); //D
      frac(buf, res1);
      sprintf(buf, "%c %c %s", stack[1], stack[5], res1);
      //printf("%s, ", buf); //D
      frac(buf, res2);
      sprintf(buf, "%c %c %s", stack[0], stack[6], res2);
      //printf("%s, ", buf); //D
      frac(buf, res);
      break;
  }
}

// 分数を小数に変換する
float frac2float(char *num) {
  if (strcmp(num, "inf") == 0){
    return 0;
  }
  float res;
  if (isfrac(num) == 0) {
    float top, bot;
    sscanf(num, "%f/%f", &top, &bot);
    res = top/bot;
  }
  else
    sscanf(num, "%f", &res);
  return res;
}

// 二分木を小数に変換する
void tree2float(Tree *t, float *resf) {
  char stack[8], resc[8];
  tree2stack(t, stack);
  stack2frac(stack, t->treeType, resc);
  //printf("%s\n", res3); //D
  *resf = frac2float(resc);
}
