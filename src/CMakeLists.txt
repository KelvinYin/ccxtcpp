# 查找 src 目录下的所有源文件
file(GLOB INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/websocket_client/*.h)
file(GLOB LIB_INC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ./websocket_client/ws_callback.h
    ./websocket_client/ws_client.h)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/websocket_client/*.cpp)

# 生成静态库
add_library(ccxtcpp_static STATIC ${INC_FILES} ${SRC_FILES})

# 生成动态库
add_library(ccxtcpp_dynamic SHARED ${INC_FILES} ${SRC_FILES})

set (LIBS curl jsoncpp websockets cpr)

# 链接 库
target_link_libraries(ccxtcpp_static ${LIBS})
target_link_libraries(ccxtcpp_dynamic ${LIBS})

# 拷贝头文件
file(COPY ${LIB_INC_FILES} DESTINATION ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})
