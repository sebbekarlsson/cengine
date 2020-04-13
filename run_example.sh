startdir=$(pwd)

make && sudo make install

cd exampleapp
make clean
make && ./a.out

cd $startdir
