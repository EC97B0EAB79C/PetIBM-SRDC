rm -rf ./*
cmake -DPETIBM_DIR=${CONDA_PREFIX} ../ || { echo "CMake failed"; exit 1; }
make all -j $(nproc) || { echo "Make failed"; exit 1; }