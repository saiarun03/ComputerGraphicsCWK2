#version 430

layout(location = 0) in vec3 iPosition; // Input vertex position
layout(location = 1) in vec3 iColor;    // Input vertex color

layout(location = 0) uniform mat4 uProjCameraWorld; // Matrix for transforming vertices

out vec3 v2fColor; // Output color passed to fragment shader

void main() {
    v2fColor = iColor; // Pass input color to fragment shader
    gl_Position = uProjCameraWorld * vec4(iPosition, 1.0); // Transform vertex position
}
