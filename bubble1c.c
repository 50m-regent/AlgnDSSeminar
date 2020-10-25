/* コマンド引数に数値を与えると、その個数分のデータを生成して、
   並べ替える。実行時間だけを表示するように変更してある */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* コマンド引数省略時のデータの件数 */

void BubbleSort(int *data, int n)
{
  int i, j, flag;

  do {
    flag=0;
    for (i=0; i<n-1; i++) {
      if (data[i]>data[i+1]) {
        /* 左右の並びがおかしければ入れ替える */
        flag=1;
        j=data[i];
        data[i]=data[i+1];
        data[i+1]=j;
      }
    }
  } while (flag==1); /* 入れ替えがある間，繰り返す．*/
}

int main(int argc, char *argv[])
{
  int *sort;
  int i, n=N;
  clock_t stime, etime;

  if (argc>1) { n = atoi(argv[1]); }
  if (n>0) {
    sort = (int *)malloc(sizeof(int)*n);
    if (sort == NULL) exit(EXIT_FAILURE);
  }

  srand((unsigned int)time(NULL));

  for (i=0; i<n; i++) {
    /* 配列にランダムな値を格納 */
    sort[i] = rand();
    /* printf("%d ", sort[i]); */
  }

  printf("\nソート開始:\n");

  stime = clock(); /* 開始時刻を記録 */
  BubbleSort(sort,n);
  etime = clock(); /* 終了時刻を記録 */

  printf("ソート終了:\n");
  /* for (i=0; i<n; i++)
    printf("%d ", sort[i]);  */

  printf("\n%d 個の並べ替えをバブルソートで行ないました。", n);
  printf("実行時間は、%.3f秒でした。\n", (float)(etime-stime)/CLOCKS_PER_SEC);

  return EXIT_SUCCESS;
}

