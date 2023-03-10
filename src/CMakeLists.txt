set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Network Widgets REQUIRED)

configure_file("git_sha1.cc.in" "git_sha1.cc" @ONLY)

add_executable(mesydaq2
    "${CMAKE_CURRENT_BINARY_DIR}/git_sha1.cc"
    controlinterface.cpp
    datacruncher.cpp
    histogram.cpp
    main.cpp
    mainwidget.cpp
    mainwidget.ui
    mcpd8.cpp
    measurement.cpp
    mesydaq2.cpp
    mpsd8.cpp
    networkdevice.cpp
    structures.cpp
)

target_compile_features(mesydaq2 PRIVATE cxx_std_17)
# Less noise while trying to get things to work.
target_compile_options(mesydaq2 PRIVATE "-Wno-deprecated-declarations")

target_link_libraries(mesydaq2 PRIVATE
    Qt5::Network
    Qt5::Widgets
)

if (WIN32)
    target_link_libraries(mesydaq2 PRIVATE ws2_32)
    #target_link_libraries(mesydaq2 PRIVATE ws2_32 winmm)
endif(WIN32)

install(TARGETS mesydaq2 RUNTIME DESTINATION bin LIBRARY DESTINATION lib)
