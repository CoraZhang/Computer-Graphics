// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  T = normalize(cross(vec3(1, 0, 0), N));
  if (T == vec3(0)) {
    T = normalize(cross(vec3(0, 1, 0), N));
  }

  B = normalize(cross(N, T));
  /////////////////////////////////////////////////////////////////////////////
}
