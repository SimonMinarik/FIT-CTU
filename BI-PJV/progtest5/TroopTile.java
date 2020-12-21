package thedrake;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class TroopTile implements Tile {

    private Troop troop;
    private PlayingSide side;
    private TroopFace face;

    public TroopTile(Troop troop, PlayingSide side, TroopFace face) {
        this.troop = troop;
        this.side = side;
        this.face = face;
    }

    public PlayingSide side() {
        return side;
    }

    public TroopFace face() {
        return face;
    }

    public Troop troop() {
        return troop;
    }

    public boolean canStepOn() {
        return false;
    }

    public boolean hasTroop() {
        return true;
    }

    public TroopTile flipped() {
        if (face == TroopFace.AVERS) {
            return new TroopTile(troop, side, TroopFace.REVERS);
        } else {
            return new TroopTile(troop, side, TroopFace.AVERS);
        }
    }

    @Override
    public List<Move> movesFrom(BoardPos pos, GameState state) {
        List<Move> result = new ArrayList<>();
        List<TroopAction> actionList = troop.actions(this.face());
        for(TroopAction it : actionList){
            result.addAll(it.movesFrom(pos,side,state));
        }
        return result;
    }
}
