#version 330 core
layout (location = 0) in vec3 position;

out vec2 TexCoord;
uniform mat4 viewProjection;
uniform mat4 model;

void main()
{
    const vec2 texCoord[4] = vec2[4](vec2(1.0f, 1.0f),
                                    vec2(1.0f, 0.0f),
                                    vec2(0.0f, 0.0f),
                                    vec2(0.0f, 1.0f));
    int index = gl_VertexID & 3;
    gl_Position = viewProjection * model * vec4(position, 1.0f);
    TexCoord = vec2(texCoord[index].x,1.0 - texCoord[index].y);
}