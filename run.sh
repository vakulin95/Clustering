# run.sh

make rebuild

if [ "$1" = "-g" ]
then
    echo Generating data

    cd gendata && rm -rf *.log
    time ./gendata.out > debug.log && cd ..
fi

#echo sleep 3 seconds
#sleep 3

if [ "$1" != "-pl" ]
then
   time ./main.out > debug.log
fi
   
if [ -h ./plot.gnu ]
then
    gnuplot plot.gnu
    IS_RUNNING="$(lsof -c display | grep -c Clustering)"
    if [ "${IS_RUNNING}" = 1 ]
    then
	killall display
    fi
    display data/out.png &
fi

echo Now check the results
