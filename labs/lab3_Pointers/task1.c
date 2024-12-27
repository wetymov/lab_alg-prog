//#define _CRT_SECURE_NO_WARNINGS // отменяет предупреждения системы
//#define ll long long
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <locale.h>
//
//
//void init_rng(void) {
//    time_t curtime;
//    time(&curtime);
//    srand((unsigned int)curtime);
//}
//
//int gen_rnd_int(void) {
//    ll t = (rand() * 1000) / RAND_MAX;
//    return (int)t;
//}
//
//int main(void) {
//    setlocale(LC_ALL, "Rus");
//
//
//    int a, b, c, d;
//    int* pa = &a, * pb = &b, * pc = &c, * pd = &d;
//
//    init_rng();
//    a = gen_rnd_int();
//    b = gen_rnd_int();
//    c = gen_rnd_int();
//    d = gen_rnd_int();
//
//    printf("\nНачальные значения после рандомайзера(псевдо): %d, %d, %d, %d", a, b, c, d);
//
//    int* temp = pa;
//    
//    if (*pa > *pb) { 
//        temp = pa; pa = pb; pb = temp; 
//    }
//    if (*pa > *pc) { 
//        temp = pa; pa = pc; pc = temp; 
//    }
//    if (*pa > *pd) { 
//        temp = pa; pa = pd; pd = temp; 
//    }
//    if (*pb > *pc) { 
//        temp = pb; pb = pc; pc = temp; 
//    }
//    if (*pb > *pd) { 
//        temp = pb; pb = pd; pd = temp; 
//    }
//    if (*pc > *pd) { 
//        temp = pc; pc = pd; pd = temp; 
//    }
//
//    // Вывод значений через указатели по возрастанию
//    printf("\nОтсортированные значения: %d, %d, %d, %d \n\n\n\n", *pa, *pb, *pc, *pd);
//
//    return 0;
//}
