# Practical CMake Syntax Tutorial
## I. Introduction
I recently worked on a C++ project and decided to learn CMake in the process. To be honest, the initially strange syntax of CMake can be intimidating. However, once you start using it, you'll realize that you only need a small portion of its features for most everyday tasks, and there's usually a pattern to follow. Mastering this part of CMake can enable you to manage larger projects with ease. This article aims to cover this essential part of CMake.

Before diving into this tutorial, it's essential to have some knowledge of code compilation and linking.

Here's how you can install CMake using apt:

```sh
sudo apt-get install build-essential
sudo apt-get install cmake
```

## II. Getting Started
Let's begin with a classic "hello, world" program as our first example.

```c
#include <stdio.h>

int main()
{
    printf("hello, world\n");
    return 0;
}
```

In this tutorial, I'll first provide the compilation command using gcc and then show how to achieve the same using CMake. For our first step, the gcc command is as follows:
```sh
gcc main.cpp -o main
```

Using CMake is somewhat similar. We need to add a configuration file, CMakeLists.txt, containing the actions we want to perform. In this section, the content of CMakeLists.txt is as follows:

```cmake
cmake_minimum_required(VERSION 3.10)

project(main)

add_executable(main main.cpp)
```

Here, the first line specifies the required CMake version, the second line sets the project name, and the third line, add_executable, accomplishes the same task as the gcc command: specifying the source file main.cpp and the output file name main to generate an executable.

To compile using CMake, you first need to generate build files using the cmake command. This will create various configuration files in the current directory, including a Makefile. Afterward, you can compile the project using the make command.

To keep our source file structure clean, you can choose to create a separate directory for building and run the cmake command there. Assuming you are in the project's root directory, you can do the following:

```sh
mkdir build
cd build
cmake ..
```

Now you can build the project using the make command and run it:

```sh
make
./main
```

At first glance, it might seem that CMake is more complicated than using gcc for a simple program like this. However, as your project structure becomes more complex, the advantages of CMake become increasingly apparent.

## III. Including Header Files
Most real-world projects consist of multiple source files. The compiler can compile them into a single .o file, and symbols between source files are shared through header files. Let's consider an example project structure for this scenario:

```text
.
|-- CMakeLists.txt
|-- include
|   `-- add.h
`-- src
    |-- add.cpp
    `-- main.cpp
```

In add.h, we declare a function int add(int a, int b), which is implemented in add.cpp. main.cpp calls this function and needs to include the header file add.h. To compile this using gcc, you can use the following command, noting that you need to specify the path to the header file with the -I flag:

```sh
gcc src/add.cpp src/main.cpp -I ./include -o main
```

For CMake, the configuration looks like this:

```cmake
cmake_minimum_required(VERSION 3.10)

project(main)

add_executable(main src/main.cpp src/add.cpp)
target_include_directories(main PRIVATE include)
```

Here, besides the add_executable command, we introduce a new command, target_include_directories. This command adds the path ./include to the header file paths required by the main target.

> Note the usage of PRIVATE in target_include_directories. It specifies the scope of the header file. PRIVATE means that the header file is only used for the current target (in this case, main) and is not exposed to files linking to the current target. There are also PUBLIC and INTERFACE options, which have different usage scenarios. If you don't fully grasp this concept yet, don't worry; we'll encounter it again later.

## IV. Compiling and Linking Libraries
Sometimes, you may need to compile a module into a library for use in different programs. Let's take the previous example but reorganize the code structure. Since main module calls functions provided by the add module, we can compile the add module into a library and then link that library with main.

To create a library in gcc, you can choose to create a static library or a dynamic shared library (dynamic link library, .so in Linux). For a static library, use the following commands to compile add:

```sh
gcc -c add/src/add.cpp -I add/include # just compile add
ar cr libadd.a add.o # create a static lib add (this name is libadd.a)
```

Next, link the library with main:
```sh
gcc main.cpp -I add/include -L . -l add -o main
```

For a shared library, use these commands to compile add:
```sh
gcc -c -fPIC add/src/add.cpp -I add/include -o add.o
gcc -shared -fPIC add.o -o libadd.so
```

Link the shared library with main:
```sh
gcc main.cpp libadd.so -I add/include -o main
```

When executing the program, set the library path as follows:

```sh
LD_LIBRARY_PATH=.
./main
```

> As you can see, as your project becomes more complex, the manual steps needed for compilation become more cumbersome. In typical scenarios, multiple commands can be combined into shell scripts. If the dependencies become even more intricate, you might need to use makefiles to manage the compilation process. However, for larger projects where writing extensive makefiles can become unwieldy, advanced tools like CMake become the natural choice.

For CMake, library compilation and linking are more straightforward. We need to introduce two new commands:
```cmake
cmake_minimum_required(VERSION 3.10)

project(main)

add_library(add add/src/add.cpp)
target_include_directories(add PUBLIC add/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE add)
```

Notice that apart from the add_executable command, we've added a new command, add_library, which creates a library (by default, a shared library; for a static library, add the STATIC keyword, e.g., add_library(add STATIC src/add.cpp)). Then, we need to link the library with the main module. Similar to including header files, CMake provides a unified method for handling both static and shared libraries, simplifying the process.

> There's another kind of "library," which only consists of header files. You can define it like this:
> ```cmake
> add_library(headerlib INTERFACE)
> target_include_directories(headerlib INTERFACE headerlib/include)
> ```

> Note the usage of PUBLIC, INTERFACE, and PRIVATE. In this case, add.h is used by main.cpp, so we use PUBLIC. Imagine removing #include <add/add.h> from add.cpp (since add.cpp defines the add function, it can be removed); then you can use INTERFACE or PUBLIC.

## V. Organizing Projects — Subdirectories
Sometimes, in larger projects, it's not a good idea to pile all your source files together. You may want to split your code into different folders based on functionality and compile each folder's content into a library that can be used by other parts of the project. However, when you have multiple modules, managing compilation operations for all of them in a single CMakeLists.txt file can become messy. A better approach is to add CMakeLists.txt files in subdirectories to manage their compilation operations and then consolidate all the subdirectories.

In CMake, adding subdirectories is as simple as using the add_subdirectory statement. To illustrate this, consider the following project structure:

```text
.
|-- add
|   |-- CMakeLists.txt
|   |-- include
|   |   `-- add
|   |       `-- add.h
|   `-- src
|       `-- add.cpp
|-- CMakeLists.txt
|-- fibo
|   |-- CMakeLists.txt
|   |-- include
|   |   `-- fibo
|   |       `-- fibo.h
|   `-- src
|       `-- fibo.cpp
`-- main.cpp
```

In this project, we've added a fibo module for computing Fibonacci numbers. This module uses the add module to perform addition. main.cpp now contains a loop to calculate Fibonacci numbers from 1 to 10 and display the results. The dependencies between modules are as follows:

```text
fibo -> add
main -> add
main -> fibo
```

We've added CMakeLists.txt files to both the add and fibo directories to manage the compilation operations within those directories. Below are the contents of the CMakeLists.txt file in the add directory:
```cmake
# add/CMakeLists.txt
add_library(add src/add.cpp)
target_include_directories(add PUBLIC include)
```

And here's the CMakeLists.txt file in the fibo directory:

```cmake
# fibo/CMakeLists.txt
add_library(fibo src/fibo.cpp)
target_include_directories(fibo INTERFACE include)
target_link_libraries(fibo PRIVATE add)
```

In the root directory's CMakeLists.txt, we use add_subdirectory to specify the paths of the add and fibo directories as subdirectories. CMake will execute the CMakeLists.txt files within those directories.

```cmake
cmake_minimum_required(VERSION 3.10)

project(main)

add_subdirectory(add)
add_subdirectory(fibo)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE add fibo)
```

> Once again, note the usage of PUBLIC, INTERFACE, and PRIVATE. Since the source code of fibo does not include fibo.h, we use INTERFACE. If you can imagine removing #include <fibo/fibo.h> from fibo.cpp (since fibo.cpp defines the fibonacci function, it can be removed), you would use INTERFACE or PUBLIC.

Using add_subdirectory, our project structure becomes much more organized!

## VI. Input/Output, Variables, and Flow Control
Sometimes, you might want to compile your project in different ways, such as choosing which modules to compile or whether to compile unit tests. Therefore, you need to input certain options during compilation. CMake provides the functionality for input, output, variables, and flow control, making it almost like a programming language. However, we won't dive too deeply into this topic in this article to keep it focused on practical usage.

> Input and output, variables, and flow control in CMake occur when you invoke the cmake command.

### Input/Output
In CMake, you can use the option command to set boolean parameters as input (you can also use set to set string parameters, but we won't cover that here). You can use the message command to output strings, and these strings can include parameters. Here's an example to illustrate their usage:
```cmake
cmake_minimum_required(VERSION 3.10)

project(io)

option(OPTION_VAR "this is help text" OFF)

message("the value of OPTION_VAR is ${OPTION_VAR}")
```

### Variables
Users can also set variables using the set command. The syntax is set(name "value"). Additionally, CMake provides some built-in variables such as the project name PROJECT_NAME, the project's root path CMAKE_SOURCE_DIR, the current path CMAKE_CURRENT_DIR, and more. Here's an example that demonstrates variable usage:

```cmake
cmake_minimum_required(VERSION 3.10)

project(variable)

set(USER_VAR "default")

message("the value of USER_VAR is ${USER_VAR}")

message("the name of project is ${PROJECT_NAME}")

message("the whole project's dir is ${CMAKE_SOURCE_DIR}")
```

Running this code should produce output similar to the following:
```text
the value of USER_VAR is default
the name of project is variable
the whole project's dir is /home/wokron/Code/Projects/practical-cmake/variable
```

With these built-in variables, you can simplify your CMakeLists.txt by using ${PROJECT_NAME} instead of specifying target names explicitly.

### Flow Control
With variables in place, it's natural to introduce conditional statements for comparisons in CMake. In this article, we'll only cover branching for simplicity. You can use if statements to control the flow of your CMakeLists.txt. Here's an example:

```cmake
cmake_minimum_required(VERSION 3.10)

project(controlflow)

option(OPTION_VAR "this is option" ON)

if(OPTION_VAR)
    message("OPTION_VAR is on")
else()
    message("OPTION_VAR is off")
endif()

set(STR_VAR "123")

if(STR_VAR MATCHES "123")
    message("is 123!")
elseif(STR_VAR MATCHES "456")
    message("is 456")
else()
    message("is other :(")
endif()
```
With parameters and branching, your project's compilation can become more flexible, accommodating complex scenarios.

### Handling Subdirectories
When you use add_subdirectory, what exactly happens in CMake? It's quite simple: CMake just goes into the subdirectory, executes the CMakeLists.txt file within it, and then returns to the original location. This behavior is similar to calling functions because the CMakeLists.txt file in the subdirectory may contain option definitions, and the CMakeLists.txt file in the parent directory can set the values of these options with the same names. This feature is useful when incorporating third-party libraries. The following two CMakeLists.txt examples demonstrate this:

```cmake
# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(subdirectory)

message("this is ${PROJECT_NAME}")

option(EXTERN_OPTION "" ON)
add_subdirectory(extern)
```

```cmake
# ./extern/CMakeLists.txt
cmake_minimum_required(VERSION 3.8)

project(extern_module)

option(EXTERN_OPTION "this is option in extern" OFF)

message("this is ${PROJECT_NAME}")

if(EXTERN_OPTION)
    message("will do something")
else()
    message("will do other things")
endif()
```

## VII. Testing
CMake provides a simple testing feature. To use it, you first need to enable testing in your project, which can be done by adding enable_testing() to your root CMakeLists.txt file:
```cmake
cmake_minimum_required(VERSION 3.10)

project(main)

enable_testing() # here!!!

add_subdirectory(add)
add_subdirectory(fibo)
add_subdirectory(test)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE add fibo)
```

Next, you'll need to create test executable files and use the add_test command to add them to your testing suite. In this article, we'll create a new directory to store our test files, but you can place them in other locations, such as within each module's directory. Here's the CMakeLists.txt file in the test directory:

```cmake
add_executable(test_add test_add.cpp)
target_link_libraries(test_add add)

add_executable(test_fibo test_fibo.cpp)
target_link_libraries(test_fibo fibo)

add_test(NAME test_add COMMAND test_add)
add_test(NAME test_fibo COMMAND test_fibo)
```

Below are the contents of the test files themselves, which are relatively simple:
```cpp
// test_add.cpp
#include "add/add.h"
#include <assert.h>

int main()
{
    assert(add(1, 2) == 3);
    assert(add(1, -1) == 0);
    assert(add(1, -2) == -1);
    assert(add(100, 100) == 200);
    return 0;
}
```
```cpp
// test_fibo.cpp
#include "fibo/fibo.h"
#include <assert.h>

int main()
{
    assert(fibonacci(1) == 1);
    assert(fibonacci(2) == 1);
    assert(fibonacci(3) == 2);
    assert(fibonacci(4) == 3);
    assert(fibonacci(5) == 5);
    assert(fibonacci(6) == 8);
    assert(fibonacci(7) == 13);
    assert(fibonacci(8) == 21);
    assert(fibonacci(9) == 34);
    assert(fibonacci(10) == 55);
    return 0;
}

```

Finally, in your build directory, execute the following commands:

```sh
cmake ..
make
make test
```

The output should indicate a successful test run:
```text
Test project /home/wokron/Code/Projects/practical-cmake/build/test
    Start 1: test_add
1/2 Test #1: test_add .........................   Passed    0.00 sec
    Start 2: test_fibo
2/2 Test #2: test_fibo ........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.00 sec
```

In the end, your project structure will look something like this:
```text
.
|-- add
|   |-- CMakeLists.txt
|   |-- include
|   |   `-- add
|   |       `-- add.h
|   `-- src
|       `-- add.cpp
|-- CMakeLists.txt
|-- fibo
|   |-- CMakeLists.txt
|   |-- include
|   |   `-- fibo
|   |       `-- fibo.h
|   `-- src
|       `-- fibo.cpp
|-- main.cpp
`-- test
    |-- CMakeLists.txt
    |-- test_add.cpp
    `-- test_fibo.cpp
```
