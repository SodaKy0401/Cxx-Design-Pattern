cmake_minimum_required(VERSION 3.10)
project(MultiExecFromSubdirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 src 目录下所有的 .cpp 文件（递归子目录）
file(GLOB_RECURSE CPP_FILES "src/*.cpp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# 引入 pthread 库
find_package(Threads REQUIRED)

# 为每个 cpp 文件创建一个可执行文件，并链接 pthread
foreach(FILE_PATH ${CPP_FILES})
    # 获取不带路径和扩展名的文件名，如 main1
    get_filename_component(EXE_NAME ${FILE_PATH} NAME_WE)

    # 添加可执行文件目标
    add_executable(${EXE_NAME} ${FILE_PATH})

    # 链接 pthread 库
    target_link_libraries(${EXE_NAME} PRIVATE Threads::Threads)
endforeach()
