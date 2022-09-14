# graph-lib


## Requirements:

* C++ 17
* SFML - graphical output
* Doxygen - generate documentation

## Installation

### Easiest way

```bash
# install sfml
sudo apt install libsfml-dev

# install doxygen
sudo apt install doxygen

# add graph-lib to your project source directory
cd "${project_src_dir}"
git clone git@github.com:RosFateev/graph-lib.git

# in project cmake file add:
# add_subdirectory(graph-lib)

# compile and run
cd "${project_bin_dir}"
cmake -S "${project_src_dir}"
cmake --build .
./project-name args
```

The documentation is available in doc subdirectory of `${project_bin_dir}` (open `${project_bin_dir}/doc/html/index.html` in your browser).
