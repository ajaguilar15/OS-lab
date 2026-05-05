# Virtual Memory Mapping

This project demonstrates how files are created and mapped into memory using `mmap()` in C. It includes two programs:

## 📦 Files

* `generate_file.c` → creates a file of a specified size
* `file_mem_map.c` → maps the file into memory and prints page-level address information

---

## ⚙️ Compilation

Compile both programs using `gcc`:

```
gcc -Wall -Wextra -o generate_file generate_file.c
gcc -Wall -Wextra -o file_mem_map file_mem_map.c
```

---

## 📝 Step 1: Generate a Test File

### Usage:

```
./generate_file output_file size unit
```

### Example:

```
./generate_file test.txt 1 MB
```

### Supported Units:

* `B`  → Bytes
* `KB` → Kilobytes (1024 bytes)
* `MB` → Megabytes
* `GB` → Gigabytes

### Constraints:

* Size must be an **integer**
* Maximum file size is **1 GB**

---

## 🧠 Step 2: Map File into Memory

### Usage:

```
./file_mem_map input_file output_file
```

### Example:

```
./file_mem_map test.txt out.txt
```

---

## 📄 Step 3: View Output

```
cat out.txt
```

---

## 🔍 What This Program Demonstrates

### 1. File Generation

* Creates a file filled with predictable data
* Used to simulate real file storage

### 2. Memory Mapping (`mmap()`)

* Maps the file directly into virtual memory
* No manual read (`fread`) required

### 3. Page-Based Memory Access

* Reads file in increments of **4096 bytes (4 KB)**
* Each step corresponds to one **memory page**

### 4. Virtual Memory Behavior

* Shows how file data is laid out in **virtual address space**
* Demonstrates **page-aligned addressing**

---

## 🧪 Example Output Snippet

```
File size: 1048576 bytes
Mapped file starts at virtual address: 0x723b0a500000

Reading file every 4096 bytes:

data[    0] address = 0x723b0a500000
 data[ 4096] address = 0x723b0a501000
 data[ 8192] address = 0x723b0a502000
```

---

## 🧠 Key Concepts

* Virtual Memory
* Paging
* Page Size (4 KB typical)
* Memory Mapping (`mmap`)
* Demand Paging (pages loaded when accessed)
