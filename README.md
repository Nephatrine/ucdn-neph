| Linux/GCC | Windows/MSVC | Binaries |
| :---------: | :------------: | :--------: |
| [![Linux Status](https://travis-ci.org/Nephatrine/ucdn-neph.svg?branch=master)](https://travis-ci.org/Nephatrine/ucdn-neph) | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/lpwxdh7nsswly6jf/branch/master?svg=true)](https://ci.appveyor.com/project/Nephatrine/ucdn-neph) | [![Binaries](https://img.shields.io/badge/bin-MS%20VC14-brightgreen.svg)](https://ci.appveyor.com/project/Nephatrine/ucdn-neph/build/artifacts)

This is my personal fork. It mostly contains changes to the build system to
bring it more in-line with other tools I use and integrate more cleanly into my
other projects and build pipeline.

I don't expect this to be useful to anyone else and suggest using the
[upstream repository](https://github.com/grigorig/ucdn) instead.

# UCDN - Unicode Database & Normalization

UCDN is a Unicode support library. Currently, it provides access
to basic character properties contained in the Unicode Character
Database and low-level normalization functions (pairwise canonical
composition/decomposition and compatibility decomposition). More
functionality might be provided in the future, such as additional
properties, string normalization and encoding conversion.

**Copyright Information:**

UCDN was written by [Grigori Goronzy](https://github.com/grigorig) <<greg@kinoho.net>>.

* UCDN is published under the [ISC license](LICENSE.md).
* The Python script required for parsing Unicode database files is licensed
  under the [PSF license](PYTHON-LICENSE).

**Other Links:**

* [Upstream @ GitHub](https://github.com/grigorig/ucdn)

## Building

**Requires**

* CMake 3.2+
* Python 2.7+

Build steps are bog-standard CMake and so a minimal example would be:

```
mkdir build
cd build
cmake ..
make
```

## Installation

You can install the project with just the basic `make install` after building,
or you can `make package` to generate an archive for the project that you can
install manually or distribute.

