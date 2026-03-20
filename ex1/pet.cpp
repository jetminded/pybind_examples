#include <pybind11/pybind11.h>

#include <string>

namespace py = pybind11;

int add(int a, int b){
    return a+b;
}

struct Pet{
    Pet(const std::string &name) : name(name){}
    void setName(const std::string &name_){
        name = name_;
    }
    const std::string &getName() const { return name; }

    std::string name;
};

// Creates a macro function that will be called
// whenever the module is imported into python
// 'mymodule' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'
PYBIND11_MODULE(pet_module, m){
    m.doc() = "example plugin"; // Optional docstring
    m.def("add", &add, "Add two integers.");

    py::class_<Pet>(m, "Pet")
            .def(py::init<const std::string &>())   // our constructor
            .def("setName", &Pet::setName)      // Expose member methods
            .def("getName", &Pet::getName)      // Think about the syntax "&Pet then "::" and the method name
            .def_readwrite("name",&Pet::name);  // Expose member variables
}
