[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![MIT][license-shield]][license-url]

<!-- PROJECT LOGO -->
<div align="center">

<h3 align="center">Utillities '2'</h3>

  <p align="center">
    Common Utillity Library
  </p>

</div>

<!-- ABOUT THE PROJECT -->
## About The Project

C & C++ Routines, Typedefines, Classes, Templates, etc... that I needed over the years to simplify my workflows  
for ABI Compatibility, it is recommended to use this project as a git submodule, with the included C headers  
See docs.md for API Documentation

### Project Structure

The project structure is the same as my [premake5-workspace-template](https://github.com/inonitz/premake5-workspace-template), except that I use CMake instead  
<br></br>

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

* CMake
* Working compiler toolchain, preferably clang
  * Windows: You should use [llvm](https://github.com/llvm/llvm-project/releases)
  * Linux:
      1. [installing-specific-llvm-version](https://askubuntu.com/questions/1508260/how-do-i-install-clang-18-on-ubuntu)
      2. [configuring-symlinks](https://unix.stackexchange.com/questions/596226/how-to-change-clang-10-llvm-10-etc-to-clang-llvm-etc)
      3. **You Don't have to use LLVM, gcc works too**

### Installation

```sh
git clone https://github.com/inonitz/util2/util2.git desired_folder_path_from_cwd
```

For Conciseness, I also include simple build steps with compile_commands.json:  

```sh
cd desired_folder_path_from_cwd/util2
mkdir -p ../build
cmake -S . -B ../build -G 'Ninja' \
  -DCMAKE_C_COMPILER=clang     \
  -DCMAKE_CXX_COMPILER=clang++  \   
  -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
  -DCMAKE_BUILD_TYPE=Debug \
  -DBUILD_SHARED_LIBS=0

cd ../build
cp "compile_commands.json" "../../compile_commands.json" 
ninja $PROJECT_NAME
```

In a single line for copying:  
```
cd util2 && mkdir -p ../build && cmake -S . -B ../build -G 'Ninja' -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=0 && cd ../build && cp "compile_commands.json" "../../compile_commands.json" && ninja util2

```

<br></br>

<!-- USAGE EXAMPLES -->
## Usage

### In Source Build

In your CmakeLists.txt:

```sh
add_subdirectory(your_directory/util2)
```

### Out-Of-Source (Submodule/etc...) Build

```sh
git submodule add https://github.com/inonitz/util2 your_dependency_folder/util2
git submodule init
git submodule update
```

In your CmakeLists.txt:

```sh
add_subdirectory(your_dependency_folder/util2)
```

<br></br>

<!-- CONTRIBUTING -->
## Contributing

If you have a suggestion, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".  

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` file for more information.

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgement

* [Tinycthread](https://github.com/tinycthread/tinycthread)
* [stb_image](https://github.com/nothings/stb)

<!-- References -->
## References

* [Modern CMake](https://cliutils.gitlab.io/modern-cmake/README.html)
* [Best-README](https://github.com/othneildrew/Best-README-Template)

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/inonitz/util2?style=for-the-badge&color=blue
[contributors-url]: https://github.com/inonitz/util2/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/inonitz/util2?style=for-the-badge&color=blue
[forks-url]: https://github.com/inonitz/util2/network/members
[stars-shield]: https://img.shields.io/github/stars/inonitz/util2?style=for-the-badge&color=blue
[stars-url]: https://github.com/inonitz/util2/stargazers
[license-shield]: https://img.shields.io/github/license/inonitz/util2?style=for-the-badge
[license-url]: https://github.com/inonitz/util2/blob/main/LICENSE

<!-- [SDL3-url]: https://github.com/libsdl-org
[SDL3.js]: https://libsdl.org/media/SDL_logo.png -->