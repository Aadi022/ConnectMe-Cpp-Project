#include <iostream>
#include<string.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <list>
#include <queue>
#include <unordered_map>
#include <limits>
using namespace std;


class User;
class Group;
class Community;

vector<User*> allusers;  //This will contain list of all users, whenever a user is created in main(), it will get pushed backed in allusers.
Group* helper_creategroup(User* us);
vector<Group*> allgroups;     //This contains all groups
vector<Community*> allcommunities;  //This contains all communities


void userfunctionalityhelper(User* us);
void userfunctionality(User* us);
void redirect1(User* us);
void user_login();
void groupfunctionality(User* us);
void groupfunctionalityhelper(User* us);
void groupfunctionalityhelper2(User* us, Group* grp);
void communityfunctionality(User* us);
void communityfunctionalityhelper(User* us);
void communityfunctionalityhelper2(User* us, Community* com);

class User{
    private:
    string password;

    public:
    string username;  
    string userid;    //Is unique for every account  
    stack<pair<string,User*>> send;          //Stack for send messages
    stack<pair<string,User*>> inbox;         //Stack for inbox messages
    stack<User*> friendrequest;   //Incoming friend request
    stack<User*> outgoingrequest; //Outgoing friend request
    list<User*> myfriends;   //This will contain all of users friends.
    vector<Group*> presentgroup;  //This will show all groupid the user is present in
    vector<Community*> presentcommunity;  //This will show all communityid the user is present in

    string getusername(User* temp){
        return temp->username;
    }

    User(string n1, string n2, string n3){
        this->password=n1;    //Sets the password from constructor itself
        this->username=n2;      //Sets the username
        this->userid=n3;        //Sets the userid. Note the name of the instance of the class should be the same as the username 
        allusers.push_back(this);  //The newly created user gets pushed in allusers 
    }

    bool accept_user(string n1){    //This will be used in the user-login function to confirm if the password entered is true or false
        if(n1==password){
            return true;
        }
        return false;
    }

    // Hash function for User
    struct Hash {
        size_t operator()(const User* user) const {
            return hash<string>()(user->userid); // Using userid for hashing
        }
    };

    // Equality comparison function for User
    struct Equal {
        bool operator()(const User* lhs, const User* rhs) const {
            return lhs->userid == rhs->userid; // Using userid for comparison
        }
    };

    void viewfriends(){    //This will print all the friends of the user.
        for(auto it:myfriends){
            cout<<it->username<<" ";
        }
    }

    void viewsend(){    //This function is to view the sent messages
        stack<pair<string,User*>> temp=send;
        if(temp.empty()){
            cout<<"The sent messages are empty"<<endl;
            return ;
        }
        char flag='Y';
        while(!temp.empty()){  //The user can view messages till he enters 'N'. If all messages have been seen, then the msg-"All messages have been viewed will come."
            cout<<"Enter `Y` if you want to continue to see sent messages, else enter `N`"<<endl;
            cin>>flag;
            if(flag=='N'){
                break;
            }
            cout<<temp.top().first<<endl;
            temp.pop();
        }
        if(temp.empty()){
            cout<<"All messages have been viewed"<<endl;
        }
    }

    void viewinbox(){   //This function is to view the inbox messages
        stack<pair<string,User*>> temp=inbox;
        if(temp.empty()){
            cout<<"The inbox messages are empty"<<endl;
            return ;
        }
        char flag='Y';
        while(!temp.empty()){
            cout<<"Enter `Y` if you want to continue to see inbox, else enter `N`"<<endl;
            cin>>flag;
            if(flag=='N'){
                break;
            }
            cout<<temp.top().first<<endl;
            temp.pop();
        }
        if(temp.empty()){
            cout<<"All messages have been viewed"<<endl;
        }
    }

    void view_outrequests(){    //This function is to view the stack that maintains the outgoing friend requests
        stack<User*> temp=outgoingrequest;
        if(temp.empty()){
            cout<<"You have sent no friend requests"<<endl; 
        }
        char flag='Y';
        while(!temp.empty()){
            cout<<"Enter `Y` if you want to continue to see sent friend requests, else enter `N`"<<endl;
            cin>>flag;
            if(flag=='N'){
                break;
            }
            cout<<temp.top()->userid<<endl;
            temp.pop();
        }
        if(temp.empty()){
            cout<<"All sent friend requests have been seen"<<endl;
        }
    }

    void view_inrequests(){     //This stack is used to view the stack that maintains the incoming friend requests
        stack<User*> temp=friendrequest;
        if(temp.empty()){
            cout<<"You have received no friend requests"<<endl; 
        }
        char flag='Y';
        while(!temp.empty()){
            cout<<"Enter `Y` if you want to continue to see friend requests, else enter `N`"<<endl;
            cin>>flag;
            if(flag=='N'){
                break;
            }
            cout<<temp.top()->userid<<endl;
            temp.pop();
        }
        if(temp.empty()){
            cout<<"All friend requests have been seen"<<endl;
        }
    }

    void sendmsg(User* us2){           //Now the sent message has been updated in the send stack of sender, and received message has been updated in inbox of the receiver
        string inp;                                 //this sends message to us2
        cout<<"Enter the message to be sent"<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,inp);
        send.push({inp,us2});
        us2->inbox.push({inp,this});
    }

    void helper_friend(User* us1, User* us2){  //This will be used in accept_friends. This pushes back mutually in myfriends list.
        us1->myfriends.push_back(us2);
        us2->myfriends.push_back(us1);
    }


    void accept_friends(){    //This function is to accept friends from inrequests
        if(friendrequest.empty()){
            cout<<"There are no Friend Requests"<<endl;
            return ;
        }
        char flag='Y';
        while(!friendrequest.empty()){
            cout<<"Enter `Y` if you want to continue to accept friend requests, else enter `N`"<<endl;
            cin>>flag;
            if(flag=='N'){
                break;
            }
            char decider;
            cout<<"Enter `Y` if you want to accept the friend request of "<<friendrequest.top()->userid<<" , else enter `N`"<<endl;
            cin>>decider;
            if(decider=='Y'){
                helper_friend(this,friendrequest.top());
            }
            friendrequest.pop();
        }
        if(friendrequest.empty()){
            cout<<"All friend requests have been viewed"<<endl;
        }
    }

    Group* creategroup(){
        Group* mygroup=helper_creategroup(this);
        this->presentgroup.push_back(mygroup);
        return mygroup;
    }

    

};

void sendfriendrequest(User* us1, User* us2){    //us1 sends friend request to us2, and the friendrequest stack of us2 gets updated. The outgoing request also gets updated.
    us2->friendrequest.push(us1);
    us1->outgoingrequest.push(us2);
    return ;
}



unordered_map<User*, list<User*>, User::Hash, User::Equal> getfriends(vector<vector<User*>> all){   //Creating unordered_map for all Users
    unordered_map<User*, list<User*>, User::Hash, User::Equal> ans;
    for(int i=0;i<all.size();i++){
        ans[all[i][0]].push_back(all[i][1]);
        ans[all[i][1]].push_back(all[i][0]);
    }
    return ans;
}

void createfriends(User* name, vector<vector<User*>> friendspool){  //The myfriends list in User will get updated, and now will contain the friends of the particular userid
    unordered_map<User*, list<User*>, User::Hash, User::Equal> all=getfriends(friendspool);
    for(auto it : all){
        if(it.first->userid==name->userid){
            name->myfriends=it.second;
        }
    }
}


//This is a helper function to recommend friends
void help_recommend(User* us1, User* us2, unordered_map<User*, bool, User::Hash, User::Equal> &visited_dfs, unordered_map<User*, bool, User::Hash, User::Equal> &visited_display, char &flag, int &count){    //us1 will help in retaining the initial user throughout, and us2 will help in the dfs cycle
    if(count>2){   //Count is used because at the start only we won't ask if you want to continue. After recommending few people we will ask.
        cout<<"Enter `Y` if you want to continue get recommended friends, else enter `N`"<<endl;
        cin>>flag;
        if(flag=='N'){
            return ;
        }
    }
    visited_dfs[us2]=true;
    if(us2!=us1 && visited_display.find(us2)==visited_display.end()){   //Only those friends will be recommended who are already not a friend. Hence visited_display is used. 
        visited_display[us2]=true;
        char decider;
        cout<<"Enter `Y` if you want to send friend request to "<<us2->userid<<" , else enter `N`."<<endl;
        cin>>decider;
        if(decider=='Y'){
            sendfriendrequest(us1,us2);
        }
    }
    for(auto it : us2->myfriends){
        if(visited_dfs.find(it)==visited_dfs.end()){
            count++;
            help_recommend(us1,it,visited_dfs,visited_display,flag,count);
            if(flag=='N'){
                return ;
            }
        }
    }
}

//This is used to recommend friends to the user
void recommend_friends(User* us){
    unordered_map<User*, bool, User::Hash, User::Equal> visited_dfs;  //This is used for dfs cycle
    unordered_map<User*, bool, User::Hash, User::Equal> visited_display;  //This is used for actual recommendation. Those who are already friends won't be recommended.
    for(auto it : us->myfriends){
        visited_display[it]=true;
    }
    visited_dfs[us]=true;
    visited_display[us]=true;
    char flag;
    int count=0;
    help_recommend(us, us, visited_dfs, visited_display, flag, count);
    if(count==0){
        cout<<"No mutuals found"<<endl;
    }
    cout<<"Avail more options"<<endl;
}

//This class is for group created between friends
class Group{ 
    public:
    string groupid;
    User* admin;
    vector<User*> members;
    vector<string> commonchat; //Is a vector of common chats
    stack<User*> outrequests;  //This contains a stack of all the users to whom the request have been sent.

    Group(string id){
        this->groupid=id;
        allgroups.push_back(this);
    }
    
    void viewadmin(){
        cout<<"The admin's username is "<<admin->username<<" and userid is "<<admin->userid<<"."<<endl;
    }

    void viewmembers(){
        cout<<"The members are ";
        for(auto it:members){
            cout<<it->userid<<" ";
        }
    }

    void chat(){   //Used to push the new message in the commonchat vector
        string inp;
        cout<<"Enter the message to be sent"<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,inp);
        commonchat.push_back(inp);
    }

    void viewmsg(){     //Used to view the commonchat vector. We traverse in reverse in the vector.
        if(commonchat.empty()){
            cout<<"The chat is empty"<<endl;
            return ;
        }
        for(int i=commonchat.size()-1;i>=0;i--){
            char flag;
            cout<<"Enter `Y` if you want to continue reading chats, else enter `N`"<<endl;
            cin>>flag;
            if(flag=='N'){
                break;
            }
            cout<<commonchat[i]<<endl;
        }
    }

    void adjustmembers(){    //This is only when group is hardcoded in main(). When the group is hardcoded in main(), call this function. This updates all the members->presentgroup
        for(auto it:members){
            for(auto it2:it->presentgroup){
                if(it2==this){
                    return ;
                }
            }
            it->presentgroup.push_back(this);
        }
    }

    void addmember(User* ad, User* newmem){
        if(ad!=admin){   //The first parameter takes in admin, and second parameter is the new member to be added. Only admin can make changes in the group.
            return ;
        }
        if(ad==admin){
            for(auto it:ad->myfriends){
                if(it==newmem){
                    members.push_back(newmem);  //Adding to members vector and adding this group to the presentgroups vector in User.
                    newmem->presentgroup.push_back(this);
                }
            }
        }
    }

    void removemember(User* ad, User* oldmem){   //We first remove from members, and then remove this group from User's presentgroup
        if(ad!=admin){  //Again this leverage is only to admin, so first check if the user is an admin
            return;
        }
        if(ad==admin){
            int i=0;
            for(auto it : members){
                if(it==oldmem){
                    members.erase(members.begin()+i);
                }
                i++;
            }
            int j=0;
            for(auto it : oldmem->presentgroup){
                if(it==this){
                    oldmem->presentgroup.erase(oldmem->presentgroup.begin()+j);
                }
                j++;
            }
        }
    }

};

User* getuser(string myid){
    for(int i=0;i<allusers.size();i++){
        if(allusers[i]->userid==myid){
            return allusers[i];
        }
    }
    return nullptr;
}

Group* getgrp(string grpid){
    for(auto it:allgroups){
        if(it->groupid==grpid){
            return it;
        }
    }
    return NULL;
}

Group* helper_creategroup(User* us1){    //us1 creates a new group and adds us2 in it.
    string myid;
    cout<<"Enter the groupid of the new group"<<endl;
    cin>>myid;
    Group* mygroup=new Group(myid);
    mygroup->admin=us1;
    mygroup->members.push_back(us1);
    cout<<"Now start adding members in the group (Member to be added should be a friend)"<<endl;
    while(true){
        char flag;
        cout<<"Enter `Y` if you want to continue adding members in the group, else enter `N`"<<endl;
        cin>>flag;
        if(flag=='N'){
            break;
        }
        string newmember;
        cout<<"Enter the userid of the new member to be added"<<endl;
        cin>>newmember;
        User* newus=getuser(newmember);
        for(auto it:us1->myfriends){
            if(it==newus){
                mygroup->addmember(us1,newus);
                cout<<"New member has been added"<<endl;
            }
        }
    }
    return mygroup;
}

void leave_group(User* us, string grpid){  //User wants to leave a group
    Group* leftgrp=getgrp(grpid);
    int count=0;
    if(us==leftgrp->admin){
        string newad;
        cout<<"Enter the userid of the next admin"<<endl;
        cin>>newad;
        leftgrp->admin=getuser(newad);
    }
    for(auto it:leftgrp->members){   //Removing user from members list of group
        if(it==us){
            leftgrp->members.erase(leftgrp->members.begin()+count);
        }
        count++;
    }
    int count2=0;
    for(auto it:us->presentgroup){  //Removing the group from user's present-group list
        if(it==leftgrp){
            us->presentgroup.erase(us->presentgroup.begin()+count2);
        }
        count2++;
    }

}


class Community{ 
    public:
    string communityid;
    User* admin;
    vector<User*> members;
    vector<string> commonchat;

    Community(string id){
        this->communityid=id;
        allcommunities.push_back(this);
    }
    
    void viewadmin(){
        cout<<"The admin's username is "<<admin->username<<" and userid is "<<admin->userid<<"."<<endl;
    }

    void viewmembers(){
        cout<<"The members are ";
        for(auto it:members){
            cout<<it->userid<<" ";
        }
    }

    void chat(){
        string inp;
        cout<<"Enter the message to be sent"<<endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,inp);
        commonchat.push_back(inp);
    }

    void viewmsg(){
        if(commonchat.empty()){
            cout<<"The chat is empty"<<endl;
            return ;
        }
        for(int i=commonchat.size()-1;i>=0;i--){
            char flag;
            cout<<"Enter `Y` if you want to continue reading chats, else enter `N`"<<endl;
            cin>>flag;
            if(flag=='N'){
                break;
            }
            cout<<commonchat[i]<<endl;
        }
    }

    void adjustmembers(){
        for(auto it:members){
            for(auto it2:it->presentcommunity){
                if(it2==this){
                    return ;
                }
            }
            it->presentcommunity.push_back(this);
        }
    }

   void removemember(User* ad, User* oldmem){   //We first remove from members, and then remove this community from User's presentcommunity
        if(ad!=admin){
            return;
        }
        if(ad==admin){
            int i=0;
            for(auto it : members){
                if(it==oldmem){
                    members.erase(members.begin()+i);
                }
                i++;
            }
            int j=0;
            for(auto it : oldmem->presentcommunity){
                if(it==this){
                    oldmem->presentcommunity.erase(oldmem->presentcommunity.begin()+j);
                }
                j++;
            }
        }
   }

};

Community* getcommunity(string comid){
    for(auto it:allcommunities){
        if(it->communityid==comid){
            return it;
        }
    }
    return NULL;
}

bool check_exists(vector<User*> com){  //To check if the detected cycle is an already existing community or not 
    int n=com.size();
    for(auto it : allcommunities){
        int count=0;
        if(it->members.size()==n){
            for(int i=0;i<n;i++){
                User* temp=com[i];
                for(auto it2:it->members){
                    if(it2==temp){
                        count++;
                        break;
                    }
                }
            }
        }
        if(count==n){
            return true;
        }
    }
    return false;
}

void dfstraversal(User* us, vector<User*> &ans, unordered_map<User*, bool, User::Hash, User::Equal> &dfsvisited){  //If user is in a cycle, then returns all users in the cycle
    dfsvisited[us]=true;
    ans.push_back(us);
    for(auto it : us->myfriends){
        if(!dfsvisited[it]){
            dfstraversal(it,ans,dfsvisited);
        }
    }
}

void detect_cycle(unordered_map<User*, bool, User::Hash, User::Equal> &visited, User* us, User* parent, bool &flag){ //Checks if user is in a cycle
    visited[us]=true;
    for(auto it:us->myfriends){
        if(!visited[it]){
            detect_cycle(visited,it,us,flag);
        }
        else if(parent!=nullptr && it!=parent){
            flag=true;
            return ;
        }
        if(flag){
            return ;
        }
    }
}

Community* recommend_community(User* us){  //This recommends community to the user
    vector<User*> ans;
    unordered_map<User*, bool, User::Hash, User::Equal> visited;
    unordered_map<User*, bool, User::Hash, User::Equal> dfsvisited;
    bool flag=false;
    for(auto it:allusers){
        visited[it]=false;
        dfsvisited[it]=false;
    }
    detect_cycle(visited,us,nullptr,flag);  //First we detect if the user is in a cycle. If yes, then only a community will be recommended to him.
    if(!flag){
        cout<<"Currently, you can't form a community. Connect more to form a community."<<endl;
    }
    if(flag){
        dfstraversal(us,ans,dfsvisited);
        if(check_exists(ans)){   //This checks if a community with the same users exists or not. If exists, then we won't proceed
            cout<<"You are already in a community"<<endl;
            return NULL;
        }
        cout<<"The following userid's can form a community-"<<endl;
        cout<<endl;
        for(auto it : ans){
            cout<<it->userid<<" ";
        }
        char decider;
        cout<<"Do you want to send request to all of them to form a community ? Enter `N` to ignore and leave, else enter `Y`."<<endl;
        cin>>decider;
        if(decider=='N'){
            return NULL;
        }
        string myid;
        cout<<"Enter the communityid"<<endl;
        cin>>myid;
        Community* mycom=new Community(myid);
        mycom->admin=us;
        for(auto it:ans){
            mycom->members.push_back(it);
            it->presentcommunity.push_back(mycom);
        }
        return mycom;
    }
    return NULL;
}

void leave_community(User* us, string comid){  //User wants to leave a group
    Community* leftcom=getcommunity(comid);
    int count=0;
    if(us==leftcom->admin){
        string nextad;
        cout<<"Enter the userid of the next admin"<<endl;
        cin>>nextad;
        leftcom->admin=getuser(nextad); 
    }
    for(auto it:leftcom->members){   //Removing user from members list of group
        if(it==us){
            leftcom->members.erase(leftcom->members.begin()+count);
        }
        count++;
    }
    int count2=0;
    for(auto it:us->presentcommunity){  //Removing the group from user's present-group list
        if(it==leftcom){
            us->presentcommunity.erase(us->presentcommunity.begin()+count2);
        }
        count2++;
    }
}

//Now starts the functions for user interaction

void main_interaction(){
    cout<<"----------------------------WELCOME TO CONNECTME----------------------------"<<endl;
    cout<<endl;
    cout<<endl;
    while(true){
        char flag;
        user_login();
        cout<<"You have logged out"<<endl;
        cout<<"Enter `Y` if you want to log in again, else enter `N`."<<endl;
        cin>>flag;
        if(flag=='N'){
            break;
        }
    }
    cout<<"Thank You. See you Soon. :)"<<endl;
}

void user_login(){
    string usid;
    bool found=false;
    cout<<"Enter the User ID requried"<<endl;
    cin>>usid;
    for(auto i=0;i<allusers.size();i++){
        if(allusers[i]->userid==usid){
            found=true;
            string pswd;
            cout<<"Enter the password of the given UserID"<<endl;
            cin>>pswd;
            if(allusers[i]->accept_user(pswd)){
                redirect1(allusers[i]);
            }
            else{
                cout<<"The Password is wrong"<<endl;
                return ;
            }
        }
    }
    if(!found){
        cout<<"Enter a valid User ID"<<endl;
    }
}  

void redirect1(User* us){
    cout<<"Enter index of which related functionality you want to avail."<<endl;
    cout<<"1.User-Related Functionality"<<endl;
    cout<<"2.Group-Related Functionality"<<endl;
    cout<<"3.Community-Related Functionality"<<endl;
    int sw;
    cin>>sw;
    if(sw==1){
        userfunctionality(us);
    }
    if(sw==2){
        groupfunctionality(us);
    }
    if(sw==3){
        communityfunctionality(us);
    }
}

//Functionalities for User starts from here 
void userfunctionality(User* us){
    char decider;
    while(true){
        cout<<"Enter `Y` if you want to continue, else enter `N`"<<endl;
        cin>>decider;
        if(decider=='N'){
            break;
        }
        userfunctionalityhelper(us);
    }
}

void userfunctionalityhelper(User* us){
    int sw;
    cout<<"Enter the respective index of the function to be done"<<endl;
    cout<<"1. View Friends"<<endl; //viewfriends
    cout<<"2. Send Friend Request"<<endl; //sendfriendrequest
    cout<<"3. View Friend Requests"<<endl; //view_inrequests
    cout<<"4. Accept Friend Requests"<<endl; //accept_friends
    cout<<"5. View Sent Friend Requests"<<endl; //view_outrequests
    cout<<"6. Send Message"<<endl;  //sendmsg
    cout<<"7. View Sent Messages"<<endl; //viewsend
    cout<<"8. View Inbox Messages"<<endl; //viewinbox
    cout<<"9. Create a Group"<<endl; //creategroup
    cout<<"10. Recommend Friends"<<endl; //recommend_friends

    cin>>sw;
    if(sw==1){
        us->viewfriends();
    }

    else if(sw==2){
    User* temp;
        string tempid;
        cout<<"Enter the receiving user's User ID to send the friend request"<<endl;
        cin>>tempid;
        temp=getuser(tempid);
        sendfriendrequest(us,temp);
    }

    else if(sw==3){
        us->view_inrequests();
    }
        
    else if(sw==4){
        us->accept_friends();
    }
        
    else if(sw==5){
        us->view_outrequests();
    }
        
    else if(sw==6){
        User* temp2;
        string temp2id;
        cout<<"Enter the receiving user's User ID to send the message"<<endl;
        cin>>temp2id;
        temp2=getuser(temp2id);
        us->sendmsg(temp2);
    }

    else if(sw==7){
        us->viewsend();
    }

    else if(sw==8){
        us->viewinbox();
    }

    else if(sw==9){
        us->creategroup();
    }

    else if(sw==10){
        recommend_friends(us);
    }

    else{
        cout<<"Enter a valid option"<<endl;
    }
    return ;
        
}

//Functionality for Group starts from here
void groupfunctionality(User* us){
    char decider;
    while(true){
        cout<<"Enter `Y` if you want to continue, else enter `N`"<<endl;
        cin>>decider;
        if(decider=='N'){
            break;
        }
        groupfunctionalityhelper(us);
    }
}

void groupfunctionalityhelper(User* us){
    if(us->presentgroup.empty()){
        cout<<us->userid<<" is present in no group"<<endl;
        return ;
    }
    else{
        string tempid;
        cout<<"Enter the groupid you are interested in"<<endl;
        cout<<"Present Groups-"<<endl;
        for(auto it : us->presentgroup){
            cout<<it->groupid<<" ";
        }
        cin>>tempid;
        groupfunctionalityhelper2(us, getgrp(tempid));
    }
}

void groupfunctionalityhelper2(User* us, Group* grp){
    int sw;
    cout<<"Enter the respective index of the group functionality you want to avail"<<endl;
    cout<<"1. View Admin"<<endl;
    cout<<"2. View Members"<<endl;
    cout<<"3. Send Message in Common Chat"<<endl;
    cout<<"4. View Messages from Common Chat"<<endl;
    cout<<"5. Add Member in the Group(Only for Admin)"<<endl;
    cout<<"6. Remove Member from the Group(Only for Admin)"<<endl;
    cout<<"7. Leave the Group"<<endl;
    cin>>sw;

    if(sw==1){
        grp->viewadmin();
    }

    else if(sw==2){
        grp->viewmembers();
    }

    else if(sw==3){
        grp->chat();
    }

    else if(sw==4){
        grp->viewmsg();
    }

    else if(sw==5){
        string newid;
        User* newmem;
        cout<<"Enter the userid of the new user to be added"<<endl;
        cin>>newid;
        newmem=getuser(newid);
        grp->addmember(us,newmem);
    }

    else if(sw==6){
        string newid;
        User* newmem;
        cout<<"Enter the userid of the user to be removed"<<endl;
        cin>>newid;
        newmem=getuser(newid);
        grp->removemember(us,newmem);
    }

    else if(sw==7){
        leave_group(us,grp->groupid);
    }

    else{
        cout<<"Enter a valid option"<<endl;
    }
}

//Functionality for Community starts from here
void communityfunctionality(User* us){
    char decider;
    while(true){
        cout<<"Enter `Y` if you want to continue, else enter `N`"<<endl;
        cin>>decider;
        if(decider=='N'){
            break;
        }
        communityfunctionalityhelper(us);
    }
}

void communityfunctionalityhelper(User* us){
    if(us->presentcommunity.empty()){
        cout<<us->userid<<" is present in no community"<<endl;
        char decider;
        cout<<"Do you want to get recommended a community? Enter `Y` if yes, else `N`."<<endl;
        if(decider=='N'){
            return ;
        }
        else{
            recommend_community(us);
        }
    }
    else{
        string tempid;
        cout<<"Enter the communityid you are interested in"<<endl;
        cout<<"Present Community-"<<endl;
        for(auto it : us->presentcommunity){
            cout<<it->communityid<<" ";
        }
        cin>>tempid;
        communityfunctionalityhelper2(us, getcommunity(tempid));
    }
}

void communityfunctionalityhelper2(User* us, Community* com){
    int sw;
    cout<<"Enter the respective index of the group functionality you want to avail"<<endl;
    cout<<"1. View Admin"<<endl;
    cout<<"2. View Members"<<endl;
    cout<<"3. Send Message in Common Chat"<<endl;
    cout<<"4. View Messages from Common Chat"<<endl;
    cout<<"5. Remove Member from the Group(Only for Admin)"<<endl;
    cout<<"6. Leave the Group"<<endl;
    cin>>sw;

    if(sw==1){
        com->viewadmin();
    }

    else if(sw==2){
        com->viewmembers();
    }

    else if(sw==3){
        com->chat();
    }

    else if(sw==4){
        com->viewmsg();
    }

    else if(sw==5){
        string newid;
        User* newmem;
        cout<<"Enter the userid of the user to be removed"<<endl;
        cin>>newid;
        newmem=getuser(newid);
        com->removemember(us,newmem);
    }

    else if(sw==6){
        leave_group(us,com->communityid);
    }

    else{
        cout<<"Enter a valid option"<<endl;
    }
}

int main() {
    //Providing hard-coded examples in main()
    User John01("John02","John","John01");  //User Instance(Password,Username,UserID)
    User Ben01("Ben02","Ben","Ben01");
    User Charles01("Charles02","Charles","Charles01");
    User Mathew01("Mathew02","Mathew","Mathew01");
    User Wade01("Wade02","Wade","Wade01");
    User Spencer01("Spencer02","Spencer","Spencer01");
    User Peter01("Peter02","Peter","Peter01");
    User Alice01("Alice02", "Alice", "Alice01");
    User Zayn01("Zayn02", "Zayn", "Zayn01");
    User Derek01("Derek02","Derek","Derek02");
    User Ethan01("Ethan02","Ethan","Ethan01");
    User Greg01("Greg02","Greg","Greg01");

    vector<vector<User*>> allfriends={{&John01,&Charles01},{&John01,&Ben01},{&Ben01,&Mathew01},{&Alice01,&Zayn01},{&Zayn01,&Peter01},{&Peter01,&Spencer01},{&Spencer01,&Wade01},{&Wade01,&Alice01},{&Derek01,&Ethan01},{&Ethan01,&Greg01},{&Greg01,&Derek01}};

    createfriends(&John01,allfriends);
    createfriends(&Ben01,allfriends);
    createfriends(&Charles01,allfriends);
    createfriends(&Mathew01,allfriends);
    createfriends(&Wade01,allfriends);
    createfriends(&Spencer01,allfriends);
    createfriends(&Peter01,allfriends);
    createfriends(&Alice01, allfriends);
    createfriends(&Zayn01, allfriends);
    createfriends(&Ethan01,allfriends);
    createfriends(&Derek01,allfriends);
    createfriends(&Greg01,allfriends);
    cout<<endl;
    //Function call to test the project
    main_interaction();
}
//The name of the class instance and the userid should remain the same for user convinience.