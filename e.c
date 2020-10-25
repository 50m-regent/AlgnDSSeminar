/* eを1000桁まで求めるプログラム */
#include <stdio.h>

void ladd(short *a, short *b, short *c);
void ldiv(short *a, short b, short *c);
void printresult(short *c);

#define L 1000                 /* 求める桁数 */
#define L1 ((L/4)+1)           /* 配列のサイズ */
#define L2 (L1+1)              /* ひとつ余分にとる */
#define N 451 /* 計算する項数 */

int main() {
  short e[L2], f[L2];
  short i;
  
  for (i = 0; i < L2; i++) e[i] = f[i] = 0;
  e[0] = f[0] = 1;

  for (i = 1; i <= N; i++) {
    ldiv(f, i, f);
    ladd(e, f, e);
  }
  printresult(e);
}

void printresult(short c[]) {
  short i;
  printf("%3d. ", c[0]); /* 最上位桁の表示 */
  for (i=1; i<L1; i++) printf("%04d ", c[i]);
  printf("\n");
}

void ladd(short a[], short b[], short c[]) {
  short i, cy=0;
  for (i=L1; i>=0; i--) {
    c[i]=a[i]+b[i]+cy;
    if (c[i]<10000) { cy = 0; }
    else {
      c[i] = c[i]-10000;
      cy = 1;
    }
  }
}

void ldiv(short a[], short b, short c[]) {
  short  i;
  long   d, rem=0;
  for (i=0; i<L2; i++) {
    d = a[i];
    c[i] =(d+rem)/b;
    rem = ((d+rem)%b)*10000;
  }
}
