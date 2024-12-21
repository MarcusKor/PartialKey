# CMakeList.txt: PartialKey 에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required(VERSION 3.8)

# 지원되는 경우 MSVC 컴파일러에 대해 핫 다시 로드 사용하도록 설정합니다.
if(POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
	endif()
endif()

if(MSVC)
	if(MSVC_VERSION GREATER 1900)
		if (${use_control_flow_guard})
			message(STATUS "Setting CONTROL FLOW GUARD") 
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /guard:cf")
			set(CMAKE_EXE_LINKER_FLAGS  "/guard:cf /DYNAMICBASE")
		endif()
		if (${use_qspectre})
			message(STATUS "Setting QSPECTRE")
			set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Qspectre")
		endif()
	endif()
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(PROJECT_LIBRARY_CHECKSUM Checksum)
set(PROJECT_LIBRARY_HASH Hash)
set(PROJECT_LIBRARY_NAME PartialKey)
set(PROJECT_NAME App)
set(TARGET ${PROJECT_NAME})

project(${PROJECT_NAME}
	VERSION 0.0.0.1
	DESCRIPTION "Partial Key Generator Library"
	HOMEPAGE_URL "www.vs3codefactory.com"
	LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app)

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_subdirectory(lib)
add_subdirectory(app)

if(CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
