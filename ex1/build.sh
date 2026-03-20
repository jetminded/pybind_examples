MODULE_NAME=$1

python3 -m venv venv
source venv/bin/activate
pip install pybind11

mkdir build
cd build

cmake ..
cmake --build .

cp "${MODULE_NAME}.cpython-312-x86_64-linux-gnu.so" "../${MODULE_NAME}.so"
