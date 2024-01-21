cmake_minimum_required(VERSION 3.10)

project(majsa_project)

# 添加源文件
file(GLOB SOURCES "src/*.c")

# 添加包含目录
include_directories(.)

# 生成可执行文件
add_executable(majsa ${SOURCES})

# 添加自定义目标和命令
add_custom_target(git_commit
    COMMAND git add -A
    COMMAND git commit --allow-empty -m "compile"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}  # 设置工作目录为项目根目录
    COMMENT "Git commit during build"
)

# 将 git_commit 添加到构建过程的依赖中
add_dependencies(majsa git_commit)