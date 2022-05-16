add_executable(ereolenwrapperctests 
test_runners/all_tests.c
TestProductionCode.c 
TestProductionCode2.c 
test_runners/TestProductionCode_Runner.c 
test_runners/TestProductionCode2_Runner.c 
)

#target_sources(test_meh_app PRIVATE

#)

target_link_libraries(ereolenwrapperctests release unity::framework)
add_test(test_meh ereolenwrapperctests)