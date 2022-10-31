echo ------------Serial SSSP is starting---------------
./sssp |& tee -a terminal.out
echo -------------Serial SSSP is done------------------
echo
echo ------------OpenMP SSSP is starting---------------
./sssp_omp |& tee -a terminal.out
echo -------------OpenMP SSSP is done------------------
echo

