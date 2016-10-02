## To build:

    mkdir build && cd build
    cmake ..
    make

This was built on a Mac El Capitan using llvm. 

## Problems I ran into:

* I never got the cmake OPENMP finder to work, I think it's intended for GCC.

* Initially I tried using the mac built-in llvm with the homebrew package `clang-openmp`, but this didn't seem to work. I got linker errors that looked like `unable to find _znam`. Errors that looked like it online were related to incompatable compiler and standard library versions so I figured `clang-openmp` was made for a different setup then the one I had.

* I tried compiling and using the openmp package that llvm provides, but that didn't seem to work either, the -fopenmp compiler flag was not found as I guess it's a compiler-specific feature.

* Equipped with the knowledge of the above two items, I used homebrew to install llvm/clang3.8, which includes openmp support. This allowed `-fopenmp` to work, but the headers and the compiled library where not found this time.

* Finally I combined clang3.8 with the compiled version openmp package that llvm provides. The OPENMP finder in cmake still didn't work, but putting in the library and header paths manually finally allowed the script to compile and run without errors.

