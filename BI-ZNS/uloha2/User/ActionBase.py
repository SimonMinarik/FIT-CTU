from OrodaelTurrim.Business.Interface.Player import IPlayer
from OrodaelTurrim.Business.Proxy import GameControlProxy, MapProxy
from ExpertSystem.Business.UserFramework import IActionBase
from OrodaelTurrim.Business.Logger import Logger
from OrodaelTurrim.Structure.Enums import GameObjectType
from OrodaelTurrim.Structure.GameObjects.GameObject import SpawnInformation
from OrodaelTurrim.Structure.Position import OffsetPosition


class ActionBase(IActionBase):
    """
    You can define here your custom actions. Methods must be public (not starting with __ or _) and must have unique
    names. Methods could have as many arguments as you want. Instance of this class will be available in
    Interference class.


    **This class provides:**

    * self.game_control_proxy [GameControlProxy] for doing actions in game
    * self.map_proxy [MapProxy] for finding places on map
    * self.player [IPlayer] instance of your player for identification yourself in proxy

    MapProxy should be used there only for finding right place on the map. For example functions like:
    * spawn_knight_on_nearest_mountain(x,y)
    * spawn_unit_near_to_base(amount_of_units, unit_type)
    * spawn_unit_far_in_direction(direction)
    * etc...

    It is forbidden, to create whole login in those functions. Whole behaviour logic must be editable without,
    touching code in ActionBase (login must mainly depend on rules). So it's forbidden to use functions like:
    * prepare_defence()
    * spawn_ideal_amount_of_units_at_ideal_places()
    * defend_my_base()
    * etc...

    You can use () operator on ActionBase instance to call your function by `str` name or `Expression` class.
    Expression class will also pass arguments from self to your method. () operator using only args so be careful about
    order and number of arguments.

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !!               TODO: Write implementation of your actions HERE                !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    """
    game_control_proxy: GameControlProxy
    map_proxy: MapProxy
    player: IPlayer


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
                             [], []))
    def spawn_ent(self, position_q: int, position_r: int):
        Logger.log('Spawning ent')
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
                             [], []))
    def spawn_magician(self, position_q: int, position_r: int):
        Logger.log('Spawning magician')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.MAGICIAN,
                             OffsetPosition(int(position_q), int(position_r)),
                             [], []))