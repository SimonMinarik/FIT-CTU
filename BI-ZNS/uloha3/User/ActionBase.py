from OrodaelTurrim.Business.Interface.Player import PlayerTag
from OrodaelTurrim.Business.Proxy import GameControlProxy
from ExpertSystem.Business.UserFramework import IActionBase
from OrodaelTurrim.Business.Logger import Logger
from OrodaelTurrim.Structure.Enums import GameObjectType
from OrodaelTurrim.Structure.Filter.AttackFilter import AttackStrongestFilter
from OrodaelTurrim.Structure.Filter.Factory import FilterFactory
from OrodaelTurrim.Structure.GameObjects.GameObject import SpawnInformation
from OrodaelTurrim.Structure.Position import OffsetPosition

from User.AttackFilter import DummyAttackFilter, EmptyAttackFilter, MagicianAttackFilter, DruidAttackFilter, KnightAttackFilter
from OrodaelTurrim.Structure.Filter.AttackFilter import AttackNearestFilter


class ActionBase(IActionBase):
    """
    You can define here your custom actions. Methods must be public (not starting with __ or _) and must have unique
    names. Methods could have as many arguments as you want. Instance of this class will be available in
    Inference class.

    **This class provides:**

    * self.game_control_proxy [GameControlProxy] for doing actions in game
    * self.player [PlayerTag] instance of your player for identification yourself in proxy

    Usage of ActionBase is described in documentation.


    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !!               TODO: Write implementation of your actions HERE                !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    """
    game_control_proxy: GameControlProxy
    player: PlayerTag


    def build_base_n(self, best_tile):
        # Custom log messages
        Logger.log('Building base')

        # Create instance of custom filter
        empty_filter = FilterFactory().attack_filter(EmptyAttackFilter)
        dummy_filter = FilterFactory().attack_filter(DummyAttackFilter, 'Base attacking')

        # Create instance of default filter
        strongest_filter = FilterFactory().attack_filter(AttackStrongestFilter)

        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.BASE,
                             best_tile,
                             [empty_filter, dummy_filter, strongest_filter], []))

    def build_base(self, position_q: int, position_r: int):
        Logger.log('Building base')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.BASE,
                             OffsetPosition(int(position_q), int(position_r)),
                             [], []))

    def spawn_archer(self, position_q: int, position_r: int):
        Logger.log('Spawning archer')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.ARCHER,
                             OffsetPosition(int(position_q), int(position_r)),
                             [], []))

    def spawn_druid(self, position_q: int, position_r: int):
        Logger.log('Spawning druid')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.DRUID,
                             OffsetPosition(int(position_q), int(position_r)),
                             [FilterFactory().attack_filter(AttackNearestFilter), FilterFactory().attack_filter(DruidAttackFilter)], []))

    def spawn_ent(self, position_q: int, position_r: int):
        Logger.log('Spawning ent')
        print("ent")
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.ENT,
                             OffsetPosition(int(position_q), int(position_r)),
                             [], []))

    def spawn_knight(self, position_q: int, position_r: int):
        Logger.log('Spawning knight')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.KNIGHT,
                             OffsetPosition(int(position_q), int(position_r)),
                             [FilterFactory().attack_filter(KnightAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))

    def spawn_knight_n(self, base_defense_tile):
        Logger.log('Spawning knight')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.KNIGHT,
                             base_defense_tile,
                             [FilterFactory().attack_filter(KnightAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))

    def spawn_knight_n2(self, base_defense_tile2):
        Logger.log('Spawning knight')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.KNIGHT,
                             base_defense_tile2,
                             [FilterFactory().attack_filter(KnightAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))

    def spawn_magician(self, position_q: int, position_r: int):
        Logger.log('Spawning magician')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.MAGICIAN,
                             OffsetPosition(int(position_q), int(position_r)),
                             [FilterFactory().attack_filter(MagicianAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))

    def spawn_magician_n(self, base_defense_tile):
        Logger.log('Spawning magician')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.MAGICIAN,
                             base_defense_tile,
                             [FilterFactory().attack_filter(MagicianAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))

    def spawn_magician_n2(self, tile_from_base):
        Logger.log('Spawning magician')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.MAGICIAN,
                             tile_from_base,
                             [FilterFactory().attack_filter(MagicianAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))

    def spawn_druid_n(self, base_defense_tile):
        Logger.log('Spawning druid')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.DRUID,
                             base_defense_tile,
                             [FilterFactory().attack_filter(DruidAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))

    def spawn_druid_a(self, tile_from_base):
        Logger.log('Spawning druid')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.DRUID,
                             tile_from_base,
                             [FilterFactory().attack_filter(DruidAttackFilter), FilterFactory().attack_filter(AttackNearestFilter)], []))