#version 330 core
//in vec3 ourColor;
in vec2 TexCoord;
out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;
uniform float opacity;

void main()
{
    // Linearly interpolate between both textures (second texture is only slightly combined)
    //color.a = 0.1;
    color = texture(ourTexture1, TexCoord) * opacity;
    //GL_Color = texturecolor * 1.0/distance(light_position,world_position);
    
}