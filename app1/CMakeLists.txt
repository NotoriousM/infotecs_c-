# app1/CMakeLists.txt
add_executable(app1 src/main.cc src/Client.cc src/Buffer.cc src/Buffer.hh src/Client.hh)
target_link_libraries(app1 Dlib pthread)