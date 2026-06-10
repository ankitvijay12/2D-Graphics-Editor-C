#include <stdio.h>
#define ROWS 30
#define COLS 60
#define MAX_SHAPES 100

char canvas[ROWS][COLS];

int shapeType[MAX_SHAPES];
int sRow[MAX_SHAPES], sCol[MAX_SHAPES];
int sW[MAX_SHAPES], sH[MAX_SHAPES];
int shapeCount = 0;

/* Function Prototypes */
void initializeCanvas();
void clearCanvas();
void displayCanvas();

void drawLine(int row, int col, int length);
void drawRectangle(int row, int col, int width, int height);
void drawTriangle(int row, int col, int size);
void drawCircle(int centerX, int centerY, int radius);

void redrawAll();
void addShape();
void deleteShape();

/* Canvas Functions */
void initializeCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = ' ';
        }
    }
}

void clearCanvas()
{
    initializeCanvas();
}

void displayCanvas()
{
    printf("\n");
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

/* Drawing Functions */
void drawLine(int row, int col, int length)
{
    for(int i = 0; i < length && col + i < COLS; i++)
    {
        if (row >= 0 && row < ROWS)
        {
            canvas[row][col + i] = '*';
        }
    }
}

void drawRectangle(int row, int col, int width, int height)
{
    for(int i = 0; i < width; i++)
    {
        if(col + i < COLS)
        {
            if (row >= 0 && row < ROWS) {
                canvas[row][col + i] = '*';
            }
            if (row + height - 1 >= 0 && row + height - 1 < ROWS) {
                canvas[row + height - 1][col + i] = '*';
            }
        }
    }

    for(int i = 0; i < height; i++)
    {
        if(row + i < ROWS)
        {
            if (col >= 0 && col < COLS) {
                canvas[row + i][col] = '*';
            }
            if (col + width - 1 >= 0 && col + width - 1 < COLS) {
                canvas[row + i][col + width - 1] = '*';
            }
        }
    }
}

void drawTriangle(int row, int col, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(row + i < ROWS && col + i < COLS)
        {
            canvas[row + i][col] = '*';
            canvas[row + size - 1][col + i] = '*';
            canvas[row + i][col + i] = '*';
        }
    }
}

void drawCircle(int centerX, int centerY, int radius)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            int dx = i - centerX;
            int dy = j - centerY;
            int d = dx * dx + dy * dy;

            if(d >= radius * radius - radius && d <= radius * radius + radius)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

/* Shape Management */
void redrawAll()
{
    clearCanvas();

    for(int i = 0; i < shapeCount; i++)
    {
        switch(shapeType[i]) /* FIXED: Changed from shapeType[1] to shapeType[i] */
        {
            case 1:
                drawLine(sRow[i], sCol[i], sW[i]);
                break;
            case 2:
                drawRectangle(sRow[i], sCol[i], sW[i], sH[i]);
                break;
            case 3:
                drawCircle(sRow[i], sCol[i], sW[i]);
                break;
            case 4:
                drawTriangle(sRow[i], sCol[i], sW[i]);
                break;
        }
    }
}

void addShape()
{
    if(shapeCount >= MAX_SHAPES)
    {
        printf("Shape storage full!\n");
        return;
    }

    printf("\n1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");

    printf("Enter Shape Type: ");
    scanf("%d", &shapeType[shapeCount]);

    printf("Enter Row and Column: ");
    scanf("%d%d", &sRow[shapeCount], &sCol[shapeCount]);

    printf("Enter Size/Width/Radius: ");
    scanf("%d", &sW[shapeCount]);

    if(shapeType[shapeCount] == 2)
    {
        printf("Enter Height: ");
        scanf("%d", &sH[shapeCount]);
    }
    else
    {
        sH[shapeCount] = 0;
    }

    shapeCount++;
    redrawAll();
    printf("Shape Added Successfully.\n");
}

void deleteShape()
{
    int index;

    if(shapeCount == 0)
    {
        printf("No shapes available.\n");
        return;
    }

    printf("Enter Shape Number to Delete (1-%d): ", shapeCount);
    scanf("%d", &index);

    index--;

    if(index < 0 || index >= shapeCount)
    {
        printf("Invalid Shape Number.\n");
        return;
    }

    for(int i = index; i < shapeCount - 1; i++)
    {
        shapeType[i] = shapeType[i + 1];
        sRow[i] = sRow[i + 1];
        sCol[i] = sCol[i + 1];
        sW[i] = sW[i + 1];
        sH[i] = sH[i + 1];
    }

    shapeCount--;
    redrawAll();
    printf("Shape Deleted Successfully.\n");
}

/* Main Function */
int main()
{
    int choice;
    initializeCanvas();

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Display Canvas\n");
        printf("4. Clear Canvas\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;
            case 2:
                deleteShape();
                break;
            case 3:
                displayCanvas();
                break;
            case 4:
                clearCanvas();
                shapeCount = 0;
                printf("Canvas Cleared.\n");
                break;
            case 5:
                printf("Exiting Program...\n");
                break;
            default:
                printf("Invalid Choice.\n");
        }

    } while(choice != 5);

    return 0;
}