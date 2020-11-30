from typing import List
from OrodaelTurrim.Business.Interface.Player import PlayerTag
from OrodaelTurrim.Business.Proxy import MapProxy, GameObjectProxy, GameUncertaintyProxy
from ExpertSystem.Business.UserFramework import IKnowledgeBase
from ExpertSystem.Structure.RuleBase import Fact
from OrodaelTurrim.Structure.Enums import TerrainType, AttributeType, EffectType, GameRole
from OrodaelTurrim.Structure.Position import OffsetPosition, CubicPosition, AxialPosition


class KnowledgeBase(IKnowledgeBase):
    """
    Class for defining known facts based on Proxy information. You can transform here any information from
    proxy to better format of Facts. Important is method `create_knowledge_base()`. Return value of this method
    will be passed to `Inference.interfere`. It is recommended to use Fact class but you can use another type.

    |
    |
    | Class provides attributes:

    - **map_proxy [MapProxy]** - Proxy for access to map information
    - **game_object_proxy [GameObjectProxy]** - Proxy for access to all game object information
    - **uncertainty_proxy [UncertaintyProxy]** - Proxy for access to all uncertainty information in game
    - **player [PlayerTag]** - class that serve as instance of user player for identification in proxy methods

    """
    map_proxy: MapProxy
    game_object_proxy: GameObjectProxy
    game_uncertainty_proxy: GameUncertaintyProxy
    player: PlayerTag

    def __init__(self, map_proxy: MapProxy, game_object_proxy: GameObjectProxy,
                 game_uncertainty_proxy: GameUncertaintyProxy, player: PlayerTag):
        """
        You can add some code to __init__ function, but don't change the signature. You cannot initialize
        KnowledgeBase class manually so, it is make no sense to change signature.
        """
        super().__init__(map_proxy, game_object_proxy, game_uncertainty_proxy, player)

    def create_knowledge_base(self) -> List[Fact]:
        """
        Method for create user knowledge base. You can also have other class methods, but entry point must be this
        function. Don't change the signature of the method, you can change return value, but it is not recommended.

        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        !!  TODO: Write implementation of your knowledge base definition HERE   !!
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        """

        facts = []

        # Add bool fact
        # Add fact with data holder
        # We can use there eval function same as data function
        # because if first_free_tile return None, bool value of None is False, otherwise bool value is True
        # You can use different functions for eval and data
        facts.append(Fact('free_tile', eval_function=self.first_free_tile, data=self.first_free_tile))
        facts.append(Fact('visible_free_tile', eval_function=self.visible_free_tile, data=self.visible_free_tile))
        facts.append(Fact('border_patrol_tile', eval_function=self.border_patrol_tile, data=self.border_patrol_tile))
        facts.append(Fact('border_patrol_count', eval_function=self.border_patrol_count, data=self.border_patrol_count))
        facts.append(Fact('border_patrol_equality', lambda x, y: self.border_patrol_equality(x, y)))
        facts.append(Fact('terrain', lambda x, y: self.get_terrain_type(x, y)))
        facts.append(Fact('have_enough_money', lambda x: self.have_enough_money(x)))
        facts.append(Fact('test_rule', lambda x, y: self.test_rule(x, y)))
        facts.append(Fact('can_place_unit', lambda x, y: self.can_place_unit(x, y)))
        facts.append(Fact('can_place_unit_n', lambda x: self.can_place_unit_n(x)))
        facts.append(Fact('first_round', lambda: self.first_round()))
        facts.append(Fact('not_first_round', lambda: self.not_first_round()))
        facts.append(Fact('base_guards', lambda: self.base_guards()))
        facts.append(Fact('not_base_guards', lambda: self.not_base_guards()))
        facts.append(Fact('player_dont_have_base', lambda: not self.map_proxy.player_have_base(self.player)))
        facts.append(Fact('base_guards_count', lambda: self.base_guards_count()))
        facts.append(Fact('guards_patrol_eq', lambda: self.guards_patrol_eq()))
        facts.append(Fact("kings_guard", lambda: self.kings_guard()))
        facts.append(Fact('best_tile', eval_function=self.best_tile, data=self.best_tile))

        facts.append(Fact("money", lambda: self.game_object_proxy.get_resources(self.player)))

        facts.append(Fact('enemies_from_left', lambda: self.enemies_from('left'), probability=self.enemies_from('left')))
        facts.append(Fact('enemies_from_right', lambda: self.enemies_from('right'), probability=self.enemies_from('right')))
        facts.append(Fact('enemies_from_top', lambda: self.enemies_from('top'), probability=self.enemies_from('top')))
        facts.append(Fact('enemies_from_bottom', lambda: self.enemies_from('bottom'), probability=self.enemies_from('bottom')))
        facts.append(Fact('base_defense_tile', eval_function=self.base_defense_tile, data=self.base_defense_tile))
        facts.append(Fact('base_defense_tile2', eval_function=self.base_defense_tile2, data=self.base_defense_tile2))
        facts.append(Fact('tile_from_base', eval_function=self.tile_from_base, data=self.tile_from_base))
        return facts

    def test_rule(self, x, y):
        """x = self.game_uncertainty_proxy.spawn_information()
        for y in x:
            for z in y:
                for p in z.positions:
                    print(p)
                print(z.game_object_type)"""
        print(self.get_terrain_type(x, y))
        self.best_tile()
        return True

    def enemies_from(self, side: str) -> float:
        spawn_info = self.game_uncertainty_proxy.spawn_information()[0]
        count = 0
        direction = 0
        enemy_count = len(spawn_info)

        if side == "left":
            direction = -6
        elif side == "right":
            direction = 6
        elif side == "top":
            enemy_side = 0
            enemy_other = 0
            direction = -6
        elif side == "bottom":
            enemy_side = 0
            enemy_other = 0
            direction = 6

        for unit in spawn_info:
            for tile in unit.positions:
                if side in {"left", "right"}:
                    if tile.position.offset.q == direction:
                        count += 1
                        break
                elif side in {"top", "bottom"}:
                    if tile.position.offset.r == direction:
                        enemy_side += 1
                    elif tile.position.offset.r == -direction:
                        enemy_other += 1

        if side in {"top", "bottom"}:
            if enemy_side >= enemy_other:
                return 1
            return 0

        res = count / enemy_count
        print(f'Enemies from {side}')
        print(f'Count: {count} and total: {enemy_count} then res: {res}')
        return res

    def first_round(self):
        if self.game_object_proxy.get_current_round() == 0:
            return True
        else:
            return False

    def not_first_round(self):
        if self.game_object_proxy.get_current_round() != 0:
            return True
        else:
            return False

    def first_free_tile(self, terrain_type: str):
        """ Find random tile with given terrain type """
        tiles = self.map_proxy.get_inner_tiles()
        border_tiles = self.map_proxy.get_border_tiles()

        for position in tiles:
            terrain = self.map_proxy.get_terrain_type(position) == TerrainType.from_string(terrain_type)
            if terrain and position not in border_tiles:
                return position
        return None

    def best_tile(self):
        tiles = self.map_proxy.get_inner_tiles()
        border_tiles = self.map_proxy.get_border_tiles()
        tilez = []
        for tile in tiles:
            neigh = tile.get_all_neighbours()
            strength = 0
            for t1le in neigh:
                if self.map_proxy.get_terrain_type(t1le) == TerrainType.VILLAGE:
                    strength += 0.15
                if self.map_proxy.get_terrain_type(t1le) == TerrainType.FOREST:
                    strength += 0.15
                if self.map_proxy.get_terrain_type(t1le) == TerrainType.HILL:
                    strength += 0.2
                if self.map_proxy.get_terrain_type(t1le) == TerrainType.FIELD:
                    strength += 0.05
                if self.map_proxy.get_terrain_type(t1le) == TerrainType.MOUNTAIN:
                    strength -= 0.3
                if self.map_proxy.get_terrain_type(t1le) == TerrainType.RIVER:
                    strength -= 0.2
                if t1le in border_tiles:
                    strength -= 100
                neigh_of_t1le = t1le.get_all_neighbours()
                for t2le in neigh_of_t1le:
                    if t2le in border_tiles:
                        strength -= 0.2
            if self.map_proxy.get_terrain_type(tile) == TerrainType.MOUNTAIN:
                strength -= 100
            tilez.append((strength, tile))
        print(sorted(tilez, key=lambda tup: tup[0]))
        print(sorted(tilez, key=lambda tup: tup[0])[-1][0])
        return sorted(tilez, key=lambda tup: tup[0])[-1][1]

    def tile_from_base(self, side: str):
        tiles = self.map_proxy.get_player_visible_tiles()
        base_tile_tmp = self.map_proxy.get_bases_positions()
        border_tiles = self.map_proxy.get_border_tiles()
        base_tile = list(base_tile_tmp)

        print("toto som chcel vidiet: " + str(base_tile[0].offset.q))

        for i in range(2,6):
            for tile in tiles:
                if side == 'left':
                    if tile.offset.q < base_tile[0].offset.q:
                        if not self.map_proxy.is_position_occupied(tile) and tile not in border_tiles:
                            if tile.distance_from(base_tile[0]) == i:
                                print(f'mal by sa spawnut na tile: {tile}')
                                return tile
                if side == 'right':
                    if tile.offset.q > base_tile[0].offset.q:
                        if not self.map_proxy.is_position_occupied(tile) and tile not in border_tiles:
                            if tile.distance_from(base_tile[0]) == i:
                                return tile
                if side == 'top':
                    if tile.offset.r < base_tile[0].offset.r:
                        if not self.map_proxy.is_position_occupied(tile) and tile not in border_tiles:
                            if tile.distance_from(base_tile[0]) == i:
                                return tile
                if side == 'bottom':
                    if tile.offset.r > base_tile[0].offset.r:
                        if not self.map_proxy.is_position_occupied(tile) and tile not in border_tiles:
                            if tile.distance_from(base_tile[0]) == i:
                                return tile
        return None

    def visible_free_tile(self, terrain_type=None):
        """ Find random free tile with given terrain type """
        tiles = self.map_proxy.get_player_visible_tiles()
        border_tiles = self.map_proxy.get_border_tiles()
        if terrain_type is None:
            for position in tiles:
                occupied = self.map_proxy.is_position_occupied(position)
                if not occupied and position not in border_tiles:
                    return position
            return None
        else:
            for position in tiles:
                terrain = self.map_proxy.get_terrain_type(position) == TerrainType.from_string(terrain_type)
                occupied = self.map_proxy.is_position_occupied(position)
                if terrain and not occupied and position not in border_tiles:
                    return position
            return None

    def border_patrol_tile(self, side: str):
        """find first free border tile from base"""
        tiles = self.map_proxy.get_player_visible_tiles()
        border_tiles = self.map_proxy.get_border_tiles()
        if side == 'left':
            for i in range(-3, 6):
                tile = OffsetPosition(int(-5), int(i))
                if tile in tiles and tile not in border_tiles and not self.map_proxy.is_position_occupied(tile):
                    return tile
        if side == 'right':
            for i in range(-3, 6):
                tile = OffsetPosition(int(5), int(i))
                if tile in tiles and tile not in border_tiles and not self.map_proxy.is_position_occupied(tile):
                    return tile
        if side == 'top':
            for i in range(-3, 6):
                tile = OffsetPosition(int(i), int(-5))
                if tile in tiles and tile not in border_tiles and not self.map_proxy.is_position_occupied(tile):
                    return tile
        if side == 'bottom':
            for i in range(-3, 6):
                tile = OffsetPosition(int(i), int(5))
                if tile in tiles and tile not in border_tiles and not self.map_proxy.is_position_occupied(tile):
                    return tile

    def border_patrol_equality(self, side1: str, side2: str):
        return self.border_patrol_count(side1) <= self.border_patrol_count(side2)

    def border_patrol_count(self, side: str, side2=None):
        count = 0
        tiles = self.map_proxy.get_player_visible_tiles()
        border_tiles = self.map_proxy.get_border_tiles()
        if side2 is not None:
            count += self.border_patrol_count(side2)
        if side == 'left':
            for i in range(-3, 6):
                tile = OffsetPosition(int(-5), int(i))
                if self.game_object_proxy.get_role(tile) == GameRole.DEFENDER:
                    count += 1
        if side == 'right':
            for i in range(-3, 6):
                tile = OffsetPosition(int(5), int(i))
                if self.game_object_proxy.get_role(tile) == GameRole.DEFENDER:
                    count += 1
        if side == 'top':
            for i in range(-3, 6):
                tile = OffsetPosition(int(i), int(-5))
                if self.game_object_proxy.get_role(tile) == GameRole.DEFENDER:
                    count += 1
        if side == 'bottom':
            for i in range(-3, 6):
                tile = OffsetPosition(int(i), int(5))
                if self.game_object_proxy.get_role(tile) == GameRole.DEFENDER:
                    count += 1
        print("border_patrol_count: " + str(count))
        return count

    def base_guards_count(self):
        count = 0
        tiles = self.map_proxy.get_player_visible_tiles()
        border_tiles = self.map_proxy.get_border_tiles()
        border_patrol_tiles = set()
        for i in range(-5, 6):
            border_patrol_tiles.add(OffsetPosition(int(-5), int(i)))
            border_patrol_tiles.add(OffsetPosition(int(5), int(i)))
            border_patrol_tiles.add(OffsetPosition(int(i), int(-5)))
            border_patrol_tiles.add(OffsetPosition(int(i), int(5)))

        for tile in tiles:
            if self.game_object_proxy.get_role(tile) == GameRole.DEFENDER and tile not in border_patrol_tiles:
                count += 1
        print("base_guards_count: " + str(count+1))
        return count + 1

    def possible_spawn_tiles(self):
        """ Get list of possible tiles, where enemy spawn a unit """
        spawn_info = self.game_uncertainty_proxy.spawn_information()

        next_round = spawn_info[0]

        possible_tiles = set()
        for unit in next_round:
            possible_tiles.update([x.position for x in unit.positions])

        return possible_tiles

    def get_terrain_type(self, x, y) -> str:
        if self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y))) == TerrainType.MOUNTAIN:
            return 'mountain'
        if self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y))) == TerrainType.FIELD:
            return 'field'
        if self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y))) == TerrainType.FOREST:
            return 'forest'
        if self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y))) == TerrainType.HILL:
            return 'hill'
        if self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y))) == TerrainType.RIVER:
            return 'river'
        if self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y))) == TerrainType.VILLAGE:
            return 'village'

    def have_enough_money(self, x) -> bool:
        return self.game_object_proxy.get_resources(self.player) >= int(x)

    def can_place_unit(self, x, y) -> bool:
        if OffsetPosition(int(x), int(y)) in self.map_proxy.get_player_visible_tiles():
            if self.map_proxy.is_position_occupied((OffsetPosition(int(x), int(y)))):
                return False
            return True
        return False

    def base_defense_tile(self):
        x = self.map_proxy.get_bases_positions()
        border_tiles = self.map_proxy.get_border_tiles()
        for z in x:
            y = z
        tiles = y.get_all_neighbours()
        for tile in tiles:
            occupied = self.map_proxy.is_position_occupied(tile)
            if tile not in border_tiles and not occupied:
                return tile
        return None

    def base_defense_tile2(self):
        x = self.map_proxy.get_bases_positions()
        visible_tiles = self.map_proxy.get_player_visible_tiles()
        border_tiles = self.map_proxy.get_border_tiles()
        for z in x:
            y = z
        tiles = y.get_all_neighbours()
        new_tiles = set()
        for t1le in tiles:
            neigh = t1le.get_all_neighbours()
            for t1lez in neigh:
                new_tiles.add(t1lez)
        for t2le in new_tiles:
            occupied = self.map_proxy.is_position_occupied(t2le)
            if t2le not in border_tiles and not occupied and t2le in visible_tiles:
                return t2le
        return None
