# Populates a ${FILESYSTEM_LACKS_SYMLINKS} variable
message(STATUS "Testing if file system supports symlinks")
execute_process(
  COMMAND ${CMAKE_COMMAND} -E create_symlink CMakeLists.txt "${CMAKE_CURRENT_BINARY_DIR}/TestingIfSymlinkWorks"
    WORKING_DIRECTORY .
    RESULT_VARIABLE FILESYSTEM_LACKS_SYMLINKS
)
If (FILESYSTEM_LACKS_SYMLINKS)
  message(STATUS "Testing if file system supports symlinks -- unsupported")
else()
  message(STATUS "Testing if file system supports symlinks -- supported")
endif()

