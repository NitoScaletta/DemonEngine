#version 460 core
out vec4 gl_FragColor;
in vec2 TexCoord;
in vec4 ourColor;

uniform vec4 u_Color;
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_Resolution;

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5);
	return 1.-smoothstep(_radius-(_radius*0.01),
                         _radius+(_radius*0.01),
                         dot(dist,dist)*4.0);
}

void main(){
	vec2 st = gl_FragCoord.xy/u_Resolution.xy;

	vec3 color = vec3(circle(st,1));

	gl_FragColor = vec4( color, 1.0 );
}