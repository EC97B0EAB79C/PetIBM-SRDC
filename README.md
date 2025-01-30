# PetIBM-SRDC 

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://github.com/barbagroup/PetIBM/raw/master/LICENSE)

This repository is a modified version of PetIBM, originally developed by the Barba Group.

Original Project: [PetIBM](https://github.com/barbagroup/PetIBM)


---

## Features

Features from PetIBM:

* multiple immersed bodies,
* moving bodies with prescribed kinematics,
* 2D and 3D stretched Cartesian meshes,
* distributed-memory architectures,
* multiple GPUs on a single node,
* GPU clusters, and
* HDF5 I/O.

---

## Documentation

* [Quick Start](doc/markdowns)
  * [Dependencies and Installation](doc/markdowns/installation.md)
  * [Run PetIBM](doc/markdowns/runpetibm.md)
  * [Input files](doc/markdowns/inputs.md)
  * [Output files](doc/markdowns/outputs.md)
  * [2D Examples](doc/markdowns/examples2d.md)
  * [3D Examples](doc/markdowns/examples3d.md)
  * [Use PetIBM API](doc/markdowns/usepetibmapi.md)
* [Online API manual](https://barbagroup.github.io/PetIBM)
* [Change Log](CHANGELOG.md)
* [Contributing](CONTRIBUTING.md)

Offline API manual can be generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/).

## Citation
### Original PetIBM citation:

If PetIBM contributes to a project that leads to a scientific publication, please cite the project.
You can use this citation or the BibTeX entry below.

> Pi-Yueh Chuang, Olivier Mesnard, Anush Krishnan, Lorena A. Barba (2018). PetIBM: toolbox and applications of the immersed-boundary method on distributed-memory architectures. _Journal of Open Source Software_, **3**(25), 558, [doi:10.21105/joss.00558](https://doi.org/10.21105/joss.00558)

```console
@article{chuang2018petibm,
  doi = {10.21105/joss.00558},
  url = {https://doi.org/10.21105/joss.00558},
  year = {2018},
  month = {may},
  publisher = {The Open Journal},
  volume = {3},
  number = {25},
  pages = {558},
  author = {Pi-Yueh Chuang and Olivier Mesnard and Anush Krishnan and Lorena A. Barba},
  title = {{PetIBM}: toolbox and applications of the immersed-boundary method on distributed-memory architectures},
  journal = {The Journal of Open Source Software}
}
```
