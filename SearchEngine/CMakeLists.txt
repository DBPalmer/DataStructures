cmake_minimum_required(VERSION 3.20)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)

configure_file(stopwords.txt stopwords.txt COPYONLY)

add_executable(22s_final_proj main.cpp AVLTree.h porter2_stemmer.cpp porter2_stemmer.h util/hash.h util/string_view.h Word.cpp Word.h CodeRunner.cpp CodeRunner.h AVLTree.cpp Document.cpp Document.h)