#version 100

precision mediump float;

varying vec3 fragPosition;
varying vec3 fragNormal;
varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

void main() {
	vec3 lightAmbient = vec3(0.25);
	vec3 lightDiffuse = vec3(0.75);
	
	vec3 lightDir = normalize(-vec3(0, 8, 10));
	float diffuseFactor = max(dot(-lightDir, fragNormal), 0.0);
	
	vec4 texelDiffuse = texture2D(texture0, fragTexCoord);
	vec3 surfaceColor = vec3(texelDiffuse*colDiffuse*fragColor);
	vec3 ambient      = lightAmbient*surfaceColor;
	vec3 diffuse      = lightDiffuse*surfaceColor*diffuseFactor;
	
	vec3 phong = ambient + diffuse;
    gl_FragColor = vec4(phong, 1.0);
}
