#version 460 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
}; 

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform Material material;

float near = 0.2; 
float far  = 50.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}


void main()
{
    // ambient
    vec4 texColor = texture(material.diffuse, TexCoords);
    if(texColor.a < 0.33)
        discard;
    texColor.a = 1.0;
        
    float depth = 1.0 - LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    FragColor = vec4(vec3(depth), 1.0) * texColor;
} 