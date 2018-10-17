cmake_minimum_required(VERSION 3.0)
project (CombatRoyale)

set(SFML_DIR "./src/3rdparty/SFML")
set(EXECUTABLE_OUTPUT_PATH "./bin")

find_package(SFML 2.5 COMPONENTS system graphics audio network REQUIRED)
add_executable(
    CombatRoyale
    src/main.cpp
)
target_link_libraries(CombatRoyale sfml-system sfml-graphics sfml-audio sfml-network)
