#include <stdio.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

void initializeCanvas();
void clearCanvas();
void displayCanvas();

void drawLine(int row, int col, int length);
void drawRectangle(int row, int col, int width, int height);

void initializeCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            canvas[i][j]=' ';
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

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(int row,int col,int length)
{
    for(int i=0;i<length && col+i<COLS;i++)
    {
        canvas[row][col+i]='*';
    }
}

void drawRectangle(int row,int col,int width,int height)
{
    for(int i=0;i<width;i++)
    {
        canvas[row][col+i]='*';
        canvas[row+height-1][col+i]='*';
    }

    for(int i=0;i<height;i++)
    {
        canvas[row+i][col]='*';
        canvas[row+i][col+width-1]='*';
    }
}

int main()
{
    int choice;

    initializeCanvas();

    do
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Display Canvas\n");
        printf("4. Clear Canvas\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            {
                int row,col,length;
                printf("Enter row col length: ");
                scanf("%d%d%d",&row,&col,&length);

                drawLine(row,col,length);
                break;
            }

            case 2:
            {
                int row,col,width,height;

                printf("Enter row col width height: ");
                scanf("%d%d%d%d",&row,&col,&width,&height);

                drawRectangle(row,col,width,height);
                break;
            }

            case 3:
                displayCanvas();
                break;

            case 4:
                clearCanvas();
                printf("Canvas Cleared\n");
                break;

            case 5:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    }while(choice!=5);

    return 0;
}
#include <stdio.h>

#define ROWS 30
#define COLS 60
#define MAX_SHAPES 100

char canvas[ROWS][COLS];

int shapeType[MAX_SHAPES];
int sRow[MAX_SHAPES], sCol[MAX_SHAPES];
int sW[MAX_SHAPES], sH[MAX_SHAPES];
int shapeCount = 0;

void initializeCanvas();
void clearCanvas();
void displayCanvas();

void drawLine(int row,int col,int length);
void drawRectangle(int row,int col,int width,int height);
void drawTriangle(int row,int col,int size);
void drawCircle(int centerX,int centerY,int radius);

void redrawAll();
void addShape();

void initializeCanvas()
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            canvas[i][j]=' ';
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

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            printf("%c",canvas[i][j]);
        }

        printf("\n");
    }
}

void drawLine(int row,int col,int length)
{
    for(int i=0;i<length && col+i<COLS;i++)
    {
        canvas[row][col+i]='*';
    }
}

void drawRectangle(int row,int col,int width,int height)
{
    for(int i=0;i<width;i++)
    {
        canvas[row][col+i]='*';
        canvas[row+height-1][col+i]='*';
    }

    for(int i=0;i<height;i++)
    {
        canvas[row+i][col]='*';
        canvas[row+i][col+width-1]='*';
    }
}

void drawTriangle(int row,int col,int size)
{
    for(int i=0;i<size;i++)
    {
        canvas[row+i][col]='*';
        canvas[row+size-1][col+i]='*';
        canvas[row+i][col+i]='*';
    }
}

void drawCircle(int centerX,int centerY,int radius)
{
    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            int dx=i-centerX;
            int dy=j-centerY;

            int d=dx*dx+dy*dy;

            if(d>=radius*radius-radius &&
               d<=radius*radius+radius)
            {
                canvas[i][j]='*';
            }
        }
    }
}

void redrawAll()
{
    clearCanvas();

    for(int i=0;i<shapeCount;i++)
    {
        switch(shapeType[i])
        {
            case 1:
                drawLine(sRow[i],sCol[i],sW[i]);
                break;

            case 2:
                drawRectangle(sRow[i],sCol[i],sW[i],sH[i]);
                break;

            case 3:
                drawCircle(sRow[i],sCol[i],sW[i]);
                break;

            case 4:
                drawTriangle(sRow[i],sCol[i],sW[i]);
                break;
        }
    }
}

void addShape()
{
    printf("\n1. Line\n");
    printf("2. Rectangle\n");
    printf("3. Circle\n");
    printf("4. Triangle\n");

    printf("Enter Shape Type: ");
    scanf("%d",&shapeType[shapeCount]);

    printf("Enter Row and Column: ");
    scanf("%d%d",&sRow[shapeCount],&sCol[shapeCount]);

    printf("Enter Size/Width/Radius: ");
    scanf("%d",&sW[shapeCount]);

    if(shapeType[shapeCount]==2)
    {
        printf("Enter Height: ");
        scanf("%d",&sH[shapeCount]);
    }
    else
    {
        sH[shapeCount]=0;
    }

    shapeCount++;

    redrawAll();

    printf("Shape Added Successfully\n");
}

int main()
{
    int choice;

    initializeCanvas();

    do
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Add Shape\n");
        printf("2. Display Canvas\n");
        printf("3. Clear Canvas\n");
        printf("4. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                displayCanvas();
                break;

            case 3:
                clearCanvas();
                shapeCount=0;
                printf("Canvas Cleared\n");
                break;

            case 4:
                printf("Exiting Program...\n");
                break;
        }

    }while(choice!=4);

    return 0;
}
