#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

#define sehirSayisi 5

#define nufusBuyuklugu 10

//yolUygunluk değişkeni bize yolun uygunluk durumunu,
//gecilenYer ise satıcının geçtiği yolu / şehri gösterir.
struct SalesMan {
    string gecilenYer;
    int yolUygunluk;
};

// Başlangıç ve bitiş için rastgele sayılar üretir.
int rastgeleMesafe(int baslangic, int hedef)
{
    int r = hedef - baslangic;
    int aradakiFark = baslangic + rand() % r;
    return aradakiFark;
}

// Karakterin girilen stringte zaten varolup olmadığını kontrol eder.
bool ikilemeKontrol(string s, char ch) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ch)
            return true;
    }
    return false;
}

// Şehirlerin rastgele değişimini sağlar.
string sehirDegistir(string gecilenYer) {
    while (true) {
        int r = rastgeleMesafe(1, sehirSayisi);
        int r1 = rastgeleMesafe(1, sehirSayisi);
        if (r1 != r) {
            char temp = gecilenYer[r];
            gecilenYer[r] = gecilenYer[r1];
            gecilenYer[r1] = temp;
            break;
        }
    }
    return gecilenYer;
}

// Şehir oluşturur
string sehirOlustur() {
    string gecilenYer = "0";
    while (true) {
        if (gecilenYer.size() == sehirSayisi) {
            gecilenYer += gecilenYer[0];
            break;
        }
        int temp = rastgeleMesafe(1, sehirSayisi);
        if (!ikilemeKontrol(gecilenYer, (char)(temp + 48)))
            gecilenYer += (char)(temp + 48);
    }
    return gecilenYer;
}

// Mesafeyi oluşturur.
int mesafeOlustur(string gecilenYer) {
    int map[sehirSayisi][sehirSayisi] = { { 0, 2, INT_MAX, 12, 5 },
                      { 2, 0, 4, 8, INT_MAX },
                      { INT_MAX, 4, 0, 3, 3 },
                      { 12, 8, 3, 0, 10 },
                      { 5, INT_MAX, 3, 10, 0 } };
    int f = 0;
    for (int i = 0; i < gecilenYer.size() - 1; i++) {
        if (map[gecilenYer[i] - 48][gecilenYer[i + 1] - 48] == INT_MAX)
            return INT_MAX;
        f += map[gecilenYer[i] - 48][gecilenYer[i + 1] - 48];
    }
    return f;
}

// Bekleme süresi için atama yapan fonksiyon.
int bekleme(int temp) {
    return (90 * temp) / 100;
}

// Geçilen şehirleri karşılaştırır.
bool sehirKiyas(struct SalesMan t1, struct SalesMan t2) {
    return t1.yolUygunluk < t2.yolUygunluk;
}

// Seyyar satıcı problemi için ana fonksiyon.
void travelPart(int map[sehirSayisi][sehirSayisi]) {
    int gen = 1;

    //İterasyon sayısı
    int gen_thres = 5;

    vector<struct SalesMan> population;
    struct SalesMan temp;

    for (int i = 0; i < nufusBuyuklugu; i++) {
        temp.gecilenYer = sehirOlustur();
        temp.yolUygunluk = mesafeOlustur(temp.gecilenYer);
        population.push_back(temp);
    }

    cout << "\nOlusturulan ilk nufus: " << endl
         << "Sehir && Uygunluk\n";
    for (int i = 0; i < nufusBuyuklugu; i++)
        cout << population[i].gecilenYer << " "
             << "     " << population[i].yolUygunluk << endl;
    cout << "\n";

    int tempDeger = 10000;

    while (tempDeger > 1000 && gen <= gen_thres) {
        sort(population.begin(), population.end(), sehirKiyas);
        cout << "\nGecici Deger: " << tempDeger << "\n";
        vector<struct SalesMan> yeniUygunluk;

        for (int i = 0; i < nufusBuyuklugu; i++) {
            struct SalesMan p1 = population[i];

            while (true) {
                string new_g = sehirDegistir(p1.gecilenYer);
                struct SalesMan yeniRota;
                yeniRota.gecilenYer = new_g;
                yeniRota.yolUygunluk = mesafeOlustur(yeniRota.gecilenYer);

                if (yeniRota.yolUygunluk <= population[i].yolUygunluk) {
                    yeniUygunluk.push_back(yeniRota);
                    break;
                }
                else {
                    float prob = pow(2.7,-1 * ((float)(yeniRota.yolUygunluk - population[i].yolUygunluk) / tempDeger));
                    if (prob > 0.5) {
                        yeniUygunluk.push_back(yeniRota);
                        break;
                    }
                }
            }
        }

        tempDeger = bekleme(tempDeger);
        population = yeniUygunluk;
        cout << "Iterasyon: " << gen << " \n";
        cout << "Sehir && Uygunluk\n";

        for (int i = 0; i < nufusBuyuklugu; i++)
            cout << population[i].gecilenYer << " "
                 << "     " << population[i].yolUygunluk << endl;
        gen++;
    }
}

int main() {
    int map[sehirSayisi][sehirSayisi] = { { 0, 2, INT_MAX, 12, 5 },
                      { 2, 0, 4, 8, INT_MAX },
                      { INT_MAX, 4, 0, 3, 3 },
                      { 12, 8, 3, 0, 10 },
                      { 5, INT_MAX, 3, 10, 0 } };
    travelPart(map);
}