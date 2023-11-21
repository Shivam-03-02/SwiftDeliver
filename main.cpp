//----------------------------------------------------------------------------
-----------------------------
// header files used in project
//----------------------------------------------------------------------------
-----------------------------
#include <iostream>
#include <time.h>
#include <conio.h>
#include <climits>
#include <cstring>
#include <ctime>
#include <windows.h>
using namespace std;
class user{
public:
user* lchild;
user* rchild;
int height;
string order;
string price;
string weight;
// user(bool adm)
// {
// if(adm==true)
// {
// admin=true;
//
// }
// else{
// admin=false;
// }
// id=rand()%100000;
// name=randomnameallocation(id);
// pwd=rand()%10000000;
//
// }
// user(string s,int pw)
// {
//
// name=s;
//
// pwd=pw;
// int i=rand()%100000;
// i=id;
// }
};
class AVL{
public:
user* root;
AVL(){root = nullptr;}
int userHeight(user* p);
int BalanceFactor(user* p);
user* LLRotation(user* p);
user* RRRotation(user* p);
user* LRRotation(user* p);
user* RLRotation(user* p);
user* rInsert(user* p,string order,string weight,string price);
void minsert(user *p,string order,string weight,string price);
void Inorder(user* p);
void Inorder(){ Inorder(root); }
user* getRoot(){ return root; }
user* search_order(user *p,string order);
};
int AVL::userHeight(user *p) {
int hl;
int hr;
hl = (p && p->lchild) ? p->lchild->height : 0;
hr = (p && p->rchild) ? p->rchild->height : 0;
return hl > hr ? hl + 1 : hr + 1;
}
int AVL::BalanceFactor(user *p) {
int hl;
int hr;
hl = (p && p->lchild) ? p->lchild->height : 0;
hr = (p && p->rchild) ? p->rchild->height : 0;
return hl - hr;
}
user* AVL::LLRotation(user *p) {
user* pl = p->lchild;
user* plr = pl->rchild;
pl->rchild = p;
p->lchild = plr;
p->height = userHeight(p);
pl->height = userHeight(pl);
if (root == p){
root = pl;
}
return pl;
}
user* AVL::RRRotation(user *p) {
user* pr = p->rchild;
user* prl = pr->lchild;
pr->lchild = p;
p->rchild = prl;
p->height = userHeight(p);
pr->height = userHeight(pr);
if (root == p){
root = pr;
}
return pr;
}
user* AVL::LRRotation(user *p) {
user* pl = p->lchild;
user* plr = pl->rchild;
pl->rchild = plr->lchild;
p->lchild = plr->rchild;
plr->lchild = pl;
plr->rchild = p;
pl->height = userHeight(pl);
p->height = userHeight(p);
plr->height = userHeight(plr);
if (p == root){
root = plr;
}
return plr;
}
user* AVL::RLRotation(user *p) {
user* pr = p->rchild;
user* prl = pr->lchild;
pr->lchild = prl->rchild;
p->rchild = prl->lchild;
prl->rchild = pr;
prl->lchild = p;
pr->height = userHeight(pr);
p->height = userHeight(p);
prl->height = userHeight(prl);
if (root == p){
root = prl;
}
return prl;
}
//see????
user* AVL::rInsert(user *p,string order,string weight,string price) {
user* t;
if (p == nullptr){
t = new user;
t->order=order;
t->price=price;
t->weight=weight;
t->lchild = nullptr;
t->rchild = nullptr;
t->height = 1;
return t;
}
if (order < p->order){
p->lchild = rInsert(p->lchild,order,weight,price);
} else if (order > p->order){
p->rchild = rInsert(p->rchild,order,weight,price);
}
p->height = userHeight(p);
if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
return LLRotation(p);
} else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){
return LRRotation(p);
} else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){
return RRRotation(p);
} else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){
return RLRotation(p);
}
return p;
}
void AVL::Inorder(user *p) {
if (p){
Inorder(p->lchild);
cout << p->order<< ", " << flush;
Inorder(p->rchild);
}
}
user*AVL::search_order(user *p,string order)
{
bool flag;
if(p==NULL)
{
flag=false;
}
else
{
if(p->order==order)
{
flag=true;
}
if(flag==false&&p->lchild!=NULL)
{
search_order(p->lchild,order);
}
if(flag==false&&p->rchild!=NULL)
{
search_order(p->rchild,order);
}
}
return p;
}
#define v 16
int arr[v][v]{0};
void help(int u, int x, int d)
{
arr[u][x] = d;
arr[x][u] = d;
}
template <typename T>
class vector
{
T *arr;
// capacity of the vector
int capacity;
// current is the number of elements
int current;
public:
// constructor
vector()
{
arr = new T[1];
capacity = 1;
current = 0;
}
vector(int c, int val = 0)
{
arr = new T[c];
for (int i = 0; i < c; i++)
{
arr[i] = val;
}
capacity = c;
current = 0;
}
// destructor
~vector()
{
delete[] arr;
}
void push_back(T data)
{
/* if the number of elements is equal to the
capacity, that means we don't have space to
accommodate more elements. We need to double the
capacity */
if (current == capacity)
{
T *temp = new T[2 * capacity];
// copying old array elements to new array
for (int i = 0; i < capacity; i++)
{
temp[i] = arr[i];
}
// deleting previous array
delete[] arr;
capacity *= 2;
arr = temp;
}
// Inserting data
arr[current] = data;
current++;
}
void push(T data, int index)
{
if (index == capacity)
push(data);
else
arr[index] = data;
}
// function to extract element at any index
T get(int index)
{
if (index < current)
return arr[index];
}
// function to delete last element
void pop()
{
current--;
}
// function to get size of the vector
int size()
{
return current;
}
// function to get capacity of the vector
int getcapacity()
{
return capacity;
}
// function to print array elements
void print()
{
for (int i = 0; i < current; i++)
{
cout << arr[i] << " ";
}
cout << endl;
}
T &operator[](int i)
{
return arr[i];
}
};
vector<int> dist(v, INT_MAX);
vector<int> parents(v);
string names[] = {
"IHC",
"M1",
"SMC",
"AC1",
"C1",
"M2",
"AC2",
"MWC",
"UP1",
"UP2",
"GC1",
"GC2",
"G3",
"G2",
"G1",
"UT"
};
static int a = 0;
void printPath(int currentVertex, vector<int> &parents)
{
// Base case : Source node has
// been processed
if (currentVertex == -1)
{
return;
}
printPath(parents[currentVertex], parents);
if (a++ > 0)
{
cout << "--->";
}
cout << names[currentVertex] << " ";
}
// A utility function to print
// the constructed distances
// array and shortest paths
int printSolution(int startVertex, vector<int> &distances,
vector<int> &parents, int d, int choice)
{
if (choice == 1)
{
cout << "\n\n\t\t\tSource\t\tDestination\t\tDistance";
cout << "\n\n\t\t\t------------------------------------------------";
}
else if (choice == 2)
{
cout << "\n\n\t\t\tSource\t\tDestination\t\tPath";
cout << "\n\n\t\t\t--------------------------------------------";
}
else if (choice == 3)
{
cout << "\n\n\t\t\tSource\t\tDestination\t\tDistance\t\tPath";
cout << "\n\n\t\t\t---------------------------------------------------
-----------------";
}
for (int vertexIndex = 0; vertexIndex < v;
vertexIndex++)
{
if (vertexIndex != startVertex && vertexIndex == d)
{
cout << "\n\n\t\t\t" << names[startVertex] << " \t\t ";
cout << names[vertexIndex] << " \t\t\t ";
return distances[vertexIndex];
}
}
return 0;
}
int dijkstra(int graph[][v], int s, int d, int choice)
{
dist[s] = 0;
parents[s] = -1;
vector<bool> fin(v, 0);
for (int j = 0; j < v - 1; j++)
{
int u = -1, i;
for (i = 0; i < v; i++)
{
if (!fin[i] && (u == -1 || dist[i] < dist[u]))
{
u = i;
}
}
fin[u] = 1;
for (int x = 0; x < v; x++)
{
if (graph[u][x] != 0 && fin[x] == 0)
{
dist[x] = min(dist[x], dist[u] + graph[u][x]);
if (dist[x] == dist[u] + graph[u][x])
parents[x] = u;
}
}
}
return printSolution(s, dist, parents, d, choice);
}
//----------------------------------------------------------------------------
-----------------------------
// function to print names of team members
//----------------------------------------------------------------------------
-----------------------------
void printMessageCenter(const char *message)
{
int len = 0;
int pos = 0;
// calculate how many space need to print
len = (78 - strlen(message)) / 2;
for (pos = 0; pos < len; pos++)
{
// print space
cout << " ";
}
// print message
cout << message << endl;
//
//cout << "\nDate: " << DATE << "\t\t\t\t\t Time: " << TIME;
cout << "\n\n\t\t 1. RHYTHM SRIVASTAVA - B11 - 21103234";
cout << "\n\n\t\t 2. SHIVAM SINGH - B11 - 21103232";
cout << "\n\n\t\t 3. AIBAD KHAN - B11 - 21103218";
}
//----------------------------------------------------------------------------
-----------------------------
// function to heading of page
//----------------------------------------------------------------------------
-----------------------------
void printMessageCenter2(const char *message)
{
int len = 0;
int pos = 0;
// calculate how many space need to print
len = (78 - strlen(message)) / 2;
for (pos = 0; pos < len; pos++)
{
// print space
cout << " ";
}
// print message
cout << message << endl;
}
//----------------------------------------------------------------------------
-----------------------------
// function of small loading page
//----------------------------------------------------------------------------
-----------------------------
void loadingpage()
{
cout << "\t\t\tPLEASE WAIT\n";
cout << "\t\t\tSYSTEM IS LOADING\n";
cout << "\n\nPress any key to start now.....";
getch();
}
//----------------------------------------------------------------------------
-----------------------------
// function to display our project name
//----------------------------------------------------------------------------
-----------------------------
void headMessage(const char *message)
{
system("cls");
cout <<"\n###########################################################################";
cout <<
"\n############ ############
";
cout << "\n############ THE MAP OF INDIRAPURAM DELIVERY (PROJECT IN C++) ############";
cout <<
"\n############ ############
";
cout <<
"\n###########################################################################
";
cout << "\n---------------------------------------------------------------
------------\n";
printMessageCenter(message);
cout << "\n---------------------------------------------------------------
-------------\n\n";
}
//----------------------------------------------------------------------------
-----------------------------
// function to display welcome message
//----------------------------------------------------------------------------
-----------------------------
void Welcome_Msg()
{
headMessage("CREATED BY :-");
loadingpage();
cout << "\n\n\n\n\n";
cout << "\n\t ------------------\n";
cout << "\n\t =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
cout << "\n\t = WELCOME =";
cout << "\n\t = TO =";
cout << "\n\t = LOGISTIC DELIVERY =";
cout << "\n\t = SYSTEM =";
cout << "\n\t =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
cout << "\n\n\t ------------------\n";
cout << "\n\n Enter any key to continue.....";
getch();
}
//----------------------------------------------------------------------------
-----------------------------
// function to display MENU
//----------------------------------------------------------------------------
-----------------------------
vector<int>index;
int max(int a, int b) { return (a > b) ? a : b; }
void printknapSack(int W, vector<int>&wt,vector<int>&val, int n)
{
int i, w;
int K[n + 1][W + 1];
for (i = 0; i <= n; i++) {
for (w = 0; w <= W; w++) {
if (i == 0 || w == 0)
K[i][w] = 0;
else if (wt[i - 1] <= w)
K[i][w] = max(val[i - 1] +
K[i - 1][w - wt[i - 1]], K[i - 1][w]);
else
K[i][w] = K[i - 1][w];
}
}
int res = K[n][W];
cout<< res << endl;
w = W;
for (i = n; i > 0 && res > 0; i--) {
if (res == K[i - 1][w])
continue;
else {
index.push_back(i-1);
res = res - val[i - 1];
w = w - wt[i - 1];
}
}
}
vector<int> m(string items[][3],int r,int c)
{
//int val[] = { 60, 100, 120 };
//int wt[] = { 10, 20, 30 };
int W = 50;
//int n = sizeof(val) / sizeof(val[0]);
vector<int>v1;
vector<int>v2;
//int s=sizeof(items)/sizeof(items[0]);
//cout<<s;
for(int i=0;i<r;i++)
{ /*for(int j=0;j<index.size();j++)
{
if(index[j]==)*/
int profit=stoi(items[i][1]);
int weight=stoi(items[i][2]);
v1.push_back(profit);
v2.push_back(weight);
}
printknapSack(W, v2, v1, v1.size());
return index;
}
void knapsack(string ites[][3])
{
vector<int> vv;
vv=m(ites,sizeof(ites)/sizeof(ites[0]),sizeof(ites[0])/ sizeof(int));
for(int i=0;i<vv.size();i++)
{cout<<ites[vv[i]]<<' ';}
}
void displaydij()
{
int choice;
do{
cout << "\n\n\t\t\t1.Minimum 
Distance [Press 1]";
cout << "\n\t\t\t2.Smallest Path [Press 2]";
cout << "\n\t\t\t3.Minimum distance and Smallest Path [Press 3]";
cout << "\n\t\t\t0.Exit [Press 0]";
cout << "\n\n\n\t\t\tEnter choice => ";
cin >> choice;
int source,destination;
if (choice >= 1 && choice <= 3)
{
string s,d;int i,j;
cout << "\n\n\t\t\tEnter the Shopping Center : ";
cin >> s;
cout << "\t\t\tEnter the Address to be delivered to : ";
cin >> d;
// this function is searching the index of points
i = j = 0;
for (int i = 0; i < 16; i++)
{
if (names[i] == s)
source = i;
if (names[i] == d)
destination = i;
}
}
switch (choice)
{
case 1:
a = 0;
cout << "\n\n";
printMessageCenter2("MINIMUM DISTANCE");
cout << dijkstra(arr, source, destination, choice) << endl;
cout << "\n\n\t\t\t";
getch();
break;
case 2:
a = 0;
cout << "\n\n";
printMessageCenter2("SMALLEST PATH");
dijkstra(arr, source, destination, choice);
printPath(destination, parents);
cout << "\n\n\t\t\t";
getch();
break;
case 3:
a = 0;
cout << "\n\n";
printMessageCenter2("MINIMUM DISTANCE WITH PATH");
cout << dijkstra(arr, source, destination, choice) << "\t\t";
printPath(destination, parents);
cout << "\n\n\t\t\t";
getch();
break;
case 0:
printf("\n\n\n\t\t\t\tThank you!!!\n\n\n\n\n");
exit(1);
break;
default:
printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
}
// Switch Ended
} while (choice != 0);
// Loop Ended
}
//void Menu()
//{
// int choice = 0;
// int i, j, source, destination;
// string s, d;
//
// help(0,1,3);
// help(1,0,3);
// help(1,2,3);
// help(2,1,3);
// help(2,3,4);
// help(3,2,4);
// help(3,4,3);
// help(4,3,3);
// help(4,5,2);
// help(5,4,2);
// help(5,6,2);
// help(6,5,2);
// help(4,6,2);
// help(6,4,2);
// help(0,6,3);
// help(6,0,3);
// help(3,7,1);
// help(7,3,1);
// help(7,8,5);
// help(8,7,5);
// help(8,9,2);
// help(9,8,2);
// help(9,10,6);
// help(10,9,6);
// help(10,11,3);
// help(11,10,3);
// help(11,12,2);
// help(12,11,2);
// help(11,13,5);
// help(13,11,5);
// help(13,14,2);
// help(14,13,2);
// help(14,15,5);
// help(15,14,5);
// Ae:
// headMessage("CREATED BY :-");
// printMessageCenter2("MAIN MENU");
// string med[8][3]={{"paracetamol","20","5"},{"crocin","30","22"},
//{"shmpoo","50","14"},
//{"food","40","15"},
//{"rattrap","20","20"},
//{"mousetreap","10","30"},{"honey","30","100"},{"money","40","40"}};
//
//
//AVL avl;
//for(int i=0;i<8;i++)
//{
//
// int price;
// obj<<med[i][2];
// obj>>price;
// int weight;
// obj<<med[i][1];
// obj>>weight;
// avl.root=avl.rInsert(avl.root,med[i][0],weight,price);
//}
// cout << "\n\n\t\t\tEnter the Number Items You Want to 
Buy ";
// int n;
// cin>>n;
// cout << "\n\n\t\t\tEnter your Order ";
// string s[n];
// int flag=0;
//for(int i=0;i<n;i++)
//{
//
// cin>>s[i];
// user* us=avl.search_order(avl.getRoot(),s[i]);
// if(us==NULL)
// {
//
// flag=1;break;
// }
//}
//if(flag==1)
//{
//
// cout<<"ITEM NOT FOUND:";
// cout<<"1. To order again [Press 1]"<<endl;
// cout<<"2. TO exit [Press 2]"<<endl;
// int c;
// cin>>c;
// switch(c){
// case 1:
// system("cls");
// goto Ae;
//
//
// break;
// case 2:
// system("cls");
//
// }
//
//}
//else
//{
// //knapsack(us->order,us->weight,us->price);
// displaydij();
//
//
//}
//}
//----------------------------------------------------------------------------
-----------------------------
// The Program starts from here
//----------------------------------------------------------------------------
-----------------------------
int main()
{
Welcome_Msg();
int choice = 0;
int i, j, source, destination;
string s, d;
help(0,1,3);
help(1,0,3);
help(1,2,3);
help(2,1,3);
help(2,3,4);
help(3,2,4);
help(3,4,3);
help(4,3,3);
help(4,5,2);
help(5,4,2);
help(5,6,2);
help(6,5,2);
help(4,6,2);
help(6,4,2);
help(0,6,3);
help(6,0,3);
help(3,7,1);
help(7,3,1);
help(7,8,5);
help(8,7,5);
help(8,9,2);
help(9,8,2);
help(9,10,6);
help(10,9,6);
help(10,11,3);
help(11,10,3);
help(11,12,2);
help(12,11,2);
help(11,13,5);
help(13,11,5);
help(13,14,2);
help(14,13,2);
help(14,15,5);
help(15,14,5);
headMessage("CREATED BY :-");
printMessageCenter2("MAIN MENU");
string items[8][3]={{"paracetamol","20","5"},{"crocin","30","22"},
{"shampoo","50","14"},
{"food","40","15"},
{"rattrap","20","20"},
{"mousetreap","10","30"},{"honey","30","100"},{"money","40","40"}};
AVL avl;
for(int i=0;i<8;i++)
{
user* rooti=avl.getRoot();
avl.root=avl.rInsert(rooti,items[i][0],items[i][1],items[i][2]);
}
// A:
//
// int flag=0;
// ;
//
// cout<<"1 to sign up :"<<endl<<" 2 to login:"<<endl;
// int c;
// cin>>c;
//
// switch(c){
// case 1:
// flag=0;
// user *a;
// a=new user;
//
// case 2:
// int ID;
// cout<<"ENTER ID:";
// cin>>ID;
// user* us=avl.search_id(avl.getRoot(),ID);
//
//// if(us->admin==true)//search admin tree
//// {
//// flag=1;
//// }
//// else if(us->admin==false)//search user tree
//// {
//// flag=0;
////
//// }
//// else
//// {
//// cout<<"INVALID ID ...."<<endl<<"PLEASE TRY AGAIN";
//// cout<<"PRESS 1 TO retry:";
//// int c;
//// cin>>c;
//// if(c==1)
//// {system("cls");
//// goto A;
////
//// }
////
////
//// }
//// break;
//
//
// if(flag==0)
// {
// cout<<"WELCOME"<<endl;
// cout<<"1 for ordering :\n 2 for checking status \n 3 for 
exit:\n";
// int c;
// cin>>c;
// switch(c){
// case 1:
// order(ID);
//
//
// case 2:
// checkstatus(ID);
//
//
// case 3:
// cout<<"Press 1 to CONTINUE 2 to exit";
// switch(c){
// case 1:
// system("cls");
// goto A;
// break;
// case 2:
// break;
// }
// }
// }
// else
// {
// cout<<"WELCOME ADMIN:"<<endl;
//
//
// //more user power???
// }
// if(s==1)
// {
// cout<<"WELCOME ASD :";
// cout<<"PLEASE ENTER YOU NAME:";
// cout<<"ENTER THE OPERATION YOU WANT TO PERFORM :"<<" 1 for entering 
number of shops to set up in city"<<endl;
// cout<<"2 for exiting the app:";
// int c;
// cin>>c;
// //verify admin
// switch(c){
// case 1:
// int n;
// cin>>n;
// kcenter(n);
// break;
// }
// case 2:
// cout<<"Press 1 to CONTINUE 2 to exit";
// switch(c){
// case 1:
// system("cls");
// goto A;
// break;
// case 2:
// break;
// }
// break;
//
// }
// else{
//
//
//
//
// }
//
//
// //after login sign up
// cout<<"
Ae:
cout<<"ENTER THE NUMBER OF ITEMS YOU WANT TO BUY:";
int n;
cin>>n;
cout<<"ENTER YOUR ORDER: ";
string str[n][3];
int flag=0;
for(int i=0;i<n;i++)
{
string pty="Dettol";
string sqr="Antispetic";
cin>>str[i][0];
user* us=avl.search_order(avl.getRoot(),str[i][0]);
if(us==NULL || str[i][0]==sqr || str[i][0]==pty)
{
flag=1;break;
}
else
{
str[i][1]=us->weight;
str[i][2]=us->price;
}
}
if(flag==1)
{
cout<<"ITEM NOT FOUND:";
cout<<"1. To order again [Press 1]"<<endl;
cout<<"2. TO exit [Press 2]"<<endl;
int c;
cin>>c;
switch(c){
case 1:
system("cls");
goto Ae;
break;
case 2:
system("cls");
}
}
else
{
knapsack(str);
cout<<"ENTER YOUR ADDRESS :";
string add;
cin>>add;
// dikstra(order,add);
displaydij();
}
return 0;
}
OUTPUTS SCREENSHOTS: