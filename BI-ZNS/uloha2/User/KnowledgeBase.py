from typing import List, Set

from OrodaelTurrim.Business.Interface.Player import IPlayer
from OrodaelTurrim.Business.Proxy import MapProxy, GameObjectProxy, GameUncertaintyProxy
from ExpertSystem.Business.UserFramework import IKnowledgeBase
from ExpertSystem.Structure.RuleBase import Fact
from OrodaelTurrim.Structure.Enums import TerrainType
from OrodaelTurrim.Structure.Position import OffsetPosition


class KnowledgeBase(IKnowledgeBase):
    """
    Class for defining known facts based on Proxy information. You can transform here any information from
    proxy to better format of Facts. Important is method `create_knowledge_base()`. Return value of this method
    will be passed to `Interference.interfere`. It is recommended to use Fact class but you can use another type.

    |
    |
    | Class provides attributes:

    - **map_proxy [MapProxy]** - Proxy for access to map information
    - **game_object_proxy [GameObjectProxy]** - Proxy for access to all game object information
    - **uncertainty_proxy [UncertaintyProxy]** - Proxy for access to all uncertainty information in game
    - **player [IPlayer]** - instance of user player for identification in proxy methods

    """
    map_proxy: MapProxy
    game_object_proxy: GameObjectProxy
    game_uncertainty_proxy: GameUncertaintyProxy
    player: IPlayer


    def __init__(self, map_proxy: MapProxy, game_object_proxy: GameObjectProxy,
                 game_uncertainty_proxy: GameUncertaintyProxy, player: IPlayer):
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

        facts.append(Fact('player_dont_have_base', lambda: self.check_base()))
        facts.append(Fact('terrain', lambda x, y: self.get_terrain_type(x, y)))
        facts.append(Fact('have_enough_money', lambda x: self.have_enough_money(x)))
        facts.append(Fact('can_place_unit', lambda x, y: self.can_place_unit(x, y)))

        return facts


    def check_base(self) -> bool:
        if self.map_proxy.player_have_base(self.player):
            return False
        return True

    #def get_terrain_type(self, x, y) -> TerrainType:
    #    print(self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y)))).value
    #    return self.map_proxy.get_terrain_type(OffsetPosition(int(x), int(y))).value

    def get_terrain_type(self, x, y) -> str:
        print('qwfqwfqwf')
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
