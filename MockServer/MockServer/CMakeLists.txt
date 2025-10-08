cmake_minimum_required(VERSION 3.19)
project(MockServer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools HttpServer)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup()

set(SRC_FILES src)
set(COMMON_FILES common)

set(HEADERS
    mockServer.h
    ${SRC_FILES}/httpServer.h
    ${COMMON_FILES}/mylog.h
)

set(UI_FILES
    mockServer.ui
)

set(SRC_FILES
    main.cpp
    mockServer.cpp
    ${SRC_FILES}/httpServer.cpp
)

qt_add_executable(MockServer
    ${SRC_FILES}
    ${HEADERS}
    ${UI_FILES}
    common/loadFileToByteArray.h
    image.qrc
    image.qrc
    video.qrc
    data.h data.cpp
    common/rand.cpp common/rand.h
)

target_include_directories(MockServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${COMMON_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_FILES}
)


target_link_libraries(MockServer
    PRIVATE
    Qt::Core
    Qt::Widgets
    Qt6::HttpServer
)


target_link_libraries(MockServer PRIVATE Qt6::Core)
target_link_libraries(MockServer PRIVATE Qt6::Core)


include(GNUInstallDirs)

install(TARGETS MockServer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MockServer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)


install(SCRIPT ${deploy_script})
