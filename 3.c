#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int *data, int n) {
  int i, j, flag, k;

  k=0;
  do {
    flag=0;
    for (i=0; i<n-1-k; i++) { /* 最後からk番目までは整列済みなので省く */
      if (data[i]>data[i+1]) {
        /* 左右の並びがおかしければ入れ替える */
        flag=1;
        j=data[i];
        data[i]=data[i+1];
        data[i+1]=j;
      }
    }
    k++;
  } while (flag==1); /* 入れ替えがある間，繰り返す．*/
}

// 残り個数がmilestone以下の時にクイックソートからバブルソートに切り替え
void MixedSort(int bottom, int top, int *data, int milestone) {
    int lower, upper, div, temp;

    if (top - bottom < milestone) {
        BubbleSort(data + bottom, top - bottom);
        return;
    }

    div = data[(top + bottom) / 2];
  
    lower = bottom;
    upper = top;
    while (1) {
        while (data[lower] < div) lower++;
        while (data[upper] > div) upper--;
        if (lower >= upper) break;
        temp = data[lower];
        data[lower] = data[upper];
        data[upper] = temp;
        lower++; upper--;
    }
    MixedSort(bottom,    lower - 1, data, milestone);
    MixedSort(upper + 1, top,       data, milestone);
}

void QuickSort(int bottom, int top, int *data)
{
  int lower, upper, div, temp;

  if (bottom>=top) return;

  div = data[(top+bottom)/2];
  
  lower=bottom;  upper=top;
  while (1) {
    while (data[lower]<div) lower++;
    while (data[upper]>div) upper--;
    if (lower>=upper) break;
    temp = data[lower];  data[lower] = data[upper];  data[upper] = temp;
    lower++; upper--;
  }
  QuickSort(bottom, lower-1, data);
  QuickSort(upper+1, top, data);
}

void set_random(int *sort, int n) {for (int i = 0; i < n; i++) sort[i] = rand();}

int main() {
    srand((unsigned int)time(NULL));
    clock_t stime, etime;
    int n_epoch = 100, qt, _mt, mt, sum = 0;

    for (int n = 10; n <= 1e6; n *= 10) {
        for (int i = 1; i <= n_epoch; i++) {
            // printf("Epoch: %d\n", i);
            int milestone = 2;

            do {
                milestone++;
                int *sort;
                if ((sort  = (int *)malloc(sizeof(int)*n)) == NULL) return EXIT_FAILURE;

                set_random(sort, n);
                stime = clock();
                MixedSort(0, n - 1, sort, milestone);
                etime = clock();
                mt = etime - stime;

                set_random(sort, n);
                stime = clock();
                QuickSort(0, n - 1, sort);
                etime = clock();
                qt = etime - stime;

                /*
                printf("\tMilestone: %2d [Mixed: %.3f, Quick: %.3f]\n",
                    milestone, (double)mt / CLOCKS_PER_SEC, (double)qt / CLOCKS_PER_SEC
                );
                */
                
               _mt = mt;
            } while (mt < qt && _mt >= mt);
            sum += milestone;
        }

        printf("\nN=%d, Mean Milestone: %.3f\n", n, (double)sum / n_epoch);
    }
    
    return EXIT_SUCCESS;
}

