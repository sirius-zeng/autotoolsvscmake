cmake_minimum_required(VERSION 3.16.3)

project(StockPrice VERSION 1.0)

# Use set command to define the C preprocessor macro
#option(PRINT_NEGATIVE "Print the negative price table" ON)
#if (PRINT_NEGATIVE)
#    set(PRINT_NEGATIVE_TABLE 1)
#endif(PRINT_NEGATIVE)

# Use option command directly to define the C preprocessor macro
option(PRINT_NEGATIVE_TABLE "Print the negative price table" ON)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(stockprice main.cc)

install(TARGETS stockprice RUNTIME DESTINATION bin)

configure_file(config.h.in config.h)

add_subdirectory(PriceTable)

target_link_libraries(stockprice PUBLIC pricetable)


target_include_directories(pricetable PUBLIC
                        ${PROJECT_BINARY_DIR}
                        ${PROJECT_SOURCE_DIR}/PriceTable)

#include_directories(${PROJECT_BINARY_DIR})






