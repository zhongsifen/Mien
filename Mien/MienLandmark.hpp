// MienLandmark.hpp

#ifndef MienLandmark_hpp
#define MienLandmark_hpp

#ifdef MienLandmark_EXPORTS
#define MienLandmark_API __declspec(dllexport) 
#else
#ifdef __linux__
#define MienLandmark_API  
#else
#define MienLandmark_API __declspec(dllimport) 
#endif
#endif

MienLandmark_API
int * facedetect_frontal(
	unsigned char * result_buffer,//buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
	unsigned char * gray_image_data, int width, int height, int step,//input image, it must be gray (single-channel) image!
	float scale=1.2f, //scale factor for scan windows
	int min_neighbors=2, //Number of neighbors each candidate rectangle should have to retain it
	int min_object_width=48, //Minimum possible face size. Faces smaller than that are ignored.
	int max_object_width=0, //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.
	int doLandmark=1); // Do landmark detection or not

MienLandmark_API 
int * facedetect_frontal_surveillance(unsigned char * result_buffer, //buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
                               unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
                               int max_object_width = 0, //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.
                               int doLandmark = 0); // landmark detection

MienLandmark_API 
int * facedetect_multiview(unsigned char * result_buffer, //buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
                               unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
                               int max_object_width = 0, //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.
                               int doLandmark = 0); // landmark detection

MienLandmark_API 
int * facedetect_multiview_reinforce(unsigned char * result_buffer, //buffer memory for storing face detection results, !!its size must be 0x20000 Bytes!!
                               unsigned char * gray_image_data, int width, int height, int step, //input image, it must be gray (single-channel) image!
                               float scale, //scale factor for scan windows
                               int min_neighbors, //how many neighbors each candidate rectangle should have to retain it
                               int min_object_width, //Minimum possible face size. Faces smaller than that are ignored.
                               int max_object_width = 0, //Maximum possible face size. Faces larger than that are ignored. It is the largest posible when max_object_width=0.
                               int doLandmark = 0); // landmark detection


#endif
