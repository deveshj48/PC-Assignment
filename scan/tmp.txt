echo
echo ---------scan has started----------
./scan 2 1 4 0 3 7 6 3 |& tee -a terminal_output.out
echo ---------scan is done-------------
echo
echo ---------scan_omp has started----------
./scan_omp 2 1 4 0 3 7 6 3 |& tee -a terminal_output.out
echo ---------scan_omp is done-------------
echo
echo ---------scan_mpi has started----------
./scan_mpi 2 1 4 0 3 7 6 3 |& tee -a terminal_output.out
echo ---------scan_mpi is done-------------