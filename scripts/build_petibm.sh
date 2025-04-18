rm -rf ./*
cmake \
    -DCMAKE_INSTALL_PREFIX=$HOME/sfw/petibm/petibm-linux-dbg \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Debug \
    -DPETSC_DIR=$CONDA_PREFIX \
    -DPETSC_ARCH="" \
    -DCUDA_DIR=$CONDA_PREFIX \
    -DAMGX_DIR=$CONDA_PREFIX \
    -DAMGXWRAPPER_DIR=$CONDA_PREFIX \
    -DYAMLCPP_DIR=$CONDA_PREFIX \
    -DSYMENGINE_DIR=$CONDA_PREFIX \
    -DPETIBM_ENABLE_TESTS=ON \
    -DPETIBM_USE_AMGX=ON \
    .. \
    || { echo "CMake failed"; exit 1; }
make all -j $(nproc) || { echo "Make failed"; exit 1; }
make check || { echo "Make check failed"; exit 1; }
make install || { echo "Make install failed"; exit 1; }