add_executable(KMPTest kmp_test.cpp)
target_link_libraries(KMPTest gtest_main)
gtest_discover_tests(KMPTest)

add_executable(ManacherTest manacher_test.cpp)
target_link_libraries(ManacherTest gtest_main)
gtest_discover_tests(ManacherTest)

add_executable(ZAlgorithmTest z_algorithm_test.cpp)
target_link_libraries(ZAlgorithmTest gtest_main)
gtest_discover_tests(ZAlgorithmTest)
