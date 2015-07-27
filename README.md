# Ising-SW
Swendsen-Wang algorithm for classical Ising model implemented in C++/ALPS

# Requirement
- ALPS v2
  - CMake

# Build
Type `ALPS_HOME=/where/ALPS/is/built sh make.sh`.
Executable file `ising` will be built in `build` directory.

# Run

    # copy template files
    cp -r template 2D && cd 2D
    
    # edit input parameters
    vi init_param.py
    
    # generate input files
    python init_param.py
    
    # run
    mpiexec -np 4 ../build/ising --mpi params.in.xml
    
    # extract results
    python plot.py


# License
This program is distributed under the Boost Software License.
See `LICENSE_1_0.txt` for detail.
