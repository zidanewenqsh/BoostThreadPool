cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
# 设置项目名称
project(multithreading)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 设置Boost库的根目录（应指向 Boost 的安装根目录）
set(BOOST_ROOT "D:/MySoft/boost_1_85_0")

# 禁用搜索系统路径
set(Boost_NO_SYSTEM_PATHS ON) # 非常重要，否则会导致找不到 Boost 库

# 查找Boost库，指定需要的组件
# find_package(Boost REQUIRED COMPONENTS filesystem regex)
find_package(Boost REQUIRED)

# 输出 Boost 的相关信息
message("Boost version: ${Boost_VERSION}")
message("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message("Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message("Boost_LIBRARIES: ${Boost_LIBRARIES}")

# 包含Boost头文件目录
include_directories(${Boost_INCLUDE_DIRS})

# 链接Boost库目录
link_directories(${Boost_LIBRARY_DIRS})

include_directories(include)
link_directories(lib)

add_library(ThreadPool SHARED ThreadPool.cpp ThreadPool.h)
add_executable(multithreading main.cpp)
target_link_libraries(multithreading ThreadPool ${Boost_LIBRARIES})

# 对Windows进行特定配置
if(WIN32)
  # 定义宏，通常用于导出DLL符号
  target_compile_definitions(ThreadPool PRIVATE THREADPOOL_EXPORTS)
endif()

# 添加依赖库