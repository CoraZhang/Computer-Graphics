// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec3 i = floor(st);
  vec3 f = fract(st);

  vec3 c1 = i;
  vec3 c2 = vec3(1 + i.x, i.y, i.z);
  vec3 c3 = vec3(i.x, 1 + i.y, i.z);
  vec3 c4 = vec3(i.x, i.y, 1 + i.z);
  vec3 c5 = vec3(1 + i.x, 1 + i.y, i.z);
  vec3 c6 = vec3(1 + i.x, i.y, 1 + i.z);
  vec3 c7 = vec3(i.x, 1 + i.y, 1 + i.z);
  vec3 c8 = vec3(1 + i.x, 1 + i.y, 1 + i.z);

  vec3 g1 = random_direction(c1);
  vec3 g2 = random_direction(c2);
  vec3 g3 = random_direction(c3);
  vec3 g4 = random_direction(c4);
  vec3 g5 = random_direction(c5);
  vec3 g6 = random_direction(c6);
  vec3 g7 = random_direction(c7);
  vec3 g8 = random_direction(c8);

  vec3 d1 = f;
  vec3 d2 = vec3(1 - f.x, f.y, f.z);
  vec3 d3 = vec3(f.x, 1 - f.y, f.z);
  vec3 d4 = vec3(1 + f.x, f.y, 1 - f.z);
  vec3 d5 = vec3(1 - f.x, 1 - f.y, f.z);
  vec3 d6 = vec3(1 - f.x, f.y, 1 - f.z);
  vec3 d7 = vec3(f.x, 1 - f.y, 1 - f.z);
  vec3 d8 = f - vec3(1);

  float r1 = dot(g1, d1);
  float r2 = dot(g2, d2);
  float r3 = dot(g3, d3);
  float r4 = dot(g4, d4);
  float r5 = dot(g5, d5);
  float r6 = dot(g6, d6);
  float r7 = dot(g7, d7);
  float r8 = dot(g8, d8);

  vec3 smoothed = improved_smooth_step(f);

  float ip1x = mix(r1, r2, smoothed.x);
  float ip2x = mix(r3, r4, smoothed.x);
  float ip3x = mix(r5, r6, smoothed.x);
  float ip4x = mix(r7, r8, smoothed.x);
  float ip1y = mix(ip1x, ip2x, smoothed.y);
  float ip2y = mix(ip3x, ip4x, smoothed.y);
  float ip1z = mix(ip1y, ip2y, smoothed.z);

  return ip1z - 0.5;
  /////////////////////////////////////////////////////////////////////////////
}

