#ifdef GL_ES
precision mediump float;
#endif

uniform samplerCube samplerCb;
varying vec3 texCoord0;
varying vec3 texCoord1;				// view vector (eye - pixel position)

void main (void)
{
	gl_FragColor = textureCube(samplerCb, texCoord0);
}
