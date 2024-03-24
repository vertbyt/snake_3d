#include "fh_math.h"
#include "math.h"

// ************
// stuff
void ease_out_quad(f32* ptr) {
	f32 t = *ptr;
	*ptr = -t*t + 2*t;
}

f32 lerp_f32(f32 a, f32 b, f32 t) { return(a + (b - a)*t); }

s32 round_f32_to_s32(f32 value) {
	s32 r = (s32)(value + 0.555f);
	return r;
}

// *******
// @vec2
Vec2 vec2(f32 x, f32 y) {
	return {x, y};
}

Vec2 vec2_from_angle(f32 angle) {
	return {cosf(angle), sinf(angle)};
}

f32 vec2_angle(Vec2 v) {
	f32 r = atan2f(v.y, v.x);
	return r;
}

f32 vec2_length(Vec2 v) { return sqrtf(v.x*v.x + v.y*v.y); }

Vec2 vec2_normalize(Vec2 v) {
	f32 l = sqrtf(v.x*v.x + v.y*v.y);
	if(l == 0.0f) return {0, 0};
	return {v.x/l, v.y/l};
}

Vec2 vec2_rotate(Vec2 v, f32 angle) {
	Vec2 r = {
		v.x*cosf(angle) - v.y*sinf(angle),
		v.x*sinf(angle) + v.y*cosf(angle)
	};
	
	return r;
}

Vec2 vec2_perp(Vec2 v) {
	Vec2 r = {v.y, -v.x};
	return r;
}


Vec2 operator+(Vec2 a, Vec2 b) { return {a.x + b.x, a.y + b.y}; }
void operator+=(Vec2 &a, Vec2 b) { a.x += b.x; a.y += b.y; }

Vec2 operator-(Vec2 a) { return {-a.x, -a.y}; }

Vec2 operator-(Vec2 a, Vec2 b) { return {a.x - b.x, a.y - b.y}; }
void operator-=(Vec2 &a, Vec2 b) { a.x -= b.x; a.y -= b.y; }

Vec2 operator*(Vec2 v, f32 s) { return {v.x*s, v.y*s}; }
Vec2 operator*(f32 s, Vec2 v) { return {v.x*s, v.y*s}; }

void operator*=(Vec2& v, f32 s) { v.x *= s; v.y *= s; }

Vec2 vec2_lerp(Vec2 a, Vec2 b, f32 t) {
	Vec2 r = a + (b - a)*t;
	return r;
}

f32 vec2_lerp_x_to_y(Vec2 v, f32 t) {
	f32 r = v.x + (v.y - v.x)*t;
	return r;
}

// *******
// @vec2i
Vec2i vec2i(s32 x, s32 y) {
	return {x, y};
}

Vec2i operator+(Vec2i a, Vec2i b) { return {a.x + b.x, a.y + b.y}; }
void operator+=(Vec2i &a, Vec2i b) { a.x += b.x; a.y += b.y; }

Vec2i operator-(Vec2i a) { return {-a.x, -a.y}; }

Vec2i operator-(Vec2i a, Vec2i b) { return {a.x - b.x, a.y - b.y}; }
void operator-=(Vec2i &a, Vec2i b) { a.x -= b.x; a.y -= b.y; }

Vec2i operator*(Vec2i v, s32 s) { return {v.x*s, v.y*s}; }
Vec2i operator*(s32 s, Vec2i v) { return {v.x*s, v.y*s}; }

void operator*=(Vec2i& v, s32 s) { v.x *= s; v.y *= s; }

// *******
// @vec3
Vec3 vec3(f32 x, f32 y, f32 z) { return {x, y, z}; }
Vec3 vec3(Vec2 v, f32 z)       { return {v.x, v.y, z}; };
Vec3 vec3(f32 x)               { return {x, x, x}; }
Vec3 vec3(Vec3i v)             { return {(f32)v.x, (f32)v.y, (f32)v.z}; }

f32 vec3_length(Vec3 v) { return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z); }

Vec3 vec3_normalize(Vec3 v) {
	f32 l = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
	if(l == 0.0f) return {0, 0, 0};
	return {v.x/l, v.y/l, v.z/l};
}

Vec3 vec3_comp_mult(Vec3 a, Vec3 b) { return {a.x*b.x, a.y*b.y, a.z*b.z}; }
f32 vec3_dot(Vec3 a, Vec3 b) { return(a.x*b.x + a.y*b.y + a.z*b.z); }

Vec3 vec3_cross(Vec3 a, Vec3 b) {
	Vec3 r = {
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
		
	};
	return r;
}

Vec3 operator+(Vec3 a, Vec3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
void operator+=(Vec3 &a, Vec3 b) { a.x += b.x; a.y += b.y; a.z += b.z; }

Vec3 operator-(Vec3 a) { return {-a.x, -a.y, -a.z}; }

Vec3 operator-(Vec3 a, Vec3 b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
void operator-=(Vec3 &a, Vec3 b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; }

Vec3 operator*(Vec3 v, f32 s) { return {v.x*s, v.y*s, v.z*s}; }
Vec3 operator*(f32 s, Vec3 v) { return {v.x*s, v.y*s, v.z*s}; }

void operator*=(Vec3& v, f32 s) { v.x *= s; v.y *= s; v.z *= s;}

// ************
// @vec3i
Vec3i vec3i(s32 x, s32 y, s32 z) { return {x, y, z}; }
Vec3i vec3i(s32 x)               { return {x, x, x}; }

Vec3i vec3i(Vec3 v) { return {(s32)v.x, (s32)v.y, (s32)v.z}; }

Vec3i operator+(Vec3i a, Vec3i b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
void operator+=(Vec3i &a, Vec3i b) { a.x += b.x; a.y += b.y; a.z += b.z; }

Vec3i operator-(Vec3i a) { return {-a.x, -a.y, -a.z}; }

Vec3i operator-(Vec3i a, Vec3i b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
void operator-=(Vec3i &a, Vec3i b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; }

bool operator==(Vec3i a, Vec3i b) {
	return(a.x == b.x && a.y == b.y && a.z == b.z);
}

// *************
// @vec4
Vec4 vec4(f32 r, f32 g, f32 b, f32 a) {
	return {r, g, b, a};
}

Vec4 vec4(Vec2 pos, Vec2 dim) {
	Vec4 r = {};
	r.pos = pos;
	r.dim = dim;
	return r;
}

Vec4 vec4(Vec3 v, f32 w) {
	Vec4 r = {v.x, v.y, v.z, w};
	return r;
}

Vec4 vec4(u32 color) {
	Vec4 c = {};
	c.r = (f32)((color >> 16)&0xFF)/255.f;
	c.g = (f32)((color >> 8)&0xFF)/255.f;
	c.b = (f32)((color >> 0)&0xFF)/255.f;
	c.a = (f32)((color >> 24)&0xFF)/255.f;
	return c;
}


Vec4 vec4_lerp(Vec4 c1, Vec4 c2, f32 t) {
	Vec4 r = {};
	r.r = c1.r + (c2.r - c1.r)*t;
	r.g = c1.g + (c2.g - c1.g)*t;
	r.b = c1.b + (c2.b - c1.b)*t;
	r.a = c1.a + (c2.a - c1.a)*t;
	return r;
}

Vec4 vec4_fade_alpha(Vec4 v, f32 a) { return {v.r, v.g, v.b, a}; }

u32 pack_color_argb(Vec4 v) {
	u32 result = 0;
	
	u32 a32 = (u32)(v.a*255.0f);
	u32 r32 = (u32)(v.r*255.0f);
	u32 g32 = (u32)(v.g*255.0f);
	u32 b32 = (u32)(v.b*255.0f);
	
	result = ((a32 << 24) | (r32 << 16) | (g32 << 8) | (b32 << 0));
	return result;
}

u32 pack_color_argb(f32 r, f32 g, f32 b, f32 a) {
	u32 result = 0;
	
	u32 a32 = (u32)(a*255.0f);
	u32 r32 = (u32)(r*255.0f);
	u32 g32 = (u32)(g*255.0f);
	u32 b32 = (u32)(b*255.0f);
	
	result = ((a32 << 24) | (r32 << 16) | (g32 << 8) | (b32 << 0));
	return result;
}


//
// @note:
// Our matrices are in row-major order.

// *******
// Mat2
Vec2 operator*(Mat2 m, Vec2 v) {
	Vec2 r = {
		v.x*m.m00 + v.y*m.m01,
		v.x*m.m10 + v.y*m.m11,
	};
	return r;
}

// ****
// Mat3
Mat3 mat3(Vec3 r, Vec3 u, Vec3 f) {
	// right, up and forward
	Mat3 m = {
		r.x, u.x, f.x,
		r.y, u.y, f.y,
		r.z, u.z, f.z
	};
	
	return m;
}

Mat3 mat3_transpose(Mat3 m) {
	Mat3 r = {
		m.m00, m.m10, m.m20,
		m.m01, m.m11, m.m21,
		m.m02, m.m12, m.m22,
	};
	
	return r;
}

Mat3 mat3_identity() {
	Mat3 r = {
		1, 0, 0, 
		0, 1, 0, 
		0, 0, 1
	};
	return r;
}

Mat3 mat3_rot_x(f32 a){
	Mat3 r = {
		1, 0,        0,      
		0, cosf(a), -sinf(a),
		0, sinf(a),  cosf(a), 
	};
	return r;
}

Mat3 mat3_rot_y(f32 a){
	Mat3 r = {
		cosf(a),  0, sinf(a), 
		0,        1, 0,      
		-sinf(a), 0, cosf(a),
	};
	return r;
}

Mat3 mat3_rot_z(f32 a){
	Mat3 r = {
		cosf(a), -sinf(a), 0,
		sinf(a),  cosf(a), 0,
		0,        0,       1,
	};
	return r;
}

Vec3 operator*(Mat3 a, Vec3 v) {
	Vec3 r = {};
	
	r.x = a.m00*v.x + a.m01*v.y + a.m02*v.z;
	r.y = a.m10*v.x + a.m11*v.y + a.m12*v.z;
	r.z = a.m20*v.x + a.m21*v.y + a.m22*v.z;
	
	return r;
}

Mat3 operator*(Mat3 a, Mat3 b) {
	Mat3 r = {};
	
	r.m00 = a.m00*b.m00 + a.m01*b.m10 + a.m02*b.m20;
	r.m01 = a.m00*b.m01 + a.m01*b.m11 + a.m02*b.m21;
	r.m02 = a.m00*b.m02 + a.m01*b.m12 + a.m02*b.m22;
	
	r.m10 = a.m10*b.m00 + a.m11*b.m10 + a.m12*b.m20;
	r.m11 = a.m10*b.m01 + a.m11*b.m11 + a.m12*b.m21;
	r.m12 = a.m10*b.m02 + a.m11*b.m12 + a.m12*b.m22;
	
	r.m20 = a.m20*b.m00 + a.m21*b.m10 + a.m22*b.m20;
	r.m21 = a.m20*b.m01 + a.m21*b.m11 + a.m22*b.m21;
	r.m22 = a.m20*b.m02 + a.m21*b.m12 + a.m22*b.m22;
	
	return r;
}

// ******
// Mat4
Mat4 mat4_identity() {
	Mat4 r = {1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1};
	return r;
}

Mat4 mat4_transpose(Mat4 m) {
	Mat4 r = {
		m.m00, m.m10, m.m20, m.m30,
		m.m01, m.m11, m.m21, m.m31,
		m.m02, m.m12, m.m22, m.m32,
		m.m03, m.m13, m.m23, m.m33,
	};
	
	return r;
}

Mat4 mat4_rot_x(f32 a){
	Mat4 r = {
		1,  0,        0,       0,
		0, cosf(a), -sinf(a), 0,
		0, sinf(a),  cosf(a), 0,
		0,  0,        0,       1,
	};
	return r;
}

Mat4 mat4_rot_y(f32 a){
	Mat4 r = {
		cosf(a),  0, sinf(a),  0,
		0,        1,  0,       0,
		-sinf(a),  0, cosf(a), 0,
		0,        0,  0,       1,
	};
	return r;
}

Mat4 mat4_rot_z(f32 a){
	Mat4 r = {
		cosf(a), -sinf(a), 0, 0,
		sinf(a),  cosf(a), 0, 0,
		0,        0,       1, 0,
		0,        0,       0, 1,
	};
	return r;
}

Mat4 mat4_perspective(f32 ar, f32 fovx, f32 n, f32 f) {
	f32 tn = tanf(fovx/2.0f);
	Mat4 r = {
		1.0f/tn, 0,      0,           0,
		0,       ar/tn,  0,           0,
		0,       0,     -(f+n)/(n-f), (2.0f*f*n)/(n-f),
		0,       0,      1,           0,
	};
	
	return r;
}

Mat4 mat4_ortho(f32 l, f32 t, f32 r, f32 b, f32 n, f32 f) {
	Mat4 rr = {
		2/(r - l), 0,         0,         -(r + l)/(r - l),
		0,        -2/(b - t), 0,          (b + t)/(b - t),
		0,         0,         2/(f - n), -(f + n)/(f - n),
		0,         0,         0,          1
	};
	
	return rr;
}

Vec4 operator*(Mat4 a, Vec4 v) {
	Vec4 r = {};
	
	r.x = a.m00*v.x + a.m01*v.y + a.m02*v.z + a.m03*v.w;
	r.y = a.m10*v.x + a.m11*v.y + a.m12*v.z + a.m13*v.w;
	r.z = a.m20*v.x + a.m21*v.y + a.m22*v.z + a.m23*v.w;
	r.w = a.m30*v.x + a.m31*v.y + a.m32*v.z + a.m33*v.w;
	
	return r;
}

Mat4 operator*(Mat4 a, Mat4 b) {
	Mat4 r = {};
	
	r.m00 = a.m00*b.m00 + a.m01*b.m10 + a.m02*b.m20 + a.m03*b.m30;
	r.m01 = a.m00*b.m01 + a.m01*b.m11 + a.m02*b.m21 + a.m03*b.m31;
	r.m02 = a.m00*b.m02 + a.m01*b.m12 + a.m02*b.m22 + a.m03*b.m32;
	r.m03 = a.m00*b.m03 + a.m01*b.m13 + a.m02*b.m23 + a.m03*b.m33;
	
	r.m10 = a.m10*b.m00 + a.m11*b.m10 + a.m12*b.m20 + a.m13*b.m30;
	r.m11 = a.m10*b.m01 + a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;
	r.m12 = a.m10*b.m02 + a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
	r.m13 = a.m10*b.m03 + a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;
	
	r.m20 = a.m20*b.m00 + a.m21*b.m10 + a.m22*b.m20 + a.m23*b.m30;
	r.m21 = a.m20*b.m01 + a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
	r.m22 = a.m20*b.m02 + a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
	r.m23 = a.m20*b.m03 + a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;
	
	r.m30 = a.m30*b.m00 + a.m31*b.m10 + a.m32*b.m20 + a.m33*b.m30;
	r.m31 = a.m30*b.m01 + a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31;
	r.m32 = a.m30*b.m02 + a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32;
	r.m33 = a.m30*b.m03 + a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33;
	
	return r;
}

// *****
// Ray
b32 ray_vs_aabb(Vec3 position, Vec3 half_extents, Vec3 ray_pos, Vec3 ray_dir, Ray_Hit* hit) {
	f32 t_smallest = 1000.0f;
	Vec3 normal = {};
	
	b32 got_hit = false;
	
	if(ray_dir.y != 0) {
		// top face
		{
			f32 t = (position.y + half_extents.y - ray_pos.y)/ray_dir.y;
			Vec3 p = ray_pos + ray_dir*t;
			if(t >= 0.0f && t < t_smallest) {
				if(FH_Abs(p.x - position.x) < half_extents.x && FH_Abs(p.z - position.z) < half_extents.z) {
					t_smallest = t;
					normal = {0, 1, 0};
					got_hit = true;
				}
			}
		};
		
		// bottom face
		{
			f32 t = (position.y - half_extents.y - ray_pos.y)/ray_dir.y;
			Vec3 p = ray_pos + ray_dir*t;
			if(t >= 0.0f && t < t_smallest) {
				if(FH_Abs(p.x - position.x) < half_extents.x && FH_Abs(p.z - position.z) < half_extents.z) {
					t_smallest = t;
					normal = {0, -1, 0};
					got_hit = true;
				}
			}
		};
	}
	
	if(ray_dir.x != 0) {
		// right face
		{
			f32 t = (position.x + half_extents.x - ray_pos.x)/ray_dir.x;
			Vec3 p = ray_pos + ray_dir*t;
			if(t >= 0.0f && t < t_smallest) {
				if(FH_Abs(p.y - position.y) < half_extents.y && FH_Abs(p.z - position.z) < half_extents.z) {
					t_smallest = t;
					normal = {1, 0, 0};
					got_hit = true;
				}
			}
		};
		
		// left face
		{
			f32 t = (position.x - half_extents.x - ray_pos.x)/ray_dir.x;
			Vec3 p = ray_pos + ray_dir*t;
			if(t >= 0.0f && t < t_smallest) {
				if(FH_Abs(p.y - position.y) < half_extents.y && FH_Abs(p.z - position.z) < half_extents.z) {
					t_smallest = t;
					normal = {-1, 0, 0};
					got_hit = true;
				}
			}
		};
	}
	
	if(ray_dir.z != 0) {
		// front face
		{
			f32 t = (position.z + half_extents.z - ray_pos.z)/ray_dir.z;
			Vec3 p = ray_pos + ray_dir*t;
			if(t >= 0.0f && t < t_smallest) {
				if(FH_Abs(p.x - position.x) < half_extents.x && FH_Abs(p.y - position.y) < half_extents.y) {
					t_smallest = t;
					normal = {0, 0, 1};
					got_hit = true;
				}
			}
		};
		
		// back face
		{
			f32 t = (position.z - half_extents.z - ray_pos.z)/ray_dir.z;
			Vec3 p = ray_pos + ray_dir*t;
			if(t >= 0.0f && t < t_smallest) {
				if(FH_Abs(p.x - position.x) < half_extents.x && FH_Abs(p.y - position.y) < half_extents.y) {
					t_smallest = t;
					normal = {0, 0, -1};
					got_hit = true;
				}
			}
		};
	}
	
	*hit = {t_smallest, normal};
	return got_hit;
}

// *****
// Camera
Mat4 camera_basis_cross(Camera3d camera) {
	Vec3 f = {};
	f.x = sinf(camera.yaw)*cosf(-camera.pitch);
	f.y = sinf(-camera.pitch);
	f.z = cosf(camera.yaw)*cosf(-camera.pitch);
	
	Vec3 r = vec3_normalize(vec3_cross(vec3(0,1,0), f));
	Vec3 u = vec3_normalize(vec3_cross(f, r));
	
	Mat4 basis = {
		r.x, u.x, f.x, 0,
		r.y, u.y, f.y, 0,
		r.z, u.z, f.z, 0,
		0,   0,   0,   1,
	};
	
	return basis;
}

Mat4 camera_view_matrix_cross(Camera3d camera) {
	Mat4 offset = {
		1,0,0, -camera.position.x,
		0,1,0, -camera.position.y,
		0,0,1, -camera.position.z,
		0,0,0, 1,
	};
	
	Mat4 result = mat4_transpose(camera_basis_cross(camera))*offset;
	return result;
}

Mat4 camera_basis(Camera3d camera) {
	Mat4 basis = mat4_rot_y(camera.yaw)*mat4_rot_x(camera.pitch);
	return basis;
}

Mat4 camera_view_matrix(Camera3d camera) {
	Mat4 offset = {
		1,0,0, -camera.position.x,
		0,1,0, -camera.position.y,
		0,0,1, -camera.position.z,
		0,0,0, 1,
	};
	
	Mat4 r = mat4_transpose(camera_basis(camera))*offset;
	return r;
}

void camera_set_rotation(Camera3d* camera, f32 yaw, f32 pitch) {
	camera->yaw = yaw;
	camera->pitch = pitch;
	
	Vec2 forw_2d = vec2_from_angle(camera->yaw);
	Vec2 right_2d = -vec2_perp(forw_2d);
	
	camera->forward_2d = vec3(forw_2d.y, 0, forw_2d.x);
	camera->right_2d   = vec3(right_2d.y, 0, right_2d.x);
}

void camera_update_target_rotation(Camera3d* camera, f32 yaw_delta, f32 pitch_delta) {
	camera->target_yaw   += yaw_delta;
	camera->target_pitch += pitch_delta;
}

void camera_lerp_rotation(Camera3d* camera, f32 lerp_speed) {
	f32 yaw   = lerp_f32(camera->yaw, camera->target_yaw, lerp_speed);
	f32 pitch = lerp_f32(camera->pitch, camera->target_pitch, lerp_speed);
	camera->yaw = yaw;
	camera->pitch = pitch;
	camera_set_rotation(camera, yaw, pitch);
}
