#ifndef REL_M401DLL_H
#define REL_M401DLL_H

#include "game/object.h"
#include "dolphin.h"

extern float camera_field_of_view;
extern float camera_near_plane;
extern float camera_far_plane;
extern s16 camera_aspect_ratio;
extern Vec camera_position;
extern Vec camera_target;
extern float camera_move_distance;
extern OMOBJ **player_objects;

typedef struct m401_player_work {
	s16 player_state;
	s32 player_index;
	s32 controller_index;
	Vec world_position;
	Vec effect_anchor_position;
	Vec target_position;
	Vec movement_origin;
	Vec reserved_vector_3c;
	OMOBJ *trail_effect;
	OMOBJ *landing_effect;
	OMOBJ *score_effect;
	OMOBJ *target_object;
	Vec movement_parameters;
	float facing_angle;
	s16 is_round_winner;
	s16 is_walking;
	s16 state_initialized;
	s16 state_timer;
	s16 reserved_state_70;
	s16 score;
	s16 score_popup_value;
	s16 reserved_state_76;
	s16 is_stunned;
	s16 stun_timer;
	s16 ai_decision_timer;
	s16 ai_behavior;
	float animation_angle;
	s16 collision_cooldown;
	s16 character_model_index;
	float jump_velocity;
	s16 run_timer;
	s16 idle_timer;
	s16 ai_input_cooldown;
	s16 ai_avoidance_flags;
	Vec reserved_vector_94;
	s8 reserved_byte_a0;
	s8 reserved_byte_a1;
} M401WorkPlayer;

typedef struct score_particle_work {
	Vec particle_position;
	OMOBJ *owner_object;
	s16 active_model_callbacks;
	s16 pool_slot_index;
	s16 fade_out_requested;
	s32 particle_variant;
	float opacity;
} ScoreParticleWork;

void show_score_gain_popup(s16 player_index);

void set_object_position(OMOBJ *object, float x, float y, float z);

void project_world_position_to_screen(Vec *world_position, Vec *screen_position);
void load_score_particle_resources(void);
void free_score_particle_resources(void);

void create_score_particle_model_pool(void);
OMOBJ *create_score_particle_effect(Vec *spawn_position, s16 particle_variant);

OMOBJ *create_particle_effect_controller(void);
OMOBJ *create_particle_model_manager(HUPROCESS *object_manager);

#endif
