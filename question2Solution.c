#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
    int n,m=0;
    printf("Enter the number of city ");
    scanf("%d",&n);
    int cities[n][2];
    for(int i=0;i<n;i++)
    {
        cities[i][0] = rand() % 500 + 500;  //value
        cities[i][1] = rand() % 50+1;       //weight
    }
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\n",cities[i][0],cities[i][1]);
    }
    while(!(m>=n-1 && m<= n * (n-1)))
    {
        m=rand()%(n*(n-1));
    }
    printf("the number of the edges %d\n",m);
    int dist[m][3];
    for(int i=0;i<n-1;i++)
    {
        dist[i][0]=i;
        dist[i][1]=i+1;
        dist[i][2]=rand()%9+1;
    }
    for(int i=n-1;i<m;i++)
    {
        int x,y,count;
        do {
            x = rand()%n;
            y = rand()%n;
            count=0;
            for(int j=0;j<i && count==0;j++)
            {
                if((x == dist[j][0] && y == dist[j][1]) || (x == dist[j][1] && y == dist[j][0]) )
                    count++;
            }
        } while(count==0 && x!=y);
        dist[i][0]=x;
        dist[i][1]=y;
        dist[i][2]= rand()%9+1;
    }
    int source , destination;
    for(int i=0;i<m;i++)
    {
        printf("%d\t%d\t%d\n",dist[i][0],dist[i][1],dist[i][2]);
    }
    printf("Enter the source city number and destination city number ");
    scanf("%d %d",&source,&destination);
    int max=0;        //max value till ye

    int s=source;    //source city
    int d=destination;    //destination city
    int r1;   //restricted city 1
    int r2;   //restricted city 2
    cities[s][0]=0;
    cities[d][0]=0;
    printf("Enter the restricted cities ");
    scanf("%d %d",&r1,&r2);
    cities[r1][0]=0;
    cities[r2][0]=0;

    int c1=-1;   //city1 select
    int c2=-1;   //city2 select
    int c3=-1;   //city3 select

    int i,j,k;

    for(i=0;i<n;i++)    // to selcet 1st city
    {
        if(i!=s && i!=d && i!=r1 && i!=r2) // check if the select city is either source destination or one of restricted city
        {
            int curr_value_i=cities[i][0];   //value of knapsack in ith city
            //cout<<curr_value_i;
            int curr_weight_i=cities[i][1];   //weight of knapsack in ith city
            for(j=i+1;j<n;j++) // to select 2nd city
            {
                if(j!=s && j!=d && j!=r1 && j!=r2)  // check if the select city is either source destination or one of restricted city
                {
                    int curr_value_j=cities[j][0]+curr_value_i;   //calculating value of knapsack in jth city
                    //cout<<curr_value_j;
                    int curr_weight_j=cities[j][1]+curr_weight_i; //calculating weight of knapsack in jth city
                    for(k=j+1;k<n;k++)
                    {
                        if(k!=s && k!=d && k!=r1 && k!=r2)    // check if the select city is either source destination or one of restricted city
                        {
                            int curr_weight_k = curr_weight_j + cities[k][1];  //calculating weight of knapsack in kth city
                            int curr_value_k = curr_value_j + cities[k][0];    //calculating value of knapsack in kth city
                            //cout<<curr_value_k;
                            if(curr_weight_k < 101) // if we get weight is less than 100
                            {
                                if(curr_value_k >= max)    // if we get value more than current maximum
                                {
                                    max=curr_value_k;
                                    c1=i;
                                    c2=j;
                                    c3=k;
                                }
                            }
                        }
                    }
                    if(curr_weight_j < 101)   // if we get weight is less than 100
                    {
                        if(curr_value_j >= max)  // if we get value more than current maximum
                        {
                            max=curr_value_j;
                            c1=i;
                            c2=j;
                            c3=-1;
                        }
                    }
                }
            }
            if(curr_weight_i < 101)   // if we get weight is less than 100
            {
                if(curr_value_i >= max)  // if we get value more than current maximum
                {
                    max=curr_value_i;
                    c1=i;
                    c2=-1;
                    c3=-1;
                }
            }
        }
    }
    max = cities[c1][0] + cities[c2][0] + cities[c3][0];
    printf("The cities selected are: \nCITY1=%d \nCITY2=%d \nCITY3=%d\n\nMAX PROFIT=%d\n",c1,c2,c3,max);
    //AFTER KNAPASACK CALCULATING PART Belman ford ALGORITHM
    int source1=source;
    int distfromsource[n];    //distance of every vertex from source
    for(i=0;i<n;i++)
    {
        if(i==source1)
            distfromsource[i]=0;
        else
            distfromsource[i]=500;
    }
    for(i=0;i<n-1;i++)    //bellman ford algorithm
    {
        for(j=0;j<m;j++)
        {
            if((distfromsource[(dist[j][0])] != 500) && (distfromsource[dist[j][1]] > distfromsource[dist[j][0]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][1]] = distfromsource[dist[j][0]] + dist[j][2];
            }
            else if((distfromsource[(dist[j][1])] != 500) && (distfromsource[dist[j][0]] > distfromsource[dist[j][1]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][0]] = distfromsource[dist[j][1]] + dist[j][2];
            }
        }
    }
    int min_city=c1,min1= distfromsource[c1];
    if(distfromsource[c2] < min1)
    {
        min_city=c2;
        min1=distfromsource[c2];
        c2=c3;
    }
    else if(distfromsource[c3] < min1)
    {
        min_city=c3;
        min1=distfromsource[c3];
    }
    else
    {
        c1=c2;
        c2=c3;
    }
    printf("\nNEXT HOP=%d \t DISTANCE=%d",min_city,min1);
    int source2=min_city;     //selecting first city as next source
    for(i=0;i<n;i++)
    {
        if(i==source2)
            distfromsource[i]=0;
        else
            distfromsource[i]=500;
    }
    for(i=0;i<n-1;i++)    //bellman ford algorithm
    {
        for(j=0;j<m;j++)
        {
            if((distfromsource[(dist[j][0])] != 500) && (distfromsource[dist[j][1]] > distfromsource[dist[j][0]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][1]] = distfromsource[dist[j][0]] + dist[j][2];
            }
            else if((distfromsource[(dist[j][1])] != 500) && (distfromsource[dist[j][0]] > distfromsource[dist[j][1]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][0]] = distfromsource[dist[j][1]] + dist[j][2];
            }
        }
    }
    min_city=c1;
    int min2 = distfromsource[c1];
    if(distfromsource[c2] < min2)
    {
        min2 = distfromsource[c2];
        min_city = c2;
    }
    else
    {
        c1=c2;
    }       // second city from first city
    printf("\nNEXT HOP=%d\tDISTANCE=%d",min_city,min2);
    int source3 = min_city;   //selecting second city as source
    for(i=0;i<n;i++)
    {
        if(i==source3)
            distfromsource[i]=0;
        else
            distfromsource[i]=500;
    }
    for(i=0;i<n-1;i++)    //bellman ford algorithm
    {
        for(j=0;j<m;j++)
        {
            if((distfromsource[(dist[j][0])] != 500) && (distfromsource[dist[j][1]] > distfromsource[dist[j][0]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][1]] = distfromsource[dist[j][0]] + dist[j][2];
            }
            else if((distfromsource[(dist[j][1])] != 500) && (distfromsource[dist[j][0]] > distfromsource[dist[j][1]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][0]] = distfromsource[dist[j][1]] + dist[j][2];
            }
        }
    }   // Third city from second city
    int min3 = distfromsource[c1];
    printf("\nNEXT HOP=%d\tDISTANCE=%d",c1,min3);
    int source4=c1;
    for(i=0;i<n;i++)
    {
        if(i==source4)
            distfromsource[i]=0;
        else
            distfromsource[i]=500;
    }
    for(i=0;i<n-1;i++)    //bellman ford algorithm
    {
        for(j=0;j<m;j++)
        {
            if((distfromsource[(dist[j][0])] != 500) && (distfromsource[dist[j][1]] > distfromsource[dist[j][0]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][1]] = distfromsource[dist[j][0]] + dist[j][2];
            }
            else if((distfromsource[(dist[j][1])] != 500) && (distfromsource[dist[j][0]] > distfromsource[dist[j][1]] + dist[j][2]) && dist[j][0]!=r1 && dist[j][1]!=r2)
            {
                distfromsource[dist[j][0]] = distfromsource[dist[j][1]] + dist[j][2];
            }
        }
    }   //destination from last city
    int min4=distfromsource[destination];
    printf("\nNEXT HOP=%d\t DISTANCE=%d\nMINIMUM DISTANCE=%d\n",destination,min4,min1+min2+min3+min4);
}
