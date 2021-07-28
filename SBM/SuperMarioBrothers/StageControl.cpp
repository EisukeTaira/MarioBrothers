#include "StageControl.h"
#include "StageControl_Config.h"

#define FRONT	(0x01U)
#define BACK	(0x02U)

static E_WorldType world_type;
static char world_view;
static T_Stage stage[MAP_HEIGHT][MAP_WIDTH];

void StageCtrl_Init(void) {
	world_type = ABOVE_GROUND;
	world_view = FRONT;

}
void StageCtrl_Update(void) {

}
void StageCtrl_Draw(void) {

}