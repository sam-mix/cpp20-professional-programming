/*************************************************************************
    > File Name: vector.c
    > Author: Netcan
    > Mail: 1469709759@qq.com
    > Created Time: 2014/12/8 15:52:07
 ************************************************************************/

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct vector {
  int *pBase;    // 数组元素首地址
  int growfact;  // 增长因子
  int cnt;       // 当前有效元素个数
  int len;       // 数组最大长度
} vector;

bool initV(vector *v);                      // 初始化 vector
void freeV(vector *v);                      // 释放 vector
void showV(vector *v);                      // 输出 vector
void showCntV(vector *v);                   // 显示有效元素个数
void insertV(vector *v, int pos, int val);  // 插入 val 到 vector[pos-1] 中
void appendV(vector *v, int val);           // 往 vector 后追加元素
bool is_fullV(vector *v);                   // 检测 vector 是否满了
bool is_emptyV(vector *v);                  // 检测 vector 是否为空
void inversionV(vector *v);                 // 倒置 vector
void sortV(vector *v);                      // 冒泡排序 vector
int getVEle(vector *v, int pos);            // 获取 vector[pos-1]
int getVSize(vector *s);                    // 获取 vector 大小

int main() {
  srand(int(time(0)));
  vector v;
  initV(&v);
  for (int i = 0; i < 50; i++)
    appendV(&v, rand() % 100);  // 测试追加和自动增长内存
  printf("vector size: %d\n", getVSize(&v));
  showV(&v);  // 测试输出
  puts("inversion vector");
  inversionV(&v);  // 测试倒置
  showV(&v);
  puts("sort vector");
  sortV(&v);  // 测试排序
  showV(&v);
  puts("find vector element");
  printf("vector[2]=%d\n", getVEle(&v, 3));  // 测试获取元素
  freeV(&v);                                 // 释放 vector

  return 0;
}

bool initV(vector *v) {
  v->growfact = 5;  // 默认增长因子为 5
  v->cnt = 0;
  v->len = v->growfact;
  if (NULL == (v->pBase = (int *)malloc(sizeof(int) * v->len))) {
    puts("malloc error");
    return false;
  }
}
void freeV(vector *v) { free(v->pBase); }

bool is_emptyV(vector *v) {
  if (v->cnt == 0)
    return true;
  else
    return false;
}

bool is_fullV(vector *v) {
  if (v->cnt == v->len)
    return true;
  else
    return false;
}

void showV(vector *v) {
  if (is_emptyV(v)) {
    puts("vector empty");
    return;
  }
  for (int i = 0; i < v->cnt; ++i) printf("%d", v->pBase[i]);
  puts("");
}

void appendV(vector *v, int val) {
  if (is_fullV(v)) {
    puts("vector full,automatic grow space.");
    int *pNew =
        (int *)malloc(sizeof(int) * (v->len + v->growfact));     // 扩展内存
    if (memcpy(pNew, v->pBase, sizeof(int) * v->len) == NULL) {  // 复制内存
      puts("vector grow space falut");
      return;
    } else {
      v->len += v->growfact;
      free(v->pBase);   // 删除原内存
      v->pBase = pNew;  // 指向新内存
      puts("vector grow space success");
    }
  }
  v->pBase[v->cnt++] = val;
}

void insertV(vector *v, int pos, int val) {
  if (is_fullV(v)) {
    puts("vector full");
    return;
  }
  if (pos < 1 || pos > v->cnt) {
    puts("insert error");
    return;
  }
  for (int i = v->cnt - 1; i >= pos - 1; i--) v->pBase[i + 1] = v->pBase[i];
  v->pBase[pos - 1] = val;
  v->cnt++;
}

void showCntV(vector *v) { printf("vector cnt: %d\n", v->cnt); }

void inversionV(vector *v) {
  if (is_emptyV(v)) {
    puts("vector empty");
    return;
  }
  for (int i = 0; i < v->cnt / 2; ++i) {
    int t = v->pBase[i];
    v->pBase[i] = v->pBase[v->cnt - i - 1];
    v->pBase[v->cnt - i - 1] = t;
  }
}

void sortV(vector *v) {
  if (is_emptyV(v)) {
    puts("vector empty");
    return;
  }
  for (int i = 0; i < v->cnt; ++i)
    for (int j = i + 1; j < v->cnt; ++j)
      if (v->pBase[i] > v->pBase[j]) {
        int t = v->pBase[i];
        v->pBase[i] = v->pBase[j];
        v->pBase[j] = t;
      }
}

int getVEle(vector *v, int pos) {
  if (pos < 1 || pos > v->cnt) {
    printf("Outside the range finding\n");
    return 0;
  }
  return v->pBase[pos - 1];
}

int getVSize(vector *v) { return v->len; }