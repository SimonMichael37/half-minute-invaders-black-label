#pragma once

void title_init(void);
void title_deinit(void);
bool title_update(float dt);
void title_draw(void);
void title_setup(void);

void gameplay_init(void);
void gameplay_deinit(void);
bool gameplay_update(float dt);
void gameplay_draw(void);
void update_score_text(int new_score);
void update_duration_text(int new_duration);

void end_init(void);
void end_deinit(void);
void end_setup(int final_score, bool is_dead);
bool end_update(float dt);
void end_draw(void);
