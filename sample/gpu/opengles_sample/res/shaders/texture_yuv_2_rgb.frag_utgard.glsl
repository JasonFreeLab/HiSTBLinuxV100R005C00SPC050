#extension GL_OES_EGL_image_external : require
precision mediump float;

varying vec4 vtexcoord;
uniform samplerExternalOES luminance;
uniform samplerExternalOES luminance_alpha;

void main()
{
	float y = texture2D(luminance, vtexcoord.xy).r;
	vec2 uv = texture2D(luminance_alpha, vtexcoord.xy).ra;
	float v = uv.x;
	float u = uv.y;

	//Android Imp.
	//https://en.wikipedia.org/wiki/YUV#HDTV_with_BT.709
	float r = y + (1.370705 * (v - 0.5));
	float g = y - (0.698001 * (v - 0.5)) - (0.337633 * (u - 0.5));
	float b = y + (1.732446 * (u - 0.5));

	gl_FragColor = vec4(r, g, b, 1);
}
