wget https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-Linux-x86_64.sh
bash Miniforge3-Linux-x86_64.sh -b -p $HOME/miniforge
source miniforge/bin/activate
mamba create \
    -n petibm \
    -c barbagroup \
    -c nvidia \
    -c conda-forge \
    "*amgxwrapper=*=cuda114*" \
    "yaml-cpp>=0.7" \
    "symengine>=0.9" \
    "cmake>=3.23" \
    "make" \
    "pkg-config" \
    "git" \
    "gxx_linux-64>=11.2"
conda activate petibm
mamba install -c nvidia cuda-toolkit
