/*
 * btc.h
 * 2016/07/29(Fri)
 * Kazuki Nagamine (145725A)
 * binary tree chromosome
 */

/* Header */
// 標準ライブラリ
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// 分数計算ライブラリ
#include "frac.h"

/* Struct */
// Node型構造体 二分木型染色体の二分木の各ノードの定義
struct node {
  int nodeType; // 0:root, 1:grandparent, 2:parent, 3:reaf
  char value; // 1~9, +, -, *, /
  struct node *el, *er; // edge left, right
}; typedef struct node Node;

// 二分木型染色体の定義
struct tree {
  int treeType; // 1 ~ 5
  Node *r; // root node
}; typedef struct tree Tree;

/* uRand */
// μsを利用した乱数生成
struct timeval myTime;
void initRand() {
  gettimeofday(&myTime, NULL);
  srand((unsigned) myTime.tv_usec);
}
int uRand(int range) {
  gettimeofday(&myTime, NULL);
  return (rand()%(RAND_MAX-1000000)+myTime.tv_usec)%range+1;
}

/* Prototype */
// set
void setNodeValues(Node *n, char value);
void setNodeStructure(Node *n, int nodeType, Node *el, Node *er);
void setTreeType(Tree *t, int treeType);
void setTreeValues(Tree *t, Node *nodes, char *opes, int *nums);
void setTreeStructures(Tree *t, Node *nodes);

// init
void initTree(Tree *t, int treeType, char *opes, int *nums, Node *nodes);

// rand
void randNums(int *nums);
void randOpes(char *opes);
void randMakeTree(Tree *t, Node *nodes);
void randSwap(Tree *t1, Tree *t2);
void randChangeNodeValue(Tree *t);

// get
void getNodeValue(Node *n, char *buf);
void getPartialTreeValues(Node *n, int *pos, char *buf);
void getTreeValues(Tree *t, char *buf);

// convert
void tree2stack(Tree *t, char *stack);
void stack2fomula(int treeType, char *stack, char *fomula);
void stack2frac(char *stack, int treeType, char *res);
void tree2fomula(Tree *t, char *fomula);
float frac2float(char *num);
void tree2float(Tree *t, float *resf);

// print
void printTreeStack(Tree *t);
void printNode(Node *n);
void printTree(Tree *t);
void printTreeFomula(Tree *t);

// copy
void copyNodeValues(Node *from, Node *to);
void copyTreeValues(Tree *from, Tree *to, Node *toNodes);
void copyTree(Tree *from, Tree *to, Node *toNodes);

// search
int searchSameTypeNodePos(Tree *t, int searchNodeType, int *passCount);

// swap
void swapNodeValues(Node *n1, Node *n2);
void swapTreeType(Tree *t1, Tree *t2);
void swapGrandParentTypeNode(Tree *t1, Tree *t2);
void swapParentTypeNode(Node *n1, Node *n2);
int swapPartialTree(Tree *t1, Tree *t2, int swapPos1, int *passCount);


/* Function */
// 1つのNodeに指定されたvalueを設定
void setNodeValues(Node *n, char value) {
  n->value = value;
}

// 1つのNodeに指定されたnodeTypeとedgeを設定
void setNodeStructure(Node *n, int nodeType, Node *el, Node *er) {
  n->nodeType = nodeType;
  n->el = el;
  n->er = er;
}

// 1つのTreeに指定されたtreeTypeを設定
void setTreeType(Tree *t, int treeType) {
  t->treeType = treeType;
}

// 1つのTreeに属する各Nodeに木のtreeTypeに従ってvalueを設定
void setTreeValues(Tree *t, Node *nodes, char *opes, int *nums) {
  switch(t->treeType) {
    case 1:
      setNodeValues(&(nodes[0]), opes[0]);
      setNodeValues(&(nodes[1]), (nums[0]+48));
      setNodeValues(&(nodes[2]), opes[1]);
      setNodeValues(&(nodes[3]), (nums[1]+48));
      setNodeValues(&(nodes[4]), (nums[2]+48));
      setNodeValues(&(nodes[5]), opes[2]);
      setNodeValues(&(nodes[6]), (nums[3]+48));
      break;
    case 2:
      setNodeValues(&(nodes[0]), opes[0]);
      setNodeValues(&(nodes[1]), (nums[0]+48));
      setNodeValues(&(nodes[2]), opes[1]);
      setNodeValues(&(nodes[3]), (nums[1]+48));
      setNodeValues(&(nodes[4]), opes[2]);
      setNodeValues(&(nodes[5]), (nums[2]+48));
      setNodeValues(&(nodes[6]), (nums[3]+48));
      break;
    case 3:
      setNodeValues(&(nodes[0]), opes[0]);
      setNodeValues(&(nodes[1]), (nums[0]+48));
      setNodeValues(&(nodes[2]), opes[1]);
      setNodeValues(&(nodes[3]), (nums[1]+48));
      setNodeValues(&(nodes[4]), opes[2]);
      setNodeValues(&(nodes[5]), (nums[2]+48));
      setNodeValues(&(nodes[6]), (nums[3]+48));
      break;
    case 4:
      setNodeValues(&(nodes[0]), opes[0]);
      setNodeValues(&(nodes[1]), (nums[0]+48));
      setNodeValues(&(nodes[2]), (nums[1]+48));
      setNodeValues(&(nodes[3]), opes[1]);
      setNodeValues(&(nodes[4]), (nums[2]+48));
      setNodeValues(&(nodes[5]), opes[2]);
      setNodeValues(&(nodes[6]), (nums[3]+48));
      break;
    case 5:
      setNodeValues(&(nodes[0]), opes[0]);
      setNodeValues(&(nodes[1]), (nums[0]+48));
      setNodeValues(&(nodes[2]), (nums[1]+48));
      setNodeValues(&(nodes[3]), opes[1]);
      setNodeValues(&(nodes[4]), (nums[2]+48));
      setNodeValues(&(nodes[5]), opes[2]);
      setNodeValues(&(nodes[6]), (nums[3]+48));
      break;
    default:
      exit(1);
      break;
  }
}

// 1つのTreeに属する各Nodeのedgeを設定してtreeTypeに従ったTreeの構造を設定
void setTreeStructures(Tree *t, Node *nodes) {
  switch(t->treeType) {
    case 1:
      setNodeStructure(&(nodes[0]), 0, &(nodes[2]), &(nodes[5]));
      setNodeStructure(&(nodes[1]), 3, NULL, NULL);
      setNodeStructure(&(nodes[2]), 2, &(nodes[1]), &(nodes[3]));
      setNodeStructure(&(nodes[3]), 3, NULL, NULL);
      setNodeStructure(&(nodes[4]), 3, NULL, NULL);
      setNodeStructure(&(nodes[5]), 2, &(nodes[4]), &(nodes[6]));
      setNodeStructure(&(nodes[6]), 3, NULL, NULL);
      break;
    case 2:
      setNodeStructure(&(nodes[0]), 0, &(nodes[4]), &(nodes[6]));
      setNodeStructure(&(nodes[1]), 3, NULL, NULL);
      setNodeStructure(&(nodes[2]), 2, &(nodes[1]), &(nodes[3]));
      setNodeStructure(&(nodes[3]), 3, NULL, NULL);
      setNodeStructure(&(nodes[4]), 1, &(nodes[2]), &(nodes[5]));
      setNodeStructure(&(nodes[5]), 3, NULL, NULL);
      setNodeStructure(&(nodes[6]), 3, NULL, NULL);
      break;
    case 3:
      setNodeStructure(&(nodes[0]), 0, &(nodes[2]), &(nodes[6]));
      setNodeStructure(&(nodes[1]), 3, NULL, NULL);
      setNodeStructure(&(nodes[2]), 1, &(nodes[1]), &(nodes[4]));
      setNodeStructure(&(nodes[3]), 3, NULL, NULL);
      setNodeStructure(&(nodes[4]), 2, &(nodes[3]), &(nodes[5]));
      setNodeStructure(&(nodes[5]), 3, NULL, NULL);
      setNodeStructure(&(nodes[6]), 3, NULL, NULL);
      break;
    case 4:
      setNodeStructure(&(nodes[0]), 0, &(nodes[1]), &(nodes[5]));
      setNodeStructure(&(nodes[1]), 3, NULL, NULL);
      setNodeStructure(&(nodes[2]), 3, NULL, NULL);
      setNodeStructure(&(nodes[3]), 2, &(nodes[2]), &(nodes[4]));
      setNodeStructure(&(nodes[4]), 3, NULL, NULL);
      setNodeStructure(&(nodes[5]), 1, &(nodes[3]), &(nodes[6]));
      setNodeStructure(&(nodes[6]), 3, NULL, NULL);
      break;
    case 5:
      setNodeStructure(&(nodes[0]), 0, &(nodes[1]), &(nodes[3]));
      setNodeStructure(&(nodes[1]), 3, NULL, NULL);
      setNodeStructure(&(nodes[2]), 3, NULL, NULL);
      setNodeStructure(&(nodes[3]), 1, &(nodes[2]), &(nodes[5]));
      setNodeStructure(&(nodes[4]), 3, NULL, NULL);
      setNodeStructure(&(nodes[5]), 2, &(nodes[4]), &(nodes[6]));
      setNodeStructure(&(nodes[6]), 3, NULL, NULL);
      break;
    default:
      exit(1);
      break;
  }
  t->r = &(nodes[0]);
}

// 与えられたパラメータを使って1つのTreeを初期化
void initTree(Tree *t, int treeType, char *opes, int *nums, Node *nodes) {
  setTreeType(t, treeType);
  setTreeValues(t, nodes, opes, nums);
  setTreeStructures(t, nodes);
}

// ランダムな数字を4つ生成
void randNums(int *nums) {
  int i;
  for (i=0; i<4; i++) {
    nums[i] = uRand(9);
  }
}

// ランダムな演算子を3つ生成
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

// ランダムなtreeTypeとNode valueのTreeを1つ生成
void randMakeTree(Tree *t, Node *nodes) {
  int treeType;
  char opes[3];
  int nums[4];
  treeType = uRand(5);
  randOpes(opes);
  randNums(nums);
  initTree(t, treeType, opes, nums, nodes);
}

// 1つのNodeのvalueを取得
void getNodeValue(Node *n, char *buf) {
  *buf = n->value;
}

// 指定されたNodeを親とした部分木の各Nodeのvalueを取得してbufに格納
void getPartialTreeValues(Node *n, int *pos, char *buf) {
  if(n == NULL) return;
  getPartialTreeValues(n->el, pos, buf);
  getPartialTreeValues(n->er, pos, buf);
  getNodeValue(n, &(buf[*pos]));
  (*pos)++;
  return;
}

// 1つのTreeの各Nodeのvalueを取得してbufに格納
void getTreeValues(Tree *t, char *buf) {
  int pos = 0;
  getPartialTreeValues(t->r, &pos, buf);
}

// 1つのTreeを逆ポーランド記法のstackに変換
void tree2stack(Tree *t, char *stack) {
  getTreeValues(t, stack);
  stack[7] = '\0';
}

// 1つのTreeをstackに変換して出力
void printTreeStack(Tree *t) {
  char stack[8];
  tree2stack(t, stack);
  printf("%s\n", stack);
}

// 1つのNodeの情報を出力
void printNode(Node *n) {
  printf("printNode --------------------\n");
  printf("nodeType  : %d\n", n->nodeType);
  printf("nodeValue : %c\n", n->value);
}

// 1つのTreeの情報を出力
void printTree(Tree *t) {
  printf("printTree --------------------\n");
  printf("treeType  : %d\n", t->treeType);
  printf("treeStack : ");
  printTreeStack(t);
}

// 1つのstackを逆ポーランド記法を用いて式に変換
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

// 1つのTreeを式に変換
void tree2fomula(Tree *t, char *fomula) {
  char stack[8];
  tree2stack(t, stack);
  stack2fomula(t->treeType, stack, fomula);
}

// 1つのTreeを式に変換して出力
void printTreeFomula(Tree *t) {
  char fomula[16];
  tree2fomula(t, fomula);
  printf("%s\n", fomula);
}

// 1つのstackをtreeTypeに従って分数に変換
void stack2frac(char *stack, int treeType, char *res) {
  char buf[32], res1[8], res2[8];
  switch (treeType) {
    case 1:
      sprintf(buf, "%c %c %c", stack[0], stack[2], stack[1]);
      frac(buf, res1);
      sprintf(buf, "%c %c %c", stack[3], stack[5], stack[4]);
      frac(buf, res2);
      sprintf(buf, "%s %c %s", res1, stack[6], res2);
      frac(buf, res);
      break;
    case 2:
      sprintf(buf, "%c %c %c", stack[0], stack[2], stack[1]);
      frac(buf, res1);
      sprintf(buf, "%s %c %c", res1, stack[4], stack[3]);
      frac(buf, res2);
      sprintf(buf, "%s %c %c", res2, stack[6], stack[5]);
      frac(buf, res);
      break;
    case 3:
      sprintf(buf, "%c %c %c", stack[1], stack[3], stack[2]);
      frac(buf, res1);
      sprintf(buf, "%c %c %s", stack[0], stack[4], res1);
      frac(buf, res2);
      sprintf(buf, "%s %c %c", res2, stack[6], stack[5]);
      frac(buf, res);
      break;
    case 4:
      sprintf(buf, "%c %c %c", stack[1], stack[3], stack[2]);
      frac(buf, res1);
      sprintf(buf, "%s %c %c", res1, stack[5], stack[4]);
      frac(buf, res2);
      sprintf(buf, "%c %c %s", stack[0], stack[6], res2);
      frac(buf, res);
      break;
    case 5:
      sprintf(buf, "%c %c %c", stack[2], stack[4], stack[3]);
      frac(buf, res1);
      sprintf(buf, "%c %c %s", stack[1], stack[5], res1);
      frac(buf, res2);
      sprintf(buf, "%c %c %s", stack[0], stack[6], res2);
      frac(buf, res);
      break;
  }
}

// 分数を小数に変換
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

// 1つのTreeを小数に変換
void tree2float(Tree *t, float *resf) {
  char stack[8], resc[8];
  tree2stack(t, stack);
  stack2frac(stack, t->treeType, resc);
  *resf = frac2float(resc);
}

// fromのNodeのvalueをtoのNodeにコピー
void copyNodeValues(Node *from, Node *to) {
  to->value = from->value;
}

// fromのTreeの各NodeのvalueをtoのTreeにコピー
void copyTreeValues(Tree *from, Tree *to, Node *toNodes) {
  Node *pf = from->r;

  int i;
  for (i=0; i<7; i++) {
    copyNodeValues(&(pf[i]), &(toNodes[i]));
  }
  to->r = &(toNodes[0]);
}

// fromのTreeの各Nodeのvalueと構造をtoのTreeにコピー
void copyTree(Tree *from, Tree *to, Node *toNodes) {
  setTreeType(to, from->treeType);
  copyTreeValues(from, to, toNodes);
  setTreeStructures(to, toNodes);
}

// 指定されたnodeTypeのNodeをtの中から探索
// 見つかればpositionを返す
// 見つからなければ-1を返す
int searchSameTypeNodePos(Tree *t, int searchNodeType, int *passCount) {
  Node *p = t->r;

  int i;
  for (i=0; i<7; i++) {
    if (p[i].nodeType == searchNodeType) {
      if (*passCount == 0) {
        return i;
      }
      else {
        (*passCount)--;
      }
    }
  }

  return -1;
}

// n1のNodeとn2のNodeのvalueの入れ替え
void swapNodeValues(Node *n1, Node *n2) {
  Node temp;
  copyNodeValues(n1, &temp);
  copyNodeValues(n2, n1);
  copyNodeValues(&temp, n2);
}

// t1のtreeTypeとt2のtreeTypeを入れ替え
void swapTreeType(Tree *t1, Tree *t2) {
  int temp = t1->treeType;
  setTreeType(t1, t2->treeType);
  setTreeType(t2, temp);
}

// nodeType=1のNode同士の部分木の入れ替え
void swapGrandParentTypeNode(Tree *t1, Tree *t2) {
  if ( (t1->treeType == 2 || t1->treeType == 3) && (t2->treeType == 2 || t2->treeType == 3) ) {
    swapNodeValues(&(t1->r[1]), &(t2->r[1]));
    swapNodeValues(&(t1->r[2]), &(t2->r[2]));
    swapNodeValues(&(t1->r[3]), &(t2->r[3]));
    swapNodeValues(&(t1->r[4]), &(t2->r[4]));
    swapNodeValues(&(t1->r[5]), &(t2->r[5]));
    swapTreeType(t1, t2);
  }
  else if ( (t1->treeType == 2 || t1->treeType == 3) && (t2->treeType == 4 || t2->treeType == 5) ) {
    swapNodeValues(&(t1->r[4]), &(t2->r[5]));
    swapNodeValues(&(t1->r[2]), &(t2->r[3]));
    swapNodeValues(&(t1->r[1]), &(t2->r[2]));
    swapNodeValues(&(t1->r[3]), &(t2->r[4]));
    swapNodeValues(&(t1->r[5]), &(t2->r[6]));
    if (t1->treeType == 2 && t2->treeType == 5) {
      setTreeType(t1, 3);
      setTreeType(t2, 4);
    }
    else if (t1->treeType == 3 && t2->treeType == 4) {
      setTreeType(t1, 2);
      setTreeType(t2, 5);
    }
  }
  else if ( (t1->treeType == 4 || t1->treeType == 5) && (t2->treeType == 2 && t2->treeType == 3) ) {
    swapNodeValues(&(t1->r[5]), &(t2->r[4]));
    swapNodeValues(&(t1->r[3]), &(t2->r[2]));
    swapNodeValues(&(t1->r[2]), &(t2->r[1]));
    swapNodeValues(&(t1->r[4]), &(t2->r[3]));
    swapNodeValues(&(t1->r[6]), &(t2->r[5]));
    if (t1->treeType == 4 && t2->treeType == 3) {
      setTreeType(t1, 5);
      setTreeType(t2, 2);
    }
    else if (t1->treeType == 5 && t2->treeType == 2) {
      setTreeType(t1, 4);
      setTreeType(t2, 3);
    }
  }
  else if ( (t1->treeType == 4 || t1->treeType == 5) && (t2->treeType == 4 || t2->treeType == 5) ) {
    swapNodeValues(&(t1->r[2]), &(t2->r[2]));
    swapNodeValues(&(t1->r[3]), &(t2->r[3]));
    swapNodeValues(&(t1->r[4]), &(t2->r[4]));
    swapNodeValues(&(t1->r[5]), &(t2->r[5]));
    swapNodeValues(&(t1->r[6]), &(t2->r[6]));
    swapTreeType(t1, t2);
  }

  setTreeStructures(t1, t1->r);
  setTreeStructures(t2, t2->r);
}

// nodeType=2のNode同士の部分木の入れ替え
void swapParentTypeNode(Node *n1, Node *n2) {
  swapNodeValues(n1->el, n2->el);
  swapNodeValues(n1->er, n2->er);
  swapNodeValues(n1, n2);
}

// Tree t1, t2の部分木を入れ替え
// swapPos1はt1で入れ替えたいNodeのpositionを表す
// passCountはt2の中で見つかったsearchNodeTypeのNodeを何回見過ごすかを表す
// 1. swapPos1を使ってt1の1つのNodeを選択しsearchNodeTypeに
// 2. searchNodeTypeに従ってpassCountを調整
//    1,0 ならどの木にも0,1のnodeTypeのNodeは1つしかないのでpassCount=0
//    2 ならt2のtreeTypeが1ならnodeTypeが2のNodeが2つあるので1以下，それ以外は1つしかないので0
// 3. t2からsearchTypeNodeのNodeを探す 見つからなければ-1を返す
// 4. searchNodeTypeに従って部分木を入れ替え
int swapPartialTree(Tree *t1, Tree *t2, int swapPos1, int *passCount) {
  int searchNodeType = t1->r[swapPos1].nodeType;
  if (searchNodeType == 0 || searchNodeType == 1) *passCount = 0;
  if (searchNodeType == 2 && *passCount > 1) *passCount = 1;
  if (searchNodeType == 2 && t2->treeType != 1) *passCount = 0;

  int swapPos2 = searchSameTypeNodePos(t2, searchNodeType, passCount);
  if (swapPos2 == -1) {
    return -1;
  }

  if (searchNodeType == 1) {
    swapGrandParentTypeNode(t1, t2);
  }
  else if (searchNodeType == 2) {
    swapParentTypeNode(&(t1->r[swapPos1]), &(t2->r[swapPos2]));
  }
  else if (searchNodeType == 3) {
    swapNodeValues(&(t1->r[swapPos1]), &(t2->r[swapPos2]));
  }
  else {
    return -1;
  }

  return 0;
}

// 2つのTreeのランダムな位置の部分木で入れ替える
void randSwap(Tree *t1, Tree *t2) {
  int swapPos1, passCount, res;
  while (1) {
    swapPos1 = uRand(6);
    passCount = uRand(4)-1;
    res = swapPartialTree(t1, t2, swapPos1, &passCount);
    if (res == 0) {
      break;
    }
  }
}

// 1つのTreeのランダムな1つのNodeのvalueをランダムに変更する
// 数値であれば数値に，演算子であれば演算子に
void randChangeNodeValue(Tree *t) {
  int changePos = uRand(7)-1;
  if (t->r[changePos].value < 48) {
    switch (uRand(4)) {
      case 1:
        t->r[changePos].value = '+';
        break;
      case 2:
        t->r[changePos].value = '-';
        break;
      case 3:
        t->r[changePos].value = '*';
        break;
      case 4:
        t->r[changePos].value = '/';
        break;
    }
  }
  else {
    t->r[changePos].value = uRand(9)+48;
  }
}
