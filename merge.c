#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *buffer;

void MergeSort(int n, int x[]) {
    int i, j, k, m;

    if (n <= 1) return;
    m = n / 2;

    MergeSort(m, x);
    MergeSort(n - m, x + m);

    for (i = 0; i < m; i++) buffer[i] = x[i];

    j = m;
    i = k = 0;

    while (i < m && j < n) {
        if (buffer[i] <= x[j]) {
            x[k] = buffer[i];
            i++;
        } else {
            x[k] = x[j];
            j++;
        }
        k++;
    }

    while (i < m) {
        x[k] = buffer[i];
        k++;
        i++;
    }
}

void QuickSort(int bottom, int top, int *data) {
    int lower, upper, div, temp;

    if (bottom >= top) return;

    div = data[bottom];

    for (lower = bottom, upper = top; lower < upper; ) {
        while (lower <= upper && data[lower] <= div) lower++;
        while (lower <= upper && data[upper] > div)  upper--;

        if (lower < upper) {
            temp = data[lower];
            data[lower] = data[upper];
            data[upper] = temp;
        }
    }

    temp = data[bottom];
    data[bottom] = data[upper];
    data[upper] = temp;

    QuickSort(bottom, upper - 1, data);
    QuickSort(upper + 1, top, data);
}

void set_random(int *sort, int n) {for (int i = 0; i < n; i++) sort[i] = rand();}

void set_ascending(int *sort, int n) {for (int i = 0; i < n; i++) sort[i] = i;}

void set_descending(int *sort, int n) {for (int i = n - 1; i >= 0; i--) sort[i] = i;}

int main() {
    srand((unsigned int)time(NULL));
    clock_t stime, etime;

    int quick_flag = 1, merge_flag = 1;

    float
        random_qt, ascending_qt, descending_qt,
        random_mt, ascending_mt, descending_mt;

    for (int n = 10; n <= 1e8; n *= 10) {
        int *sort;

        random_qt = ascending_qt = descending_qt = random_mt = ascending_mt = descending_mt = -1;
        
        if ((sort  = (int *)malloc(sizeof(int)*n))           == NULL) quick_flag = 0;
        if ((buffer= (int *)malloc(sizeof(int)*(n / 2 + 1))) == NULL) merge_flag = 0;

        if (quick_flag) {
            set_random(sort, n);
            stime = clock();
            QuickSort(0, n - 1, sort);
            etime = clock();
            random_qt = etime - stime;

            if (n <= 100000) {
                set_ascending(sort, n);
                stime = clock();
                QuickSort(0, n - 1, sort);
                etime = clock();
                ascending_qt = etime - stime;

                set_descending(sort, n);
                stime = clock();
                QuickSort(0, n - 1, sort);
                etime = clock();
                descending_qt = etime - stime;
            }
        }
        
        if (merge_flag) {
            set_random(sort, n);
            stime = clock();
            MergeSort(n, sort);
            etime = clock();
            random_mt = etime - stime;

            set_ascending(sort, n);
            stime = clock();
            MergeSort(n, sort);
            etime = clock();
            ascending_mt = etime - stime;

            set_descending(sort, n);
            stime = clock();
            MergeSort(n, sort);
            etime = clock();
            descending_mt = etime - stime;
        }

        printf("N=%d\n    Random:     [Quick: %.3fs, Merge: %.3fs]\n    Ascending:  [Quick: %.3fs, Merge: %.3fs]\n    Descending: [Quick: %.3fs, Merge: %.3fs]\n",
            n,
            random_qt / CLOCKS_PER_SEC, random_mt / CLOCKS_PER_SEC,
            ascending_qt / CLOCKS_PER_SEC, ascending_mt / CLOCKS_PER_SEC,
            descending_qt / CLOCKS_PER_SEC, descending_mt / CLOCKS_PER_SEC
        );
    }
    return EXIT_SUCCESS;
}
