add_executable(real_time_light_cuts_cpu
	real_time_light_cuts_cpu.cpp
	colors.cpp
 "include/LightCut.h" "include/UBO.h" "include/morton_code_gen.h" )

target_include_directories(real_time_light_cuts_cpu PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(real_time_light_cuts_cpu PUBLIC
	glm::glm
)

if (MSVC) 
  target_link_options(real_time_light_cuts_cpu PRIVATE $<$<CONFIG:RELWITHDEBINFO>:/PROFILE>)
endif()

set_property(TARGET real_time_light_cuts_cpu PROPERTY CXX_STANDARD 20)
