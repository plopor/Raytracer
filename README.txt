Dependencies:
OpenGL 3.2+
GLFW
    http://www.glfw.org/
Lua
    http://www.lua.org/
GLM
    http://glm.g-truc.net/0.9.7/index.html
ImGui
    https://github.com/ocornut/imgui

Compilation: make clean and make

Manual:

NOTE tested only on Linux environments.

NOTE that this is using the Phong illumination model.
NOTE that the diffuse coefficient is used to decide the ambient component of Phong lighting.
NOTE that the c1 + c2 * r + c3 * r ^ 2 denominator is used for attenuation.
NOTE that the intensity and distance coefficients of the above attenuation of each light source is arbitrarily determined, set to 0.01 for all coefficients and 1500 for intensity.
NOTE that the Phong lighting exponent variable can is arbitrarily determined and set to 1.
NOTE that the number of shadow rays for soft shadows is arbitrarily determined and set to 20.
NOTE that the sampled plane for area lights is arbitrarily determined and set to have a width and height of 200.
NOTE that the number of glossy transmission rays is arbitrarily determined and set to 6.
NOTE that the number of glossy reflection rays is is arbitrarily determined and set to 36.
The arbitrary constants set above were decided based on what I personally thought looked the best and took the least time to render.


To render the image described by the lua script demo.lua, use ./RT Assets/demo.lua.

To create materials in the lua file, the first two parameters represent the diffuse and specular coefficients for RGB values respectively. The third specifies shininess or the exponent variable of Phong lighting (always assumed to be 1).
    NOTE there are three special appended parameters which are, in order: a double for the index of refraction, a double between 0 and 1 for the reflectivity, and a boolean 0 or 1 for whether it is glossy.
    NOTE that if the index of refraction is 0, it is not a transmissive material. Similarly, if the reflectivity is 0, it is not reflective.
To create nonhierspheres in the lua file, the first parameter specifies object id, the second specifies xyz coordinates (note that we look down the -z axis), and the thid specifies size.
    NOTE there are two special appended parameters which are, in order: a boolean 0 or 1 for whether the material is bump mapped and a boolean 0 or 1 for whether the material is texture mapped.
    NOTE that when creating spheres in the lua file, the only available bump map is that of a golf ball, and the only available texture map is that of Earth.
NOTE that when assigning materials to spheres, there should be a DIFFERENT material used for each sphere if it is being textured. This is because texturing will edit the color of the material directly.

NOTE that in addition to screenshot.png which is my final scene, I've also included several additional screenshots labelled *_demo.png that each demonstrate a specific feature.
NOTE that in terms of external resources, I've included stb_image.hpp to take input from a PNG to texture and bump map along with their PNGs.
NOTE that for the objective of UI, the PDF documenting each objective will be appended to the end of the project report.
    The images for the UI PDF however, will be the same *_demo.png images is included in this submission. The references to the external resources is also included in the report.

The final scene consists of 2 lights; white, yellow and a collection of spheres exhibiting perfect/glossy reflection/refraction, bump mapping, texture mapping, soft shadows, and anti-aliasing.