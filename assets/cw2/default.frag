#version 430

in vec3 v2fColor; // Input color from vertex shader

layout(location = 0) out vec3 oColor; // Output color to the framebuffer

void main() {
    oColor = v2fColor; // Use interpolated color
}
