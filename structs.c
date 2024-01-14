#include <stdio.h>

typedef struct ogr
{
    char ad[20];
    char soyad[20];
    int numara;
    int sinif;
    int vize;
    int final;
    float ortalama;
    char harf[3];
} ogr;

typedef struct kemal
{
    int a : 8;
    char b : 3;
} kemal;

typedef struct nested
{
    int a;
    int b;
    kemal c;
} nested;

int main()
{
    sizeof(kemal);
    ogr ogrenci1 = {"Ahmet", "Yilmaz", 123, 1, 80, 90, 0, "AA"};
    ogr ogrenci2 = {.ad = "Mehmet", .soyad = "Yilmaz", .sinif = 1, .vize = 80, .final = 90, .ortalama = 0, .harf = "AA"};

    nested n = {1, 2, 3, 4};

    printf("%p\n", &ogrenci2);
    printf("%p\n", &(ogrenci2.soyad));
    ogrenci2 = ogrenci1;

    /* int a[100]; */
    /* int b[100]; */
    /* typedef int memcpy[100]; */
    /* (memcpy) a = (memcpy)b; */

    printf("%s %s %d %d %d %d %f %s\n", ogrenci2.ad, ogrenci2.soyad, ogrenci2.numara, ogrenci2.sinif, ogrenci2.vize, ogrenci2.final, ogrenci2.ortalama, ogrenci2.harf);
    printf("%p\n", &(ogrenci2.soyad));
}