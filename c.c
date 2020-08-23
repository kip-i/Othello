#include <stdio.h>
/*課題メモ
×1.プレイヤー1を入力できるようにしたい
×2.オセロのコマを○と●にしたい
×3.置くところがない時の処理
×4.終了の処理
×5.勝敗の処理
×6.●したい（4つの3*3の位置に）
×7.端っこの時にバグってる(0 4)
*/
//----------------------------------------------------------------
//表示
int display(int board[10][10])
{
    int i,j;
    //一行目
    printf("   |");
    for(i=1;i<=8;i++)
    {
        printf(" %d |",i);
        if(i==8)
        {
            printf("\n");
        }
    }
    //二行目
    for(i=0;i<36;i++)
    {
        if(i==3||i==7||i==11||i==15||i==19||i==23||i==27||i==31)
        {
            printf("+");
        }
        else
        {
            if(i==35)
            {
                printf("|\n");
            }
            else
            {
                printf("=");
            }            
        }
    }
    //表
    for(i=1;i<=8;i++)
    {
        //左の表示
        printf(" %d |",i);
        for(j=1;j<=8;j++)
        {
            if(board[i][j]==0)
            {
                printf("   |");
            }
            else
            {
                if(board[i][j]==1)
                {
                    printf(" ● |");
                }
                else
                {
                    printf(" ○ |");
                }
            }
            if(j==8)
            {
                printf("\n");
            }
        }
        //仕切り
        for(j=0;j<36;j++)
        {
            if(i!=8)
            {
                if(i==2||i==6)
                {
                    if(j==11||j==27)
                    {
                        printf("●");
                    }
                    else
                    {
                        if(j==3||j==7||j==15||j==19||j==23||j==31)
                        {
                            printf("+");
                        }
                        else
                        {
                            if(j==35)
                            {
                                printf("|\n");
                            }
                            else
                            {
                                printf("-");
                            }
                        }
                    }
                }
                else
                {
                    if(j==3||j==7||j==11||j==15||j==19||j==23||j==27||j==31)
                    {
                        printf("+");
                    }
                    else
                    {
                        if(j==35)
                        {
                            printf("|\n");
                        }
                        else
                        {
                            printf("-");
                        }
                    }
                }
            }
            else
            {
                printf("-");
                if(j==35)
                {
                    printf("\n");
                }
            }
        }
    }
    return 0;
}
//----------------------------------------------------------------
//プレイヤー1の確認
int confirm1(int row,int col,int board[10][10])
{
    int i,j,around[3]={-1,0,1},rowsum=0,colsum=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[row+around[i]][col+around[j]]==2)
            {
                while(board[row+around[i]+rowsum][col+around[j]+colsum]==2)
                {
                    rowsum=rowsum+around[i];
                    colsum=colsum+around[j];            
                }
                if(board[row+around[i]+rowsum][col+around[j]+colsum]==1)
                {
                    return 1;//あったとき1で返す
                }
                rowsum=0;
                colsum=0;
            }
        }
    }
    return 2;//なかったとき2で返す
}
//----------------------------------------------------------------
//プレイヤー2の確認
int confirm2(int row,int col,int board[10][10])
{
    int i,j,around[3]={-1,0,1},rowsum=0,colsum=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[row+around[i]][col+around[j]]==1)
            {
                while(board[row+around[i]+rowsum][col+around[j]+colsum]==1)
                {
                    rowsum=rowsum+around[i];
                    colsum=colsum+around[j];            
                }
                if(board[row+around[i]+rowsum][col+around[j]+colsum]==2)
                {
                    return 2;//あったとき1で返す
                }
                rowsum=0;
                colsum=0;
            }
        }
    }
    return 1;//なかったとき2で返す
}
//----------------------------------------------------------------
//空欄マスの特定
int mass(int board[10][10],int player)
{
    int i,j,judgment=0;
    int none=0;
    for(i=1;i<=8;i++)
    {
        for(j=1;j<=8;j++)
        {
            if(board[i][j]==0)
            {
                if(player==1)
                {
                    judgment = confirm1(i,j,board);
                    if(judgment==1)
                    {
                        return judgment;
                    }
                }
                else
                {
                    judgment = confirm2(i,j,board);
                    if(judgment==2)
                    {
                        return judgment;
                    }
                }
                none=1;
            }
        }
    }
    if(none==0)
    {
        return 3;
    }
    return judgment;
}
//----------------------------------------------------------------
//プレイヤー1の配置
int input1(int board[10][10],char name[1024])    
{    
    int loop = 1, row=0, col=0, around[3]={-1,0,1},i,j,k,rowsum=0,colsum=0,coount=0;
    while(loop==1)
    {
        printf("●%sさん、置きたいマスの\"行 列\"を入力してください：",name);
        scanf("%d %d",&row,&col);
        if(board[row][col]==1||board[row][col]==2)
        {
            printf("すでにコマが置いてあります.もう一度入力してください.\n");
        }
        else
        {
            if(board[row][col]==3)
            {
                printf("1~8で入力してください.ここは場外です.\n");
            }
            loop=0;
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[row+around[i]][col+around[j]]==2)
            {
                while(board[row+around[i]+rowsum][col+around[j]+colsum]==2)
                {
                    rowsum=rowsum+around[i];
                    colsum=colsum+around[j];
                    coount++;
                }
                if(board[row+around[i]+rowsum][col+around[j]+colsum]==1)
                {
                    for(k=0;k<=coount;k++)
                    {
                        board[row+around[i]*k][col+around[j]*k]=1;
                        loop=1;
                    }
                }
            }
            rowsum=0;
            colsum=0;
            coount=0;
        }
    }
    if(loop==1)
    {
        return 2;
    }
    else
    {
        printf("\aそこには置けません.\nもう一度入力してください.\n");
        return 1;
    }
}
//----------------------------------------------------------------
//プレイヤー2の配置
int input2(int board[10][10],char name[1024])    
{    
    int loop = 1, row=0, col=0, around[3]={-1,0,1},i,j,k,rowsum=0,colsum=0,coount=0;
    while(loop==1)
    {
        printf("○%sさん、置きたいマスの\"行 列\"を入力してください：",name);
        scanf("%d %d",&row,&col);
        if(board[row][col]==1||board[row][col]==2)
        {
            printf("すでにコマが置いてあります.もう一度入力してください.\n");
        }
        else
        {
            if(board[row][col]==3)
            {
                printf("1~8で入力してください.ここは場外です.\n");
            }            
            loop=0;
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[row+around[i]][col+around[j]]==1)
            {
                while(board[row+around[i]+rowsum][col+around[j]+colsum]==1)
                {
                    rowsum=rowsum+around[i];
                    colsum=colsum+around[j];
                    coount++;
                }
                if(board[row+around[i]+rowsum][col+around[j]+colsum]==2)
                {
                    for(k=0;k<=coount;k++)
                    {
                        board[row+around[i]*k][col+around[j]*k]=2;
                        loop=1;

                    }    
                }
            }
            rowsum=0;
            colsum=0;
            coount=0;
        }
    }
    if(loop==1)
    {
        return 1;
    }
    else
    {
        printf("\aそこには置けません.\nもう一度入力してください.\n");
        return 2;
    }
}
//----------------------------------------------------------------
//main関数
int main(void)
{
    int i, j,loop=1;
    //--------------------------------
    //初期化
    int board[10][10];
    for(i=0;i<10;i++)
    {
        if(i==0||i==9)
        {
            for(j=0;j<10;j++)
            {
                board[i][j]=3;
            }
        }
        else
        {            
            if(j==0||j==9)
            {
                board[i][j]=3;
            }
            else
            {
                for(j=0;j<10;j++)
                {
                    board[i][j]=0;
                }   
            }
        }
    }
    board[4][5]=board[5][4] = 1; 
    board[5][5]=board[4][4] = 2; 
    //名前登録
    char play_1[1024],play_2[1024];
    printf("●プレイヤー1さんの名前を登録してください:");
    scanf("%s",play_1);
    printf("○プレイヤー2さんの名前を登録してください:");
    scanf("%s",play_2);
    display(board);
    //--------------------------------    
    //入力処理
    while(loop==1||loop==2)
    {
        if(loop==1)//1pの確認
        {
            loop=mass(board,loop);
            if(loop==2)
            {
                loop=mass(board,loop);
                if(loop==1)
                {
                    printf("%sさん,%sさんともに置く位置がありません.\n",play_1,play_2);
                    loop=3;
                }
                else
                {
                    printf("%sさんの置く位置がありません.\n%sさんのターンになります.\n",play_1,play_2);
                    break;
                }
            }
        }
        else//2pの確認
        {
            loop=mass(board,loop);
            if(loop==1)
            {
                loop=mass(board,loop);
                if(loop==2)
                {
                    printf("%sさん,%sさんともに置く位置がありません.\n",play_2,play_1);
                    loop=3;
                }
                else
                {
                    printf("%sさんの置く位置がありません.\n%sさんのターンになります.\n",play_2,play_1);
                    break;
                }
            }
        }
        if(loop==1)//置く処理
        {
            loop=input1(board,play_1);
            display(board);
        }
        else
        {
            if(loop==2)
            {
                loop=input2(board,play_2);
                display(board);
            }
        }
    }
    printf("終了しました.\n");
    //--------------------------------    
    //コマの数判定
    int one_point=0,two_point=0;
    for(i=1;i<=8;i++)
    {
        for(j=1;j<=8;j++)
        {
            if(board[i][j]==1)
            {
                one_point++;
            }
            else
            {
                if(board[i][j]==2)
                {
                    two_point++;
                }
            }
        }
    }
    printf("%sさんは%d個と%sさんは%d個で",play_1,one_point,play_2,two_point);
    if(one_point==two_point)
    {
        printf("同点でした.");
    }
    else
    {
        if(one_point>two_point)
        {
            printf("%sさんが勝ちました.",play_1);
        }
        else
        {
            printf("%sさんが勝ちました.",play_2);
        }
    }
    return 0;
}