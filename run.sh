# run.sh

make rebuild

if [ "$1" = "-g" ]
then
    echo run.sh: Generating data

    cd gendata && rm -rf *.log
    #time ./gendata.out > debug.log && cd ..
    time ./gendata.out && cd ..
fi

#echo sleep 3 seconds
#sleep 3

if [ "$2" != "-nc" ]
then
    echo run.sh: Clustering
    time mpirun -np 1 ./main.out > debug.log
fi

if [ -h ./plot.gnu ]
then
    echo run.sh: Plot
    gnuplot plot.gnu
    IS_RUNNING="$(lsof -c display | grep -c Clustering)"
    if [ "${IS_RUNNING}" = 1 ]
    then
	killall display
    fi
    display data/out.png &
fi

echo Now check the results
