/* クイックソート */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10 /* データの件数 */

void QuickSort(int bottom, int top, int *data)
{
  int lower, upper, div, temp;

  if (bottom>=top) return;

  /* 先頭の値を「適当な値」とする */
  div = data[bottom];

  for (lower=bottom, upper=top; lower<upper; ) {
    while (lower<=upper && data[lower]<=div) lower++;
    while (lower<=upper && data[upper]>div)  upper--;

    if (lower<upper) {
      temp = data[lower];
      data[lower] = data[upper];
      data[upper] = temp;
    }
  }
  /* 最初に選択した値を中央に移動する */
  temp=data[bottom];
  data[bottom]=data[upper];
  data[upper]=temp;

  QuickSort(bottom, upper-1, data);
  QuickSort(upper+1, top, data);
}

void set_random(int *sort, int n) {for (int i = 0; i < n; i++) sort[i] = rand();}

int main(int argc, char *argv[]) {
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
    // printf("%d ", sort[i]);
  }

  printf("\nソート開始:\n");

    stime = clock();
  QuickSort(0,n-1,sort);
    etime = clock();

  printf("ソート終了:\n");

  /*
  for (i=0; i<N; i++)
    printf("%d ", sort[i]);
*/

    printf("\n%d 個の並べ替えをクイックソートで行ないました。", n);
  printf("実行時間は、%.3f秒でした。\n", (float)(etime-stime)/CLOCKS_PER_SEC);

  return EXIT_SUCCESS;
}
