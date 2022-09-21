attribute vec3 aVetexCoord;
attribute vec2 aTexureCoord;
varying vec2 vTextureCoord;

void main(void)
{
	 gl_Position = vec4(aVetexCoord, 1.0);
	 vTextureCoord = aTexureCoord;
}

