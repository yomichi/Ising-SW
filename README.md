# Ising-SW
Swendsen-Wang algorithm for classical Ising model implemented with ALPS/parapack library.

# Requirement
- ALPS v2

# Build
Type `ALPS_HOME=/where/ALPS/is/built ./make.sh`.
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
    
    # several output files have been generated
    ls *.dat

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

- squared magnetization per site `<M^2>`
    - Observable name :  `Magnetization^2`
    - result file (`plot.py`) : `mag2-L*.dat`
- biquadratic magnetization per site `<M^4>`
    - Observable name : `Magnetization^4`
    - result file (`plot.py`) : `mag4-L*.dat`
- absolute magnetization per site `<|M|>`
    - Observable name : `|Magnetization|`
    - result file (`plot.py`) : `amag-L*.dat`
- Binder ratio defined as `<M^4>/<M^2>^2`
    - Observable name : `Binder Ratio`
    - result file (`plot.py`) : `binder-L*.dat`
- Magnetic susceptibility `N <M^2> / T`
    - Obaservable name : `Susceptibility`
    - This _survives_ in ordered state
    - result file (`plot.py`) : `sus-L*.dat`
- Magnetic susceptibility `N (<M^2> - <|M|>^2 ) /T`
    - Observable name : `Connected Susceptibility`
    - This _vanishes_ in ordered state
    - result file (`plot.py`) : `csus-L*.dat`
- total energy (_not_ per site or bond)
    - Observable name : `Energy`
    - result file (`plot.py`) : `ene-L*.dat`
- specific heat
    - Observable name : `Specific Heat`
    - result file (`plot.py`) : `spec-L*.dat`
    - NOTE: This evaluator has not been tested enough...

# License
This program is distributed under the Boost Software License.
See [LICENSE_1_0.txt](LICENSE_1_0.txt) for detail.
