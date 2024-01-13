#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;
struct Musteri {
    int hesapNo;
    string isim;
    double bakiye;
};

vector<Musteri> musteriler;

void musteriKaydet(const Musteri& musteri) {
    ofstream dosya("musteriler.txt", ios::app);
    if (dosya.is_open()) {
        dosya << musteri.hesapNo << ";" << musteri.isim << ";" << musteri.bakiye << endl;
        dosya.close();
       cout << "Müþteri kaydedildi.\n";
    } else {
        cerr << "Dosya açýlamadý!\n";
    }
}

bool stringToInt(const string& str, int& result) {
    istringstream iss(str);
    return !(iss >> result).fail();
}

bool stringToDouble(const string& str, double& result) {
    istringstream iss(str);
    return !(iss >> result).fail();
}

void musterileriOku() {
    musteriler.clear();
    ifstream dosya("musteriler.txt");
    Musteri musteri;
    string satir;
    
    if (dosya.is_open()) {
        while (getline(dosya, satir)) {
            stringstream ss(satir);
            string token;
            getline(ss, token, ';');
            if (!stringToInt(token, musteri.hesapNo)) {
                cerr << "Hesap numarasý dönüþtürme hatasý: " << token <<endl;
                continue;
            }
            getline(ss, musteri.isim, ';');
            getline(ss, token, ';');
            if (!stringToDouble(token, musteri.bakiye)) {
                cerr << "Bakiye dönüþtürme hatasý: " << token <<endl;
                continue;
            }
            musteriler.push_back(musteri);
        }
        dosya.close();
    } else {
        cerr << "Dosya açýlamadý!\n";
    }
}

void musterileriGoster() {
    for (size_t i = 0; i < musteriler.size(); ++i) {
        const Musteri& musteri = musteriler[i];
        cout << "Hesap No: " << musteri.hesapNo << ", Ýsim: " << musteri.isim << ", Bakiye: " << musteri.bakiye <<endl;
        cout<<endl;
    }
}

void yeniMusteriEkle() {
    Musteri musteri;
    cout << "Yeni müþteri hesap numarasý: ";
    cin >> musteri.hesapNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Yeni müþteri ismi: ";
    getline(cin, musteri.isim); 
    cout << "Baþlangýç bakiyesi: ";
    cin >> musteri.bakiye;

    musteriler.push_back(musteri); 
    musteriKaydet(musteri);
}
void paraYatir() {
    int hesapNo;
    double miktar;
    cout << "Para yatýrýlacak hesap numarasý: ";
    cin >> hesapNo;
    cout << "Yatýrýlacak miktar: ";
    cin >> miktar;

    for (size_t i = 0; i < musteriler.size(); ++i) {
        if (musteriler[i].hesapNo == hesapNo) {
            musteriler[i].bakiye += miktar;
            cout << "Para yatýrma iþlemi baþarýlý. Yeni bakiye: " << musteriler[i].bakiye <<endl;
            return;
        }
    }
    cerr << "Hesap numarasý bulunamadý!\n";
}

void paraCek() {
    int hesapNo;
    double miktar;
    cout << "Para çekilecek hesap numarasý: ";
    cin >> hesapNo;
    cout << "Çekilecek miktar: ";
    cin >> miktar;

    for (size_t i = 0; i < musteriler.size(); ++i) {
        if (musteriler[i].hesapNo == hesapNo) {
            if (musteriler[i].bakiye >= miktar) {
                musteriler[i].bakiye -= miktar;
                cout << "Para çekme iþlemi baþarýlý. Yeni bakiye: " << musteriler[i].bakiye << endl;
            } else {
                cerr << "Yetersiz bakiye!\n";
            }
            return;
        }
    }
    cerr << "Hesap numarasý bulunamadý!\n";
}

void musterileriKaydet() {
    ofstream dosya("musteriler.txt", ios::trunc);
    if (!dosya.is_open()) {
        cerr << "Dosya açýlamadý!\n";
        return;
    }
    
    for (size_t i = 0; i < musteriler.size(); ++i) {
        dosya << musteriler[i].hesapNo << ";" << musteriler[i].isim << ";" << musteriler[i].bakiye << endl;
    }
    dosya.close();
}
void musterileriTemizle() {
    musteriler.clear(); 
    std::cout << "Müþteri listesi temizlendi.\n";
}


int main() {
	setlocale (	LC_ALL, "Turkish");
    musterileriOku(); 
bool devam = true;
    while (devam) {

    int secim;

    do {
        cout << "1: Yeni Müþteri Ekle\n";
        cout << "2: Müþteri Listesini Göster\n";
        cout << "3: Para Yatýr\n";
        cout << "4: Para Çek\n";
        cout << "5. Müþteri Listesini Temizle\n";
        cout << "6: Çýkýþ\n";
        cout << "Seçiminizi yapýnýz (1-6): ";
 		cin >> secim;
 		switch (secim) {
            case 1:
                yeniMusteriEkle();
                musterileriKaydet();
                break;
            case 2:
                musterileriGoster();
                break;
            case 3:
                paraYatir();
                musterileriKaydet();
                break;
            case 4:
                paraCek();
                musterileriKaydet();
                break;
                  case 5:
                musterileriTemizle();
                break;

            case 6:
                cout << "Programdan çýkýlýyor.\n";
                break;
            default:
            cout << "Geçersiz seçim! Lütfen 1-9 arasýnda bir seçim yapýnýz.\n";
        
		}
    } while (secim != 9);}}



