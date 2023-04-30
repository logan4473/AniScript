cmake_minimum_required(VERSION 3.7)
project(Ani VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
include(FindCurses)

set(LLVM_PATH /usr/local/Cellar/llvm/3.9/)
set(LLVM_INCLUDE_DIRS ${LLVM_PATH}/include)
link_directories(${LLVM_PATH}/lib)


BISON_TARGET(Parser
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp
    COMPILE_FLAGS "-d --defines=${CMAKE_CURRENT_BINARY_DIR}/Parser.h")

FLEX_TARGET(Lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Lexer.l
    ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

add_executable(Ani
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AstNode.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/codegen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/codegen.h
    ${FLEX_Lexer_OUTPUTS}
    ${BISON_Parser_OUTPUTS})

target_include_directories(Ani
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src
      ${CMAKE_CURRENT_BINARY_DIR}
      ${LLVM_INCLUDE_DIRS})

set_target_properties(Ani PROPERTIES CXX_STANDARD 14)

target_link_libraries(Ani
    LLVMX86Disassembler LLVMX86AsmParser LLVMX86CodeGen LLVMGlobalISel
    LLVMSelectionDAG LLVMAsmPrinter LLVMDebugInfoCodeView LLVMDebugInfoMSF
    LLVMCodeGen LLVMScalarOpts LLVMInstCombine LLVMTransformUtils LLVMBitWriter
    LLVMX86Desc LLVMMCDisassembler LLVMX86Info LLVMX86AsmPrinter LLVMX86Utils
    LLVMMCJIT LLVMExecutionEngine LLVMTarget LLVMAnalysis LLVMProfileData
    LLVMRuntimeDyld LLVMObject LLVMMCParser LLVMBitReader LLVMMC LLVMCore
    LLVMSupport LLVMDemangle z m ${CURSES_LIBRARIES})