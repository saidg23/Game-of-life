#include <iostream>
#include <cstring>
#include <utility>
#include <windows.h>

using namespace std;

const int ySize = 38;
const int xSize = 38;

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
    cout << "\t\t\t\t\t\t";
}

void dispField(bool field[ySize][xSize])
{
    ShowConsoleCursor(false);

    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), {30, (ySize + 6)} );
    for(int i = 0; i < 300; ++i)
        cout << ' ';
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), {0, 0} );

    cout << "\n\n\n";
    centerField();

    char tlCorner = 218;
    cout << tlCorner;

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
        cout << vLine;
        for(int x = 0; x < xSize; ++x)
        {
            if(field[y][x] == false)
                cout << "  ";
            else
                cout << box << box;
        }
        cout << vLine <<'\n';
    }

    centerField();
    char blCorner = 192;
    cout << blCorner;

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
    cout << "enter X coordinate: ";
    int x;
    cin >> x;

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
    while(true)
    {
        bool tempField[ySize][xSize] = {0};

        //iterates though every cell
        for(int yPos = 0; yPos < ySize; ++yPos)
        {
            for(int xPos = 0; xPos < xSize; ++xPos)
            {
                int y = yPos - 1;
                int x = xPos - 1;
                int neighborCount = 0;
                int tempX = x;

                //checks surrounding cells
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
                if(field[yPos][xPos])
                    neighborCount -= 1;
                //"game" rules
                if((field[yPos][xPos]) && (neighborCount < 2))
                    tempField[yPos][xPos] = false;
                else if((field[yPos][xPos]) && (neighborCount > 3))
                    tempField[yPos][xPos] = false;
                else if((field[yPos][xPos] == false) &&(neighborCount == 3))
                    tempField[yPos][xPos] = true;
                else if((field[yPos][xPos]) && ((neighborCount == 2) || (neighborCount == 3)))
                    tempField[yPos][xPos] = true;
                else if((field[yPos][xPos] == false) && (neighborCount == 0))
                    tempField[yPos][xPos] = false;
            }
        }
        for(int yPos = 0; yPos < ySize; ++yPos)
        {
            for(int xPos = 0; xPos < xSize; ++xPos)
            {
                field[yPos][xPos] = tempField[yPos][xPos];
            }
        }
        dispField(field);
        Sleep(150);
    }
}
int main()
{
    bool field[ySize][xSize] = {0};

    field[9][9] = true;
    field[9][8] = true;
    field[9][10] = true;
    field[9][11] = true;
    field[8][8] = true;
    field[7][8] = true;
    field[6][9] = true;
    field[8][12] = true;
    field[6][12] = true;

    field[20][20] = true;
    field[20][21] = true;
    field[20][19] = true;
    field[19][21] = true;
    field[18][20] = true;

    field[20][5] = true;
    field[20][6] = true;
    field[20][4] = true;
    field[19][6] = true;
    field[18][5] = true;

    field[30][6] = true;
    field[30][7] = true;
    field[30][8] = true;
    field[29][7] = true;
    field[31][6] = true;
    field[31][8] = true;
    field[32][7] = true;

    while(true)
    {
        dispField(field);
        cout << '\n';
        centerField();

        cout << "toggle cell(0) or run(1)?: ";
        bool option;
        cin >> option;

        if(option == 0)
            toggleCell(field);
        else
            run(field);
    }

    return 0;
}