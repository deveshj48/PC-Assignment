# PC-Assignment

## Description
This README.md file servers to give the tester a brief overview on how our assignment is structured.

## How to run tests
### Scan
* Navigate to the "scan" folder in the terminal
    * run _make_
    * run _./run.sh_
* This will then run the 3 versions (Serial | OpenMP Parallel | MPI Parallel) of the scan operation
* To test with your own input array, change the following values in the _run.sh_ file to the desired values.
    * [Screenshot-change-values](./Resources/Screenshot-run-values-scan.png)
    * Note
        * Ensure to change the values for all 3 runs to ensure they are all running with the same input values
        * Format: <programme_name> <arr[0]> <arr[1]> <arr[2]> ... <arr[N]>
* The output is also appended to a text file named terminal_output.txt. This file includes some sample runs but terminal output will be appended to this file on new runs.

### Bitonic Sort
* Navigate to the "bitonic" folder in the terminal
    * run _make_
    * run _./run.sh_
* This will then run the 3 versions (Serial | OpenMP Parallel | MPI Parallel) of the bitonic algorithm
* ???To test with your own input array, change the following values in the _run.sh_ file to the desired values.
    * [Screenshot-change-values](./Resources/Screenshot-run-values-scan.png)
    * Note
        * Ensure to change the values for all 3 runs to ensure they are all running with the same input values
        * Format: <programme_name> <arr[0]> <arr[1]> <arr[2]> ... <arr[N]>

* The output is also appended to a text file named terminal_output.txt. This file includes some sample runs but terminal output will be appended to this file on new runs.

### SSSP Algorithm
* Navigate to the "dijkstra" folder in the terminal
    * run _make_
    * run _./run.sh_
* This will then run the 2 versions (Serial | OpenMP Parallel ) of the dijkstra algorithm.
* To test with different input textfiles, change the GRAPH_FILE constant in both sssp_omp.c and sssp.c files.

* The output is also appended to a text file named terminal_output.txt. This file includes some sample runs but terminal output will be appended to this file on new runs.