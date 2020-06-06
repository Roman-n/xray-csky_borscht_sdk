cmake_minimum_required(VERSION 3.15)
project(luabind LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DLUABIND_BUILDING)
target_include_directories(${PROJECT_NAME} PUBLIC
	"../luajit/src"
	"include")
target_sources(${PROJECT_NAME} PRIVATE
	luabind_memory.cpp
	src/class.cpp
	src/class_info.cpp
	src/class_registry.cpp
	src/class_rep.cpp
	src/create_class.cpp
	src/error.cpp
	src/find_best_match.cpp
	src/function.cpp
	src/implicit_cast.cpp
	src/link_compatibility.cpp
	src/object.cpp
	src/object_rep.cpp
	src/open.cpp
	src/pcall.cpp
	src/ref.cpp
	src/scope.cpp
	src/stack_content_by_name.cpp
	src/weak_ref.cpp
	src/wrapper_base.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE imdexlib lua51.lib)
