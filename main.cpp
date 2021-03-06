#include <iostream>
#include <cstring>
#include <utility>
#include <windows.h>

using namespace std;

const int ySize = 35;
const int xSize = 35;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void centerField()
{
    //makes things look nicer
    cout << "\t\t\t\t\t\t";
}

void dispField(bool field[ySize][xSize])
{
    ShowConsoleCursor(false);

    //clears text at the bottom of the screen and returns the cursor to origin
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), {30, (ySize + 6)} );
    for(int i = 0; i < 600; ++i)
        cout << ' ';
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), {0, 0} );

    cout << "\n\n\n";
    centerField();

    char tlCorner = 218;
    cout << tlCorner;

    //draws top of bounding box
    for(int i = 0; i <= xSize-1; ++i)
    {
        char hLine = 196;
        cout << hLine << hLine;
    }

    char trCorner = 191;
    cout << trCorner;
    cout << '\n';

    char box = 219;
    for(int y = 0; y < ySize; ++y)
    {
        centerField();

        char vLine = 179;
        cout << vLine; //draws left side of bounding box

        //draws field contents
        for(int x = 0; x < xSize; ++x)
        {
            if(field[y][x] == false)
                cout << "  ";
            else
                cout << box << box;
        }

        cout << vLine <<'\n'; //draws right side of bounding box
    }

    centerField();
    char blCorner = 192;
    cout << blCorner;

    //draws bottom of bounding box
    for(int i = 0; i <= xSize-1; ++i)
    {
        char hLine = 196;
        cout << hLine << hLine;
    }

    char brCorner = 217;
    cout << brCorner;

    cout << '\n';

    ShowConsoleCursor(true);
}

void toggleCell(bool (&field)[ySize][xSize])
{
    centerField();
    cout << "enter X coordinate: ";
    int x;
    cin >> x;

    centerField();
    cout << "enter Y coordinate: ";
    int y;
    cin >> y;

    if(field[y][x])
        field[y][x] = false;
    else
        field[y][x] = true;
}

void run(bool (&field)[ySize][xSize])
{
    centerField();
    cout << "run for how many cycles?\n";
    int cycles;
    centerField();
    cin >> cycles;

    for(int i = 0; i < cycles; ++i)
    {
        bool tempField[ySize][xSize] = {0};

        //iterates though every cell
        for(int yPos = 0; yPos < ySize; ++yPos)
        {
            for(int xPos = 0; xPos < xSize; ++xPos)
            {
                //counter start position
                int y = yPos - 1;
                int x = xPos - 1;

                int neighborCount = 0;
                int tempX = x;

                //checks all cells in a 3x3 area around the current cell
                for(int ity = 0; ity < 3; ++ity, ++y)
                {
                    //causes y to wrap around
                    if(y < 0)
                        y = (ySize - 1);
                    else if(y > (ySize - 1))
                        y = 0;

                    for(int itx = 0; itx < 3; ++itx, ++x)
                    {
                        //causes x to wrap around
                        if(x < 0)
                            x = (xSize - 1);
                        else if(x > (xSize - 1))
                            x = 0;

                        if(field[y][x])
                            ++neighborCount;
                    }
                    //resets x to initial value;
                    x = tempX;
                }
                //the current cell is also counted this removes it from the count
                if(field[yPos][xPos])
                    neighborCount -= 1;

                //"game" rules
                if((field[yPos][xPos]) && ((neighborCount == 2) || (neighborCount == 3)))
                    tempField[yPos][xPos] = true;

                else if((field[yPos][xPos] == false) && (neighborCount == 3))
                    tempField[yPos][xPos] = true;

                else
                    tempField[yPos][xPos] = false;
            }
        }

        //copies temporary field to the main field
        for(int yPos = 0; yPos < ySize; ++yPos)
        {
            for(int xPos = 0; xPos < xSize; ++xPos)
            {
                field[yPos][xPos] = tempField[yPos][xPos];
            }
        }

        dispField(field);
        Sleep(50); //delay in milliseconds
    }
}

int main()
{
    bool field[ySize][xSize] = {0};

    field[15][15] = true;
    field[15][16] = true;
    field[15][17] = true;

    while(true)
    {
        dispField(field);
        cout << '\n';
        centerField();

        cout << "toggle cell(0), run(1) or quit(3)?: ";
        int option;
        cin >> option;

        if(option == 0)
            toggleCell(field);
        else if(option == 1)
            run(field);
        else if(option == 3)
            break;
    }

    return 0;
}
