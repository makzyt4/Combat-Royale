cmake_minimum_required(VERSION 3.0)
project (CombatRoyale)

set(SFML_DIR "./3rdparty/SFML")
set(EXECUTABLE_OUTPUT_PATH "./bin")

find_package(SFML 2.5 COMPONENTS system graphics audio network REQUIRED)
add_executable(
    CombatRoyale
    src/game/Player.cpp
    src/graphics/appearance/PlayerAppearance.cpp
    src/graphics/util/SpriteInfo.cpp
    src/physics/Box.cpp
    src/physics/Entity.cpp
    src/util/JsonLoader.cpp
    src/util/TextureLoader.cpp
    src/main.cpp
)
target_link_libraries(CombatRoyale libBox2D.a sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
