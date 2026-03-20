python3 -m venv venv
source venv/bin/activate
pip install pybind11

mkdir build
cd build

cmake ..
cmake --build .
