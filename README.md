# Custom Memory Allocator in C++

A from-scratch implementation of a **custom heap memory allocator** that mimics the internal behavior of `malloc` and `free`.

This project demonstrates how dynamic memory management works internally in operating systems and C/C++ runtime libraries.

---

## 🚀 Features

- Private 1 MB heap managed manually
- Block metadata using headers
- Separate **heap list** and **free list**
- Block **splitting** during allocation
- Block **coalescing** during deallocation
- Memory **alignment (8 bytes)**
- Support for **First Fit** and **Best Fit** allocation strategies
- Fragmentation visualization
- Safety checks:
  - Double free detection
  - Invalid free detection
- Heap statistics and memory map visualization

---

## 🧠 How Memory is Managed

Every block in the heap looks like this:

```
| BlockHeader | -------- Payload (User Memory) -------- |
```

### 📌 Insert Hand Drawn Diagram Here (Block Structure)

---

## 🗂 Heap Structure

The allocator maintains two linked lists:

1. **Heap List** → connects all blocks in physical memory order
2. **Free List** → connects only free blocks for faster allocation search

### 📌 Insert Hand Drawn Diagram Here (Heap List vs Free List)

---

## ⚙️ Allocation Process (`myMalloc`)

1. Align requested size to 8 bytes
2. Search free list using chosen strategy:
   - First Fit
   - Best Fit
3. Remove block from free list
4. Split block if larger than needed
5. Return pointer to payload

### 📌 Insert Hand Drawn Diagram Here (Block Splitting)

---

## ♻️ Deallocation Process (`myFree`)

1. Validate pointer (invalid / double free detection)
2. Mark block as free
3. Add block to free list
4. Coalesce with neighboring free blocks

### 📌 Insert Hand Drawn Diagram Here (Coalescing)

---

## 📊 Fragmentation Example

When a middle block is freed, fragmentation occurs:

```
| Used | Free | Used | Free |
```

First Fit and Best Fit behave differently here.

---

## 🧪 Demo Programs

Two demos are provided:

- `demo_first_fit.cpp`
- `demo_best_fit.cpp`

These demonstrate:
- Allocation
- Fragmentation
- Strategy behavior
- Coalescing
- Safety checks

---

## 🛠 How to Run

### First Fit Demo

```bash
g++ src/MemoryAllocator.cpp demo/first_fit.cpp -Iinclude -o first
./first
```
or run the file : first_fit.bat

### Best Fit Demo

```bash
g++ src/MemoryAllocator.cpp demo/best_fit.cpp -Iinclude -o best
./best
```

or run the file : best_fit.bat

---

## 🖥 Example Output

(Insert terminal screenshots here for LinkedIn / README)

---

## 📚 What This Project Demonstrates

This project showcases understanding of:

- Low level memory management
- Heap design
- Fragmentation handling
- Linked list management in memory
- Allocation strategies
- Systems programming concepts

---

## 👨‍💻 Author

Vansh Sharma
