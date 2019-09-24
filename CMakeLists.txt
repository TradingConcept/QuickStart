cmake_minimum_required (VERSION 3.5)
project(QuickStart)

set(QUICK_START_VERSION_MAJOR 1)
set(QUICK_START_VERSION_MINOR 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Creamos librerías
set(SOURCESLIB ${PROJECT_SOURCE_DIR}/src/QuickStart.cpp)
include_directories(
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/ConcurrentCollections/include"
        "${PROJECT_SOURCE_DIR}/ParallelLib/include"
        "${PROJECT_SOURCE_DIR}/LoggingLib/include"
        )
add_library(QuickStartLib STATIC ${SOURCESLIB})

# Habilitamos testing
enable_testing()
add_subdirectory(test)


####################################################################################################
# MulticastSender - Creamos librerías
####################################################################################################
set(MULTICAST_SENDER_SOURCESLIB ${PROJECT_SOURCE_DIR}/src/MulticastSender.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(MulticastSenderLib STATIC ${MULTICAST_SENDER_SOURCESLIB})

####################################################################################################
# MulticastReceiver - Creamos librerías
####################################################################################################
set(MULTICAST_RECEIVER_SOURCESLIB ${PROJECT_SOURCE_DIR}/src/MulticastReceiver.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(MulticastReceiverLib STATIC ${MULTICAST_RECEIVER_SOURCESLIB})

####################################################################################################
# Parametros - Creamos librerías
####################################################################################################
set(PARAMETROS_SOURCESLIB ${PROJECT_SOURCE_DIR}/src/Parametros.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")
add_library(ParametrosLib STATIC ${PARAMETROS_SOURCESLIB})

####################################################################################################
# librerías externa
####################################################################################################
add_subdirectory(ParallelLib)
add_subdirectory(ConcurrentCollections)
add_subdirectory(LoggingLib)

# Creamos el ejecutable prinipal y le pegamos la librería
set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/Dog.cpp        
    ${PROJECT_SOURCE_DIR}/src/OpenFile.cpp        
    ${PROJECT_SOURCE_DIR}/src/Lab.cpp        
    )
include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(QuickStart ${SOURCES})
# find_package(Boost COMPONENTS regex system filesystem REQUIRED)
find_package(Boost COMPONENTS system REQUIRED) # por el momento parece que sólo requerimos la de system, ya 
target_link_libraries (
        QuickStart
        QuickStartLib
        ParametrosLib
        MulticastSenderLib
        MulticastReceiverLib        
        ConcurrentCollections
        ParallelLib
        LoggingLib
        pthread
        ${Boost_SYSTEM_LIBRARY}
        # ejemplo para otras librerías de boost que vayan surgiendo
        # ${Boost_FILESYSTEM_LIBRARY}         
        # ${Boost_REGEX_LIBRARY}
        )
