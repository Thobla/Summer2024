# Chess Engine
## TODO:
### Implementation details:
#### Structs:
- struct board, keeps all piece longs
    - methods for easy vertical, horizontal and diagonal movement.

#### Classes:
Game.cpp
    - Only keeps track of the game loop
Board.cpp
    - Keeps track of the board-struct, and moves the pieces, checks if space is occupied. Translate
    Board position to longlong index.
Judge.cpp
    - Keeps track of which moves are legal, if king in check, if forced draw.
Gui.cpp
    - Graphic user interface class, keeps track of input from user/agent, and draws the board.



### Create Board:
    - longlong for each piece type

### Piece Movement:
#### Pawn:
    - Forward-move
    - Diagonal-capture
    - En-pessant
#### Rook:
    - Vertical-movement
    - Horizontal-movement
#### Pony:
    - Jump
#### Bishop:
    - Diagonal-movement
#### Queen:
    - Vertical-Movement
    - Horizontal-movement
    - Diagonal-movement
#### King:
    - Vertical-Movement
    - Horizontal-movement
    - Diagonal-movement

### Find legal moves
    - Run all possible moves, check if king is put in check, if it is not, it is legal.

### Forced draw

### Check, Check-mate
    - See if any enemy piece is looking at king.

