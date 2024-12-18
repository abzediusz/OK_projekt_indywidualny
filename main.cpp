#include<iostream>
#include<vector>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<climits>
#include<fstream>
#include<string>
#include<nlohmann/json.hpp>
#include<stdio.h>
#define MAX 2147483647
using namespace std;
using json = nlohmann::json;
struct droga
{
    int czas;
    int koszt;
};
const double MUTATION_RATE=0.2;
const int GENERATIONS=500;
//const int POPULATION_SIZE=10000;
string toString(int a) {
    string w="";
    while(a>0) {
        w=char(a%10+48)+w;
        a=a/10;
    }
    return w;
}
/*bool** generatorGraph(int n,int d,int k)
{
    fstream outfile;
    string name="input" + itoa(k) + ".json";
    outfile.open(name,ios::out);
    bool** G=new bool* [n];
    for(int i=0;i<n;i++)
    {
        G[i]=new bool [n];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
    {
        G[i][j]=0;
    }
    }
    vector<int> v;
    for(int i=0;i<n;i++)
    {
        v.push_back(i);
    }
    random_shuffle(v.begin(),v.end());
    for(int i=0;i<n-1;i++)
    {
        G[v[i]][v[i+1]]=1;
        G[v[i+1]][v[i]]=1;
    }
    G[v[n-1]][v[0]]=1;
    G[v[0]][v[n-1]]=1;
    int pom;
    srand(time(0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
    {
        if(i!=j && !G[i][j])
        {
            pom=rand()%100+1;
            if(pom<=d)
            {
                G[i][j]=1;
                G[j][i]=1;
            }
        }
    }
    }
    return G;
}
droga** generatorValues(bool** G,int n)
{
    droga** W=new droga* [n];
    for(int i=0;i<n;i++)
    {
        W[i]=new droga [n];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
    {
        W[i][j].czas=-1;
        W[i][j].koszt=-1;
    }
    }
    int pom1,pom2;
    srand(time(0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
    {
        if(G[i][j])
        {
            pom1=rand()%1000+1;
            pom2=rand()%1000+1;
            W[i][j].czas=pom1;
            W[i][j].koszt=pom2;
            W[j][i].czas=pom1;
            W[j][i].koszt=pom2;

        }
    }
    }
    return W;
}*/
/*void brute_force(bool** G,droga** W,int n)
{*/
    /*visited[cur]=1;
    if()
    for(int i=0;i<n;i++)
    {
        if(G[cur][i] && !visited[i])
        {
            *ocena=*ocena+W[cur][i].czas+W[cur][i].koszt;
            vertices.push_back(i);
            brute_force(G,W,vertices,start,i,ocena,n);
        }
    }*/
    /*vector<int> miasta;
    vector<int> best;
    int cur_time=0;
    int cur_cost=0;
    int min_time=MAX;
    int min_cost=MAX;
    bool valid=1;
    int from,to;
    for(int i=0;i<n;i++)
    {
        miasta.push_back(i);
    }
    best=miasta;
    do
    {*/
        /*for(int i=0;i<n;i++)
        {
            cout<<miasta[i]<<" ";
        }
        cout<<miasta[0]<<endl;*/
        /*cur_time=0;
        cur_cost=0;
        valid=1;
        for(int i=0;i<n-1;i++)
        {
            from=miasta[i];
            to=miasta[i+1];
            if(!G[from][to])
            {
                valid=0;
                //cout<<from<<" "<<to<<endl;
                break;
            }
            cur_time+=W[from][to].czas;
            cur_cost+=W[from][to].koszt;
        }
        from=miasta[n-1];
        to=miasta[0];
        if(valid && G[from][to])
        {
            if(cur_time<min_time || (cur_time==min_time && cur_cost<min_cost))
            {
                min_time=cur_time;
                min_cost=cur_cost;
                best=miasta;
            }
        }
    }while(next_permutation(miasta.begin(),miasta.end()));
    for(int i=0;i<n;i++)
    {
        cout<<best[i]<<" ";
    }
    cout<<best[0]<<endl;
    cout<<"Najlepszy czas: "<<min_time<<endl;
    cout<<"Najlepszy koszt: "<<min_cost<<endl;
}*/
void backtracking(bool** G,droga** W,int cur,int n,bool* visited,vector<int>&curPath,vector<int>&bestPath,int curTime,int curCost,int &bestTime,int &bestCost)
{
    if(curPath.size()==n)
    {
        int returnTime=W[cur][curPath[0]].czas;
        int returnCost=W[cur][curPath[0]].koszt;
        if(returnTime!=-1 && returnCost!=-1)
        {
            int totalTime=curTime+returnTime;
            int totalCost=curCost+returnCost;
            if(totalTime<bestTime || (totalTime==bestTime && totalCost<bestCost))
            {
                bestTime=totalTime;
                bestCost=totalCost;
                bestPath=curPath;
                bestPath.push_back(curPath[0]);
            }
        }
        return;
    }
    for(int i=0;i<n;i++)
    {
        if(!visited[i] && G[cur][i])
        {
            visited[i]=true;
            curPath.push_back(i);
            backtracking(G,W,i,n,visited,curPath,bestPath,curTime+W[cur][i].czas,curCost+W[cur][i].koszt,bestTime,bestCost);
            visited[i]=0;
            curPath.pop_back();
        }
    }
}

void findOptimalPath(bool** G,droga** W, int n)
{
    bool* visited=new bool [n];
    for(int i=0;i<n;i++)
    {
        visited[i]=0;
    }
    vector<int> curPath;
    visited[0]=1;
    curPath.push_back(0);
    int bestTime=MAX;
    int bestCost=MAX;
    vector<int> bestPath;
    ofstream plik;
    string name="outputs/"+toString(n)+"_brute-force_out.json";
    plik.open(name,ios::out);
    json out;
    //bestPath.push_back(0);
    backtracking(G,W,0,n,visited,curPath,bestPath,0,0,bestTime,bestCost);
    if(bestTime==MAX || bestCost==MAX)
    {
        out={{"Best_Time",MAX},{"Best_Cost",MAX},{"Best_Path",0}};
        plik<<out;
        plik.close();
        cout<<"Nie ma optymalnej sciezki"<<endl;
    }
    else
    {

        out={{"Best_Time",bestTime},{"Best_Cost",bestCost},{"Best_Path",bestPath}};
        plik<<out;
        plik.close();
        for(int i=0;i<bestPath.size();i++)
    {
        cout<<bestPath[i]<<" ";
    }
    cout<<endl;
    cout<<"Najlepszy czas: "<<bestTime<<endl;
    cout<<"Najlepszy koszt: "<<bestCost<<endl;

    }
}
bool isMember(vector<int> v,int a)
{
    for(int i=0;i<v.size();i++)
    {
        if(v[i]==a)
            return 1;
    }
    return false;
}
bool compare2(pair<int,droga> &a,pair<int,droga> &b)
{
    if(a.second.czas<b.second.czas)
    {
        return 1;
    }
    if(a.second.czas==b.second.czas)
    {
        if(a.second.koszt<b.second.koszt)
        {
            return 1;
        }
        return false;
    }
    return false;
}
void greedy_random(bool** G,droga** W,int n)
{
    vector<bool> visited;
    vector<int> path;
    for(int i=0;i<n;i++)
    {
        visited.push_back(0);
    }
    int totalTime=0;
    int totalCost=0;
    int cur_miasto=0;
    visited[cur_miasto]=1;
    path.push_back(cur_miasto);
    pair<int,droga> next;
    int min_time;
    int min_cost;
    bool flag=0;
    vector<int> dis;
    int i=1;
    srand(time(0));
    int pom;
    vector<pair<int,droga>> neighbours;
    ofstream plik;
    string name="outputs/"+toString(n)+"_greedy-random_out.json";
    plik.open(name,ios::out);
    json out;
    while(i<n)
    {

        /*if(flag)
        {
            cout<<"K"<<endl;
            i--;
        }*/
        //cout<<i<<endl;
        //flag=0;
        //next=-1;
        neighbours.clear();
        min_time=MAX;
        min_cost=MAX;
        for(int j=0;j<n;j++)
        {
            if(G[cur_miasto][j] && !visited[j])
               {
                   neighbours.push_back({j,W[cur_miasto][j]});
               }
        }
        if(neighbours.empty())
        {
            //cout<<i<<endl;
            out={{"Best_Time",MAX},{"Best_Cost",MAX},{"Best_Path",0}};
            plik<<out;
            plik.close();
            cout<<"Nie mozna znalezc optymalnej trasy"<<endl;
            return;
        }
        sort(neighbours.begin(),neighbours.end(),compare2);
        if(neighbours.size()==1)
        {
            next=neighbours[0];
        }
        else if(neighbours.size()==2)
        {
            pom=rand()%2;
            next=neighbours[pom];
        }
        else
        {
            pom=rand()%3;
            next=neighbours[pom];
        }
        neighbours.clear();
        totalTime+=next.second.czas;
        totalCost+=next.second.koszt;
        visited[next.first]=1;
        //cout<<next<<endl;
        path.push_back(next.first);
        cur_miasto=next.first;
        i++;
    }

    if(G[cur_miasto][path[0]])
    {
        totalTime+=W[cur_miasto][path[0]].czas;
        totalCost+=W[cur_miasto][path[0]].koszt;
        path.push_back(path[0]);
    }

    else
    {
        out={{"Best_Time",MAX},{"Best_Cost",MAX},{"Best_Path",0}};
        plik<<out;
        plik.close();
        cout<<"Nie mozna wrocic do miasta poczatkowego"<<endl;
        return;
    }
    out={{"Best_Time",totalTime},{"Best_Cost",totalCost},{"Best_Path",path}};
    plik<<out;
    plik.close();
    for(int k=0;k<path.size();k++)
    {
        cout<<path[k]<<" ";
    }
    cout<<endl;
    cout<<"Najlepszy czas zachlannie: "<<totalTime<<endl;
    cout<<"Najlepszy koszt zachlannie: "<<totalCost<<endl;


}
droga evaluation(bool** G,droga** W,vector<int> path)
{
    droga wynik;
    wynik.czas=0;
    wynik.koszt=0;
    int from,to;
    for(int i=0;i<path.size()-1;i++)
    {
        from=path[i];
        to=path[i+1];
        if(!G[from][to])
        {
            wynik.czas=MAX;
            wynik.koszt=MAX;
            return wynik;
        }
        wynik.czas+=W[from][to].czas;
        wynik.koszt+=W[from][to].koszt;
    }
    from=path[path.size()-1];
    to=path[0];
    if(!G[from][to])
        {
            wynik.czas=MAX;
            wynik.koszt=MAX;
            return wynik;
        }
    wynik.czas+=W[from][to].czas;
        wynik.koszt+=W[from][to].koszt;
        return wynik;

}
bool isValid(bool** G,vector<int> v)
{
    int from,to;
    for(int i=0;i<v.size()-1;i++)
    {
        from=v[i];
        to=v[i+1];
        if(!G[from][to])
            return false;
    }
    return 1;
}
vector<int> generateRandomPath(bool** G,int n)
{
    vector<int> path;
    for(int i=0;i<n;i++)
    {
        path.push_back(i);
    }
    random_shuffle(path.begin()+1,path.end());
    while(!isValid(G,path))
    {
        random_shuffle(path.begin()+1,path.end());
    }
    return path;
}
vector<int> crossover(vector<int> &parent1,vector<int> &parent2)
{
    int n=parent1.size();
    vector<int> child;
    for(int i=0;i<n;i++)
    {
        child.push_back(-1);
    }
    srand(time(0));
    int start=rand()%n;
    int end=start+rand()%(n-start);
    for(int i=start;i<=end;i++)
    {
        child[i]=parent1[i];
    }
    int cur=0;
    for(int i=0;i<n;i++)
    {
        if(cur>=n)
            break;
        if(!isMember(child,parent2[i]))
        {
            while(child[cur]!=-1)
            {
                cur++;
            }
            child[cur]=parent2[i];
        }
    }
    return child;
}
void mutate(vector<int> &path)
{
    int n=path.size();
    int i,j;
    srand(time(0));
    if(rand()/RAND_MAX<MUTATION_RATE)
    {
        i=rand()%n;
        j=rand()%n;
        while(i==j)
        {
            j=rand()%n;
        }
        swap(path[i],path[j]);
    }
}
bool compare(pair<droga,vector<int>> &a,pair<droga,vector<int>> &b)
{
    if(a.first.czas<b.first.czas)
    {
        return 1;
    }
    if(a.first.czas==b.first.czas)
    {
        if(a.first.koszt<b.first.koszt)
        {
            return 1;
        }
        return false;
    }
    return false;
}
void genetic(bool** G,droga** W,int n)
{
    int POPULATION_SIZE=100*n;
    vector<vector<int>> population;
    for(int i=0;i<POPULATION_SIZE;i++)
    {
        //cout<<"K"<<endl;
        population.push_back(generateRandomPath(G,n));

    }

    vector<int> best;
    droga fitness;
    droga best_val;
    best_val.czas=MAX;
    best_val.koszt=MAX;
    for(int i=0;i<GENERATIONS;i++)
    {
        //cout<<"H"<<endl;
        vector<pair<droga,vector<int>>> fitnessPopulation;
        for(auto &path : population)
        {
            fitness=evaluation(G,W,path);
            //cout<<fitness.czas<<endl;
            fitnessPopulation.push_back({fitness,path});
        }
        sort(fitnessPopulation.begin(),fitnessPopulation.end(),compare);
        /*for(int j=0;j<fitnessPopulation.size();j++)
        {
            cout<<fitnessPopulation[0].first.czas<<" "<<fitnessPopulation[0].first.koszt<<endl;
        }*/
        if(fitnessPopulation[0].first.czas<best_val.czas || (fitnessPopulation[0].first.czas==best_val.czas && fitnessPopulation[0].first.koszt<best_val.koszt))
        {
            best_val=fitnessPopulation[0].first;
            best=fitnessPopulation[0].second;
        }
        vector<vector<int>> newPopulation;
        for(int i=0;i<POPULATION_SIZE/2;i++)
        {
            newPopulation.push_back(fitnessPopulation[i].second);
        }
        while(newPopulation.size()<POPULATION_SIZE)
        {
            int parent1=rand()%(POPULATION_SIZE/2);
            int parent2=rand()%(POPULATION_SIZE/2);
            while(parent1==parent2)
            {
                parent2=rand()%(POPULATION_SIZE/2);
            }
            vector<int> child=crossover(newPopulation[parent1],newPopulation[parent2]);
            mutate(child);
            newPopulation.push_back(child);

        }
    }
    ofstream plik;
    string name="outputs/"+toString(n)+"_genetic_out.json";
    plik.open(name,ios::out);
    json out;
    best.push_back(best[0]);
    out={{"Best_Time",best_val.czas},{"Best_Cost",best_val.koszt},{"Best_Path",best}};
    plik<<out;
    plik.close();
    cout<<"Najlepszy czas genetycznie: "<<best_val.czas<<endl;
    cout<<"Najlepszy koszt genetycznie: "<<best_val.koszt<<endl;
    for(int i=0;i<best.size();i++)
    {
        cout<<best[i]<<" ";
    }
    //cout<<best[0];
    cout<<endl;

}
int main(int argc,char* argv[] )
{
    if(argc<1) {
        cout<<"Za malo argumentow"<<endl;
        exit(1);
    }
    ifstream plik1;
    plik1.open(argv[1],ios::in);
    bool** G;
    droga** W;
    int n,k,a,b,c,d,start;
    json data;
    string linia;
    //plik1>>n>>k;
    plik1>>data;
    //getline(plik1,linia);
    n=data["N"];
    k=data["K"];
    /*plik>>start;
    getline(plik,linia);*/
    G=new bool* [n];
    W=new droga* [n];
    for(int i=0;i<n;i++)
    {
        G[i]=new bool [n];
        W[i]=new droga [n];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
    {
        G[i][j]=0;
        W[i][j].czas=-1;
        W[i][j].koszt=-1;
    }
    }
    /*for(int i=0;i<k;i++)
    {
        plik>>a>>b>>c>>d;
        getline(plik,linia);
        G[a][b]=1;
        G[b][a]=1;
        W[a][b].czas=c;
        W[a][b].koszt=d;
        W[b][a].czas=c;
        W[b][a].koszt=d;
    }*/
    int a1,b1,c1,d1;
    for(int i=0;i<k;i++) {
        a1=data["edges"][i]["v1"];
        b1=data["edges"][i]["v2"];
        c1=data["edges"][i]["time"];
        d1=data["edges"][i]["cost"];
        //cout<<a1<<" "<<b1<<endl;
        G[a1][b1]=1;
        G[b1][a1]=1;
        W[a1][b1].czas=c1;
        W[b1][a1].czas=c1;
        W[a1][b1].koszt=d1;
        W[b1][a1].koszt=d1;

    }
    /*for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }*/
    /*for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<G[i][j]<<" ";
        }
        cout<<endl;
    }*/
    //brute_force(G,W,n);
    clock_t start1,stop;
    fstream time1,time2,time3;

    string name2="times/"+toString(n)+"time_greedy-random.json";
    string name3="times/"+toString(n)+"time_genetic_.json";
    double time_brute,time_greedy,time_genetic;
    json outtime;
    if(n<=13) {
        string name1="times/"+toString(n)+"time_brute-force.json";
        time1.open(name1,ios::out);
        start1=clock();
        findOptimalPath(G,W,n);
        stop=clock();
        time_brute=(stop-start1)/CLOCKS_PER_SEC;
        outtime={"time",time_brute};
        time1<<outtime;
        time1.close();
    }
    time2.open(name2,ios::out);
    time3.open(name3,ios::out);



    start1=clock();
    greedy_random(G,W,n);
    stop=clock();
    time_greedy=(stop-start1)/CLOCKS_PER_SEC;
    outtime={"time",time_greedy};
    time2<<outtime;
    time2.close();
    start1=clock();
    genetic(G,W,n);
    stop=clock();
    time_genetic=(stop-start1)/CLOCKS_PER_SEC;
    outtime={"time",time_genetic};
    time3<<outtime;
    time3.close();
    return 0;
}
