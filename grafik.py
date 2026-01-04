import matplotlib.pyplot as plt
import os

RESULT_FILENAME = "deney_sonuclari.txt"

def plot_graph():
    if not os.path.exists(RESULT_FILENAME):
        print(f"HATA: '{RESULT_FILENAME}' dosyası bulunamadı. Önce C++ kodunu çalıştırın.")
        return

    data = {} # { 'DosyaAdi': { k: ortalama } }

    try:
        with open(RESULT_FILENAME, 'r') as f:
            for line in f:
                line = line.strip()
                if not line: continue
                
                # C++'ta şu formatta yazdırmıştık: DosyaAdi, k, Ortalama, Maksimum
                parts = line.split(',')
                if len(parts) < 3: continue

                filename = parts[0].strip()
                k = int(parts[1].strip())
                avg = float(parts[2].strip())

                if filename not in data:
                    data[filename] = {'k': [], 'avg': []}
                
                # Aynı k değeri tekrar yazılmışsa üstüne yazmamak için kontrol edebiliriz
                # veya basitçe listeye ekleriz. Burada listeye ekliyoruz.
                data[filename]['k'].append(k)
                data[filename]['avg'].append(avg)

    except Exception as e:
        print(f"Dosya okunurken hata oluştu: {e}")
        return

    # Grafik Çizimi
    plt.figure(figsize=(10, 6))

    colors = ['blue', 'orange', 'green', 'red']
    color_idx = 0

    for filename, values in data.items():
        # Verileri k değerine göre sıralayalım (karışık girildiyse düzelir)
        # Zip ile birleştirip sıralayıp geri açıyoruz
        sorted_pairs = sorted(zip(values['k'], values['avg']))
        k_list = [p[0] for p in sorted_pairs]
        avg_list = [p[1] for p in sorted_pairs]

        plt.plot(k_list, avg_list, marker='o', linestyle='-', linewidth=2, label=filename, color=colors[color_idx % len(colors)])
        color_idx += 1

    plt.title('Hibrit Hashing Performans Analizi (Otomatik Veri)', fontsize=14)
    plt.xlabel('k Değeri (Linear Probing Limiti)', fontsize=12)
    plt.ylabel('Ortalama Arama Maliyeti', fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=11)
    plt.xscale('log') # Logaritmik ölçek (k değerleri çok açıldığı için)
    
    # Tüm k değerlerini X ekseninde göstermeye çalışalım (eğer çok fazla yoksa)
    all_k = set()
    for v in data.values():
        all_k.update(v['k'])
    sorted_all_k = sorted(list(all_k))
    plt.xticks(sorted_all_k, labels=[str(k) for k in sorted_all_k])

    plt.tight_layout()
    plt.savefig('Otomatik_Grafik.png', dpi=300)
    plt.show()
    print("Grafik 'Otomatik_Grafik.png' olarak kaydedildi.")

if __name__ == "__main__":
    plot_graph()