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
       cout << "M��teri kaydedildi.\n";
    } else {
        cerr << "Dosya a��lamad�!\n";
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
                cerr << "Hesap numaras� d�n��t�rme hatas�: " << token <<endl;
                continue;
            }
            getline(ss, musteri.isim, ';');
            getline(ss, token, ';');
            if (!stringToDouble(token, musteri.bakiye)) {
                cerr << "Bakiye d�n��t�rme hatas�: " << token <<endl;
                continue;
            }
            musteriler.push_back(musteri);
        }
        dosya.close();
    } else {
        cerr << "Dosya a��lamad�!\n";
    }
}

void musterileriGoster() {
    for (size_t i = 0; i < musteriler.size(); ++i) {
        const Musteri& musteri = musteriler[i];
        cout << "Hesap No: " << musteri.hesapNo << ", �sim: " << musteri.isim << ", Bakiye: " << musteri.bakiye <<endl;
        cout<<endl;
    }
}

void yeniMusteriEkle() {
    Musteri musteri;
    cout << "Yeni m��teri hesap numaras�: ";
    cin >> musteri.hesapNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Yeni m��teri ismi: ";
    getline(cin, musteri.isim); 
    cout << "Ba�lang�� bakiyesi: ";
    cin >> musteri.bakiye;

    musteriler.push_back(musteri); 
    musteriKaydet(musteri);
}
void paraYatir() {
    int hesapNo;
    double miktar;
    cout << "Para yat�r�lacak hesap numaras�: ";
    cin >> hesapNo;
    cout << "Yat�r�lacak miktar: ";
    cin >> miktar;

    for (size_t i = 0; i < musteriler.size(); ++i) {
        if (musteriler[i].hesapNo == hesapNo) {
            musteriler[i].bakiye += miktar;
            cout << "Para yat�rma i�lemi ba�ar�l�. Yeni bakiye: " << musteriler[i].bakiye <<endl;
            return;
        }
    }
    cerr << "Hesap numaras� bulunamad�!\n";
}

void paraCek() {
    int hesapNo;
    double miktar;
    cout << "Para �ekilecek hesap numaras�: ";
    cin >> hesapNo;
    cout << "�ekilecek miktar: ";
    cin >> miktar;

    for (size_t i = 0; i < musteriler.size(); ++i) {
        if (musteriler[i].hesapNo == hesapNo) {
            if (musteriler[i].bakiye >= miktar) {
                musteriler[i].bakiye -= miktar;
                cout << "Para �ekme i�lemi ba�ar�l�. Yeni bakiye: " << musteriler[i].bakiye << endl;
            } else {
                cerr << "Yetersiz bakiye!\n";
            }
            return;
        }
    }
    cerr << "Hesap numaras� bulunamad�!\n";
}

void musterileriKaydet() {
    ofstream dosya("musteriler.txt", ios::trunc);
    if (!dosya.is_open()) {
        cerr << "Dosya a��lamad�!\n";
        return;
    }
    
    for (size_t i = 0; i < musteriler.size(); ++i) {
        dosya << musteriler[i].hesapNo << ";" << musteriler[i].isim << ";" << musteriler[i].bakiye << endl;
    }
    dosya.close();
}
void musterileriTemizle() {
    musteriler.clear(); 
    std::cout << "M��teri listesi temizlendi.\n";
}


int main() {
	setlocale (	LC_ALL, "Turkish");
    musterileriOku(); 
bool devam = true;
    while (devam) {

    int secim;

    do {
        cout << "1: Yeni M��teri Ekle\n";
        cout << "2: M��teri Listesini G�ster\n";
        cout << "3: Para Yat�r\n";
        cout << "4: Para �ek\n";
        cout << "5. M��teri Listesini Temizle\n";
        cout << "6: ��k��\n";
        cout << "Se�iminizi yap�n�z�(1-6):�";
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
                cout << "Programdan ��k�l�yor.\n";
                break;
            default:
            cout << "Ge�ersiz se�im! L�tfen 1-9 aras�nda bir se�im yap�n�z.\n";
        
		}
    } while (secim != 9);}}



