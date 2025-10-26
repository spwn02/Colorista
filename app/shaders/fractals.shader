#version 460 core

// CC0: Just another cube
// Glowtracers are great for compact coding, but I wanted to see how much
// I could squeeze a more normal raymarcher in terms of characters used.

// Twigl: https://twigl.app?ol=true&ss=-OW-y9xgRgWubwKcn0Nd

layout(location = 0) out vec4 fragColor;

layout(location = 0) uniform float iTime;
layout(location = 1) uniform vec2 iResolution;

vec3 palette( float t ) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);

    return a + b*cos( 6.28318*(c*t+d) );
}

//https://www.shadertoy.com/view/mtyGWy
void main() {
    vec2 uv = (gl_FragCoord.xy * 2.0 - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    
    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;

        float d = length(uv) * exp(-length(uv0));

        vec3 col = palette(length(uv0) + i*0.4 + iTime*0.4);

        d = sin(d*8.0 + iTime)/8.0;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        finalColor += col * d;
    }

    fragColor = vec4(finalColor, 1.0);
}