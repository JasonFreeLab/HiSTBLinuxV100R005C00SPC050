precision highp float;
varying vec2 vTextureCoord;
uniform sampler2D uTextureSampler;

void main(void)
{
	vec4 color = texture2D(uTextureSampler, vTextureCoord);
	gl_FragColor = vec4(color.r, color.g, color.b, color.a);
}

