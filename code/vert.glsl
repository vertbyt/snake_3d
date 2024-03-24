#version 100

attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;
attribute vec3 vertexNormal;
attribute vec4 vertexColor;

varying vec3 fragPosition;
varying vec3 fragNormal;
varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;

void main() {
	gl_Position = mvp*vec4(vertexPosition, 1.0);
	
	fragPosition = vec3(matModel*vec4(vertexPosition, 1.0));
	fragNormal   = normalize(vec3(matNormal*vec4(vertexNormal, 1.0)));
	fragTexCoord = vertexTexCoord;
	fragColor    = vertexColor;
}