#include <jni.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <android/log.h>
#include "ezsift.h"

#ifndef JNIEXPORT
#define JNIEXPORT
#endif

#ifndef JNICALL
#define JNICALL
#endif

#define  LOG_TAG    "ezsift"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"{
	void test() {
		char *file1 = "/storage/sdcard/img1.pgm";

		ImageObj<unsigned char> image;	
		if(read_pgm(file1, image.data, image.w, image.h)!=0)
		{
			LOGI("Failed to open input image!\n");
			return;
		}
		LOGI("image size: %d x %d\n", image.w, image.h);

		bool bExtractDescriptor = true;
		std::list<SiftKeypoint> kpt_list;

		// Double the original image as the first octive.
		double_original_image(true);

		// Perform SIFT computation on CPU.
		LOGI("Start SIFT detection ...\n");
		sift_cpu(image, kpt_list, bExtractDescriptor);

		// Generate output image with keypoints drawing
		char filename[255];
		sprintf(filename, "%s_psift_output.ppm", file1);
		draw_keypoints_to_ppm_file(filename, image, kpt_list);

		// Generate keypoints list
		sprintf(filename, "%s_psift_key.key", file1);
		export_kpt_list_to_file(filename, kpt_list, bExtractDescriptor);

		LOGI("\n");
		LOGI("Total keypoints number: \t\t %d\n", kpt_list.size());
	}

	void Java_com_example_pbatest_MainActivity_test(JNIEnv* env, jobject thiz )
	{
		test();
	}
}