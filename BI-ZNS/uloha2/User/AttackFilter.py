from typing import List

from OrodaelTurrim.Business.Logger import Logger
from OrodaelTurrim.Business.Proxy import GameObjectProxy, MapProxy
from OrodaelTurrim.Structure.Filter.FilterPattern import AttackFilter
from OrodaelTurrim.Structure.Position import Position

""" 
In this file you can define your ow attack filters if default filters are not enough for your. 
Filter must be subclass of class `AttaclFilter` and must implement filter method with same signature

def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
    pass
    
    
You can here define as many filters as you want. Framework fill find correct filters and load them.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!                  TODO: You can define your own filters HERE                  !!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
"""


class DummyAttackFilter(AttackFilter):
    """ Example of custom filter """


    def __init__(self, map_proxy: MapProxy, game_object_proxy: GameObjectProxy, log_text: str):
        super().__init__(map_proxy, game_object_proxy)
        self.log_text = log_text


    def filter(self, position: Position, tiles: List[Position]) -> List[Position]:
        Logger.log(self.log_text)
        return tiles
