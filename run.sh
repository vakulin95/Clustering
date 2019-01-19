# run.sh

if [ "$1" = "-g" ]
then
    echo Generating data

    cd gendata && rm -rf *.log
    time ./gendata.out > debug.log && cd ..

    gnuplot plot.gnu
    IS_RUNNING="$(lsof -c display | grep -c Clustering)"
    if [ "${IS_RUNNING}" = 1 ]
    then
	killall display
    fi
    display data/out.png &
fi

echo sleep 3 seconds
sleep 3

time ./main.out

echo Now check the results
