prevdir=$(pwd)


mkdir -p packages
cd packages

git clone git://github.com/glfw/glfw.git --depth=1
cd glfw
cmake .
make
cd ../

git clone git://git.savannah.gnu.org/freetype/freetype2.git --depth=1
cd freetype2
./autogen.sh
./configure
make
cd ../

git clone git://github.com/recp/cglm.git --depth=1
cd cglm
cmake .
make
cd ../

wget https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.tgz/download
tar xf download
cd glew-2.1.0
make
cd ..

git clone git://github.com/glennrp/libpng.git --depth=1
cd libpng
./configure
cmake .
make
cd ..

cd $prevdir
mkdir -p lib
cp $(find ./packages/ | grep "\.so$\|\.a$") lib/.
cp ./libcengine.a lib/.
