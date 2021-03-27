/*
*
*    That friendship program was chef's kiss. Thank you.
*
*/

# include <stdio.h>
# include <stdlib.h>

# define DEFAULT_CAP 2
# define MAX_RANK_ATTACKERS 2
# define MAX_FILE_ATTACKERS 2
# define MAX_ROW_LEN 1000000001

// Typedefs
typedef struct Piece Piece;
typedef struct Row Row;
typedef struct Board Board;

// The struct for storing the data for each piece
struct Piece {
    int id, rank, file;
};

// The struct for storing the information for each rank/row
struct Row {
    int identifier;
    Piece**arr;
    int size, cap;
};

// The struct for storing board data(there will be two boards)
struct Board {
    Row**arr;
    int size, cap;
};

// Prototypes
Board* createBoard();
Row* createRow(int row_id);
Piece* createPiece(int id, int rank, int file);
void destroyBoard(Board* Board);
void destroyRow(Row* Row);
void destroyPiece(Piece* Piece);
void addPieceToRow(Row* Row, Piece* Piece);
void addRowToBoard(Board* Board, Row* Row);
void expandBoard(Board* Board);
void expandRow(Row* Row, Piece* Piece);
Row* findRow(Board* Board, int row_id);

// I use the pointer passed to yield the necessary IDs, so no return necessary
void findAttackers(Board* Board, int row, int file, int* attackers);

int main() {

    // Build the data structure
    Board* rankBoard = createBoard();
    Board* fileBoard = createBoard();

    // Holding variables for the piece and row pointers
    // I use when loading the board.
    Piece* Piece;
    Row* Row;

    // I made these pointers so that I could pass them into and modify them
    // from the findAttackers function.
    int* rank_attackers;
    int* file_attackers;
    int num_attackers;

    int num_pieces, piece_rank, piece_file;

    // This gives us the number of loops
    scanf("%d", &num_pieces);

    // The alternative to a 'findPiece' function that I originally had
    // This gives us a quick and easy way to avoid iterating to find
    // current piece information, as the ID will be tied to the output
    // print/calculation loop iteration and we will be able to go directly
    // to the index that holds the pieces information, even though it's just
    // a shallow copy.
    int rooks[num_pieces][2];

    // Creating the pieces and loading the boards
    for (int i = 0; i < num_pieces; i++) {
        piece_rank = piece_file = 0;

        //Get Piece info
        scanf("%d %d", &piece_rank, &piece_file);

        // Filling our shallow copy array
        rooks[i][0] = piece_rank;
        rooks[i][1] = piece_file;

        // loading rankBoard
        Piece = createPiece(i + 1, piece_rank, piece_file);
        Row = findRow(rankBoard, Piece->rank);
        addPieceToRow(Row, Piece);

        // loading fileBoard
        // This is the critical move right here. By flipping the coordinates of
        // the piece, we, in essence, flip the dimensions of the fileBoard,
        // allowing us access to the file from the same direction as the rank
        // of the rankBoard.
        Piece = createPiece(i + 1, piece_file, piece_rank);
        // Because we flipped the dimensions, in memory the Piece->rank for
        // this piece is going to be the file of the piece we read in.
        Row = findRow(fileBoard, Piece->rank);
        addPieceToRow(Row, Piece);
    }

    // Finding attackers and printing output
    for(int i = 0; i < num_pieces; i++) {

        // Increment counter
        num_attackers = 0;

        rank_attackers = calloc(MAX_RANK_ATTACKERS, sizeof(int));
        file_attackers = calloc(MAX_FILE_ATTACKERS, sizeof(int));


        // Note that in the second call to findAttackers, we had to flip the
        // coordinates for the parameters. While coordinates are flipped in
        // the boards, we only maintain one static array of the shallow copies
        // of the pieces, so the simple solution is just pass them in flipped.
        findAttackers(rankBoard, rooks[i][0], rooks[i][1], rank_attackers);
        findAttackers(fileBoard, rooks[i][1], rooks[i][0], file_attackers);

        for(int j = 0; j < MAX_RANK_ATTACKERS; j++) {
            if(rank_attackers[j] != 0) {
                num_attackers++;
            }
        }
        for(int j = 0; j < MAX_FILE_ATTACKERS; j++) {
            if(file_attackers[j] != 0) {
                num_attackers++;
            }
        }

        printf("%d ", num_attackers);

        // We only print if an ID was grabbed
        for(int j = 0; j < MAX_RANK_ATTACKERS; j++) {
            if(rank_attackers[j] != 0) {
                printf("%d ", rank_attackers[j]);
            }
        }
        for(int j = 0; j < MAX_FILE_ATTACKERS; j++) {
            if(file_attackers[j] != 0) {
                printf("%d ", file_attackers[j]);
            }
        }

        // So we don't get an extra newline at the end of the output
        // Which was not present in the big_output.txt sample
        if(i != num_pieces - 1) {
            printf("\n");
        }

        free(rank_attackers);
        free(file_attackers);
    }

    // Destroy Boards
    // Because we had 2 sets of pieces we don't have to sweat double frees.
    // We can freely free
    destroyBoard(rankBoard);
    destroyBoard(fileBoard);

    return 0;
}

// This function finds the right row thanks to our shallow rooks array contents,
// used that to match a row identifier(just like findRow()), and then does a
// single sweep to find the IDs of the closest pieces. We have to traverse the
// entire row because the pieces in input are unsorted and, as such, the final
// piece read in can have a column value that falls to the left of the first
// piece read in for the row(worst case scenario).
void findAttackers(Board* Board, int target_row, int target_file, int* attackers) {
    // These two values 'squeeze' to the target piece's values
    int next_smaller = 0;
    int next_larger = MAX_ROW_LEN;


    for(int i = 0; i < Board->size; i++) {
        Row* curRow = Board->arr[i]; // Clarity
        if(curRow->identifier == target_row) {
            for(int j = 0; j < curRow->size; j++) {
                Piece* curPiece = curRow->arr[j]; // Clarity
                // Here is where we're going to check for the largest column
                // value less than the targeted piece's(left) and the smallest
                // column value greater than the targeted piece's(right)
                if((curPiece->file > next_smaller) &&
                   (curPiece->file < target_file )) {
                    attackers[0] = curPiece->id;
                    next_smaller = curPiece->file;
                }
                // Despite refactoring, they still were 80+, so 2 lines it is.
                else if((curPiece->file < next_larger) &&
                        (curPiece->file > target_file )) {
                    attackers[1] = curPiece->id;
                    next_larger = curPiece->file;
                }
            }
        }
    }
}

// Allocating mem for our board and returning a pointer to access it
Board* createBoard() {
    Board* ret;

    ret = (Board*) calloc(1, sizeof(Board));

    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    // An array that will hold Row pointers
    ret->arr = (Row**) calloc(DEFAULT_CAP, sizeof(Row*));

    return ret;
}

// Allocating mem for our row and returning a pointer to access it
Row* createRow(int rank_num) {
    Row* ret;

    ret = (Row*) calloc(1, sizeof(Row));

    // Because we don't store every row, it becomes imperative that we 'tag'
    // each row for identification
    ret->identifier = rank_num;
    ret->size = 0;
    ret->cap = DEFAULT_CAP;
    // An array that will hold Piece pointers
    ret->arr = calloc(DEFAULT_CAP, sizeof(Piece*));

    return ret;
}

// Creating a pointer to a loaded piece struct in mem
Piece* createPiece(int id, int rank, int file) {
    Piece* ret;

    ret = (Piece*)calloc(1, sizeof(Piece));

    ret->id = id;
    ret->rank = rank;
    ret->file = file;

    return ret;
}

// Frees each row, then the row pointer array, then the board
void destroyBoard(Board* Board) {
    for(int i = 0; i < Board->size; i++) {
        Row* curRow = Board->arr[i]; // Convenience
        destroyRow(curRow);
    }
    free(Board->arr);
    free(Board);
}

// Frees each piece on the row passed, then the piece ptr array, then the row
void destroyRow(Row* curRow) {
    for (int i = 0; i < curRow->size; i++) {
        destroyPiece(curRow->arr[i]);
    }
    free(curRow->arr);
    free(curRow);
}

// Low usefulness, but accommodates more if the piece structure evolves
void destroyPiece(Piece* Piece) {
    free(Piece);
}

// First we check to make sure there's room to add a piece
// If not, we expand the row first
// If so, we add the piece and make sure to adjust our variable
// that measures number of pieces on the row
void addPieceToRow(Row* Row, Piece* Piece) {
    if (Row->size == Row->cap) {
        expandRow(Row, Piece);
    }

    Row->arr[Row->size] = Piece;
    Row->size++;
}

// Same as above, with a level up on each struct
void addRowToBoard(Board* Board, Row* Row) {
    if(Board->cap == Board->size) {
        expandBoard(Board);
    }

    Board->arr[Board->size] = Row;
    Board->size++;
}

// When we run out space for new row pointers in Board->arr
// We have to increase the array and the var that holds its length(cap)
void expandBoard(Board* Board) {
    int newCap = Board->cap * 2;
    Board->arr = realloc(Board->arr, newCap* sizeof(Row*));
    Board->cap = newCap;
}

// Same logic as expandBoard
void expandRow(Row* Row, Piece* Piece) {
    int newCap = Row->cap * 2;
    Row->arr = realloc(Row->arr, newCap * sizeof(Piece));
    Row->cap = newCap;
}

// This is the crucial function to get right for loading.
// First you check to see if the row exists:
// If yes, return the pointer to that row
// If no, we must create the row and link it to the board.
// Regardless of board state upon entering the function,
// upon exiting the function, we 100% have a row in which
// to place the piece.
Row* findRow(Board* Board, int row_id) {
    Row* ret;

    for(int i = 0; i < Board->size; i++) {
        if(row_id == Board->arr[i]->identifier) {
            ret = Board->arr[i];
            return ret;
        }
    }

    ret = createRow(row_id);
    addRowToBoard(Board, ret);

    return ret;
}
