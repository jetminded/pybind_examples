#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
namespace py = pybind11;

template <class T>
class Component{
public:
    Component() {}
    
    void SetData(T _data){
        data = _data;
    }
    
    T GetData(){
        return data;
    }
    
    // Less-than operator with error handling
    bool operator<(const Component<T>& other) const {
        try {
            // Try Python comparison - will raise exception if not comparable
            return data < other.data;
        } catch (const py::error_already_set& e) {
            // Handle case where objects don't support comparison
            throw std::runtime_error("Objects cannot be compared with < operator");
        }
    }

private:
    T data;
};

PYBIND11_MODULE(library, m){
    m.doc() = "Templated class library with some exposed types";

    // Bind for py::object (any Python object)
    py::class_<Component<py::object>>(m, "Component")
    .def(py::init<>())
    .def("SetData", &Component<py::object>::SetData)
    .def("GetData", &Component<py::object>::GetData)
    .def("__lt__", &Component<py::object>::operator<);
}