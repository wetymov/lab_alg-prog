#define _CRT_SECURE_NO_WARNINGS // отменяет предупреждения системы
#include <stdio.h>
#define ll long long
#define xorswap(a, b) (int*)((ll)a ^ (ll)b)
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// (a == b) ? yes : no

void init_rng(void) {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)curtime); // установка зерна для (псевдо)рандома
}

int gen_rnd_int(void) {
    ll t = (rand() * 1000) / RAND_MAX;
    return (int)t; // рандом
}

int main(void) {
    setlocale(LC_ALL, "Rus");

    // инициализация 4 переменных и ptr для них
    int a, b, c, d;
    int* pa = &a, * pb = &b, * pc = &c, * pd = &d;
    init_rng();
    a = gen_rnd_int();
    b = gen_rnd_int();
    c = gen_rnd_int();
    d = gen_rnd_int();


    // якобы табличный вывод
    printf("\nНачальные значения после рандомайзера:\n |  A  |  B  |  C  |  D  |\n | %d | %d | %d | %d |", a, b, c, d);

    // сортировка указателей
    if (*pa > *pb) {
        pa = xorswap(pa, pb);
        pb = xorswap(pa, pb);
        pa = xorswap(pa, pb);
    }
    if (*pa > *pc) {
        pa = xorswap(pa, pc);
        pc = xorswap(pa, pc);
        pa = xorswap(pa, pc);
    }
    if (*pa > *pd) {
        pa = xorswap(pa, pd);
        pd = xorswap(pa, pd);
        pa = xorswap(pa, pd);
    }
    if (*pb > *pc) {
        pb = xorswap(pb, pc);
        pc = xorswap(pb, pc);
        pb = xorswap(pb, pc);
    }
    if (*pb > *pd) {
        pb = xorswap(pb, pd);
        pd = xorswap(pb, pd);
        pb = xorswap(pb, pd);
    }
    if (*pc > *pd) {
        pc = xorswap(pc, pd);
        pd = xorswap(pc, pd);
        pc = xorswap(pc, pd);
    }

    printf("\nОтсортированные значения:\n |  pA  |  pB  |  pC  |  pD  |\n | %d  | %d  | %d  |  %d | \n\n\n\n", *pa, *pb, *pc, *pd);
    printf("\nЗначения:\n |  A  |  B  |  C  |  D  |\n | %d  | %d  | %d  |  %d | \n\n\n\n", a, b, c, d);
    printf("\n%i ,%i",sizeof(ll),sizeof(int *));
    return 0;
}
