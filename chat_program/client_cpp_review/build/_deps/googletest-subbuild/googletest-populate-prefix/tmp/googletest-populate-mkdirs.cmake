# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-src"
  "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-build"
  "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/kimminchae/Desktop/cpp_practice_kim/cpp_practice/chat_program/client_cpp_review/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
