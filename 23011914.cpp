#include <iostream>
#include <vector>
#include <fstream> 
#include <string>
#include <cmath>
#include <iomanip>
#include <chrono>

using namespace std;

// - Hibrit yapıyı destekleyen veri yapımız.
struct TableEntry {
    int value = -1;           // Ana tablodaki değer
    vector<int> chain;        // Separate Chaining için dinamik dizi (vektör)
    bool isOccupied = false;  // Doluluk kontrolü
};

// - Asal sayı bulma fonksiyonu.
// Tablo boyutunu (m) belirlerken kullanıyoruz.
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// - Veri sayısına en yakın asal sayıyı bulan yardımcı fonksiyon.
int getNextPrime(int n) {
    int prime = n;
    if (prime % 2 == 0) prime++; 
    while (true) {
        if (isPrime(prime)) return prime;
        prime += 2;
    }
}

// - Hem Linear Probing hem Chaining mantığı burada.
void insertHybrid(vector<TableEntry>& table, int key, int k, int tableSize) {
    // 1. Adım: Hash adresini hesapla (Modülo işlemi)
    int h = key % tableSize;

    // - İlk adres boşsa direkt yerleştir (En iyi durum)
    if (!table[h].isOccupied) {
        table[h].value = key;
        table[h].isOccupied = true;
        return;
    }

    // - Çakışma varsa: 'k' adım boyunca Linear Probing yap
    for (int i = 1; i <= k; ++i) {
        int next_h = (h + i) % tableSize;
        if (!table[next_h].isOccupied) {
            table[next_h].value = key;
            table[next_h].isOccupied = true;
            return;
        }
    }

    // - 'k' adımda da yer yoksa: Zincire (Vektöre) ekle (Separate Chaining)
    table[h].chain.push_back(key);
}

// - Arama Maliyetini (Number of Probing) hesaplayan fonksiyon
int getSearchCost(const vector<TableEntry>& table, int key, int k, int tableSize) {
    int h = key % tableSize;

    // 1. Durum: Ana tabloda mı? (Maliyet: 1)
    if (table[h].isOccupied && table[h].value == key) return 1;

    // 2. Durum: Linear Probing bölgesinde mi? (Maliyet: i + 1)
    for (int i = 1; i <= k; ++i) {
        int next_h = (h + i) % tableSize;
        if (table[next_h].isOccupied && table[next_h].value == key) return i + 1; 
    }

    // 3. Durum: Zincirde mi? (Maliyet: k + 1 + ZincirdekiSıra)
    int chainPos = 1;
    for (int val : table[h].chain) {
        if (val == key) return k + 1 + chainPos;
        chainPos++;
    }

    return 0; // Hata durumu
}

void processFile(string filename, int k) {
    auto start = chrono::high_resolution_clock::now();

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << " [HATA] " << filename << " acilamadi!" << endl;
        return;
    }

    // - İlk satırdan veri sayısını okuyoruz.
    int numUsers = 0;
    if (!(inputFile >> numUsers)) return;

    // Tablo boyutunu dinamik belirliyoruz (En yakın asal sayı)
    int tableSize = getNextPrime(numUsers);
    
    // - Tabloyu oluşturuyoruz. Bellek yönetimi için vector kullanıldık.
    vector<TableEntry> table(tableSize);
    vector<int> allKeys; 
    allKeys.reserve(numUsers);

    cout << "\n -> Dosya Okunuyor: " << filename << " (Veri Sayisi: " << numUsers << ")" << endl;

    int key;
    // Dosyadaki tüm verileri okuyup tabloya ekliyoruz
    while (inputFile >> key) {
        insertHybrid(table, key, k, tableSize);
        allKeys.push_back(key);
    }
    inputFile.close();

    // - Ortalama ve Maksimum probing sayısını hesapla
    long long totalCost = 0;
    int maxCost = 0;

    for (int currentKey : allKeys) {
        int cost = getSearchCost(table, currentKey, k, tableSize);
        totalCost += cost;
        if (cost > maxCost) maxCost = cost;
    }

    double avgCost = (double)totalCost / numUsers;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // - 1. EKRANA YAZDIRMA
    cout << "------------------------------------------------" << endl;
    cout << " ANALIZ SONUCU (" << filename << ")" << endl;
    cout << "------------------------------------------------" << endl;
    cout << " k Degeri         : " << k << endl;
    cout << " Ortalama Probing : " << fixed << setprecision(5) << avgCost << endl;
    cout << " Maksimum Probing : " << maxCost << endl;
    cout << " Islem Suresi     : " << setprecision(2) << elapsed.count() << " sn" << endl;
    cout << "------------------------------------------------" << endl;

    // - 2. DOSYAYA KAYDETME (Grafik İçin)
    ofstream resultFile("deney_sonuclari.txt", ios::app);
    if (resultFile.is_open()) {
        resultFile << filename << "," << k << "," << avgCost << "," << maxCost << endl;
        resultFile.close();
        cout << " -> [OK] Sonuclar 'deney_sonuclari.txt' dosyasina eklendi." << endl;
    } else {
        cerr << " -> [HATA] Dosyaya yazilamadi!" << endl;
    }
}

int main() {
    int k;
    // - k bilgisi kullanıcıdan alınmalıdır.
    cout << "Lutfen k degerini giriniz: ";
    cin >> k;
    
    // Performans için I/O hızlandırma
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // - Dosya isimleri kodun içine gömülüdür (Hardcoded).
    // Hem verilen dosyayı hem kendi dosyamızı işliyoruz.
    processFile("ID-1_5M.txt", k);
    processFile("My_Input.txt", k);

    cout << "\nCikmak icin bir tusa ve Enter'a basiniz...";
    string dummy;
    cin >> dummy;

    return 0;
}