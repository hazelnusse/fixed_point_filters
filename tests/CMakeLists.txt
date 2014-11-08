include_directories(${GTEST_INCLUDE_DIRS}
                    ${EMBEDDED_FILTER_SOURCE_DIR})

add_executable(test_fir
    test_fir.cc
    ${EMBEDDED_FILTER_SOURCE_DIR}/fixed_point_fir.h)
target_link_libraries(test_fir ${GTEST_BOTH_LIBRARIES})
add_test(TestFIR test_fir)

add_executable(test_iir
    test_iir.cc
    ${EMBEDDED_FILTER_SOURCE_DIR}/fixed_point_iir.h)
target_link_libraries(test_iir ${GTEST_BOTH_LIBRARIES})
add_test(TestIIR test_iir)

