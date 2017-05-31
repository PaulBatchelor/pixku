RUNT_LIBS=(
cray 
runt-cairo 
runt-img 
runt-plumber)

for val in ${RUNT_LIBS[@]}
do
    cd $val
    make 
    make install
    cd -
done
