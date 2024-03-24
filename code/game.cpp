//
// Our and raylib math types conversion
// 
Vec3 vec3_from_rlvec3(Vector3 v) { return {v.x, v.y, v.z}; }
Vector3 rlvec3(Vec3 v) { return {v.x, v.y, v.z}; }

//
// Model functions
// 
void model_scale_and_center(Model* model) {
	BoundingBox bb = GetModelBoundingBox(*model);
	Vec3 min = vec3_from_rlvec3(bb.min);
	Vec3 max = vec3_from_rlvec3(bb.max);
	
	Vec3 size = max - min;
	f32 max_dim = FH_Max(size.x, FH_Max(size.y, size.z));
	f32 scale = 2.0f/max_dim;

	Vec3 offset = (-min - size*0.5f)*scale;
	
	Matrix scale_mat = MatrixScale(scale, scale, scale);
	Matrix trans_mat = MatrixTranslate(offset.x, offset.y, offset.z);
	Matrix transform = MatrixMultiply(scale_mat, trans_mat);
	
	model->transform = transform;
}

void model_scale_and_root(Model* model) {
	BoundingBox bb = GetModelBoundingBox(*model);
	Vec3 min = vec3_from_rlvec3(bb.min);
	Vec3 max = vec3_from_rlvec3(bb.max);
	
	Vec3 size = max - min;
	f32 max_dim = FH_Max(size.x, FH_Max(size.y, size.z));
	f32 scale = 2.0f/max_dim;
	
	Vec3 offset = (-min - vec3(size.x, 0, size.z)*0.5f)*scale;
	
	Matrix scale_mat = MatrixScale(scale, scale, scale);
	Matrix trans_mat = MatrixTranslate(offset.x, offset.y, offset.z);
	Matrix transform = MatrixMultiply(scale_mat, trans_mat);
	
	model->transform = transform;
}

void model_set_material_shader(Model* model, Shader shader) {
	Loop(i, model->materialCount) {
		Material* mat = &model->materials[i];
		mat->shader = shader;
	}
}

void draw_text_line(Font font, char* text, f32 y) {
	Vector2 text_center_pos = {(f32)GetScreenWidth()/2, y};
	
	Vector2 text_dim          = MeasureTextEx(font, text,font.baseSize, 0);
	Vector2 text_top_left_pos = Vector2Subtract(text_center_pos, Vector2Scale(text_dim, 0.5f));
	
	DrawTextEx(font, text, text_top_left_pos, font.baseSize, 0, WHITE);
}




#define PLAY_AREA_SIZE     7

#define MOVE_TICK 0.325f

#define SNAKE_BODY_COLOR {0xAA, 0, 0, 0xFF}
#define SNAKE_HEAD_COLOR {0xDD, 0, 0, 0xFF}

#define SNAKE_BODY_SCALE 1.01f
#define SNAKE_HEAD_SCALE 1.02f

enum Game_State {
	Game_State_Wait_For_Input,
	Game_State_Move,
	Game_State_Death,
};

enum Move_Result {
	Move_Result_Ok,
	Move_Result_Food,
	Move_Result_Death
};


Game_State game_state;

f32 snake_move_time;

Vec3 snake_move_dir;
Vec3 snake_new_move_dir;

Vec3 snake_segments[1024];
s32 snake_segments_count;
b32 snake_got_food;

Vec3 food_pos;

Camera3D camera;

// Resources
Shader shader;

Font font_karmina;

Model ground_model;
Model border_model;
Model apple_model;


//
// Food!!!!
//
void food_spawn() {
	Loop(i, 100) {
		s32 rx = GetRandomValue(-(PLAY_AREA_SIZE/2 - 1), PLAY_AREA_SIZE/2 - 1);
		s32 rz = GetRandomValue(-(PLAY_AREA_SIZE/2 - 1), PLAY_AREA_SIZE/2 - 1);
		
		b32 at_origin = (rx == 0 && rz == 0);
		if(at_origin) continue;
		
		b32 not_in_snake = true;
		Loop(i, snake_segments_count) {
			Vec3i pos = {rx, 1, rz};
			Vec3i seg = vec3i(snake_segments[i]);
			
			if(pos == seg) {
				not_in_snake = false;
				break;
			}
		}
		
		if(not_in_snake) { 
			food_pos = vec3(rx, 1, rz);
			break;
		}
	}
}

//
// Game init
//
void game_init() {
	InitWindow(1280, 720, "snake_3d");
	SetTargetFPS(60);

	shader = LoadShader("shaders/vert.glsl", "shaders/frag.glsl");
	
	font_karmina = LoadFontEx("font/karmina.ttf", 32, 0, 0);
	
	camera = {};
	camera.position = { 0.0f, 15.0f, 5.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	
	
	apple_model = LoadModel("models/apple.glb");
	model_scale_and_center(&apple_model);
	model_set_material_shader(&apple_model, shader);
	
	ground_model = LoadModel("models/blockRounded.glb");
	model_scale_and_center(&ground_model);
	model_set_material_shader(&ground_model, shader);
	
	border_model = LoadModel("models/rocks.glb");
	model_scale_and_root(&border_model);
	model_set_material_shader(&border_model, shader);
	
	game_state = Game_State_Wait_For_Input;
	
	snake_segments_count = 5;
	Loop(i, snake_segments_count) snake_segments[i] = { 0, 1, 0 };

	snake_move_time = 0.0f;
	snake_move_dir = {};
	
	food_spawn();
}


b32 snake_wait_for_input() {
	Vec3 dir = {};
	if(IsKeyPressed(KEY_UP))    dir.z = -1;
	if(IsKeyPressed(KEY_DOWN))  dir.z =  1;
	if(IsKeyPressed(KEY_LEFT))  dir.x = -1;
	if(IsKeyPressed(KEY_RIGHT)) dir.x =  1;
	
	b32 got_dir_in_one_dimension = (dir.x != 0.0f || dir.z != 0.0f) && (dir.x == 0.0f || dir.z == 0.0f);
	if(got_dir_in_one_dimension) {
		snake_move_dir = dir;
		snake_new_move_dir = dir;
		return true;
	}
	
	return false;
}

void snake_get_input_while_moving() {
	Vec3 dir = {};
	if(IsKeyPressed(KEY_UP))    dir.z = -1;
	if(IsKeyPressed(KEY_DOWN))  dir.z =  1;
	if(IsKeyPressed(KEY_LEFT))  dir.x = -1;
	if(IsKeyPressed(KEY_RIGHT)) dir.x =  1;
	
	b32 got_dir_in_one_dimension = (dir.x != 0.0f || dir.z != 0.0f) && (dir.x == 0.0f || dir.z == 0.0f);
	b32 not_going_back_into_self = (FH_Abs(vec3_dot(dir, snake_move_dir)) < 0.001f);
	if(got_dir_in_one_dimension && not_going_back_into_self) {
		snake_new_move_dir = dir;
	}
}

void snake_fake_move() {
	snake_move_time += GetFrameTime();
}

void snake_actualy_move() {
	Loop(i, snake_segments_count) {
		snake_segments[snake_segments_count - i] = snake_segments[snake_segments_count - i - 1];
	}
	snake_segments[0] += snake_move_dir;

	snake_move_time = 0.0f;
}

b32 snake_grow_if_eaten() {
	if(snake_got_food) {
		snake_got_food = false;
		snake_segments_count += 1;
		return true;
	}
	
	return false;
}

b32 snake_movement_to_tile_compleated() {
	b32 complete = snake_move_time > MOVE_TICK;
	return complete;
}

Move_Result snake_consider_next_move() {
	snake_move_dir = snake_new_move_dir;
	
	Vec3 new_head_pos = snake_segments[0] + snake_move_dir;
	
	b32 hit_border_x = (FH_Abs(new_head_pos.x) > (PLAY_AREA_SIZE/2 - 1));
	b32 hit_border_z = (FH_Abs(new_head_pos.z) > (PLAY_AREA_SIZE/2 - 1));
	b32 hit_border   = hit_border_x || hit_border_z;
	
	b32 hit_self = false;
	Loop(i, snake_segments_count) {
		if(i == 0) continue;
		
		Vec3i seg  = vec3i(snake_segments[i]);
		Vec3i head = vec3i(new_head_pos);
		
		if(seg == head) {
			hit_self = true;
			break;
		}
	}
	
	b32 should_die = hit_border || hit_self;
	b32 got_food = (vec3i(new_head_pos) == vec3i(food_pos));

	if(should_die) return Move_Result_Death;
	if(got_food)   return Move_Result_Food;
	
	return Move_Result_Ok;
}

void snake_prepare_to_grow() {
	snake_got_food = true;
}

void snake_revive() {
	snake_segments_count = 5;
	Loop(i, 5) snake_segments[i] = {0, 1, 0};
}

//
// Game update.
//
void game_update() {
	switch(game_state) {
		case Game_State_Wait_For_Input: {
			b32 got_input = snake_wait_for_input();
			
			if(got_input) game_state = Game_State_Move;
		}break;
		case Game_State_Move: {
			snake_get_input_while_moving();
			
			snake_fake_move();
			if(snake_movement_to_tile_compleated()) {
				snake_actualy_move();
				if(snake_grow_if_eaten()) food_spawn();
				
				Move_Result next_move = snake_consider_next_move();
				if(next_move == Move_Result_Food)  snake_prepare_to_grow();
				if(next_move == Move_Result_Death) game_state = Game_State_Death;
			}
		}break;
		case Game_State_Death: {
			if(IsKeyPressed(KEY_ENTER)) {
				snake_revive();
				game_state = Game_State_Wait_For_Input;
			}
		}break;
	}
	
}

//
// Game Rener
//

void snake_draw_moving() {
	f32 move_t = snake_move_time/(f32)MOVE_TICK;
	
	Vec3 dir      = snake_move_dir;
	Vec3 prev_dir = dir;
	
	Loop(i, snake_segments_count) {
		Color col = SNAKE_HEAD_COLOR;
		f32 scale = SNAKE_HEAD_SCALE;
		
		prev_dir = dir;
		
		b32 is_body = (i > 0);
		if(is_body) {
			col   = SNAKE_BODY_COLOR;
			scale = SNAKE_BODY_SCALE;
			dir   = snake_segments[i - 1] - snake_segments[i];
		}
		
		b32 should_fill_up_body_turn = FH_Abs(vec3_dot(prev_dir, dir)) < 0.01f;
		if(should_fill_up_body_turn) {
			DrawCube(rlvec3(snake_segments[i - 1]), scale, scale, scale, col);
		}
		
		Vec3 pos = snake_segments[i] + dir*move_t;
		DrawCube(rlvec3(pos), scale, scale, scale, col);
	}
}


void snake_draw_eating() {
	// Immovable body
	Loop(i, snake_segments_count) {
		Vec3 pos = snake_segments[i];
		f32 s = SNAKE_BODY_SCALE;
		DrawCube(rlvec3(pos), s, s, s, SNAKE_BODY_COLOR);
	}
	
	// Head only moving
	f32 move_t = snake_move_time/(f32)MOVE_TICK;
	f32 s = SNAKE_HEAD_SCALE;
	DrawCube(rlvec3(snake_segments[0] + move_t*snake_move_dir), s, s, s, SNAKE_HEAD_COLOR);
}

void snake_draw() {
	if(snake_got_food) snake_draw_eating();
	else               snake_draw_moving();
}

void play_area_draw() {
	Vec3 offset_for_centering = vec3(-(s32)PLAY_AREA_SIZE/2, 0, -(s32)PLAY_AREA_SIZE/2);
	
	Loop(x, PLAY_AREA_SIZE) {
		Loop(z, PLAY_AREA_SIZE) {
			b32 on_border_x = (x == 0 || x == PLAY_AREA_SIZE - 1);
			b32 on_border_z = (z == 0 || z == PLAY_AREA_SIZE - 1);
			b32 on_border   = (on_border_x || on_border_z);
			
			Vec3 ground_pos = vec3(x, 0, z) + offset_for_centering;
			DrawModel(ground_model, rlvec3(ground_pos), 0.5f, WHITE);
			
			if(on_border) {
				Vec3 border_pos = vec3(x, 0.5f, z) + offset_for_centering;
				DrawModel(border_model, rlvec3(border_pos), 0.5f, WHITE);
			}
		}
	}
}

void apple_draw() {
	DrawModel(apple_model, rlvec3(food_pos), 0.45f, WHITE);
}

void info_text_draw() {
	if(game_state == Game_State_Death) {
		char* text = "Sneak Dead. Press ENTER to play again...";
		draw_text_line(font_karmina, text, GetScreenHeight() - 50);
	}
	else if(game_state == Game_State_Wait_For_Input) {
		char* text = "Arrow keys to move...";
		draw_text_line(font_karmina, text, GetScreenHeight() - 50);
	}
}

void score_text_draw() {
	char* text = (char*)TextFormat("Score: %d", snake_segments_count);
	draw_text_line(font_karmina, text, 50);
}

void game_render() {
	BeginDrawing();	
	ClearBackground({0x22, 0x22, 0x22, 0xFF});
	
	// 3d 
	BeginMode3D(camera);
	
	play_area_draw();
	snake_draw();
	apple_draw();

	EndMode3D();

	// 2d
	info_text_draw();
	score_text_draw();
	
	EndDrawing();
}

//
// Game Loop
//
void game_loop() {
	game_update();
	game_render();
}