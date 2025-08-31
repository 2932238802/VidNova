cmake_minimum_required(VERSION 3.19)
project(VisNova LANGUAGES CXX)

# ==================== 依赖查找 ====================
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)


qt_standard_project_setup()

include_directories(
    ${PROJECT_SOURCE_DIR}
)



# ==================== 目录和文件定义 ====================
set(START_PAGE_DIR startPage)
set(COMPONENT_DIR component)
set(STYLE_DIR style)
set(COMMON_DIR common)


set(SOURCES
    main.cpp
    vidNovaMain.cpp
    ${START_PAGE_DIR}/startPage.cpp
    ${COMPONENT_DIR}/pageSwitchBtn.cpp
    ${COMPONENT_DIR}/homePageCpt.cpp
    ${COMPONENT_DIR}/searchLineEdit.cpp

)

set(HEADERS
    vidNovaMain.h
    ${START_PAGE_DIR}/startPage.h
    ${COMPONENT_DIR}/pageSwitchBtn.h
    ${COMPONENT_DIR}/homePageCpt.h
    ${COMPONENT_DIR}/searchLineEdit.h

    ${STYLE_DIR}/btnStyle.h
    ${COMMON_DIR}/myLog.h
)

set(UI_FILES
    vidnovamain.ui
    ${COMPONENT_DIR}/homePageCpt.ui
)

# 资源文件
qt_add_resources(RESOURCES imageRsc.qrc)

# ==================== 可执行文件创建 ====================
qt_add_executable(VisNova
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    component/vedioBox.h component/vedioBox.cpp component/vedioBox.ui
    component/playerPage.h component/playerPage.cpp component/playerPage.ui


)



target_sources(VisNova PRIVATE ${RESOURCES})

# ==================== 包含目录设置 ====================
target_include_directories(VisNova PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${START_PAGE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${COMPONENT_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${STYLE_DIR}
)

# ==================== 国际化支持 ====================
qt_add_translations(VisNova
    TS_FILES VisNova_zh_CN.ts
)

# ==================== 库链接 ====================
target_link_libraries(VisNova PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(VisNova PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(VisNova PRIVATE Qt6::Core Qt6::Widgets)

# ==================== 安装配置 ====================
include(GNUInstallDirs)

install(TARGETS VisNova
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ==================== 部署脚本 ====================
qt_generate_deploy_app_script(
    TARGET VisNova
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
