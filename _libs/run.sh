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
runt-scheme
runt-math"

install_patchwerk()
{
    cd patchwerk
    git pull origin master
    make patchwerk.c
    cd runt 
    make
    make install
    if [ $? != 0 ] ; then 
        exit 1 
    fi 
    cd ../../
}

install_libline()
{
    cd libline
    git pull origin master
    make  
    cd runt 
    make
    make install
    if [ $? != 0 ] ; then 
        exit 1 
    fi 
    cd ../../
}

install()
{
for val in $RUNT_LIBS
do
    cd $val
    git pull origin master
    make 
    make install
    if [ $? != 0 ] ; then 
        exit 1 
    fi 
    cd -
done 
install_patchwerk
install_libline
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
