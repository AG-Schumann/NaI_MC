#NaI Crystall Geant4 MC code

It simulates an SCIONIX Holland 3"x3" NaI Crystal with the Pmt Casing and a PE Holder. 
The Crystal and PMT are oriented along the Y-axis with the front Plane (X-Z) of the Crystal with Casing at y=0.

The code was developed using the following eviroments:

The DELight MC code is developed using the following environment:
  * [ROOT v6.26/06](https://root.cern/install/all_releases/)
  * [GEANT4 v11.0.3](https://geant4.web.cern.ch/download/11.0.3.html)

using the **C++17** standard for multithreading purpose.

## Obtain this code

Clone this repository and compile the code:
  * Create a `build` directory within the repository and access it
    ```
    mkdir build
    cd ./build
    ```
  * Run cmake (version >= 3.16, <=3.21)
     ```
     cmake ..
     ```
  * As the dependencies are generated, you can start the compilation
    ```
    make -j<number_of_cpus>
    ```
    where the option `-j` is not mandatory, but it speeds up the compilation time using more CPUs (if available).

At this point, if the compilation was successful, you are left with the executable `DELight_G4`.

## Run the code
The executable creates only the framework for the simulation, but the actual simulation requires specific commands (e.g., what particle to generate, where, how many, etc.).
These are passed via <b>macro</b> files (.mac). 

The code can be executed as follows:
```
./NaI_MC [-o <output_file.root>] [-m <macro_file.mac>] [-p <preinit_macro_file.mac>] [-n <number_of_primaries>]
```

| Option | Explanation | Default |
|--------|-------------|---------|
| -o     | Sets the output file path. | `./NaI_Simulation.root`    |
| -m     | Sets the macro file path. | `./macros/init.mac`    |
| -p     | Sets the preinit macro file path. | `None`    |
| -n     | Sets the number of primaries. | 1000    |

## Output
Everything is stored under the tree Hits

  | Name          | Type           | Description                           | Units |
  |---------------|----------------|---------------------------------------|-------|
  | x_pri         | double         | X-coordinate of primary particle      | mm    |
  | y_pri         | double         | Y-coordinate of primary particle      | mm    |
  | z_pri         | double         | Z-coordinate of primary particle      | mm    |
  | dx_pri        | double         | X-component of primary direction      | %     |
  | dy_pri        | double         | Y-component of primary direction      | %     |
  | dz_pri        | double         | Z-component of primary direction      | %     |
  | E_pri         | double         | kinetic Energy of Primary             | keV   |
  | edep          | double         | total Energy deposited in NaI         | keV   |
