if [ "$#" -eq 0 ]
then
echo "Usage: sh run.sh [install|clean]"
exit
fi

RUNT_LIBS=(cray 
runt-cairo 
runt-img 
runt-plumber
runt-scheme)

install()
{

for val in ${RUNT_LIBS[@]}
do
    cd $val
    make 
    make install
    cd -
done
}

clean()
{

for val in ${RUNT_LIBS[@]}
do
    cd $val
    make 
    make clean 
    cd -
done
}

if [ "$1" == install ] 
then
install
elif [ "$1" == "clean" ]
then
clean
fi
