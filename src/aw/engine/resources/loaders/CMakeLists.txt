#add_to_target(awEngine PRIVATE assimpLoader.cpp)
add_to_target(awEngine PRIVATE ofbxLoader.cpp)

add_to_target(awEngine PRIVATE impl/ofbx/miniz.c)
add_to_target(awEngine PRIVATE impl/ofbx/ofbx.cpp)
