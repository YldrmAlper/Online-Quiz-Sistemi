

#include <stdio.h>
#include "kutuphane.h"
int main() {
    FILE *cevap_pointer;
    cevap_pointer= fopen("kullanicicevaplari.txt","w");  //Yeni bir kullanıcı quize başladığında bir
    fprintf(cevap_pointer,"");                            // önceki kullanıcının cevaplarını silmek için burada dosyayı 'w' modunda açıyoruz.
    fclose(cevap_pointer);

    struct Ogrenci ogrenci;

    printf("--------------QUIZ--------------\n        BASARILAR DILERIZ\n ");
    printf("NOT: Her sorunun dogru cevabi 10 puandir\n\n");

    printf("Lutfen ad soyadinizi giriniz: ");
    scanf("%s %s",&ogrenci.ad,&ogrenci.soyad);

    printf("\nLutfen ogrenci numaranizi giriniz: ");
     scanf("%ld",&ogrenci.ogr_num);

    struct Kategori kategoriler[5] = {
            {"Matematik", "matematik.txt"},
            {"Fizik", "fizik.txt"},
            {"Algoritma", "algoritma.txt"},
            {"Genel Kultur", "genel_kultur.txt"},
            {"Turkce", "turkce.txt"}
    };

    quiz_Baslat(ogrenci,kategoriler);
    Cevaplari_Incele();
    return 0;
}
