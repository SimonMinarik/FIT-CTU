package thedrake;

public class Board {

	private BoardTile[][] board;
	private int dimension;

	public Board(int dimension) {
		this.dimension = dimension;
		board = new BoardTile[dimension][dimension];
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				board[i][j] = BoardTile.EMPTY;
			}
		}
	}

	public int dimension() {
		return dimension;
	}

	public BoardTile at(BoardPos pos) {
		return board[pos.i()][pos.j()];
	}

	public Board withTiles(Board.TileAt ...ats) {
		Board board_temp = new Board(dimension);
		for (int i = 0; i < dimension; i++) {
			board_temp.board[i] = this.board[i].clone();
		}
		for (Board.TileAt arg : ats) {
			board_temp.board[arg.pos.i()][arg.pos.j()] = arg.tile;
		}
		return board_temp;
	}

	public PositionFactory positionFactory() {
		return new PositionFactory(dimension);
	}
	
	public static class TileAt {
		public final BoardPos pos;
		public final BoardTile tile;
		
		public TileAt(BoardPos pos, BoardTile tile) {
			this.pos = pos;
			this.tile = tile;
		}
	}
}

