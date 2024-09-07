# Sample static library
add_library(dictionarylib STATIC)

target_sources(
    dictionarylib
    PRIVATE
        "Dictionary.h"
        "Dictionary.cpp"
 "DictionaryNode.h"  "Definitions.h" "Statistics.h" "Statistics.cpp"  "Interface.h" "File.h" "HelperFunctions.h")

add_executable(application)

target_sources(
    application
    PRIVATE
        "application.cpp"
 "DictionaryNode.h"  "Definitions.h" "Statistics.h" "Statistics.cpp"  "Interface.h" "File.h" "HelperFunctions.h")

target_link_libraries(
    application
    PRIVATE
        dictionarylib
)
