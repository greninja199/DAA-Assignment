#include<iostream>
#include<stdio.h>

using namespace std;

struct city
{
  int value;
  int weight;
}
int main()
{
  int n,m;
  cout<<"Enter the number of city ";
  cin>>n;
  city cities[n];
  cout<<"Enter the details of the city given its value and weight "<<endl;
  for(int i=0;i<n;i++)
  {
    cin>>cities[i].value>>cities[i].weight;
  }
  cout<<"Enter the number of the edges ";
  cin>>m;
  int dist[m][3];
  cout<<"Enter the source city no.(0-n-1), destination and distance between them ";
  for(int i=0;i<m;i++)
  {
    cin>>dist[i][0]>>dist[i][1]>>dist[i][2];
  }
  int source , destination;
  cout<<"Enter the source city number and destination city number ";
  cin>>source>>destination;

  //  KNAPSACK PART

  //AFTER KNAPASACK CALCULATING PART DIJKITSRA ALGORITHM
  int distfromsource[m];
  for(int i=0;i<m;i++)
  {
    if(i==source-1)
      distfromsource[i]=0;
    else
      distfromsource[i]=500;
  }

  for(int i=0;i<n-1;i++)
  {
    for(int j=0;j<m;j++)
    {
      if((distfromsource[(dist[j][0])] != 500) && (distfromsource[dist[j][1]] > distfromsource[dist[j][0]] + dist[j][2]))
      {
        distfromsource[dist[j][1]] = distfromsource[dist[j][0]] + dist[j][2];s
      }
    }
  }

}
