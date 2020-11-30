from typing import List

from OrodaelTurrim.Business.Logger import Logger
from OrodaelTurrim.Business.Proxy import GameObjectProxy, MapProxy
from OrodaelTurrim.Structure.Filter.FilterPattern import AttackFilter
from OrodaelTurrim.Structure.Position import Position
from OrodaelTurrim.Structure.Enums import GameObjectType

""" 
In this file you can define your ow attack filters if default filters are not enough for your. 
Filter must be subclass of class `AttackFilter` and must implement filter method with same signature

def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
    pass
    
    
You can here define as many filters as you want. Framework fill find correct filters and load them.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!                  TODO: You can define your own filters HERE                  !!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
"""


class EmptyAttackFilter(AttackFilter):
    """ Example of empty custom filter. Method filter is only method, you need to implement """

    def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
        """ This method must always return a subset of given positions (tiles parameter) """
        return tiles


class DummyAttackFilter(AttackFilter):
    """
    Example of custom filter with parameter.
    If you want to have a filter with a parameter, you must overload __init__ function. You must call parent __init__.

    Parameters map_proxy and game_object_proxy will be passed by FilterFactory.
    """

    def __init__(self, map_proxy: MapProxy, game_object_proxy: GameObjectProxy, log_text: str):
        super().__init__(map_proxy, game_object_proxy)
        self.log_text = log_text

    def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
        """
        :param position: Current positions of game object
        :param tiles: List of all tiles, where unit could attack (based on visibility, attack range, etc.)
        :return: List of position, that left after filtering
        """
        Logger.log(self.log_text)
        return tiles


class MagicianAttackFilter(AttackFilter):
    def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
        new_tiles = []
        for x in tiles:
            if self.game_object_proxy.get_object_type(x) == GameObjectType.NECROMANCER or self.game_object_proxy.get_object_type(x) == GameObjectType.DEMON:
                new_tiles.append(x)
        if len(new_tiles) > 0:
            return new_tiles
        else:
            return tiles

class DruidAttackFilter(AttackFilter):
    def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
        new_tiles = []
        for x in tiles:
            if self.game_object_proxy.get_object_type(x) == GameObjectType.ELEMENTAL or self.game_object_proxy.get_object_type(x) == GameObjectType.CYCLOPS:
                new_tiles.append(x)
        if len(new_tiles) > 0:
            return new_tiles
        else:
            return tiles

class KnightAttackFilter(AttackFilter):
    def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
        new_tiles = []
        for x in tiles:
            if self.game_object_proxy.get_object_type(x) == GameObjectType.GARGOYLE or self.game_object_proxy.get_object_type(x) == GameObjectType.CYCLOPS:
                new_tiles.append(x)
        if len(new_tiles) > 0:
            return new_tiles
        else:
            return tiles