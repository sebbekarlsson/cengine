startdir=$(pwd)
appname=$1

make && sudo make install

cd examples/$appname
make clean
make && ./a.out

cd $startdir
