#include<iostream>
using namespace std;
class flight
{
    int i,j,n;
    string city[10];
    int tim[10][10];
    public:
    void readdata();
    void displaydata();
};
void flight::readdata()
{
    cout<<"enter no of citys :";
    cin>>n;
    cout<<"enter city names :"<<endl;
    for(i=0;i<n;i++)
    {
        cin>>city[i];
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cout<<"whether route exist between "<<city[i]<<" to "<<city[j]<<" [y/n] ";
            char ch;
            cin>>ch;
            if(ch=='y')
            {
                cout<<"enter distance :";
                cin>>tim[i][j];
            }
            else
            {
            tim[i][j]=0;
            }
        }
    }
}
void flight::displaydata()
{
    cout<<"Graph is:"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<"     "<<city[i];
    }
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<city[i]<<"     ";
        for(j=0;j<n;j++)
        {
       cout<<tim[i][j]<<"     ";
        }
        cout<<endl;
    }
}
int main()
{
    flight f;
    f.readdata();
    f.displaydata();
return 0;
}
