# app2/CMakeLists.txt
add_executable(app2 src/main.cc src/Server.cc src/Server.hh)
target_link_libraries(app2 Dlib pthread)