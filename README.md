# 🔍 C++ Profiling Benchmark: Inefficient Matrix Kernel

This project is a deliberately inefficient C++ application designed to serve as a **benchmarking and profiling target** for tools like:

- [Score-P](https://www.vi-hps.org/projects/score-p/)
- [perf](https://perf.wiki.kernel.org/)
- [gprof](https://gcc.gnu.org/onlinedocs/gcc-13.1.0/gprof.html)
- [Valgrind](https://valgrind.org/)
- [Google gperftools](https://github.com/gperftools/gperftools)
- [Tracy](https://github.com/wolfpld/tracy)

Its purpose is to help engineers **understand and compare profiler outputs** across multiple tools, including CPU cycles, memory usage, call graphs, and context switches.

---

## 📼 Demonstration (YouTube)

🎬 **Watch the video walkthrough here:**  
👉 [Profiling seminar](https://youtu.be/A6e2e2GZxnM)

---

## 🧠 What the Program Does

This program allocates a 2D matrix, fills it with pseudo-random values, and applies a **3×3 convolutional kernel** (sharpening filter). It includes artificial inefficiencies such as:

- Manual `malloc`/`free` management
- Redundant `memset` calls
- Unnecessary string operations in loops
- Lack of loop optimizations
- Verbose `printf` debugging
- No vectorization or blocking

---

## 📂 Project Structure

```bash
.
├── CMakeLists.txt           # Builds the project and supports optional profiler flags
├── src/
│   └── main.cpp             # The inefficient benchmark application
├── README.md                # You're here
```

---

## 🛠️ Build Instructions

### AIO script

```bash
bash run.sh
```

> ✅ Remember to compile with `-fno-omit-frame-pointer` and `-g -O2` for best stack traces.

---

## 📊 What to Look for in Profilers

| Profiler | What it Shows                           | Notes |
|----------|------------------------------------------|-------|
| Score-P + CUBE | Inclusive/exclusive time, call tree, thread breakdown | High overhead |
| perf      | Hardware counters, CPU samples, call stacks | Very low overhead |
| gprof     | Call graph and function timings          | Requires `-pg`, no threading support |
| Valgrind Memcheck | Invalid memory, leaks              | Very slow |
| Tracy     | Real-time frame timings, GPU+CPU zones   | Requires manual zone annotations |

---

## 📜 License

This project is distributed under the MIT License.

---

## 🙋‍♂️ Contributions

Feel free to fork, improve inefficiencies, or add integrations with other profilers. Pull requests welcome!
