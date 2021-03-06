#version 150

layout(points) in;
layout(triangle_strip, max_vertices = 15) out;


uniform	sampler2D	uNoiseMap;
uniform	float	time;

uniform mat4 ciProjectionMatrix;
uniform mat4 ciViewMatrix;
in vec3 color[];
in vec3 text[];

in float flatD[];

out vec3 vColor;

void main()
{
    float fla =flatD[0];
    float flaInv = 1.0-fla;
    vColor =color[0];
    
    
    vec4 pos = gl_in[0].gl_Position;
    
    
    
    
    
    
    float size =text[0].z*fla;
    vec2 dir = vec2(text[0].x,text[0].y);
    vec2 dirS = vec2(-dir.y,dir.x);
    vec2 uv = pos.xy/1000.0;
    uv.x+=time;
    uv.y+=time;
    vec2 dirWind = (texture(uNoiseMap, uv).xy - vec2(0.5,0.5) )*15*fla +dirS*2.0+dirS*flaInv*text[0].z*0.5;
     
    
    
    //mid
    vec4 offsetMid1 = vec4( dir.xy* 6.0+dirWind ,+size, 0.0 );
    vec4 posMid1 = ciProjectionMatrix *ciViewMatrix* (pos + offsetMid1);
    
    
    
    vec4 offsetMid2 = vec4( dir.xy* -6.0 +dirWind,+size, 0.0 );
    vec4 posMid2 = ciProjectionMatrix *ciViewMatrix* (pos + offsetMid2);
   
    
    
    vec4 offsetMid3 = vec4( dirS.xy*6.0 +dirWind,+size, 0.0 );
    vec4 posMid3 = ciProjectionMatrix *ciViewMatrix* (pos + offsetMid3);
   
    
    vec4 offsetMid4 = vec4( dirS.xy*-6.0 +dirWind,+size, 0.0 );
    vec4 posMid4 = ciProjectionMatrix *ciViewMatrix* (pos + offsetMid4);

    
    
    

    
  

    
    
    
    
    
    // vColor =vec3(1,0,0);
    
    
    gl_Position = posMid1;
    EmitVertex();
    
    gl_Position = posMid2;
    EmitVertex();
    
    gl_Position = posMid3;
    EmitVertex();
    
    EndPrimitive();
    
    
    
    gl_Position = posMid1;
    EmitVertex();
    
    gl_Position = posMid2;
    EmitVertex();
    
    gl_Position = posMid4;
    EmitVertex();
    
    EndPrimitive();

   /* //////////////////////////////////////
    //vColor =vec3(0,1,0);
    gl_Position = posBase3;
   
    EmitVertex();
    
    
    gl_Position = posBase1;
   
    EmitVertex();
    
    gl_Position = posMid3;

    EmitVertex();
    
    
    gl_Position = posMid1;
  
    EmitVertex();
    
    
    gl_Position = posTop;
   
    EmitVertex();
    EndPrimitive();
    
    //////////////////////////////////
    //vColor =vec3(0,0,1);
    gl_Position = posBase3;

    EmitVertex();
    
    gl_Position = posBase2;

    EmitVertex();
    
    gl_Position = posMid3;
  
    EmitVertex();
    
    gl_Position = posMid2;
 
    EmitVertex();
    
    
    
    
    gl_Position = posTop;
   
    EmitVertex();
    EndPrimitive();*/
}
