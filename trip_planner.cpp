#include <bits/stdc++.h> 

 using namespace std; 
int **A;
#define max 9999999 
vector<string> city;
struct flight{
        int source, dest;
        float Cost;
}; 
struct graph{
    int noOfCity, noOfFlight;
    struct flight* flight; 
}; 
struct graph* createmap(int noOfCity, int noOfFlight){     
    struct graph* g= new graph;     
    g->noOfCity= noOfCity;     
    g->noOfFlight= noOfFlight;     
    g->flight= new flight[noOfFlight];     
    return g; 
} 
void print(int n){     
    cout<<"Vertex\t distance from source"<<endl;     
    for(int i=0; i<n; i++){         
        for(int j=0; j<n; j++){
            if(A[i][j]!=0 && A[i][j]!= max){
                cout<<"From "<<city[i]<<" to "<<city[j]<<" cost is "<< A[i][j]<<endl;
            }
        }     
    } 
} 
void lowest_cost(struct graph *g){  //floyd warshall Algorithm
    int noOfCity= g->noOfCity;     
    int noOfFlight= g->noOfFlight;
    A= new int*[noOfCity];
    for(int i=0; i<noOfCity; i++){
        A[i]= new int[noOfCity];
        for(int j=0; j<noOfCity; j++){
            A[i][j]=0;
        }
    }
    for(int i=0; i<noOfFlight; i++){
        int j= g->flight[i].source;
        int k= g->flight[i].dest;
        A[j][k]= g->flight[i].Cost;
    }
    for(int i=0; i<noOfCity; i++){
        for(int j=0; j<noOfCity; j++){
            if(i!=j && A[i][j]==0){
                A[i][j]= max;
            }
        }
    }
    for(int k=0; k<noOfCity; k++){
        for(int i=0; i<noOfCity; i++){
            for(int j=0; j<noOfCity; j++){
                A[i][j]= (A[i][j]<(A[i][k]+A[k][j])? A[i][j] : (A[i][k]+ A[k][j]));
            }
        }
    }
}
int findcity(string s){
    int n= city.size();
    int i, p=0;
    for( i=0; i<n; i++){
        if(city[i]==s){
            p++;
            break;
        }
    }
    if(p==1){
        return i;
    }
    else{
        city.push_back(s);
        return n;
    }
}
int main() {     
    int V;     
    int E;
    cout<<"Enter no of Cities: ";
    cin>>V;
    cout<<"Enter no of flights: ";
    cin>>E;     
    struct graph* gf= createmap(V, E);     
    for(int i=0; i<E; i++){
        string p, q;
        cout<<"Enter details for flight"<<i+1<<" (Use lowercase letter and numbers only) :"<<endl;
        cout<<"Source city :";
        cin>>p;
        gf->flight[i].source= findcity(p);
        cout<<"Destination city :";
        cin>>q;
        gf->flight[i].dest= findcity(q);
        cout<<"Amount of Cost :";
        cin>>gf->flight[i].Cost;
    }
    lowest_cost(gf);
    do{
        int n, i, j;
        cout<<"1: Enter 1 to see lowest cost to travel between 2 cities:"<<endl;
        cout<<"2: Enter 2 to see all the list of lowest cost  between every 2 cities"<<endl;
        cout<<"3: Enter 3 to exit"<<endl;
        cin>>n;
        string p, q;
        switch(n){
            case 1:
                cout<<"Source city :";
                cin>>p;
                i= findcity(p);
                if(i>=V){
                    cout<<"You Entered Wrong Input";
                    city.pop_back();
                    break;
                }
                cout<<"Destination city :";
                cin>>q;
                j= findcity(q);
                if(j>=V){
                    cout<<"You Entered Wrong Input";
                    city.pop_back();
                    break;
                }
                cout<<"The Cost is: "<<A[i][j]<<endl;
                break;
            case 2:
                print(V);
                break;
            case 3:
                cout<<"Thank You"<<endl;
                exit(0);
        }


    }while(1);
    return 0; 
}