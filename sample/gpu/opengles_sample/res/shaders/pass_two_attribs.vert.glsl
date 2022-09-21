attribute vec4 aposition;
attribute vec4 atexcoord;

varying vec4 vtexcoord;

void main()
{
	gl_Position = aposition;

	vtexcoord = atexcoord;
}


