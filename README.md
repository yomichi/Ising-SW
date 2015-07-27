# Ising-SW
Swendsen-Wang algorithm for classical Ising model implemented with ALPS/parapack library.

# Requirement
- ALPS v2

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

# Input parameters
- `T`
    - Temperature
- `J`
    - Coupling constant (only ferromagnet system (J>0) can be dealt with)
    - By default, `J = 1`
- `LATTICE`
    - Lattice name ('chain lattice', 'square lattice', 'simple cubic lattice', ...)
    - please consult [ALPS web page](http://alps.comp-phys.org/mediawiki/index.php/Tutorials:LatticeHOWTO).
- `L`, `W`, `H`
    - Lattice length, width, and height.
    - `W` and `H` are equal to `L` and `W` by default.
- `SWEEPS`
    - Monte Carlo steps
    - By default, `SWEEPS = 65536`
- `THERMALIZATION`
    - Thermalization steps
    - By default, `THERMALIZATION = SWEEPS >> 3`

# Observables
Except for `|Magnetization|` and `Connected Susceptibility`,
improved estimator is implemented.

- `Magnetization^2`
    - squared magnetization per site `<M^2>`
- `Magnetization^4`
    - biquadratic magnetization per site `<M^4>`
- `|Magnetization|`
    - absolute magnetization per site `<|M|>`
- `Binder Ratio`
    - Binder ratio defined as `<M^4>/<M^2>^2`
- `Susceptibility`
    - Magnetic susceptibility `N <M^2> / T`
    - This _survives_ in ordered state
- `Connected Susceptibility`
    - Magnetic susceptibility `N (<M^2> - <|M|>^2 ) /T`
    - This _vanishes_ in ordered state
- `Energy`
    - total energy (_not_ per site or bond)
- `Specific Heat`
    - specific heat


# License
This program is distributed under the Boost Software License.
See `LICENSE_1_0.txt` for detail.
