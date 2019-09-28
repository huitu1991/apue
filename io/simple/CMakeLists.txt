


add_executable(io-simple simple.cc)

# 复制read_text到目标二进制目录
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/read_text
        ${CMAKE_CURRENT_BINARY_DIR}/read_text
        COPYONLY)