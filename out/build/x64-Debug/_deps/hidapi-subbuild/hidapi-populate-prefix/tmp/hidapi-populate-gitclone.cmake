
if(NOT "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-subbuild/hidapi-populate-prefix/src/hidapi-populate-stamp/hidapi-populate-gitinfo.txt" IS_NEWER_THAN "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-subbuild/hidapi-populate-prefix/src/hidapi-populate-stamp/hidapi-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-subbuild/hidapi-populate-prefix/src/hidapi-populate-stamp/hidapi-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/bin/git.exe"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/signal11/hidapi.git" "hidapi-src"
    WORKING_DIRECTORY "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/signal11/hidapi.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/bin/git.exe"  checkout a6a622ffb680c55da0de787ff93b80280498330f --
  WORKING_DIRECTORY "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'a6a622ffb680c55da0de787ff93b80280498330f'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/bin/git.exe"  submodule update --recursive --init 
    WORKING_DIRECTORY "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-subbuild/hidapi-populate-prefix/src/hidapi-populate-stamp/hidapi-populate-gitinfo.txt"
    "E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-subbuild/hidapi-populate-prefix/src/hidapi-populate-stamp/hidapi-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'E:/Backup DO NOT DELETE/git/JoyShockLibrary-GMS/out/build/x64-Debug/_deps/hidapi-subbuild/hidapi-populate-prefix/src/hidapi-populate-stamp/hidapi-populate-gitclone-lastrun.txt'")
endif()

