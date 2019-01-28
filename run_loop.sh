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

#
for (( i=10000000; i <= 100000000; i += 1800000 ))
do
    echo "1thread: NUM_OF_ELEMENTS = $i"
    sed -i "13s/.*/NUM_OF_ELEMENTS = $i/" Options
    make rebuild
    time mpirun -np 1 ./main.out > debug.log
done

for (( i=10000000; i <= 100000000; i += 1800000 ))
do
    echo "2thread: NUM_OF_ELEMENTS = $i"
    sed -i "13s/.*/NUM_OF_ELEMENTS = $i/" Options
    make rebuild
    time mpirun -np 2 ./main.out > debug.log
done

if [ -h ./plot.gnu ]
then
    echo run.sh: Plot
#    gnuplot plot.gnu
    IS_RUNNING="$(lsof -c display | grep -c Clustering)"
    if [ "${IS_RUNNING}" = 1 ]
    then
	killall display
    fi
#    display data/out.png &
fi

echo Now check the results
