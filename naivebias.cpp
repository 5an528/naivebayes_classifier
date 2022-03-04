#include<iostream>
#include<vector>
#include<fstream>
#include<cctype>
#include <cctype>
#include <cstring>
#include <cstdio>

using namespace std;


vector<string>att;
vector<string>classf;

string str1[100],str2[100];
int countv = 0,c = 0;
bool flag = false;

struct classStructure
{
    string name1,name2;
    int countnum=0;
    double pri;
} likelyhd[10];


struct priorStructure
{
    string classString;
    int nmb = 0;
    double pr;
} priorknowledge[10];

void likelyhood()
{
    for(int j=0; j<classf.size(); j++)
    {
        for(int k=0; k<att.size(); k++)
        {
            likelyhd[c].name1 = att[k];
            likelyhd[c].name2 = classf[j];
            c++;

        }
    }
    int temp = 0;
    for(int j=0; j<classf.size(); j++)
    {
        for(int k=0; k<att.size(); k++)
        {
            for(int i=0; i<countv; i++)
            {
                if(str2[i]==classf[j] && str1[i]==att[k])
                {
                    likelyhd[temp].countnum++;
                }
            }
            temp++;
        }
    }
    for(int i=0; i<c; i++)
    {
        if(i%2==1)
        {
            likelyhd[i].pri = likelyhd[i].countnum/(likelyhd[i].countnum+likelyhd[i-1].countnum+0.00);
        }
        else
        {
            likelyhd[i].pri = likelyhd[i].countnum/(likelyhd[i].countnum+likelyhd[i+1].countnum+0.00);
        }
    }
    for(int i=0; i<c; i++)
    {
        cout<<likelyhd[i].name1<<" eared "<<likelyhd[i].name2<<" = "<<likelyhd[i].countnum<<" Probability "<<likelyhd[i].pri<<endl;
    }
    cout<<endl;
    int oj=c-1;
    ofstream outobj("result.txt", ios::out | ios::trunc);
    while(oj>=0)
    {
        outobj<<likelyhd[oj].name1<<" ";
        outobj<<likelyhd[oj].name2<<" ";
        outobj<<likelyhd[oj].pri<<endl;
        oj--;
    }
}

void train()
{

    ifstream inp("data.txt");
    while(inp>>str1[countv])
    {
        inp>>str2[countv];
        flag = false;
        for(int i=0; i<att.size(); i++)
        {
            if(str1[countv]==att[i])
            {
                flag = true;
            }
        }
        if(!flag)
        {
            att.push_back(str1[countv]);
        }
        flag = false;
        for(int i=0; i<classf.size(); i++)
        {
            if(str2[countv]==classf[i])
            {
                flag = true;
            }
        }
        if(!flag)
        {
            classf.push_back(str2[countv]);
        }
        countv++;
    }
    cout<<endl;
    cout<<att.size()<<" attributes have been found."<<endl;
    cout<<classf.size()<<" classes have been found."<<endl;

    for(int i=0; i<classf.size(); i++)
    {
        for(int j=0; j<countv; j++)
        {
            if(str2[j]==classf[i])
            {
                priorknowledge[i].nmb++;
            }
        }
        priorknowledge[i].classString = classf[i];
        priorknowledge[i].pr = priorknowledge[i].nmb/(countv+0.00);
    }
    int itmp = 0;
    ofstream obja("savedata.txt");
    while(itmp<classf.size())
    {
        obja<<priorknowledge[itmp].classString<<" "<<priorknowledge[itmp].pr<<endl;
        itmp++;
    }
    cout<<endl;
    cout<<endl;
    cout<<"Classes Parentage are given below --> "<<endl;
    for(int i=0; i<classf.size(); i++)
    {
        cout<<priorknowledge[i].classString<<" ";
        cout<<priorknowledge[i].pr*100<<"%"<<endl;
    }
    cout<<endl;
    likelyhood();
}


void predict()
{
    int input;
    string x1[10],x2[10],x3[10],usergiven,evaluatedclass;
    double priority1[10],priority2[10],rslt=-1;
    double gg[10];
    int l1 = 0,l2 = 0;
    while(1)
    {
        cout<<endl<<"Press 1 For Small ear result."<<endl<<"Press 2 for Big ear result."<<endl;
        cin>>input;
        if(input==1)
            {
                usergiven="small";
                break;
            }
        else if(input==2)
            {
                usergiven="big";
                break;
            }
        else
            cout<<endl<<"You have entered the wrong select. PLEASE TRY AGAIN!!!!"<<endl<<endl;
    }
    cout<<"You Choose "<<usergiven<<" ear result."<<endl<<endl;
    ifstream inpobj("result.txt");
    while(inpobj>>x1[l1])
    {
        inpobj>>x2[l1];
        inpobj>>priority1[l1];
        cout<<x1[l1]<<" eared "<<x2[l1]<<" predicted value --> "<<priority1[l1]*100<<"%"<<endl;
        l1++;
    }
    cout<<endl;
    ifstream inpobjb("savedata.txt");

    while(inpobjb>>x3[l2])
    {
        inpobjb>>priority2[l2];
        cout<<"Probability of "<<x3[l2]<<" is "<<priority2[l2]*100<<"%"<<endl;
        l2++;
    }
    cout<<endl;
    for(int i=0; i<l1; i++)
    {
        for(int j=0; j<l2; j++)
        {
            if(x1[i]==usergiven && x3[j]==x2[i] && rslt<priority1[i]*priority2[j])
            {
                evaluatedclass = x2[i];
                rslt = priority1[i]*priority2[j];
            }
        }
    }



    if(rslt!=-1)
        cout<<endl<<"SO THE CLASS IS "<<evaluatedclass<<endl<<endl;
    else
        cout<<"ERROR404: NOT FOUND"<<endl;

    cout<<"Combined Result is "<<rslt*100<<"%"<<endl<<endl;


}
int main()
{

    char select;
    while(1)
    {
        cout<<"Press 1 to Train this code.\nPress 2 to Predict the result.\nPress 3 to Exit.\n";
        cin>>select;
        if(select=='1')
        {
            train();
        }
        else if(select=='2')
        {
            predict();
        }
        else if(select=='3')
        {
            cout<<endl<<endl<<"***** Thank You So Much *****"<<endl<<endl;
            break;
        }
        else
        {
            cout<<"You have entered the wrong select. PLEASE TRY AGAIN!!!!"<<endl<<endl;
        }
    }
}

