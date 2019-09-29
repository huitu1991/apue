
# 添加子目录
ADD_SUBDIRECTORY(simple)

# 复制read_text到目标二进制目录
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/resource/read_text
        ${CMAKE_CURRENT_BINARY_DIR}/resource/read_text
        COPYONLY)