from OrodaelTurrim.Business.Interface.Player import IPlayer
from OrodaelTurrim.Business.Proxy import GameControlProxy
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

    * self.game_control_proxy (GameControlProxy) for doing actions in game
    * self.player [IPlayer] instance of your player for identification yourself in proxy

    You can use () operator on ActionBase instance to call your function by `str` name or `Expression` class.
    Expression class will also pass arguments from self to your method. () operator using only args so be careful about
    order and number of arguments.

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !!               TODO: Write implementation of your actions HERE                !!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    """
    game_control_proxy: GameControlProxy
    player: IPlayer


    def build_base(self, position_q: int, position_r: int):
        Logger.log('Building base')
        self.game_control_proxy.spawn_unit(
            SpawnInformation(self.player,
                             GameObjectType.BASE,
                             OffsetPosition(int(position_q), int(position_r)),
                             [], []))
