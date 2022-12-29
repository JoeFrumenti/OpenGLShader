#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float offsetValueX;
uniform float offsetValueY;
out vec3 ourColor;
void main()
{
	gl_Position = vec4(aPos.x + offsetValueX, -aPos.y + offsetValueY, aPos.z, 1.0);

	float xvalue = gl_Position.x;
	float yvalue = gl_Position.y;
	if(xvalue < 0)
		xvalue = -xvalue;
	if(yvalue < 0)
		yvalue = -yvalue;

	ourColor = vec3(xvalue, yvalue, gl_Position.z);
}