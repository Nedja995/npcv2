# README
 1. About
 2. Prerequisites
 3. Building
 4. CMake
 5. Library user
 
### 1. ABOUT:
 - This is training and experimental project for Computer Vision, C++ and CMake.
 - This is child of project [`npcv pure C library`](https://github.com/Nedja995/npcv-c).
 - Now i'm finished with:
     1. Base image operation (load/write, arithmetic, scale, convert)
     2. Convolution matrix filtering
     3. Edge detection (Canny)
     4. Erosion

##### TODO:
 - Demos for Erosion (HIGH)
 - Zoom interpolation (In progress)
 - Improve edge detection (old [EdgeDetection.cc](https://github.com/Nedja995/npcv-c/blob/master/src/base/imageproc/EdgeDetection.cc))
 - Classification OCR Edge based (old [image_classification.cc](https://github.com/Nedja995/npcv-c/blob/master/src/base/classification/image_classification.cc))
 
### 2. PREREQUISITES

 This project requires:
  * Cross-platform Make (CMake) v2.6.2+
  * GNU Make or equivalent.
  * GCC or an alternative, reasonably conformant C++ compiler (Visual Studio 2015).

### 3. BUILDING 
 
 First generate with CMake project for target platform (Windows, Linux).
 
### 4. CMake
 
 Demos - you can choose to generate demos projects
 TestApp - developing test
 
### 5. Library user
 
 Include headers from /include and link lib from lib/Release (x64 only).
 There is also doxygen documentation in /docs/html/.
