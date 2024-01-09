#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Soru {
    char soruMetni[500];
    char secenekler[5][500];
    char dogruCevap;
};
struct Ogrenci {
    char ad[100];
    char soyad[100];
    long ogr_num;
};
struct Kategori {
    char ad[20];
    char dosya_adi[20];
};

void Sorulari_Yukle(char dosya_adi[20], struct Soru sorular[10]);
void Sonuclari_Kaydet(struct Ogrenci ogrenci, struct Kategori kategoriler[5], int secim, int toplamPuan);

void quiz_Baslat(struct Ogrenci ogrenci, struct Kategori kategoriler[5]) {
    int toplamPuan = 0;
    int secim;
    printf("\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s\n", i + 1, kategoriler[i].ad); // 5 adet kategori yazdýrýr
    }

    printf("Lutfen bir kategori secin (1-5): ");
    scanf("%d", &secim);

    if (secim < 1 || secim > 5) {
        printf("Geçersiz kategori numarasi!");
        exit(1);
    }

    struct Soru sorular[10];
    Sorulari_Yukle(kategoriler[secim - 1].dosya_adi, sorular);

    for (int i = 0; i < 10; i++) {
        printf("\nSoru %d: %s", i + 1, sorular[i].soruMetni); // Soru cümlelerini yazdýrýr

        for (int j = 0; j < 5; ++j) {
            printf("%s", sorular[i].secenekler[j]); // Sorunun þýklarýný yazdýrýr
        }

        char cevap;
        printf("Cevabiniz: ");
        scanf(" %c", &cevap);
        if ( (cevap=='A') || (cevap=='B') || (cevap=='C') || (cevap=='D') || (cevap=='E') ) cevap+=32; // Büyük harfleri küçüðe çevirir
        if ( (cevap!='a') && (cevap!='b') && (cevap!='c') && (cevap!='d') && (cevap!='e') )
        {
            int control=1;
            while(control)
            {
                printf("\nGecersiz cevap girdiniz\n");
                printf("Cevabiniz: ");
                scanf(" %c", &cevap);
                if ( (cevap=='A') || (cevap=='B') || (cevap=='C') || (cevap=='D') || (cevap=='E') ) cevap+=32;
                if ( (cevap!='a') && (cevap!='b') && (cevap!='c') && (cevap!='d') && (cevap!='e') ) control=1;
                else control=0;
            }

        }



        FILE *cevap_pointer;                                               // Kullanýcýnýn cevaplarýný dosyaya kaydeder
        cevap_pointer= fopen("kullanicicevaplari.txt","a");
        if (cevap_pointer == NULL) {
            printf("Dosya acilamadi lutfen programý tekrar baslatýnýz");
            exit(1);
        }
        if (cevap == sorular[i].dogruCevap) {
            toplamPuan += 10;
            fprintf(cevap_pointer,"%c             |        %c          |       +\n",cevap,sorular[i].dogruCevap);
        }

        else{
            fprintf(cevap_pointer,"%c             |        %c          |        -\n",cevap,sorular[i].dogruCevap);
        }


        fclose(cevap_pointer);

    }

    printf("\nToplam Puaniniz: %d\n", toplamPuan);

    Sonuclari_Kaydet(ogrenci,kategoriler,secim,toplamPuan);

}



void Sorulari_Yukle(char dosya_adi[20], struct Soru sorular[10]) {
    FILE *dosya = fopen(dosya_adi, "r");                        // Sorularý dosyadan okur
    if (dosya == NULL) {
        printf("Dosya acilamadi lutfen programý tekrar baslatýnýz");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        fgets(sorular[i].soruMetni, sizeof(sorular[i].soruMetni), dosya);

        for (int j = 0; j < 5; j++) {
            fgets(sorular[i].secenekler[j], sizeof(sorular[i].secenekler[j]), dosya);
        }

        fscanf(dosya, " %c\n", &sorular[i].dogruCevap);
    }

    fclose(dosya);
}


void Sonuclari_Kaydet(struct Ogrenci ogrenci, struct Kategori kategoriler[5], int secim, int toplamPuan){
    FILE *sonuc_pointer;                                   // Kullanýcýnýn öðrenci numarasýný, adýný, soyadýný ve puanýný dosyaya kaydeder
    sonuc_pointer= fopen("sonuclar.txt","a");
    if (sonuc_pointer == NULL) {
        printf("Dosya acilamadi lutfen programý tekrar baslatýnýz");
        exit(1);
    }
    fprintf(sonuc_pointer,"%ld           %s %s            %d(%s)\n------------------------------------------------\n",ogrenci.ogr_num,ogrenci.ad,ogrenci.soyad,toplamPuan,kategoriler[secim-1].ad);
    fclose(sonuc_pointer);

}


void Cevaplari_Incele(){

    FILE *inceleme_pointer; // Kullanýcýnýn sorulara verdiði cevaplarý, sorularýn doðru cevaplarýný ve soruyu doðru yapýp
    inceleme_pointer= fopen("kullanicicevaplari.txt","r"); //yapmadýðýný optik form þeklinde kullanýcýya sunar
    if (inceleme_pointer == NULL) {
        printf("Dosya acilamadi lutfen programý tekrar baslatýnýz");
        exit(1);
    }
    char karakter[100],karakter_2[100],karakter_3[100],karakter_4[100],karakter_5[100];
    printf("\nSoru Numarasi    |       Cevaplariniz   |         Dogru Cevaplar        |             +/-\n");
    for(int j=1;j<11;j++)
    {
        fscanf(inceleme_pointer,"%s%s%s%s%s\n",karakter,karakter_2,karakter_3,karakter_4,karakter_5);
        if (j==10) printf("       %d        |           %s          %s               %s               %s             %s\n",j,karakter,karakter_2,karakter_3,karakter_4,karakter_5);
        else printf("       %d         |           %s          %s               %s               %s             %s\n",j,karakter,karakter_2,karakter_3,karakter_4,karakter_5);

    }




    fclose(inceleme_pointer);

}
