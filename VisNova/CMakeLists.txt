cmake_minimum_required(VERSION 3.19)
project(VisNova LANGUAGES CXX)

# ==================== 依赖查找 ====================
find_package(Qt6
    REQUIRED
    COMPONENTS
    Core
    Widgets
    LinguistTools
    Multimedia
    MultimediaWidgets
)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)


qt_standard_project_setup()

include_directories(
    ${PROJECT_SOURCE_DIR}
)

set(START_PAGE_DIR startPage)
set(COMPONENT_DIR component)
set(STYLE_DIR style)
set(COMMON_DIR common)
set(LRPAGR_DIR lrPage)
set(MPV_DIR mpv)

set(SOURCES
    main.cpp
    vidNovaMain.cpp
    ${START_PAGE_DIR}/startPage.cpp
    ${COMPONENT_DIR}/pageSwitchBtn.cpp
    ${COMPONENT_DIR}/homePageCpt.cpp
    ${COMPONENT_DIR}/searchLineEdit.cpp
    ${COMPONENT_DIR}/playerPage.cpp
    ${COMPONENT_DIR}/playerSlider.cpp
    ${COMPONENT_DIR}/volume.cpp
    ${COMPONENT_DIR}/playSpeed.cpp
    ${COMPONENT_DIR}/bulletEdit.cpp
    ${COMPONENT_DIR}/myPage.cpp
    ${COMPONENT_DIR}/myPageAvatarBtn.cpp
    ${COMPONENT_DIR}/modifySelfInfo.cpp
    ${COMPONENT_DIR}/uploadVideoPage.cpp
    ${COMPONENT_DIR}/modifyPd.cpp
    ${COMPONENT_DIR}/videoBox.cpp
    ${COMPONENT_DIR}/adminPage.cpp
    ${COMPONENT_DIR}/rolePageForAp.cpp
    ${COMPONENT_DIR}/checkPageForAp.cpp
    ${COMPONENT_DIR}/checkPageItem.cpp
    ${COMPONENT_DIR}/rolePageItem.cpp
    ${COMPONENT_DIR}/editUserForAp.cpp
    ${COMPONENT_DIR}/pageBtn.cpp
    ${COMPONENT_DIR}/paginator.cpp
    ${COMPONENT_DIR}/toast.cpp
    ${COMPONENT_DIR}/mpvPlayer.cpp
    ${LRPAGR_DIR}/login.cpp

)

set(HEADERS
    vidNovaMain.h
    ${START_PAGE_DIR}/startPage.h
    ${COMPONENT_DIR}/pageSwitchBtn.h
    ${COMPONENT_DIR}/homePageCpt.h
    ${COMPONENT_DIR}/searchLineEdit.h
    ${COMPONENT_DIR}/playerPage.h
    ${COMPONENT_DIR}/playerSlider.h
    ${COMPONENT_DIR}/volume.h
    ${COMPONENT_DIR}/playSpeed.h
    ${STYLE_DIR}/style.h
    ${COMMON_DIR}/myLog.h
    ${COMMON_DIR}/readLocalFile.h
    ${COMPONENT_DIR}/bulletEdit.h
    ${COMPONENT_DIR}/myPage.h
    ${COMPONENT_DIR}/myPageAvatarBtn.h
    ${COMPONENT_DIR}/modifySelfInfo.h
    ${COMPONENT_DIR}/modifyPd.h
    ${COMPONENT_DIR}/uploadVideoPage.h
    ${COMPONENT_DIR}/videoBox.h
    ${COMPONENT_DIR}/adminPage.h
    ${COMPONENT_DIR}/checkPageForAp.h
    ${COMPONENT_DIR}/rolePageForAp.h
    ${COMPONENT_DIR}/checkPageItem.h
    ${COMPONENT_DIR}/rolePageItem.h
    ${COMPONENT_DIR}/editUserForAp.h
    ${COMPONENT_DIR}/pageBtn.h
    ${COMPONENT_DIR}/paginator.h
    ${COMPONENT_DIR}/toast.h
    ${COMPONENT_DIR}/mpvPlayer.h
    ${LRPAGR_DIR}/login.h
    ${MPV_DIR}/client.h
    ${MPV_DIR}/render.h
    ${MPV_DIR}/render_gl.h
    ${MPV_DIR}/stream_cb.h
)

set(UI_FILES
    vidnovamain.ui
    ${COMPONENT_DIR}/homePageCpt.ui
    ${COMPONENT_DIR}/videoBox.ui
    ${COMPONENT_DIR}/playerPage.ui
    ${COMPONENT_DIR}/playerSlider.ui
    ${COMPONENT_DIR}/volume.ui
    ${COMPONENT_DIR}/playSpeed.ui
    ${COMPONENT_DIR}/bulletEdit.ui
    ${COMPONENT_DIR}/myPage.ui
    ${COMPONENT_DIR}/modifySelfInfo.ui
    ${COMPONENT_DIR}/uploadVideoPage.ui
    ${COMPONENT_DIR}/modifyPd.ui
    ${COMPONENT_DIR}/adminPage.ui
    ${COMPONENT_DIR}/rolePageForAp.ui
    ${COMPONENT_DIR}/checkPageForAp.ui
    ${COMPONENT_DIR}/checkPageItem.ui
    ${COMPONENT_DIR}/rolePageItem.ui
    ${COMPONENT_DIR}/editUserForAp.ui
    ${LRPAGR_DIR}/login.ui
)

# 资源文件
qt_add_resources(RESOURCES imageRsc.qrc)

# ==================== 可执行文件创建 ====================
qt_add_executable(VisNova
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    common/constants.h
    component/bulletItem.h component/bulletItem.cpp
    component/bulletManage.h component/bulletManage.cpp
)

target_sources(VisNova PRIVATE ${RESOURCES})

# ==================== 包含目录设置 ====================
target_include_directories(VisNova PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${START_PAGE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${COMPONENT_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${STYLE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${COMMON_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${LRPAGR_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${MPV_DIR}
)



# ==================== 库链接 ====================
target_link_libraries(VisNova PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    ${CMAKE_CURRENT_SOURCE_DIR}/${MPV_DIR}/libmpv.dll.a
)
target_link_libraries(VisNova PRIVATE Qt6::Core)
target_link_libraries(VisNova PRIVATE Qt6::Widgets)
target_link_libraries(VisNova PRIVATE Qt6::Core)


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
