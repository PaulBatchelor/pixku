#! /bin/sh
if [ "$#" -eq 0 ]
then
echo "Usage: sh run.sh [install|clean]"
exit
fi

RUNT_LIBS="cray 
runt-cairo 
runt-img 
runt-plumber
runt-scheme"

install_patchwerk()
{
    cd patchwerk
    make patchwerk.c
    cd runt 
    make
    make install
    cd ../../
}


install()
{
for val in $RUNT_LIBS
do
    cd $val
    make 
    make install
    cd -
done
install_patchwerk
}

clean_patchwerk()
{
    cd patchwerk
    make clean
    cd runt
    make clean
    cd ../../
}

clean()
{
for val in $RUNT_LIBS
do
    cd $val
    make clean 
    cd -
done
clean_patchwerk
}

if [ "$1" == install ] 
then
install
elif [ "$1" == "clean" ]
then
clean
fi
