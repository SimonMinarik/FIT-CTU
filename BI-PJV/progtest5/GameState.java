package thedrake;

import java.util.*;
import java.io.PrintWriter;

public class GameState implements JSONSerializable{
	private final Board board;
	private final PlayingSide sideOnTurn;
	private final Army blueArmy;
	private final Army orangeArmy;
	private final GameResult result;

	public GameState(
			Board board,
			Army blueArmy,
			Army orangeArmy) {
		this(board, blueArmy, orangeArmy, PlayingSide.BLUE, GameResult.IN_PLAY);
	}

	public GameState(
			Board board,
			Army blueArmy,
			Army orangeArmy,
			PlayingSide sideOnTurn,
			GameResult result) {
		this.board = board;
		this.sideOnTurn = sideOnTurn;
		this.blueArmy = blueArmy;
		this.orangeArmy = orangeArmy;
		this.result = result;
	}

	public Board board() {
		return board;
	}

	public PlayingSide sideOnTurn() {
		return sideOnTurn;
	}

	public GameResult result() {
		return result;
	}

	public Army army(PlayingSide side) {
		if(side == PlayingSide.BLUE) {
			return blueArmy;
		}

		return orangeArmy;
	}

	public Army armyOnTurn() {
		return army(sideOnTurn);
	}

	public Army armyNotOnTurn() {
		if(sideOnTurn == PlayingSide.BLUE)
			return orangeArmy;

		return blueArmy;
	}

	public Tile tileAt(BoardPos pos) {
		if(!blueArmy.boardTroops().at(pos).equals(Optional.empty())){
			return blueArmy.boardTroops().at(pos).get();
		}else if(!orangeArmy.boardTroops().at(pos).equals(Optional.empty())){
			return orangeArmy.boardTroops().at(pos).get();
		}else if(!board.at(pos).hasTroop())
			return board.at(pos);
		return null;
	}

	private boolean canStepFrom(TilePos origin) {
		if(     !origin.equals(TilePos.OFF_BOARD)
				&& result.equals(GameResult.IN_PLAY)
				&& armyOnTurn().boardTroops().at(board.positionFactory().pos(origin.i(),origin.j())).isPresent()
				&& !blueArmy.boardTroops().isPlacingGuards()
				&& !orangeArmy.boardTroops().isPlacingGuards()){
			return true;
		}
		return false;
	}

	private boolean canStepTo(TilePos target) {
		return !target.equals(TilePos.OFF_BOARD)
				&& result.equals(GameResult.IN_PLAY)
				&& !armyNotOnTurn().boardTroops().at(board.positionFactory().pos(target.i(),target.j())).isPresent()
				&& armyOnTurn().boardTroops().at(board.positionFactory().pos(target.i(),target.j())).equals(Optional.empty())
				&& board.at(board.positionFactory().pos(target.i(),target.j())).canStepOn();
	}

	private boolean canCaptureOn(TilePos target) {
		return !target.equals(TilePos.OFF_BOARD)
				&& result.equals(GameResult.IN_PLAY)
				&& armyNotOnTurn().boardTroops().at(board.positionFactory().pos(target.i(),target.j())).isPresent();
	}

	public boolean canStep(TilePos origin, TilePos target)  {
		return canStepFrom(origin) && canStepTo(target);
	}

	public boolean canCapture(TilePos origin, TilePos target)  {
		return canStepFrom(origin) && canCaptureOn(target);
	}

	public boolean canPlaceFromStack(TilePos target) {
		if (target.equals(TilePos.OFF_BOARD) || !result.equals(GameResult.IN_PLAY) || armyOnTurn().stack().isEmpty()) {
			return false;
		}

		if (!this.armyOnTurn().boardTroops().isLeaderPlaced()) {

			if (sideOnTurn.equals(PlayingSide.BLUE)) {
				return target.row() == 1;
			}

			if (target.column() == armyNotOnTurn().boardTroops().leaderPosition().column()) {
				if (target.row() - 2 > armyNotOnTurn().boardTroops().leaderPosition().row()) {
					return true;
				}
				return false;
			} else {
				return target.row() == this.board.dimension();
			}
		}
		else if (armyOnTurn().boardTroops().isPlacingGuards() && armyOnTurn().boardTroops().at(board.positionFactory().pos(target.i(), target.j())).equals(Optional.empty())) {
			for (BoardPos it : board.positionFactory().pos(target.i(), target.j()).neighbours()) {
				if (armyOnTurn().boardTroops().leaderPosition().equalsTo(it.i(), it.j()))
					return true;
			}
		}
		else if (this.armyNotOnTurn().boardTroops().at(board.positionFactory().pos(target.i(), target.j())).equals(Optional.empty())
				&& this.armyOnTurn().boardTroops().at(board.positionFactory().pos(target.i(), target.j())).equals(Optional.empty())) {
			for (BoardPos it : board.positionFactory().pos(target.i(), target.j()).neighbours()) {
				if (this.canStepTo(target) && armyOnTurn().boardTroops().troopPositions().contains(it))
					return true;
			}
		}

		return false;
	}

	public GameState stepOnly(BoardPos origin, BoardPos target) {
		if(canStep(origin, target))
			return createNewGameState(
					armyNotOnTurn(),
					armyOnTurn().troopStep(origin, target), GameResult.IN_PLAY);

		throw new IllegalArgumentException();
	}

	public GameState stepAndCapture(BoardPos origin, BoardPos target) {
		if(canCapture(origin, target)) {
			Troop captured = armyNotOnTurn().boardTroops().at(target).get().troop();
			GameResult newResult = GameResult.IN_PLAY;

			if(armyNotOnTurn().boardTroops().leaderPosition().equals(target))
				newResult = GameResult.VICTORY;

			return createNewGameState(
					armyNotOnTurn().removeTroop(target),
					armyOnTurn().troopStep(origin, target).capture(captured), newResult);
		}

		throw new IllegalArgumentException();
	}

	public GameState captureOnly(BoardPos origin, BoardPos target) {
		if(canCapture(origin, target)) {
			Troop captured = armyNotOnTurn().boardTroops().at(target).get().troop();
			GameResult newResult = GameResult.IN_PLAY;

			if(armyNotOnTurn().boardTroops().leaderPosition().equals(target))
				newResult = GameResult.VICTORY;

			return createNewGameState(
					armyNotOnTurn().removeTroop(target),
					armyOnTurn().troopFlip(origin).capture(captured), newResult);
		}

		throw new IllegalArgumentException();
	}

	public GameState placeFromStack(BoardPos target) {
		if(canPlaceFromStack(target)) {
			return createNewGameState(
					armyNotOnTurn(),
					armyOnTurn().placeFromStack(target),
					GameResult.IN_PLAY);
		}

		throw new IllegalArgumentException();
	}

	public GameState resign() {
		return createNewGameState(
				armyNotOnTurn(),
				armyOnTurn(),
				GameResult.VICTORY);
	}

	public GameState draw() {
		return createNewGameState(
				armyOnTurn(),
				armyNotOnTurn(),
				GameResult.DRAW);
	}

	private GameState createNewGameState(Army armyOnTurn, Army armyNotOnTurn, GameResult result) {
		if(armyOnTurn.side() == PlayingSide.BLUE) {
			return new GameState(board, armyOnTurn, armyNotOnTurn, PlayingSide.BLUE, result);
		}

		return new GameState(board, armyNotOnTurn, armyOnTurn, PlayingSide.ORANGE, result);
	}

	public void toJSON(PrintWriter writer) {
		String json = "";
		json += "{";
		json += "\"result\":\"" + this.result + "\",";
		json += "\"board\":{";
		json += "\"dimension\":" + this.board.dimension() + ",";
		json += "\"tiles\":[";
		for (int i = 0; i < this.board.dimension(); i++){
			for (int j = 0; j < this.board.dimension(); j++) {
				if (this.board.at(this.board.positionFactory().pos(j, i)) == BoardTile.EMPTY) {
					json += "\"empty\",";
				} else {
					json += "\"mountain\",";
				}
			}
		}
		json = json.substring(0, json.length() - 1);
		json += "]},\"blueArmy\":{";
		json += "\"boardTroops\":{";
		json += "\"side\":\"BLUE\",";
		json += "\"leaderPosition\":\"" + this.blueArmy.boardTroops().leaderPosition() + "\",";
		json += "\"guards\":" + this.blueArmy.boardTroops().guards() + ",";
		json += "\"troopMap\":{";
		Map<BoardPos, TroopTile> troopMap = new HashMap<>();
		for (BoardPos x:blueArmy.boardTroops().troopPositions()){
			troopMap.put(x, blueArmy.boardTroops().at(x).get());
		}
		Map<BoardPos, TroopTile> blueArmyPos = new TreeMap<>(troopMap);
		for (Map.Entry<BoardPos, TroopTile> entry : blueArmyPos.entrySet()){
			json += "\"" + entry.getKey().toString() + "\":{";
			json += "\"troop\":\"" + entry.getValue().troop().name() + "\",";
			json += "\"side\":\"" + entry.getValue().side() + "\",";
			json += "\"face\":\"" + entry.getValue().face() + "\"},";
		}
		if (!blueArmyPos.isEmpty()) {
			json = json.substring(0, json.length() - 1);
		}
		json += "}},";
		json += "\"stack\":[";
		List<Troop> blueArmyStack = blueArmy.stack();
		for (Troop troop:blueArmyStack){
			json += "\"" + troop.name() + "\",";
		}
		if (!blueArmy.stack().isEmpty()){
			json = json.substring(0, json.length() - 1);
		}
		json += "],";
		json += "\"captured\":[";
		for (Troop troop:blueArmy.captured()){
			json += "\"" + troop.name() + "\",";
		}
		if (!blueArmy.captured().isEmpty()){
			json = json.substring(0, json.length() - 1);
		}

		json += "]},\"orangeArmy\":{";
		json += "\"boardTroops\":{";
		json += "\"side\":\"ORANGE\",";
		json += "\"leaderPosition\":\"" + this.orangeArmy.boardTroops().leaderPosition() + "\",";
		json += "\"guards\":" + this.orangeArmy.boardTroops().guards() + ",";
		json += "\"troopMap\":{";
		Map<BoardPos, TroopTile> troopMap2 = new HashMap<>();
		for (BoardPos x:orangeArmy.boardTroops().troopPositions()){
			troopMap2.put(x, orangeArmy.boardTroops().at(x).get());
		}
		Map<BoardPos, TroopTile> orangeArmyPos = new TreeMap<>(troopMap2);
		for (Map.Entry<BoardPos, TroopTile> entry : orangeArmyPos.entrySet()){
			json += "\"" + entry.getKey().toString() + "\":{";
			json += "\"troop\":\"" + entry.getValue().troop().name() + "\",";
			json += "\"side\":\"" + entry.getValue().side() + "\",";
			json += "\"face\":\"" + entry.getValue().face() + "\"},";
		}
		if (!orangeArmyPos.isEmpty()) {
			json = json.substring(0, json.length() - 1);
		}
		json += "}},";
		json += "\"stack\":[";
		List<Troop> orangeArmyStack = orangeArmy.stack();
		for (Troop troop:orangeArmyStack){
			json += "\"" + troop.name() + "\",";
		}
		if (!orangeArmy.stack().isEmpty()){
			json = json.substring(0, json.length() - 1);
		}
		json += "],";
		json += "\"captured\":[";
		for (Troop troop:orangeArmy.captured()){
			json += "\"" + troop.name() + "\",";
		}
		if (!orangeArmy.captured().isEmpty()){
			json = json.substring(0, json.length() - 1);
		}
		json += "]}}";


		writer.printf(json);
	}
}
