#ifndef UNIT_H
#define UNIT_H

#include "random.h"
#include "map.h"
#include "unit_move_behavior.h"
#include <memory>

const int FACING_RIGHT = 0;
const int FACING_UP_RIGHT = 1;
const int FACING_UP = 2;
const int FACING_LEFT_UP = 3;
const int FACING_LEFT = 4;
const int FACING_DOWN_LEFT = 5;
const int FACING_DOWN = 6;
const int FACING_RIGHT_DOWN = 7;
const int FACINGS = 8;          // used to calculate width of each 'tile' for a unit given a tilset

const int SUBCELL_UPLEFT = 1;
const int SUBCELL_UPRIGHT = 2;
const int SUBCELL_CENTER = 3;
const int SUBCELL_DOWNLEFT = 4;
const int SUBCELL_DOWNRIGHT = 5;

class Unit : public sf::Drawable
{

  public:
    Unit(const Map& map, UnitMoveBehavior* move_behavior, int world_x, int world_y, int view_range, int sub_cell);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void updateState();

    //void order_move(sf::Vector2i target);

    //const Player& getOwner() const;

    void select();
    void unselect();
    bool is_selected();
//    //bool is_within(const Rectangle& rectangle);
//    bool is_on_air_layer();
//    bool is_on_ground_layer();
    //bool is_point_within(const Point& point);

  private:
    sf::Vector2f target;            // target of interest (move/attack, etc)
    sf::Vector2f position;          // coordinates relative to top/left of map (in pixels)
    sf::Vector2f sub_position;
    sf::Vector2f next_move_position;
    sf::Vector2f next_move_direction;
    sf::Vector2f prev_position;

    sf::Vector2i tile_size;
    sf::Vector2i unit_size;

    //Player* owner; //player who owns the unit

    int shadow_alpha;       // how transparant is the shadow being drawn (0 = invisible, 256 is solid)
    int anim_frame;         // animation frames are 'rows' in the tileset
    int offset_x, offset_y; // the offset from the tile respective up-left corner
    int view_range;
    int body_facing;        // facing, 8 directions. Clock-wise. ie: 0 (up), 1 (up-right), 2 (right), etc;
    int desired_body_facing;

    bool selected;

    bool is_infantry;

    Map* map;
    std::shared_ptr<UnitMoveBehavior> move_behavior;

    void init(Map *map, int world_x, int world_y, int view_range, UnitMoveBehavior* move_behavior, int sub_cell);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void turn_body();
    void updateMovePosition(sf::Vector2i p);

    int  desired_facing();
    bool is_moving();
    bool has_target();
    bool should_turn_body();
    void stopMoving();

    int  getDrawX();
    int  getDrawY();

    bool isOnLayer(short layer);
};


const int UNIT_QUAD = 0;
const int UNIT_TRIKE = 1;
const int UNIT_DEVASTATOR = 2;
const int UNIT_CARRYALL = 3;
const int UNIT_FRIGATE = 4;
const int UNIT_SOLDIER = 5;
const int MAX_UNIT_TYPES = 16;


class UnitRepository {

  public:
    UnitRepository(Map *map);
    ~UnitRepository();

    void destroy();

    Unit* create(int unitType, int x, int y, int view_range, int sub_cell);

   private:
      Map* map;

      // several unit behaviors
      AirUnitMoveBehavior*    air_unit_move_behavior;
      GroundUnitMoveBehavior* ground_unit_move_behavior;
      FootUnitMoveBehavior*   foot_unit_move_behavior;
};

#endif
