#version 440

layout(location=0) in vec3 vert;
layout(location=1) in vec3 textCoord;
layout(location=2) in vec4 col;
layout(location=3) in int textN;

layout(std140) uniform matrixes{
    mat4 projectionMatrix;
    mat4 perpectiveProjectionMatrix;
};

uniform mat4 viewMatrix;

out vec2 textCo;
flat out int textNr;
out vec4 color;

void main(){

   gl_Position = perpectiveProjectionMatrix*viewMatrix*vec4(vert,1.0);

   textCo = vec2(textCoord.x,-textCoord.y);
   textNr = textN;
   color = col;

}
