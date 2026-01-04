# Hybrid Hashing Algorithm & Performance Analysis

This project implements a **Hybrid Hashing Algorithm** designed to map unique user IDs to physical memory addresses efficiently. [cite_start]It combines **Linear Probing** and **Separate Chaining** to optimize memory usage and minimize collision costs[cite: 9, 10].

## 🧠 Algorithm Logic

[cite_start]The algorithm follows a 4-step hybrid strategy for inserting or searching keys [cite: 14-20]:

1.  **Hash Calculation:** computes the index using modulo operator: $h = key \pmod m$.
2.  **Direct Mapping:** If the slot `Table[h]` is empty, the data is placed there.
3.  **Linear Probing:** If a collision occurs, the algorithm checks the next `k` slots ($h+1, h+2...$) to find an empty spot. [cite_start]This step aims to keep data in the main table for better cache locality[cite: 18].
4.  **Separate Chaining:** If no empty slot is found after `k` steps, the key is inserted into a dynamic array (vector) linked to the original index `h`.

> [cite_start]**Optimization Note:** Instead of traditional Linked Lists, **Dynamic Arrays (Vectors)** were used for chaining to improve cache performance and reduce memory fragmentation[cite: 46].

## 📂 Repository Contents

* **`23011914.cpp`**: Main C++ implementation of the hybrid hashing logic.
* **`grafik.py`**: Python script using Matplotlib to visualize performance data.
* **`ID-1_5M.txt`**: Real-world dataset with ~1.5 million unique IDs.
* **`My_Input.txt`**: Synthetic dataset generated to force collisions and test the hybrid mechanism[cite: 43].
* **`23011914.pdf`**: Detailed technical report and algorithm analysis.

## 📊 Time Complexity Analysis

The total time complexity $T(n)$ depends on the load factor and collision handling [cite: 73-87]:

| Case | Complexity | Description |
| :--- | :--- | :--- |
| **Best Case** | $O(1)$ | Key is found immediately at the hashed index. |
| **Average Case** | $O(1)$ | Under Simple Uniform Hashing assumption. |
| **Worst Case** | $O(n)$ | All keys collide at the same index (requires scanning the full chain). |

## 🚀 How to Run

### 1. Compile the C++ Code
You need a C++ compiler (like G++ or MinGW).

```bash
g++ 23011914.cpp -o HybridHash
```

### 2. Run the Algorithm
Run the executable. You will be asked to input a `k` value (limit for Linear Probing).

```bash
./HybridHash
# On Windows: HybridHash.exe
```
*This will generate/update the `deney_sonuclari.txt` file.*

### 3. Visualize Results
Use the Python script to generate the performance graph.

```bash
python grafik.py
```
*Output image: `Otomatik_Grafik.png`*

## 📈 Analysis Results

Based on the project report[cite: 40, 43]:
* **Dataset `ID-1_5M.txt`**: Showed nearly "Perfect Hashing" behavior with very few collisions.
* **Dataset `My_Input.txt`**: Successfully demonstrated the hybrid trade-off. As `k` (probing limit) increases, the usage of chaining decreases, but the probing cost per search increases.

## 👤 Author

**Enes Emin Özbilgin**
