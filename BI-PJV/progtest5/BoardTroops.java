package thedrake;

import java.util.*;

public class BoardTroops {
	private final PlayingSide playingSide;
	private final Map<BoardPos, TroopTile> troopMap;
	private final TilePos leaderPosition;
	private final int guards;
	
	public BoardTroops(PlayingSide playingSide) { 
		this.playingSide = playingSide;
		this.troopMap = Collections.emptyMap();
		this.leaderPosition = TilePos.OFF_BOARD;
		this.guards = 0;
	}
	
	public BoardTroops(
			PlayingSide playingSide,
			Map<BoardPos, TroopTile> troopMap,
			TilePos leaderPosition, 
			int guards) {
		this.playingSide = playingSide;
		this.troopMap = troopMap;
		this.leaderPosition = leaderPosition;
		this.guards = guards;
	}

	public Optional<TroopTile> at(TilePos pos) {
		if (this.troopMap.get(pos) != null) {
			return Optional.of(troopMap.get(pos));
		} else {
			return Optional.empty();
		}
	}
	
	public PlayingSide playingSide() {
		return this.playingSide;
	}
	
	public TilePos leaderPosition() {
		return this.leaderPosition;
	}

	public int guards() {
		return this.guards;
	}
	
	public boolean isLeaderPlaced() {
		if (this.leaderPosition == TilePos.OFF_BOARD) {
			return false;
		} else {
			return true;
		}
	}
	
	public boolean isPlacingGuards() {
		if (this.leaderPosition != TilePos.OFF_BOARD) {
			if (this.guards < 2) {
				return true;
			}
		}
		return false;
	}	
	
	public Set<BoardPos> troopPositions() {
		Set<BoardPos> temp = new HashSet<>();
		for (Map.Entry<BoardPos, TroopTile> entry : this.troopMap.entrySet()) {
			temp.add(entry.getKey());
		}
		return temp;
	}

	public BoardTroops placeTroop(Troop troop, BoardPos target) {
		Map<BoardPos, TroopTile> newTroops = new HashMap<>(troopMap);
		if (this.leaderPosition == TilePos.OFF_BOARD) {
			newTroops.put(target, new TroopTile(troop, this.playingSide, TroopFace.AVERS));
			return new BoardTroops(this.playingSide, newTroops, target, 0);
		} else if (this.troopMap.get(target) != null) {
			throw new IllegalArgumentException();
		} else {
			newTroops.put(target, new TroopTile(troop, this.playingSide, TroopFace.AVERS));
			if (guards < 2) {
				return new BoardTroops(this.playingSide, newTroops, this.leaderPosition, this.guards + 1);
			} else {
				return new BoardTroops(this.playingSide, newTroops, this.leaderPosition, this.guards);
			}
		}
	}
	
	public BoardTroops troopStep(BoardPos origin, BoardPos target) {
		if (this.leaderPosition == TilePos.OFF_BOARD || this.guards < 2) {
			throw new IllegalStateException();
		}
		if (!at(origin).isPresent() || this.troopMap.get(target) != null) {
			throw new IllegalArgumentException();
		}
		Map<BoardPos, TroopTile> newTroops = new HashMap<>(troopMap);
		if (origin.equals(this.leaderPosition)) {
			TroopTile tile = newTroops.remove(origin);
			newTroops.put(target, tile.flipped());
			return new BoardTroops(this.playingSide, newTroops, target, this.guards);
		} else {
			TroopTile tile = newTroops.remove(origin);
			newTroops.put(target, tile.flipped());
			return new BoardTroops(this.playingSide, newTroops, this.leaderPosition, this.guards);
		}
	}
	
	public BoardTroops troopFlip(BoardPos origin) {
		if(!isLeaderPlaced()) {
			throw new IllegalStateException(
					"Cannot move troops before the leader is placed.");			
		}
		
		if(isPlacingGuards()) {
			throw new IllegalStateException(
					"Cannot move troops before guards are placed.");			
		}
		
		if(!at(origin).isPresent())
			throw new IllegalArgumentException();
		
		Map<BoardPos, TroopTile> newTroops = new HashMap<>(troopMap);
		TroopTile tile = newTroops.remove(origin);
		newTroops.put(origin, tile.flipped());

		return new BoardTroops(playingSide(), newTroops, leaderPosition, guards);
	}
	
	public BoardTroops removeTroop(BoardPos target) {
		if (!isLeaderPlaced() || isPlacingGuards()) {
			throw new IllegalStateException(
					"Cannot remove troops before the leader/guards are placed.");
		}
		if(!at(target).isPresent()) {
			throw new IllegalArgumentException();
		}
		Map<BoardPos, TroopTile> newTroops = new HashMap<>(troopMap);
		newTroops.remove(target);
		if (target.equals(this.leaderPosition)) {
			return new BoardTroops(playingSide(), newTroops, TilePos.OFF_BOARD, guards);
		} else {
			return new BoardTroops(playingSide(), newTroops, leaderPosition, guards);
		}
	}
}
