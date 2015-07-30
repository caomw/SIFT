APP_STL := stlport_static
APP_CPPFLAGS := -frtti -fexceptions -mfloat-abi=softfp -mfpu=neon -std=gnu++0x -Wno-deprecated \
-ftree-vectorize -ffast-math -fsingle-precision-constant
APP_PLATFORM := android-21