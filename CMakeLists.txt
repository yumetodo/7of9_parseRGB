﻿cmake_minimum_required(VERSION 2.8.12)

project(libparseRGB C)
set(CMAKE_C_STANDARD 11) # C++11...
set(CMAKE_C_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_C_EXTENSIONS OFF) #...without compiler extensions like gnu++11

# 1. INTERFACE_INCLUDE_DIRECTORIES にソースディレクトリとビルドディレクトリを自動追加する。
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_C_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUC)
  # Update if necessary
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

# 2. ライブラリのビルド指定
add_library(parseRGB STATIC parseRGB.c)

# 3. インストールするヘッダファイルを指定しておく。
# 指定したファイルは、INSTALL(TARGETS) の PUBLIC_HEADER で指定した
# ディレクトリにインストールされる。
set_target_properties(parseRGB PROPERTIES
        PUBLIC_HEADER parseRGB.h
)

# 5. ターゲットのインストール指定
install(TARGETS parseRGB
    EXPORT parseRGB-export                         # 5.a EXPORT オプションで エクスポート名を指定する
    ARCHIVE        DESTINATION lib
    LIBRARY        DESTINATION lib            # 5.b ライブラリのインストール先
    INCLUDES       DESTINATION include        # 5.c エクスポート時にincludeパスに含めるパスを指定する
    PUBLIC_HEADER  DESTINATION include/parseRGB)   # ヘッダのインストール先

# 6. parseRGB-config.cmake を自動生成してインストールする。 
install(EXPORT parseRGB-export                     # 6.a 
    FILE parseRGB-config.cmake                     # 6.b ファイル名を指定する
    DESTINATION share/cmake/parseRGB/              # 6.c インストール先
    EXPORT_LINK_INTERFACE_LIBRARIES)          # 6.d 同時にリンクすべきライブラリをエクスポートする

add_subdirectory(test)
