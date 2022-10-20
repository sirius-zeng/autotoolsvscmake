# Autotools vs CMake (Basic Usage)
- [Autotools vs CMake (Basic Usage)](#autotools-vs-cmake-basic-usage)
  - [1. Workflows](#1-workflows)
    - [1.1 Autotools workflows](#11-autotools-workflows)
    - [1.2 CMake workflows](#12-cmake-workflows)
    - [1.3 Both preojects need input files written by developer](#13-both-preojects-need-input-files-written-by-developer)
  - [2. Source Tree Structure](#2-source-tree-structure)
    - [2.2 Autotools project source tree structure](#22-autotools-project-source-tree-structure)
    - [2.2 CMake project source tree structure](#22-cmake-project-source-tree-structure)
    - [2.3 Common source files in both project](#23-common-source-files-in-both-project)
    - [2.4 Build system related files in autotool project](#24-build-system-related-files-in-autotool-project)
    - [2.5 Build system related files in cmake project](#25-build-system-related-files-in-cmake-project)
  - [3. Basic features](#3-basic-features)
    - [3.1 Project or Package definitions](#31-project-or-package-definitions)
      - [3.1.1 Autotools](#311-autotools)
      - [3.1.2 CMake](#312-cmake)
    - [3.2 Project `config.h` file](#32-project-configh-file)
      - [3.2.1 Autotools](#321-autotools)
      - [3.2.2 CMake](#322-cmake)
    - [3.3 Executable target](#33-executable-target)
      - [3.3.1 Autotools](#331-autotools)
      - [3.3.2 CMake](#332-cmake)
    - [3.4 Include header files](#34-include-header-files)
      - [3.4.1 Autotools](#341-autotools)
      - [3.4.2 CMake](#342-cmake)
    - [3.5 Build options](#35-build-options)
      - [3.5.1 Autotools](#351-autotools)
      - [3.5.2 CMake](#352-cmake)
    - [3.6 Add C/C++ preprocessor macro definitions into config.h](#36-add-cc-preprocessor-macro-definitions-into-configh)
      - [3.6.1 Autotools](#361-autotools)
      - [3.6.2 CMake](#362-cmake)
    - [3.7 Makefiles in subdir](#37-makefiles-in-subdir)
      - [3.7.1 Autotools](#371-autotools)
        - [3.7.1.1 Recursive mode build](#3711-recursive-mode-build)
        - [3.7.1.2 None-recursive mode build](#3712-none-recursive-mode-build)
      - [3.7.2 CMake](#372-cmake)
    - [3.8 Library target](#38-library-target)
      - [3.8.1 Autotools](#381-autotools)
        - [3.8.1.1 Without libtool](#3811-without-libtool)
        - [3.8.1.2 With libtool](#3812-with-libtool)
      - [3.8.2 CMake](#382-cmake)
    - [3.9 Debug build and release build](#39-debug-build-and-release-build)
      - [3.9.1 Autotools](#391-autotools)
      - [3.9.2 CMake](#392-cmake)
    - [3.10 Install target](#310-install-target)
      - [3.10.1 Autotools](#3101-autotools)
      - [3.10.2 CMake](#3102-cmake)


## 1. Workflows
### 1.1 Autotools workflows
![](pics/autotools_workflow.png)

### 1.2 CMake workflows
![](pics/cmake_workflow.png)

### 1.3 Both preojects need input files written by developer
Autotools project need the following input files:
- configure.ac
- Makefile.am
- config.h.in ( Autotool will generate it automatically based on the configure.ac settings.)

CMake project needs the following input files:
- CMakeLists.txt
- config.h.in

For autotool project, the basic build flow is:
- step1: `autoreconf -i`
- step2: `configure`
- step3: `make`

For cmake project, the basic build flow is:
- step1: `mkdir build && cd build`
- step2: `cmake ../`
- step3: `make`

For both projects the final ouput files after the configuration will be:
- Makefile
- config.h


## 2. Source Tree Structure

### 2.2 Autotools project source tree structure
```
pricetable_autotool/
├── configure.ac
├── main.cc
├── Makefile.am
└── PriceTable
    ├── Makefile.am
    ├── PriceTable.cc
    └── PriceTable.h
```

### 2.2 CMake project source tree structure
```
pricetable_cmake
├── CMakeLists.txt
├── config.h.in
├── main.cc
└── PriceTable
    ├── CMakeLists.txt
    ├── PriceTable.cc
    └── PriceTable.h
```

### 2.3 Common source files in both project
```
pricetable_xxx
├── config.h.in
├── main.cc
└── PriceTable
    ├── PriceTable.cc
    └── PriceTable.h
```

### 2.4 Build system related files in autotool project
```
pricetable_autotool/
├── configure.ac
├── Makefile.am
└── PriceTable
    ├── Makefile.am
```
**Note:** Don't need config.h.in because autotool will generate it directly based on the configure.ac settings. 

### 2.5 Build system related files in cmake project

```
pricetable_cmake
├── CMakeLists.txt
├── config.h.in
└── PriceTable
    ├── CMakeLists.txt
```
## 3. Basic features
### 3.1 Project or Package definitions
The project or package definition should lie in the top level build configuration file. 

#### 3.1.1 Autotools
For autotools project, it is in `configure.ac`:
```
AC_INIT([StockPrice], [1.0])
```

#### 3.1.2 CMake
For cmake project, it is in the top level `CMakeLists.txt`:
```
project(StockPrice VERSION 1.0)
```

### 3.2 Project `config.h` file
#### 3.2.1 Autotools
For autotools project, it will generate the `config.h.in` file direclty based on the setting of `configure.ac` when user runs `autoreconf` command. Then it generates the `config.h` file after user runs the `configure` command.

The setting in `configure.ac` is as following:
```
AC_CONFIG_HEADERS([config.h])
```  

#### 3.2.2 CMake
For CMake project, user will supply the `config.h.in` file, and cmake will generated the `config.h` file based on the setting of `CMakeLists.txt`. 

The setting in `CMakeLists.txt` is as following:
```
configure_file(config.h.in config.h)
```

### 3.3 Executable target
#### 3.3.1 Autotools
For autotools project, the executable target is defined by the product list variable in `Makefile.am`:
```
bin_PROGRAMS = stockprice
stockprice_SOURCES = main.cc 
```

#### 3.3.2 CMake
For CMake project, the executable target is defined by `add_executable` command in `CMakeLists.txt`:
```
add_executable(stockprice main.cc)
```

### 3.4 Include header files
#### 3.4.1 Autotools
For autotools project, the include path is defined by the `product_CPPFLAGS` variable in Makefile.am as following:
```
stockprice_CPPFLAGS = -I$(top_srcdir)/PriceTable
```
#### 3.4.2 CMake
FOr automake project, the include path can be defined by `target_include_directories` command or `include_directories` command:
```
target_include_directories(pricetable PUBLIC
                        ${PROJECT_BINARY_DIR}
                        ${PROJECT_SOURCE_DIR}/PriceTable)

#include_directories(${PROJECT_BINARY_DIR})
```

### 3.5 Build options
#### 3.5.1 Autotools
For autotools project, use `AC_ARG_ENABLE` command to define the configration option:
```
AC_ARG_ENABLE([fulltable],
	[AS_HELP_STRING([--enable-fulltable], [Enable print the negative price table])])
```
User can use `--enable-fulltable` or `--disable-fulltable` option when run the `configure command`:
```
configure --enable-fulltable  
```
or
```
configure --disable-fulltable
```

#### 3.5.2 CMake
For CMake project, the similar command is `option`. The option value will be saved in cmake cach, also a C/C++ preprocessor macro will be added into `config.h`. 
```
option(PRINT_NEGATIVE_TABLE "Print the negative price table" ON)
```

User can change the value of the option when run `cmake` command:
```
cmake ../ -DPRINT_NEGATIVE_TABLE=ON
```

For cmake project, you can find the macro definition in the generated `config.h` file:
```
//Use option command directly to define the C preprocessor macro
#define PRINT_NEGATIVE_TABLE ON
```

### 3.6 Add C/C++ preprocessor macro definitions into config.h
#### 3.6.1 Autotools
For autotools project, use `AC_DEFINE` command in `configure.ac` file to add user defined macro into config.h:
```
if test "${enable_fulltable}" = "yes" ; then
   AC_DEFINE([PRINT_NEGATIVE_TABLE], [1], [Print the values in negative table])
fi
``` 

#### 3.6.2 CMake
For CMake project, there have two methods to add user defined macro into config.h. One method is by the `option` command in `CMakeLists.txt` described upper. The other method is by `set` command in `CMakeLists.txt`:
```
# Use set command to define the C preprocessor macro
#option(PRINT_NEGATIVE "Print the negative price table" ON)
#if (PRINT_NEGATIVE)
#    set(PRINT_NEGATIVE_TABLE 1)
#endif(PRINT_NEGATIVE)

# Use option command directly to define the C preprocessor macro
option(PRINT_NEGATIVE_TABLE "Print the negative price table" ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
```

For CMake project, user must edit `config.h.in` file manually:
```
//Use set command to define the C preprocessor macro
//#cmakedefine PRINT_NEGATIVE_TABLE @PRINT_NEGATIVE_TABLE@
//#cmakedefine PRINT_NEGATIVE @PRINT_NEGATIVE@

//Use option command directly to define the C preprocessor macro
#cmakedefine PRINT_NEGATIVE_TABLE @PRINT_NEGATIVE_TABLE@
```
### 3.7 Makefiles in subdir
#### 3.7.1 Autotools
For autotools project, there have two build modes which can involve the `Makefile.am` under subdirecotries. They are `recursive` mode and `non-recursive` mode. 

##### 3.7.1.1 Recursive mode build
For `recursive` mode, user should update both `configure.ac` and high level `Makefile.am`. In `configure.ac`, user should add the Makefile.am in subdir into the configuration file list:
```
# Automake - recursive make mode 
AM_INIT_AUTOMAKE([foreign 1.16])
AC_CONFIG_FILES([Makefile PriceTable/Makefile])
```
Then in high level `Makefile.am`, use the `SUBDIRS` command to include the `Makefile.am` in subdir:
```
# Automake - recursive make mode
SUBDIRS = PriceTable
``` 

##### 3.7.1.2 None-recursive mode build
For `non-recursive` mode, user should add `subdir-objects` option to `AM_INIT_AUTOMAKE` command, so that it can include the files in subdir:
```
# Automake - non-recursive make mode
AM_INIT_AUTOMAKE([foreign 1.16 subdir-objects])
AC_CONFIG_FILES([Makefile])
```
Then in the high level `Makefile.am`, use the `include` command to include the `Makefile.am` in subdir:
```
# Automake - non-recursive make mode
include $(top_srcdir)/PriceTable/Makefile.am
```
For autotools project, the `recursive` mode is harmful and `none-recursive` mode is preferred. 


#### 3.7.2 CMake
For CMake project, it is simple, only need the `add_subdirectory` command in `CMakeLists.txt:
```
add_subdirectory(PriceTable)
```

### 3.8 Library target
#### 3.8.1 Autotools
##### 3.8.1.1 Without libtool
Without libtool, we can use `PRODUCT_LIBRARIES` variable to add static library in `Makefile.am`. The following is the example to add one static libray as the target in the Makefile.am of subdirectory:
```
# Without libtool -- static library
lib_LIBRARIES = %reldir%/libpricetable.a
%canon_reldir%_libpricetable_a_SOURCES =  %reldir%/PriceTable.cc
```

To use the static library, use `PRODUCT_LDADD` variable:
```
# Without libtool -- static library
stockprice_LDADD = $(top_builddir)/PriceTable/libpricetable.a
```

##### 3.8.1.2 With libtool
With libtool, we can support both static and shared library in our project easily. 
To enable libtool support, we should add the following lines into `configure.ac`:
```
LT_PREREQ([2.4])
LT_INIT
```

Then we can use `PRODUCT_LTLIBRARIES` variable to add the libtool format library as following in `Makefile.am`: 
```
# libtool 
lib_LTLIBRARIES =  %reldir%/libpricetable.la
%canon_reldir%_libpricetable_la_SOURCES =  %reldir%/PriceTable.cc
%canon_reldir%_libpricetable_la_LDFLAGS = -version-info 0:0:0
```

To use the libtool format library, we can still use the `PRODUCT_LDADD` variable:
```
# With libtool
stockprice_LDADD = $(top_builddir)/PriceTable/libpricetable.la
```

With libtool support, it can generate both static and shared library at the same time. The real libraries and the executable files are in a hidden folder named `.libs`. We can use configuration option `--enable-shared` and `--enable-static` to control whether we will generate the shared library or static library. 

It takes trouble to debug the executable program with libtool shared library. Because the generated executable program is in fact a wrapped shell script file, so that we can's use GDB directly. One simple way I used is to disable the shared library by `--disable-shared` option when run `configure` command. Then I can use GDB to debug the program as normal. It's useful in the IDE which know nothing about the libtool. 
```
configure --disable-shared
make
```

#### 3.8.2 CMake
It's simple to use library with CMake. You can use `add_library` command to add static or shared library into the project. 
```
add_library(pricetable STATIC PriceTable.cc)
```
or
```
add_library(pricetable SHARED PriceTable.cc)
```

In our example, we use `add_library(pricetable PriceTable.cc)` without library type, then the library type is decided by `BUILD_SHARED_LIBS` option. We set the default value of this option in top level CMakeLists.txt. 
```
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
```

We can change the value in `cmake` command line:
```
cmake ../ -DBUILD_SHARED_LIBS=OFF
```

### 3.9 Debug build and release build
#### 3.9.1 Autotools
User have to change the `CFLAGS` or `CCFLAGS` manually to decide the build type. 

#### 3.9.2 CMake
It is simple, `CMAKE_BUILD_TYPE` variable will be use to control the build type. You can use it in cmake command line:
```
cmake -DCMAKE_BUILD_TYPE=Debug.
```
or
```
cmake -DCMAKE_BUILD_TYPE=Release .
```
### 3.10 Install target
#### 3.10.1 Autotools
It will install all of the thing in production list. 

Use `--prefix` option of `configure` to configure the default install location:
```
./configure --prefix=/home/vince/usr
```

Use `DESTDIR` of `make` to diverting the installation to a differerent location:
```
$ make
$ make DESTDIR=/home/vince/target-rootfs/ install
```

#### 3.10.2 CMake
Use `install` command to specify the target to be installed:
```
// CMakeLists.txt
install(TARGETS stockprice RUNTIME DESTINATION bin)
```

```
// PriceTable/CMakeLists.txt
install(TARGETS pricetable LIBRARY DESTINATION lib)
```

Use `CMAKE_INSTALL_PREFIX` to configure the default install location:
```
cmake -DCMAKE_INSTALL_PREFIX=/home/vince/user .
```

Use `DESTDIR` of `make` to diverting the installation to a differerent location:
```
$ make
$ make DESTDIR=/home/vince/target-rootfs/ install
```

About shared library, it will remove the `RUNPATH` infomation when run `make install` command:
```
vince@vince-Virtulbox-test:~/my_workspace/pricetable_cmake/build$ make install
[ 50%] Built target pricetable
[100%] Built target stockprice
Install the project...
-- Install configuration: ""
-- Installing: /home/vince/my_workspace/pricetable_cmake/install_local/bin/stockprice
-- Set runtime path of "/home/vince/my_workspace/pricetable_cmake/install_local/bin/stockprice" to ""
-- Installing: /home/vince/my_workspace/pricetable_cmake/install_local/lib/libpricetable.so
```

If you want to install the shared library together with the executable, you can change the `RUNPATH` by `CMAKE_INSTALL_RPATH` variable and `CMAKE_INSTALL_RPATH_USE_LINK_PATH` variable as following, so that it can always find the library. You should call these command before you create the executable target.
```
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(stockprice main.cc)
```

Then check the log output of `make install` command:
```
vince@vince-Virtulbox-test:~/my_workspace/pricetable_cmake/build$ make install
[ 50%] Built target pricetable
[100%] Built target stockprice
Install the project...
-- Install configuration: ""
-- Installing: /home/vince/my_workspace/pricetable_cmake/install_local/bin/stockprice
-- Set runtime path of "/home/vince/my_workspace/pricetable_cmake/install_local/bin/stockprice" to "/home/vince/my_workspace/pricetable_cmake/install_local/lib"
-- Installing: /home/vince/my_workspace/pricetable_cmake/install_local/lib/libpricetable.so
-- Set runtime path of "/home/vince/my_workspace/pricetable_cmake/install_local/lib/libpricetable.so" to "/home/vince/my_workspace/pricetable_cmake/install_local/lib"
```






