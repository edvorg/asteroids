CPP_FLAGS= -std=c++11 -I/home/edvorg/Projects/zepto/android-ndk-r9c/platforms/android-18/arch-arm/usr/include/ -I/home/edvorg/Projects/zepto/android-ndk-r9c/sources/android/native_app_glue/

all:
	clang++ ${CPP_FLAGS} main.cpp

check-syntax:
	clang++ ${CPP_FLAGS} -fsyntax-only -fno-color-diagnostics ${CHK_SOURCES}

print-cflags:
	echo ${CPP_FLAGS}
