cmake_minimum_required(VERSION 3.16)

project(SCUSportQuery VERSION 0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appSCUSportQuery
    main.cpp
)

set(ANDROID_SOURCES
    android/AndroidManifest.xml
    android/build.gradle
    android/res/values/libs.xml
    android/res/xml/qtprovider_paths.xml
    android/gradle/wrapper/gradle-wrapper.jar
    android/gradle/wrapper/gradle-wrapper.properties
    android/gradle.properties
    android/gradlew
    android/gradlew.bat
)

qt_add_qml_module(appSCUSportQuery
    URI SCUSportQuery
    VERSION 0.3
    QML_FILES
        Main.qml
        SOURCES SportQueryDBRead.h SportQueryDBRead.cpp
        RESOURCES
        SOURCES SportQuestion.h SportQuestion.cpp
        SOURCES SportQuestionListModel.h SportQuestionListModel.cpp
        RESOURCES ${ANDROID_SOURCES}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSCUSportQuery PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSCUSportQuery
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSCUSportQuery
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appSCUSportQuery
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(ANDROID)
    set(ANDROID_VERSION_NAME "0.3")
    set(ANDROID_VERSION_CODE 3)

    # 添加Android资源文件
    set(QT_ANDROID_PACKAGE_SOURCE_DIR android)

    # 构建前将question.db复制到android/assets目录
    add_custom_command(TARGET appSCUSportQuery PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/question.db
        ${CMAKE_BINARY_DIR}/android-build-appSCUSportQuery/assets/question.db
    )
else()
    # 构建后将question.db复制到构建目录的data目录
    add_custom_command(TARGET appSCUSportQuery POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/question.db
        ${CMAKE_BINARY_DIR}/data/question.db
    )
endif()
