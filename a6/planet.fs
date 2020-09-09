// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in;
in vec4 view_pos_fs_in;
// Outputs:
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent

vec3 normal_func(vec3 p){
	vec3 T, B;
	tangent(p, T, B);
	float eps = 0.0001;

	vec3 p1 = bump_position(is_moon, p);
	vec3 p2 = bump_position(is_moon, p + eps * T);
	vec3 p3 = bump_position(is_moon, p + eps * B);
	vec3 n = normalize(cross((p2-p1) / eps, (p3-p1) / eps));

  return dot(p, n) <= 0 ? -n: n;
}

void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  vec3 v = normalize(view_pos_fs_in.xyz / view_pos_fs_in.w);

  float ang = animation_seconds * (M_PI / 4.0);
  mat4 rotate = mat4(
  cos(ang),0,sin(ang),0,
  0,1,0,0,
  -sin(ang),0,cos(ang),0,
  0,0,0,1);
  vec3 l = (view * rotate * vec4(7, 7, 7, 1)).xyz;

  mat4 view_transform = view * model(is_moon, animation_seconds);
  vec3 normal = normalize((inverse(transpose(view_transform)) * vec4(normal_func(sphere_fs_in), 1.0)).xyz);

  vec3 ks = vec3(0.8);
  float p;
  vec3 ka, kd;

  if (is_moon) {
    ka = vec3(0.05);
    kd = vec3(0.5);
    p = 500;
  } else {
    p = 1000;
    float height = bump_height(is_moon, sphere_fs_in);
    if (height <= .001 && .5 * sphere_fs_in.z / animation_seconds <= 0.1 && animation_seconds > .5){
      ka = vec3(0.01, 0.02, 0.05);
      kd = vec3(0.2, 0.3, 0.8);
      ks = vec3(0.8, 0.8, 0.8);
    } else {
     ka = vec3(0.01, 0.01, 0.01);
     kd = vec3(1.2 * (1 - abs(sphere_fs_in.y)), 1, .2);
     ks = vec3(0.3, 0.3, 0.3);
    }
  }
  color = blinn_phong(ka, kd, ks, p, normal, v, l);

  /////////////////////////////////////////////////////////////////////////////
}
