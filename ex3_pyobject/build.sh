python3 -m venv venv
source venv/bin/activate
pip install pybind11

mkdir build
cd build

cmake ..
cmake --build .

cp library.cpython-312-x86_64-linux-gnu.so ../library.so
