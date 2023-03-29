cmake_minimum_required(VERSION 3.11)

project(Test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS OFF)
if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb" )
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -DNDEBUG")
endif()

include(FetchContent)

include_directories(
	"${CMAKE_CURRENT_LIST_DIR}/include" 
	"${CMAKE_CURRENT_LIST_DIR}/include/state" 
	"${CMAKE_CURRENT_LIST_DIR}/include/UI" 
	"${CMAKE_CURRENT_LIST_DIR}/include/handler" 
	"${CMAKE_CURRENT_LIST_DIR}/include/entity" 
	"${CMAKE_CURRENT_LIST_DIR}/include/renderer" 
	"${CMAKE_CURRENT_LIST_DIR}/lib" 
	"${CMAKE_CURRENT_LIST_DIR}/include/attack" 
)

add_executable(test
	src/main.cpp 
	src/playState.cpp 
	src/menuState.cpp 
	src/stateHandler.cpp 
	src/dataHandler.cpp 
	src/tileGrid.cpp 
	src/tileRenderer.cpp 
	src/zapper.cpp 
	src/entityRenderer.cpp 
	src/fraber.cpp
	src/enemyHandler.cpp 
	src/towerHandler.cpp 
	src/guiRenderer.cpp 
	src/gameHandler.cpp 
	src/upgradeMenu.cpp
	src/buildMenu.cpp 
	src/pulser.cpp 
	src/attackHandler.cpp 
	src/attackRenderer.cpp 
	src/freezer.cpp 
	src/hermer.cpp 
	src/tanker.cpp
	src/focuser.cpp 
	src/sniper.cpp 
	src/overState.cpp
)

# --------------- SFML ---------------
FetchContent_Declare(
	SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(test
		sfml-graphics 
		sfml-audio 
		sfml-network 
		sfml-window 
		sfml-system
)

# --------------- Eigen ---------------
FetchContent_Declare(
	Eigen
	GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
	GIT_TAG master
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)

set(EIGEN_BUILD_DOC OFF)
set(BUILD_TESTING OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)

FetchContent_MakeAvailable(Eigen)

target_link_libraries(test
		 Eigen3::Eigen
)