include <stdio.h>

char canvas[30][60];

void initializeCanvas();
void clearCanvas();
void displayCanvas();
void drawLine(int row, int col, int length);
void drawRectangle(int row, int col, int width, int height);

void initializeCanvas()
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            canvas[i][j]=' ';
        }
    }
}

void clearCanvas()
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            canvas[i][j]=' ';
        }
    }
}

void displayCanvas()
{
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<60;j++)
        {
            printf("%c",canvas[i][j]);
        }
        printf("\n");
    }
}

void drawLine(int row, int col, int length)
{
    for(int i=0;i<length;i++)
    {
        canvas[row][col+i]='*';
    }
}

void drawRectangle(int row, int col, int width, int height)
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

    } while(choice != 5);

    return 0;
}