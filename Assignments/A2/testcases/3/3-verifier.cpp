#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int MAP_SIZE = 7;

typedef pair<int, int> Move;
const vector<vector<char>> SOLVED_MAP = {
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
    {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    {'O', 'O', 'O', 'N', 'O', 'O', 'O'},
    {'O', 'O', 'O', 'O', 'O', 'O', 'O'},
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'},
    {'X', 'X', 'O', 'O', 'O', 'X', 'X'}};

enum Exception
{
  INVALID_POSITION,
  INVALID_MOVE,
  POSITION_NOT_PIECE,
  MOVE_OUT_OF_RANGE,
  MOVE_NOT_REMOVING_PIECE,
  MOVE_DEST_NOT_EMPTY,
  FINAL_MAP_NOT_VALID
};

void print_exception(Exception e)
{
  switch (e)
  {
  case INVALID_POSITION:
    cout << "Input position is invalid" << endl;
    break;

  case INVALID_MOVE:
    cout << "Input move is invalid" << endl;
    break;

  case POSITION_NOT_PIECE:
    cout << "Input position is not a piece (N)" << endl;
    break;

  case MOVE_OUT_OF_RANGE:
    cout << "Move will result being out of range" << endl;
    break;

  case MOVE_NOT_REMOVING_PIECE:
    cout << "Move does not remove any piece" << endl;
    break;

  case MOVE_DEST_NOT_EMPTY:
    cout << "Move will result in a piece cell that is not empty (O)" << endl;
    break;

  default:
    break;
  }
}

bool is_cordinate_valid(int cor)
{
  if (cor < 0 || cor >= MAP_SIZE)
    return false;
  return true;
}

pair<int, int> get_position(string position)
{
  if (int(position[0] < int('A') || (int(position[0] >= int('A') + MAP_SIZE))))
    throw INVALID_POSITION;
  int i = int(position[0]) - int('A');
  if (!is_cordinate_valid(i))
    throw INVALID_POSITION;

  int j = stoi(string(1, position[1])) - 1;
  if (!is_cordinate_valid(j))
    throw INVALID_POSITION;
  return pair<int, int>(i, j);
}

Move get_move(string move)
{
  if (move == "LEFT")
    return Move(0, -1);
  else if (move == "RIGHT")
    return Move(0, 1);
  else if (move == "DOWN")
    return Move(1, 0);
  else if (move == "UP")
    return Move(-1, 0);
  else
    throw INVALID_MOVE;
}

void validate_move(vector<vector<char>> &map, int i, int j, Move move)
{
  if (map[i][j] != 'N')
    throw POSITION_NOT_PIECE;

  if (!is_cordinate_valid(i + 2 * move.first) || !is_cordinate_valid(j + 2 * move.second))
    throw MOVE_OUT_OF_RANGE;

  if (map[i + move.first][j + move.second] != 'N')
    throw MOVE_NOT_REMOVING_PIECE;

  if (map[i + 2 * move.first][j + 2 * move.second] != 'O')
    throw MOVE_DEST_NOT_EMPTY;
}

void make_move(vector<vector<char>> &map, string position, string move)
{
  auto p = get_position(position);
  int i = p.first, j = p.second;
  Move m = get_move(move);
  validate_move(map, i, j, m);

  map[i][j] = 'O';
  map[i + m.first][j + m.second] = 'O';
  map[i + 2 * m.first][j + 2 * m.second] = 'N';
}

void validate_final_map(vector<vector<char>> &map)
{
  for (int i = 0; i < MAP_SIZE; i++)
    for (int j = 0; j < MAP_SIZE; j++)
      if (map[i][j] != SOLVED_MAP[i][j])
        throw FINAL_MAP_NOT_VALID;
}

void print_map(vector<vector<char>> &map)
{
  for (auto row : map)
  {
    for (auto c : row)
      cout << c << " ";
    cout << endl;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    cout << "Invalid argument" << endl;
    cout << "Usage: " << argv[0] << " <BOARD_FILE_NAME> <MOVE_INPUT_FILE_NAME>" << endl;
    exit(1);
  }

  string board_file_name = argv[1];
  string move_input_file_name = argv[2];

  vector<vector<char>> board;
  string line;
  cout << "opening board file: " << board_file_name << endl;
  fstream board_fs(board_file_name);
  for (int i = 0; i < MAP_SIZE; i++)
  {
    vector<char> row;
    board_fs >> line;
    for (auto c : line)
      row.push_back(c);
    board.push_back(row);
  }
  cout << "loaded board:" << endl;
  print_map(board);

  cout << "opening move input file: " << move_input_file_name << endl;
  fstream move_input_fs(move_input_file_name);
  stringstream ss;
  try
  {
    while (getline(move_input_fs, line))
    {
      ss << line;
      string position, move;
      ss >> position >> move;
      cout << "processing line: " << line << endl;
      make_move(board, position, move);
      // Uncomment the following two lines for
      cout << "resulting board:" << endl;
      print_map(board);
      ss.clear();
    }
    validate_final_map(board);
    cout << "Valid input" << endl;
    exit(0);
  }
  catch (Exception e)
  {
    print_exception(e);
    exit(1);
  }
}