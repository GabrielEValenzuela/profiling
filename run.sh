#!/bin/bash

echo "Running score-p"
mkdir build_scorep && cd build_scorep
SCOREP_WRAPPER=off cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_COMPILER=/opt/scorep/bin/scorep-g++
make -j$(nproc)
./original 1000 10 > output.txt
cd ..

echo "Running GNU performance tools"
mkdir build_gprof && cd build_gprof
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS=-pg -DCMAKE_EXE_LINKER_FLAGS=-pg -DCMAKE_SHARED_LINKER_FLAGS=-pg
make -j$(nproc)
./original 1000 10 > output.txt
cd ..


echo "Running Google performance tools (MEM)"
mkdir build_gperfmem && cd build_gperfmem
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_GPERF_MEM=ON
make -j$(nproc)
HEAPPROFILE=/tmp/heapprof ./original 1000 10 > output.txt
cd ..

echo "Running Google performance tools (CPU)"
mkdir build_gperfcpu && cd build_gperfcpu
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_GPERF_CPU=ON
make -j$(nproc)
CPUPROFILE=/tmp/prof.out ./original 1000 10 > output.txt
cd ..

echo "Running perf tools"
mkdir build_perf && cd build_perf
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
make -j$(nproc)
sudo perf record -e cycles -e sched:sched_switch --switch-events --sample-cpu -m 8M --aio -z --call-graph dwarf ./original 1000 10 > output.txt
cd ..

echo "Running Callgrind"
mkdir build_callgrind && cd build_callgrind
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
make -j$(nproc)
valgrind --tool=callgrind ./original 1000 10 > outputCall.txt
valgrind --tool=callgrind --simulate-cache=yes ./original 1000 10 > outputCallCacheSim.txt
echo "Run callgrind_annotate --auto=yes callgrind.out" 
valgrind --tool=cachegrind ./original 1000 10 > outputCache.txt
cd ..

echo "Running tracy"
if [ ! -d "$(pwd)/tracy" ]; then
    echo "Tracy not found, please clone it first."
    exit 1
fi

mkdir build_tracy && cd build_tracy
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_TRACY=ON
make -j$(nproc)
cd ..

echo "Done!"
