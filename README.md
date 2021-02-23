# Image-convolution-for-2-core-system-on-Vivado-SDK

Convolution is often used for image filtering and bluring effects.
On this project, CPU0 initialize an image, acting as a black-white image.
Both CPUs are trying to apply the convolution effect, by working at one pixel lane at a time.
Our custom array in use for concolution in the following:

-1  -1  -1
-1  9 -1
-1  -1  -1

The image is an 128x128 2d array. The program is using pointers to store the daat, so that both CPUs have access to similar values.
