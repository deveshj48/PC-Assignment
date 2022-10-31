echo ------------Serial SSSP is starting---------------
./sssp |& tee sssp.out
echo -------------Serial SSSP is done------------------
echo
echo ------------OpenMP SSSP is starting---------------
./sssp_omp |& tee sssp_omp.out
echo -------------OpenMP SSSP is done------------------
echo

