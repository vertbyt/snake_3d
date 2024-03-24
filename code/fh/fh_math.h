
#ifndef FH_MATH_H
#define FH_MATH_H

#include "fh_base.h"

#define Pi32 3.141592

#define ToRadians(x) (((x)*Pi32)/180.0)
#define ToDegrees(x) (((x)*180.0)/Pi32)

void ease_out_quad(f32* ptr);
f32 lerp_f32(f32 a, f32 b, f32 t);
s32 round_f32_to_s32(f32 value);

// @vec2
struct Vec2 {
	union {
		struct { f32 x, y; };
		struct { f32 width, height; };
		struct { f32 min, max; };
	};
};

Vec2 vec2(f32 x, f32 y);
Vec2 vec2_from_angle(f32 angle);

f32  vec2_angle(Vec2 v);
f32  vec2_length(Vec2 v);
Vec2 vec2_normalize(Vec2 v);
Vec2 vec2_rotate(Vec2 v, f32 angle);
Vec2 vec2_perp(Vec2 v);


Vec2 vec2_lerp(Vec2 a, Vec2 b, f32 t);
f32 vec2_lerp_x_to_y(Vec2 v, f32 t);

Vec2 operator+(Vec2 a, Vec2 b);
void operator+=(Vec2 &a, Vec2 b);

Vec2 operator-(Vec2 a);

Vec2 operator-(Vec2 a, Vec2 b);
void operator-=(Vec2 &a, Vec2 b);

Vec2 operator*(Vec2 v, f32 s);
Vec2 operator*(f32 s, Vec2 v);

void operator*=(Vec2& v, f32 s);

// @vec2i
struct Vec2i {
	union {
		struct { s32 x, y; };
		struct { s32 width, height; };
		struct { s32 min, max; };
	};
};

Vec2i vec2i(s32 x, s32 y);

Vec2i operator+(Vec2i a, Vec2i b);
void operator+=(Vec2i &a, Vec2i b);

Vec2i operator-(Vec2i a);

Vec2i operator-(Vec2i a, Vec2i b);
void operator-=(Vec2i &a, Vec2i b);

Vec2i operator*(Vec2i v, s32 s);
Vec2i operator*(s32 s, Vec2i v);

void operator*=(Vec2i& v, s32 s);

// **********
// @vec3
struct Vec3 {
	f32 x, y, z;
};

Vec3 vec3(f32 x, f32 y, f32 z);
Vec3 vec3(Vec2 v, f32 z);
Vec3 vec3(f32 x);
Vec3 vec3(struct Vec3i v);

f32  vec3_length(Vec3 v);
Vec3 vec3_normalize(Vec3 v);

f32  vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec3 vec3_comp_mult(Vec3 a, Vec3 b);

Vec3 operator+(Vec3 a, Vec3 b);
void operator+=(Vec3 &a, Vec3 b);

Vec3 operator-(Vec3 a);

Vec3 operator-(Vec3 a, Vec3 b);
void operator-=(Vec3 &a, Vec3 b);

Vec3 operator*(Vec3 v, f32 s);
Vec3 operator*(f32 s, Vec3 v);

void operator*=(Vec3& v, f32 s);

//*************
// @vec3i
struct Vec3i {
	s32 x, y, z;
};

Vec3i vec3i(s32 x, s32 y, s32 z);
Vec3i vec3i(s32 x);
Vec3i vec3i(Vec3 v);

Vec3i operator+(Vec3i a, Vec3i b);
void operator+=(Vec3i &a, Vec3i b);

Vec3i operator-(Vec3i a);

Vec3i operator-(Vec3i a, Vec3i b);
void operator-=(Vec3i &a, Vec3i b);

bool operator==(Vec3i a, Vec3i b);


//*************
// @vec4
struct Vec4 {
	union{
		struct { f32 x, y, z, w; };
		//struct { f32 x, y, width, height; };
		struct { f32 top, left, bottom, right; };
		struct { Vec2 pos, dim;  };
		struct { Vec3 rgb; f32 ignored_a; };
		struct { Vec3 xyz; f32 ignored_w; };
		
		struct { f32 r, g, b, a; };
	};
};


Vec4 vec4(f32 r, f32 g, f32 b, f32 a);
Vec4 vec4(Vec2 pos, Vec2 dim);
Vec4 vec4(Vec3 v, f32 w);
Vec4 vec4(u32 color);

Vec4 vec4_lerp(Vec4 c1, Vec4 c2, f32 t);
Vec4 vec4_fade_alpha(Vec4 v, f32 a);
u32  pack_color_argb(Vec4 v);
u32  pack_color_argb(f32 r, f32 g, f32 b, f32 a);

// *********
// @vec4i
struct Vec4i {
	union{
		struct { s32 x, y, z, w; };
		//struct { s32 x, y, width, height; };
		struct { s32 top, left, bottom, right; };
	};
};

// @note:
// Our matrices are in row-major order.

// *****
// @mat2
struct Mat2 {
	union {
		struct {
			f32 m00, m01;
			f32 m10, m11;
		};
		f32 m[4];
	};
};

Vec2 operator*(Mat2 m, Vec2 v);

// *********
// @mat4
struct Mat3 {
	union {
		struct {
			f32 m00, m01, m02;
			f32 m10, m11, m12;
			f32 m20, m21, m22;
		};
		f32 m[9];
	};
};


Mat3 mat3(Vec3 r, Vec3 u, Vec3 f);
Mat3 mat3_identity();

Mat3 mat3_transpose(Mat3 m);

Mat3 mat3_rot_x(f32 a);
Mat3 mat3_rot_y(f32 a);
Mat3 mat3_rot_z(f32 a);

Vec3 operator*(Mat3 a, Vec3 v);
Mat3 operator*(Mat3 a, Mat3 b);

// *********
// @mat4
struct Mat4 {
	union {
		struct {
			f32 m00, m01, m02, m03;
			f32 m10, m11, m12, m13;
			f32 m20, m21, m22, m23;
			f32 m30, m31, m32, m33;
		};
		f32 m[16];
	};
};


Mat4 mat4_identity();
Mat4 mat4_tranpose();

Mat4 mat4_rot_x(f32 a);
Mat4 mat4_rot_y(f32 a);
Mat4 mat4_rot_z(f32 a);

Mat4 mat4_ortho(f32 l, f32 t, f32 r, f32 b, f32 n, f32 f);
Mat4 mat4_perspective(f32 ar, f32 fovx, f32 n, f32 f);

Vec4 operator*(Mat4 a, Vec4 v);
Mat4 operator*(Mat4 a, Mat4 b);

// *****
// ray
struct Ray_Hit {
	f32 t;
	Vec3 normal;
};

b32 ray_vs_aabb(Vec3 position, Vec3 half_extents, Vec3 ray_pos, Vec3 ray_dir, Ray_Hit* hit);


// ***************
// @camera
struct Camera3d {
	Vec3 position;
	Vec3 forward_2d, right_2d;
	
	f32 yaw, pitch;
	f32 target_yaw, target_pitch;
};

Mat4 camera3d_basis(Camera3d camera);
Mat4 camera3d_view_matrix(Camera3d camera);

Mat4 camera3d_basis_cross(Camera3d camera);
Mat4 camera3d_view_matrix_cross(Camera3d camera);

void camera3d_set_rotation(Camera3d* camera, f32 yaw, f32 pitch);
void camera3d_update_target_rotation(Camera3d* camera, f32 yaw, f32 pitch);
void camera3d_lerp_rotation(Camera3d* camera, f32 lerp_speed);

#endif

