#extension GL_OES_EGL_image_external : require
precision mediump float;

varying vec4 vtexcoord;
uniform samplerExternalOES luminance;
uniform samplerExternalOES luminance_alpha;

void main()
{
	float y = texture2D(luminance, vtexcoord.xy).r;
	vec2 uv = texture2D(luminance_alpha, vtexcoord.xy).ra;
	float u = uv.x;
	float v = uv.y;

	//convert yuv to rgb
	float r = y + (1.370705 * (v - 0.5));
	float g = y - (0.698001 * (v - 0.5)) - (0.337633 * (u - 0.5));
	float b = y + (1.732446 * (u - 0.5));

	//convert rgb to yuv
	y = clamp((r * 0.299) + (g * 0.587) + (b * 0.114), 0.6274, 0.92156);
	v = 0.5 + (r - y) * 0.713;
	u = 0.5 + (b - y) * 0.565;

	y = 0.29882226 * r + 0.5868146 * g + 0.114631 * b;

	gl_FragColor = vec4(y, y, y, y);
}
