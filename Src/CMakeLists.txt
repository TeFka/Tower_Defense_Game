# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND game_includes
    	${CMAKE_CURRENT_LIST_DIR}/Render/Shader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/Texture.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/Camera.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/TextManager.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/ShaderPipeline.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/ParticleEngine2D.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/RenderEngine.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceWidget.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceBox.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceLayout.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceButton.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceScreen.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceActionScreen.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceEngine.cpp
	${CMAKE_CURRENT_LIST_DIR}/App/AppEngine.cpp
	${CMAKE_CURRENT_LIST_DIR}/NoiseProvider.cpp
	${CMAKE_CURRENT_LIST_DIR}/TowerDefenseGame.cpp
	${CMAKE_CURRENT_LIST_DIR}/TowerDefenseGameLevelGenerator.cpp
	${CMAKE_CURRENT_LIST_DIR}/GameEntity.cpp
	${CMAKE_CURRENT_LIST_DIR}/GameEnemy.cpp
	${CMAKE_CURRENT_LIST_DIR}/GameAlly.cpp
	${CMAKE_CURRENT_LIST_DIR}/GameWeapon.cpp
	${CMAKE_CURRENT_LIST_DIR}/DefenseBuilding.cpp
	${CMAKE_CURRENT_LIST_DIR}/TowerDefenseGameScreen.cpp
	${CMAKE_CURRENT_LIST_DIR}/MainMenuScreen.cpp
)

# /CMakeLists.txt-------------------------------------------------------------