# Hybrid Hashing Algorithm & Performance Analysis

Bu proje, büyük ölçekli veri kümelerinde kimlik-bellek eşlemesi (ID-Memory Mapping) yapmak için geliştirilmiş **Hibrit Bir Hashing Algoritması**nı içerir.

Geliştirilen algoritma, **Linear Probing (Doğrusal Yoklama)** ve **Separate Chaining (Ayrı Zincirleme)** tekniklerini birleştirerek bellek kullanımını optimize etmeyi ve çakışma (collision) maliyetlerini en aza indirmeyi hedefler.

## 🧠 Algoritma Mantığı (Nasıl Çalışır?)

Algoritma, veriyi tabloya yerleştirirken veya ararken 4 aşamalı kademeli bir strateji izler:

1.  **Hash Hesaplama:** Anahtarın (Key) tablo boyutuna (m) göre modu alınır: $h = key \pmod m$.
2.  **Doğrudan Yerleşim:** Eğer $h$ indisi boşsa, veri buraya yerleştirilir.
3.  **Linear Probing (Kademeli Yoklama):** Eğer $h$ indisi doluysa, algoritma önceden belirlenen bir **$k$** limitine kadar sonraki indisleri ($h+1, h+2...$) kontrol eder. Bu adım, veriyi ana tabloda tutarak önbellek (cache) performansını artırmayı amaçlar.
4.  **Separate Chaining (Zincirleme):** Eğer $k$ adım boyunca boş yer bulunamazsa, anahtar ilk hesaplanan $h$ indisindeki dinamik diziye (vector) eklenir.

> **Not:** Zincirleme yapısı için Linked List yerine **Dynamic Array (Vector)** kullanılarak modern işlemcilerde bellek erişim hızı (cache locality) optimize edilmiştir.

## 📂 Proje İçeriği

* **`HybridHashing.cpp`**: Algoritmanın C++ implementasyonu. Hem hashing mantığını hem de performans testlerini içerir.
* **`grafik.py` & `veri.py`**: C++ çıktısı olan `deney_sonuclari.txt` dosyasını okuyarak performans grafikleri (Matplotlib) oluşturan Python betikleri.
* **`ID-1_5M.txt`**: Yaklaşık 1.5 Milyon kayıt içeren gerçek dünya veri seti.
* **`My_Input.txt`**: Algoritmanın hibrit yapısını (çakışma yönetimini) zorlamak için oluşturulmuş, yüksek çakışma oranına sahip sentetik veri seti.
* **`23011914.pdf`**: Projenin detaylı teknik raporu ve analiz dokümanı.

## 📊 Karmaşıklık Analizi (Time Complexity)

Algoritmanın zaman karmaşıklığı $T(n)$, Hash, Probing ve Chaining maliyetlerinin toplamıdır.

| Durum | Karmaşıklık | Açıklama |
| :--- | :--- | :--- |
| **En İyi (Best Case)** | $O(1)$ | Eleman doğrudan hesaplanan hash adresindedir. |
| **Ortalama (Avg Case)** | $O(1)$ | Basit düzgün hashing varsayımı altında. |
| **En Kötü (Worst Case)** | $O(n)$ | Tüm elemanların aynı indise yığıldığı durum. |

## 🚀 Kurulum ve Kullanım

Projeyi çalıştırmak için C++ derleyicisine (G++) ve grafik çizimi için Python'a ihtiyacınız vardır.

### 1. Derleme (Compile)
Terminali proje klasöründe açın ve kodu derleyin:

```bash
g++ HybridHashing.cpp -o HybridHashing
```

### 2. Çalıştırma (Run)
Derlenen programı çalıştırın. Program sizden bir `k` (Linear Probing limiti) değeri isteyecektir.

```bash
# Windows
HybridHashing.exe

# Linux/Mac
./HybridHashing
```

*Program çalıştıktan sonra sonuçları `deney_sonuclari.txt` dosyasına yazar.*

### 3. Görselleştirme
Analiz sonuçlarını grafiğe dökmek için Python scriptini çalıştırın:

```bash
python grafik.py
```
Bu işlem sonucunda **`Otomatik_Grafik.png`** dosyası oluşturulacaktır.

## 📈 Test Sonuçları

Rapor analizlerine göre:
* **`ID-1_5M.txt`** veri setinde "Mükemmel Hashleme"ye yakın bir durum gözlenmiş ve $k$ değeri artsa da probing maliyeti çok düşük kalmıştır.
* **`My_Input.txt`** veri setinde ise hibrit yapının etkisi net olarak görülmüş; $k$ değeri arttıkça zincirleme azalmış, ancak probing maliyeti artmıştır.

## 👤 Yazar

**Enes Emin Özbilgin**
