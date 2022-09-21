#extension GL_OES_EGL_image_external : require
precision mediump float;
uniform samplerExternalOES yuv;
varying mediump vec4 vtexcoord;
void main()
{
	mediump vec3 rgb;
	rgb = texture2D(yuv, vtexcoord.xy).xyz;
	gl_FragColor = vec4(rgb, 1);
}
