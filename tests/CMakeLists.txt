enable_testing()

function(SETUP_TESTS)
    foreach(_testname ${ARGN})
        add_executable(${_testname} tst_${_testname}.cpp)
        add_test(NAME ${_testname} COMMAND ${_testname})
        target_include_directories(${_testname} PUBLIC ../include)
        target_link_libraries(${_testname} PRIVATE
            Qt${QT_MAJOR_VERSION}::Test
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Multimedia
        )
    endforeach()
endfunction()

SETUP_TESTS(
    logic direction score snake
)
