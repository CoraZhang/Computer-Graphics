// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
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
// expects: PI, blinn_phong
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
  vec3 n = normalize(normal_fs_in);

  float p;
  vec3 ka, kd, ks;
  if (is_moon) {
    p = 200;
    ka = vec3(0.05);
    kd = vec3(0.5);
    ks = vec3(1.0);
  } else {
    p = 1000;
    ka = vec3(0.03, 0.03, 0.06);
    kd = vec3(0.2, 0.2, 0.8);
    ks = vec3(1.0);
  }
  color = blinn_phong(ka, kd, ks, p, n, v, l);
  /////////////////////////////////////////////////////////////////////////////
}
