

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()




########## generic_system block #############
# Definition of system, platform and toolset
#############################################





set(CMAKE_C_COMPILER "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe")




# Definition of VS runtime, defined from build_type, compiler.runtime, compiler.runtime_type
cmake_policy(GET CMP0091 POLICY_CMP0091)
if(NOT "${POLICY_CMP0091}" STREQUAL NEW)
    message(FATAL_ERROR "The CMake policy CMP0091 must be NEW, but is '${POLICY_CMP0091}'")
endif()
set(CMAKE_MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Debug>:MultiThreadedDebugDLL>")

message(STATUS "Conan toolchain: C++ Standard 17 with extensions OFF")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Conan conf flags start: 
# Conan conf flags end

foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/pbsun/.conan2/p/b/fmt8bb01e0f80214/p/lib" "C:/Users/pbsun/.conan2/p/b/sfmla86a788ae427a/p/lib" "C:/Users/pbsun/.conan2/p/b/freet35b21436b0288/p/lib" "C:/Users/pbsun/.conan2/p/b/libpn4064ef446273c/p/lib" "C:/Users/pbsun/.conan2/p/b/zlib592a5a0a7a140/p/lib" "C:/Users/pbsun/.conan2/p/b/bzip28a593390cbdae/p/lib" "C:/Users/pbsun/.conan2/p/b/brotlbc52b78e6c457/p/lib" "lib" "C:/Users/pbsun/.conan2/p/b/flac8801be4820a19/p/lib" "C:/Users/pbsun/.conan2/p/b/opena58847b8721ffa/p/lib" "C:/Users/pbsun/.conan2/p/b/vorbiae079c10491bb/p/lib" "C:/Users/pbsun/.conan2/p/b/oggeb32fc78aa77b/p/lib" "lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/pbsun/.conan2/p/b/fmt8bb01e0f80214/p/include" "C:/Users/pbsun/.conan2/p/b/sfmla86a788ae427a/p/include" "C:/Users/pbsun/.conan2/p/b/freet35b21436b0288/p/include" "C:/Users/pbsun/.conan2/p/b/freet35b21436b0288/p/include/freetype2" "C:/Users/pbsun/.conan2/p/b/libpn4064ef446273c/p/include" "C:/Users/pbsun/.conan2/p/b/zlib592a5a0a7a140/p/include" "C:/Users/pbsun/.conan2/p/b/bzip28a593390cbdae/p/include" "C:/Users/pbsun/.conan2/p/b/brotlbc52b78e6c457/p/include" "C:/Users/pbsun/.conan2/p/b/brotlbc52b78e6c457/p/include/brotli" "include" "C:/Users/pbsun/.conan2/p/b/flac8801be4820a19/p/include" "C:/Users/pbsun/.conan2/p/b/opena58847b8721ffa/p/include" "C:/Users/pbsun/.conan2/p/b/opena58847b8721ffa/p/include/AL" "C:/Users/pbsun/.conan2/p/b/vorbiae079c10491bb/p/include" "C:/Users/pbsun/.conan2/p/b/oggeb32fc78aa77b/p/include" "include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration


if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()