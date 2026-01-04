# Hybrid Hashing Algorithm & Performance Analysis

This project implements a **Hybrid Hashing Algorithm** designed to map unique user IDs to physical memory addresses efficiently. It combines **Linear Probing** and **Separate Chaining** to optimize memory usage and minimize collision costs.

## 🧠 Algorithm Logic

The algorithm follows a 4-step hybrid strategy for inserting or searching keys:

1.  **Hash Calculation:** Computes the index using modulo operator: $h = key \pmod m$.
2.  **Direct Mapping:** If the slot `Table[h]` is empty, the data is placed there.
3.  **Linear Probing:** If a collision occurs, the algorithm checks the next `k` slots ($h+1, h+2...$) to find an empty spot. This step aims to keep data in the main table for better cache locality.
4.  **Separate Chaining:** If no empty slot is found after `k` steps, the key is inserted into a dynamic array (vector) linked to the original index `h`.

> **Optimization Note:** Instead of traditional Linked Lists, **Dynamic Arrays (Vectors)** were used for chaining to improve cache performance and reduce memory fragmentation.

## 📂 Repository Contents

* **`23011914.cpp`**: Main C++ implementation of the hybrid hashing logic.
* **`grafik.py`**: Python script using Matplotlib to visualize performance data.
* **`ID-1_5M.txt`**: Real-world dataset with ~1.5 million unique IDs.
* **`My_Input.txt`**: Synthetic dataset generated to force collisions and test the hybrid mechanism.
* **`23011914.pdf`**: Detailed technical report and algorithm analysis.

## 📊 Time Complexity Analysis

The total time complexity $T(n)$ depends on the load factor and collision handling:

| Case | Complexity | Description |
| :--- | :--- | :--- |
| **Best Case** | $O(1)$ | Key is found immediately at the hashed index. |
| **Average Case** | $O(1)$ | Under Simple Uniform Hashing assumption. |
| **Worst Case** | $O(n)$ | All keys collide at the same index (requires scanning the full chain). |

## 🚀 How to Run

### 1. Compile the C++ Code
You need a C++ compiler (like G++ or MinGW).

    g++ 23011914.cpp -o HybridHash

### 2. Run the Algorithm
Run the executable. You will be asked to input a `k` value (limit for Linear Probing).

    # Windows
    HybridHash.exe

    # Linux/Mac
    ./HybridHash

*This will generate/update the `deney_sonuclari.txt` file.*

### 3. Visualize Results
Use the Python script to generate the performance graph.

    python grafik.py

*Output image: `Otomatik_Grafik.png`*

## 📈 Analysis Results

Based on the project report:
* **Dataset `ID-1_5M.txt`**: Showed nearly "Perfect Hashing" behavior with very few collisions.
* **Dataset `My_Input.txt`**: Successfully demonstrated the hybrid trade-off. As `k` (probing limit) increases, the usage of chaining decreases, but the probing cost per search increases.

## 👤 Author

**Enes Emin Özbilgin**
