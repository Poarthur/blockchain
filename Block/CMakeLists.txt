set(headers
Block.h
Header.h
Sha256.h
Signature.h
Key.h
IBlock.h
)
set(sources
Block.cpp
Header.cpp
Sha256.cpp
Signature.cpp
Key.cpp
)

add_library(Block ${headers} ${sources})

include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

target_include_directories(Block INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Block PUBLIC ${CMAKE_SOURCE_DIR}/merklecpp)

# install rules
install(TARGETS Block DESTINATION lib)