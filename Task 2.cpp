#include<iostream>
#include<string>
#include<cstdlib>
#include <cstdio>
using namespace std;

//Each Pair object holds a pair that meets the criteria
//To save memory and for increased flexibility, a linked list
//approach was followed rather than using array of Pair objects
class Pair{
public:
    Pair* next; //to hold pointer to the next element in the list
    int members[2];
    void SetPair(int n1,int n2)
    {
        //Keep the larger element first in the pair to match the output pattern
        if(n1>n2)
        {
            members[0] = n1;
            members[1] = n2;
        }
        else
        {
            members[0] = n2;
            members[1] = n1;
        }
    }
    int* GetPair()
    {
        return members;
    }
};

Pair* head; //the pointer to the first element in the list
int numArrayLength=1000; //since 1<=n<=1000
int numOfInputs;
int numOfPairs; //total number of pairs found

void InsertPair(int n1,int n2)
{
    Pair* temp= new Pair();
    temp->SetPair(n1,n2);
    temp->next=head;
    head=temp;
}

int CharToInt(char c)
{
    return (int)c-48; //since ASCII value of character '0' is 48, '1' is 49 and so on
}

//to convert the whole string input to array of numbers
void StringToNumArray(string arr,int* numArr)
{
    int j = 1;
    numOfInputs = 0;
    int mul = 1, n;
    for(int i=1;i<arr.length();i++)
    {
        if(arr[i]==','||arr[i]==']')
        {
            string s = arr.substr(j,i-1); //taking the characters in between commas
            numArr[numOfInputs] = 0;
            for(int k=i-1;k>=j;k--) //calculating the number from individual digits, e.g. (1*100) + (2*10) + (3*1) = 123
            {
                if(arr[k]!='-')
                {
                    n = CharToInt(arr[k]);
                    n *= mul;
                    numArr[numOfInputs] += n;
                    mul *= 10;
                }
                else
                {
                    numArr[numOfInputs] *= -1;
                }
            }
            mul = 1;
            j=i+2; //since there is a space after comma
            numOfInputs++;
        }
    }
}

void FindPairs(int* arr,int target)
{
    for(int i=0;i<numOfInputs;i++)
    {
        for(int j=i+1;j<numOfInputs;j++)
        {
            if(abs(arr[i]-arr[j]) == target)
                {
                    InsertPair(arr[i],arr[j]);
                    numOfPairs++;
                }
        }
    }
}

void PrintAns()
{
    if(numOfPairs!=0)
    {
        Pair* temp=head;
        int* a;
        cout<<numOfPairs<<" -> ";
        while(temp->next!=NULL)
        {
            a = temp->GetPair();
            cout<<"["<<a[0]<<","<<a[1]<<"]"<<", ";
            temp=temp->next;
        }
        a = temp->GetPair();
        cout<<"["<<a[0]<<","<<a[1]<<"]";
    }
    else
    {
        cout<<"o";
    }
}

int main()
{
    string arr;
    int target;
    head = NULL;
    numOfPairs=0;

    getline(cin,arr);
    cin>>target;

    int numArr[numArrayLength];
    StringToNumArray(arr,numArr);

    FindPairs(numArr,target);
    PrintAns();

    return 0;
}
