cmake_minimum_required(VERSION 3.21)

project(
    minesweeper
    VERSION 0.1.0
    DESCRIPTION "Minesweeper game in the terminal"
    HOMEPAGE_URL "https://github.com/EfesX/minesweeper"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(FTXUI)

add_executable(minesweeper 
    src/minesweeper.cc 
    src/board.cc
    src/game.cc
    src/ui_game.cc
)
target_link_libraries(minesweeper PRIVATE dom component)
target_include_directories(minesweeper PRIVATE include)


include(GNUInstallDirs)
install(
    TARGETS minesweeper
    RUNTIME 
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(CPack)
