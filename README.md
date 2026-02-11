# Custom Memory Allocator in C++

A from-scratch implementation of a **custom heap memory allocator** in C++ that mimics the internal behavior of `malloc` and `free`.

This project demonstrates how dynamic memory management works internally in operating systems and C/C++ runtime libraries, including fragmentation handling, allocation strategies, and safety checks.

---

## 🚀 Features

- Private **1 MB heap** managed manually
- Block metadata stored using headers
- Separate **heap list** and **free list**
- **Block splitting** during allocation
- **Block coalescing** during deallocation
- **8-byte memory alignment**
- Support for:
  - **First Fit**
  - **Best Fit** allocation strategies
- Fragmentation visualization
- Safety checks:
  - Double free detection
  - Invalid free detection
- Heap statistics and memory map visualization

---

## 🧠 How Memory Is Managed

Every allocation inside the custom heap is structured as:

```
+------------------------+--------------------------------------+
|      BlockHeader       |        Payload (User Memory)         |
+------------------------+--------------------------------------+
```

### BlockHeader contains:
```
size | isFree | prev | next | prevFree | nextFree
```

- The **user only receives the payload pointer**
- The header is stored **just before** user memory
- Metadata is invisible to the user but critical for management

---

## 🗂 Heap Structure

The allocator maintains **two linked lists**:

### 1️⃣ Heap List (Physical Memory Order)

```
[Block A] <--> [Block B] <--> [Block C] <--> [Block D]
```

- Contains **all blocks**
- Used for traversal and **coalescing adjacent blocks**

### 2️⃣ Free List (Only Free Blocks)

```
[Block B] <--> [Block D]
```

- Contains **only free blocks**
- Used to speed up allocation search

---

## ⚙️ Allocation Process (`myMalloc`)

Steps followed during allocation:

1. Align requested size to **8 bytes**
2. Search the free list using selected strategy:
   - First Fit → first sufficient block
   - Best Fit → smallest sufficient block
3. Remove chosen block from free list
4. **Split block** if it is larger than required
5. Return pointer to payload

---

## ✂️ Block Splitting (Exact Behavior)

Initial free block:

```
+--------------------------------------------------+
|               Free Block (1048552 bytes)         |
+--------------------------------------------------+
```

Request: `myMalloc(40)`

After splitting:

```
+-----------+--------------------------------------+
| Used 40   |        Free 1048464                  |
+-----------+--------------------------------------+
```

The remaining portion becomes a **new free block** with its own header.

---

## 📊 Fragmentation Example

After allocations and freeing a middle block:

```
|U40|F80|U24|F1048336|
```

Visual layout:

```
+---------+---------+---------+------------------+
| Used 40 | Free 80 | Used 24 |   Free (large)   |
+---------+---------+---------+------------------+
```

Memory is available but fragmented.

---

## 🧲 First Fit vs Best Fit

Free blocks available:

```
[ Free 100 ]   [ Free 60 ]   [ Free 200 ]
```

Request: `myMalloc(50)`

### First Fit
```
Chooses: Free 100 (first sufficient block)
```

### Best Fit
```
Chooses: Free 60 (tightest fit)
```

This difference is demonstrated clearly in the demo programs.

---

## ♻️ Deallocation Process (`myFree`)

Steps followed during deallocation:

1. Validate pointer:
   - Must belong to allocator heap
   - Must not already be free
2. Mark block as free
3. Insert block into free list
4. **Coalesce** with neighboring free blocks if possible

---

## 🔄 Coalescing Example

Before:

```
+---------+---------+
| Free 40 | Free 24 |
+---------+---------+
```

After coalescing:

```
+-------------------+
|     Free 64       |
+-------------------+
```

This reduces external fragmentation.

---

## 🚫 Safety Checks

### Double Free Detection

```
Attempting to free an already free block → ERROR
```

### Invalid Free Detection

```
Pointer not belonging to allocator heap → ERROR
```

These checks prevent heap corruption.

---

## 🗺 Memory Map Visualization

From demo output:

```
|U40|F80|U24|F1048336|
```

Legend:
- `U` → Used block
- `F` → Free block

This gives a compact view of heap state.

---

## 🧪 Demo Programs

Two detailed demos are provided:

- `demo_first_fit.cpp`
- `demo_best_fit.cpp`

Each demo showcases:
- Allocation
- Fragmentation
- Strategy behavior
- Coalescing
- Double free detection
- Invalid free detection

---

## 🛠 How to Run

### First Fit Demo

```bash
g++ src/MemoryAllocator.cpp demo/demo_first_fit.cpp -Iinclude -o first
./first
```

or on Windows:

```
run_first_fit.bat
```

### Best Fit Demo

```bash
g++ src/MemoryAllocator.cpp demo/demo_best_fit.cpp -Iinclude -o best
./best
```

or on Windows:

```
run_best_fit.bat
```

---

## 📚 What This Project Demonstrates

This project demonstrates strong understanding of:

- Low-level memory management
- Heap design and layout
- Fragmentation handling
- Linked list manipulation in raw memory
- Allocation strategies
- Systems programming concepts

---

## 👨‍💻 Author

**Vansh Sharma**
