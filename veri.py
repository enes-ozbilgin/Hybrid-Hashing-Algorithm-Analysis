import random

# Veri Sayısı
N = 1100000 
filename = "My_Input.txt"

print(f"{filename} oluşturuluyor...")

data = random.sample(range(1, 100000000), N)

with open(filename, 'w') as f:
    f.write(f"{N}\n")
    for number in data:
        f.write(f"{number}\n")