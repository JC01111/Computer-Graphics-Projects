# Rasterizer

> Jan 2024

[Specs](https://cs184.eecs.berkeley.edu/sp24/docs/hw1-spec)

This is my personal writeup after implementing these functions to achieve the funtionality of rasterizing.

#### Task1:
1. This task helps me fully understand of how does the rasterizing work instead of conceptually. I rasterize the triangles by sampling each pixel within the range of x_values and y_values, by choosing the center of each pixel and sample it. Then I applied the barycentric coordinates to solve the issue of winding order, because barycentric coordinates are always nonnegative for points inside the triangle, regardless of the winding order of the vertices. Finally, if the alpha, beta, gamma are greater or equal to zero, x and y are greater or equal to zero and within the bounding box, we can fill color for this pixel.
2. Efficiency of Algorithm:
The algorithm is efficient because it limits the point-in-triangle tests to the pixels within the bounding box of the triangle, rather than checking every pixel on the screen. By doing this, the number of checks is reduced to only those necessary, since pixels outside the bounding box cannot be inside the triangle. 
<br>
(basic/test4.svg)

![task1.png](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/129e6f38fe0cd371952c634658c0921c7a2fd336/writeup/task1.png)
<br>

#### Task2:
1. Supersampling is an antialiasing technique. It’s useful since it averages out the samples to determine the color of each pixel from higher resolution image to a low resolution image. It smoothes out the edges to make it look less jaggy. In the rasterization method, the sample buffer is a dynamic sized(determined by the sample_rate) vector that stores diff color values for each supersample. And the buffer is resized to get high num of pixels(w*h*sample_rate). And correspondingly, fill_pixel, rasterize_triangle, these methods are adapted to work with the supersampled buffer to calculate the position and color for each supersample in the area.
. So the set_sample_rate and set_framebuffer_target methods ensure that the sample buffer is at the correct size based on the supersampling rate and the dimension of the framebuffer. In the rasterize_triangle method, it iterates over the bounding box of triangles at the supersampled resolution, and used barycentric coordinates to determine which supersamples are in range and should be colored. And after rendering we used the resolve_to_frambuffer to average out the color values of supersamples for each pixel.
2. If you look at the three images below with different supersample rate. At sample 1, you should see very clear jaggies around the edges of the triangle. At the sample rate4(2*2 supersampling), you should observed that the edges become smoother and the triangle should have a more slowly transition in terms of colors. And in the sample rate 16 (4*4), the antialiasing effect would be even more apparent. All the edges and corners are more smoother.
<br>
(basic/test4.svg at sample rate 1)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/Task2_1.png)

(basic/test4.svg at sample rate 4)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/Task2_2.png)

(basic/test4.svg at sample rate 16)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/Task2_3.png)
<br>

#### Task3:
![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/task3.png)
<br>

#### Task4:
Based on my understanding, Barycentric coordinates are the coordinates that we calculate the proportional distances from three points, and we use the proportion of each direction as the proportion for our coordinate, then we apply the same idea for the color interpolation, use the proportional distances as the proportion of each different color proportion. 
<br> (svg/basic/test7.svg)
![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/task4.png)
<br>

#### Task5:
1. Pixel sampling is the process of selecting a color value from a texture image to apply to a pixel on the screen. The way I did the texture mapping is by finding the closest grid of a point then find the texel of that point.
2. Nearest-Neighbor Sampling: This method is the simplest form of texture filtering. It selects the color of the nearest texel to the specified texture coordinate. Since texture coordinates are usually floating-point numbers but texels are discrete, the nearest texel is the one with the closest integer coordinates to the texture coordinate. This approach is straightforward and fast, but it can produce a blocky or pixelated image, especially when the texture is magnified or viewed at a steep angle.
3. Bilinear Sampling: Bilinear sampling considers the colors of the four nearest texels that surround the specified texture coordinate. It then uses a weighted average of these colors, with the weights determined by the distance of the texture coordinate from each texel's center (similar to supersampling). This method involves two steps of linear interpolation: first horizontally between the top and bottom pairs of texels, and then vertically between the results of the first interpolation. This method produces smoother images with more gradual transitions between texels.
4. See the below images of Nearest, bilinear texture sampling methods’ screenshots, we can see the bilinear filtering have more detailing to the picture (some orange color around the coastline), while the nearest sampling has more unclear image, and the color is not colorful as the bilinear filtering.
5. The largest differences between nearest-neighbor and bilinear sampling will be seen when textures are being scaled significantly up or down. Nearest-neighbor will maintain the sharpness of the original texels, but at the cost of potentially introducing blocky or aliased visuals. Bilinear filtering smooths out the transitions between texels, leading to a more visually better image when textures are scaled, but can make textures look blurry, especially when viewed up close.
<br>
(Nearest at sample rate 1)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/nearest1.png)

(Nearest at sample rate 16)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/nearest16.png)

(Bilinear at sample rate 1)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/bilinear1.png)

(Bilinear at sample rate 16)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/bilinear16.png)
<br>

#### Task6:
1.  Level sampling is basically selecting the right level of detail from textures/mipmaps when rendering an object. And it’s adjusted based off the derivative of the texture coordinates to get rid of blurs and aliasing. And we use mipmap this method to make sure the image looks clear regardless of its distance by applying different layers of resolutions. So in our implementation we used du/dx and dv/dy to represent how the texture coordinates changed across the surface of the object. Then inside the get_level method we calculated the difference of coordinates between pixels to get the rate of change. After that we scaled it by the actual dimensions to get texture’s size. Then we calculate the length of the vectors and choose the max length to represent the most rapid change in coordinates. And the final step is to calculate the mipmap level within the range.
2.  So L_Zero uses the base lv mipmap without any interpolation; L_Nearest finds the nearest mipmap lv for sampling; L_Linear interpolates between two mipmap level to get a mixed result which can be smoother. Sample_nearest can be fast since it returns the color thats closest to the coordinates but it can turn out blurry while sample_bilinear  grabs the four closest coordinates to get a smoother image which can require more memory, power and time to compute. So overall, nearest sampling can turnout fast but very pixeled image. While more samples per pix and bilinear can be slower but comes with higher quality. And in terms of memory, Higher level of details can consume more memories and using nearest levels can save memories. Antialiasing power is very effective on bilinear since with higher sample rate reduces the jaggies but can cost more memory.

(L_ZERO and P_NEAREST)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/Task6_1.png)

(L_ZERO and P_LINEAR)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/Task6_2.png)

(L_NEAREST and P_NEAREST)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/Task6_3.png)

(L_NEAREST and P_LINEAR)

![](https://github.com/cal-cs184-student/hw1-rasterizer-sp24-j-c/blob/5210b49ff4151da7c79005af6323edfe36781678/writeup/Task6_4.png)
