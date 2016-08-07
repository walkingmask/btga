# btga10


binary tree genetic algorythm for 10 puzzle

二分木を使った遺伝的アルゴリズムで10パズルを生成するプログラム


## build & run

    gcc btga10.c -o btga10
    ./btga10

## setting

    #define POPULN 100          // 集団の個体数
    #define PARENTSN 10*2       // 選択する親の数
    #define CHILDRENN PARENTSN  // 生成される子の最大数
    #define MAXGEN 10000        // 最大世代交代数

    sleep(1); // 適当に

## TODO

Stock内のstackとの類似度を利用した少し複雑な適応度関数の実装
