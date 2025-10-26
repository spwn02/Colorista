#version 460 core

// CC0: Just another cube
// Glowtracers are great for compact coding, but I wanted to see how much
// I could squeeze a more normal raymarcher in terms of characters used.

// Twigl: https://twigl.app?ol=true&ss=-OW-y9xgRgWubwKcn0Nd

layout(location = 0) out vec4 fragColor;

layout(location = 0) uniform float iTime;
layout(location = 1) uniform vec2 iResolution;

mat2 R;
float d=1.0, z, G=9, M=1e-3;

float D(vec3 p) {
  p.xy *= R;
  p.xz *= R;

  vec3 S = sin(123.0*p);

  G = min(G, max(abs(length(p)-0.6), d = pow(dot(p*=p*p*p,p),0.125) - 0.5 - pow(1.0+S.x*S.y*S.z,8.0)/1e5));

  return d;
}

void main()
{
  vec2 uv = gl_FragCoord.xy;
  vec3 p, O, r=vec3(iResolution, 1), I=normalize(vec3(uv-0.5*r.xy, r.y)), B=vec3(1,2,9)*M;

  for(R = mat2(cos(.3*iTime+vec4(0,11,33,0))); z < 9. && d > M; z += D(p)) {
    p = z*I,
    p.z -= 2.0;
  }

  if(z < 9.0) {
    for (int i = 0; i < 3; O[i++] = D(p+r) - D(p-r)) {
      r -= r,
      r[i] = M;
    }

    z = 1.0+dot(O = normalize(O), I);
    r = reflect(I, O);
    uv = (p+r*(5.0-p.y)/abs(r.y)).xz;
    O = z*z*(r.z>0.0 ? 5e2*smoothstep(5.0, 4.0, d = sqrt(length(uv*uv))+1.0)*d*B : exp(-2.0*length(uv))*(B/M-1.0))+pow(1.0+O.y,5.0)*B;
  }

  fragColor = sqrt(O+B/G).xyzx;
}