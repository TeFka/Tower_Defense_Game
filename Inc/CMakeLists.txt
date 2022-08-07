# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND game_includes
    	${CMAKE_CURRENT_LIST_DIR}/Render/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/Render/Texture.h
	${CMAKE_CURRENT_LIST_DIR}/Render/Camera.h
	${CMAKE_CURRENT_LIST_DIR}/Render/TextManager.h
	${CMAKE_CURRENT_LIST_DIR}/Render/ShaderPipeline.h
	${CMAKE_CURRENT_LIST_DIR}/Render/ParticleEngine2D.h
	${CMAKE_CURRENT_LIST_DIR}/Render/RenderEngine.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceWidget.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceBox.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceLayout.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceButton.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceScreen.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceActionScreen.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceEngine.h
	${CMAKE_CURRENT_LIST_DIR}/App/AppEngine.h
	${CMAKE_CURRENT_LIST_DIR}/NoiseProvider.h
	${CMAKE_CURRENT_LIST_DIR}/TowerDefenseGame.h
	${CMAKE_CURRENT_LIST_DIR}/TowerDefenseGameLevelGenerator.h
	${CMAKE_CURRENT_LIST_DIR}/GameEntity.h
	${CMAKE_CURRENT_LIST_DIR}/GameEnemy.h
	${CMAKE_CURRENT_LIST_DIR}/GameAlly.h
	${CMAKE_CURRENT_LIST_DIR}/GameWeapon.h
	${CMAKE_CURRENT_LIST_DIR}/DefenseBuilding.h
	${CMAKE_CURRENT_LIST_DIR}/TowerDefenseGameScreen.h
	${CMAKE_CURRENT_LIST_DIR}/MainMenuScreen.h
)

# /CMakeLists.txt-------------------------------------------------------------