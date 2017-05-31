RUNT_LIBS=(
cray 
runt-cairo 
runt-img 
runt-plumber
runt-scheme)

for val in ${RUNT_LIBS[@]}
do
    cd $val
    make 
    make install
    cd -
done
