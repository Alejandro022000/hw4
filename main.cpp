#include "ArgumentManager.h"
#include "queue.h"
#include "bst.h"
#include <fstream>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main(int argc, char *argv[]) {
  //my_queue output;

  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));

  /*
    ifstream input("input3.txt");
    ofstream out("output1.txt");
  */
  string inStr; // input string
  my_queue pqueue;
  queue<string> encoded_message;
  BST b, *root = NULL;
  int order;


  while (getline(input, inStr)) {
    if (inStr == "Inorder"){
      order =1;
      continue;
    }
    else if (inStr == "Preorder"){
      order =2;
      continue;
    }
    else if (inStr == "InoPostorderrder"){
      order =3;
      continue;
    }

    if (inStr.size() != 0) {
        int index = 0;
        string temp_str = "";
        string temp_num="";
        while(inStr[index]!='('){
          temp_str+=inStr[index];
          index++;
        }
        index++;
        while(inStr[index]!=')'){
          temp_num+=inStr[index];
          index++;
        }
        //cout<<temp_str<< " "<<temp_num<<endl;
        pqueue.enqueue(stoi(temp_num), temp_str);
    }
  }
  //pqueue.print_queue(out);

  
  
  while(!pqueue.empty()){
    //cout<<pqueue.get_top_val()<<endl;
    int index = 0;
    string temp_str = "";
    string temp_num="";
    string inStr = pqueue.get_top_val();
    while(inStr[index]!=':'){
      temp_str+=inStr[index];
      index++;
    }
    
    
    if(temp_str == "DECODE")
      {
        index+=2;
        string word = "";
        while(inStr[index]!=']'){
          word+=inStr[index++];
        }
        encoded_message.push(word);
        //cout<<encoded_message.front()<<endl;
      }
    else if(temp_str== "REPLACE")
      {
        
          char a,b;
          index+=2;
          a=inStr[index++];
          if(inStr[index+1]==']')
          b=' ';
          else
          b = inStr[index+1];
          
          string str = encoded_message.front();
          encoded_message.pop();
          for(int j=0;j<str.length();j++)
          {
              if(str[j]==a)
              str[j]=b;
          }
          encoded_message.push(str);
          //cout<<encoded_message.front()<<endl;
      }
    else if(temp_str=="SWAP")
      { 
        if(!encoded_message.empty()){     
          cout<<"ASDasd"<<endl;
          char a,b;
          index++;
          a=inStr[index+=1];
          if(inStr[index+=1]==']')
          b=' ';
          else
          b=inStr[index+=1];
          //cout<<"swap "<<a<< " "<<b<<endl;
          string str = encoded_message.front();
          encoded_message.pop();

          for(int j=0;j<str.length();j++)
          {
              if(str[j]==a)
              str[j]=b;
              else if(str[j]==b)
              str[j]=a;
          }   
          encoded_message.push(str);
          //cout<<encoded_message.front()<<endl;
        }
      }
    else if(temp_str=="REMOVE")
      {
          string str = encoded_message.front(),t="";
          encoded_message.pop();
          char a;
          index++;
          a=inStr[index+=1];
          for(int j=0;j<str.length();j++)
          {
              if(str[j]!=a)
              t+=str[j];
          }
          encoded_message.push(t);
          //cout<<encoded_message.front()<<endl;
      }
    else if(temp_str=="ADD")
      {               
        string str = encoded_message.front(),t="";
        encoded_message.pop();
        char a,b;
        index++;
        a = inStr[index+=1];
        b = inStr[index+=2];
        for(int j=0;j<str.length();j++)
        {
            t+=str[j];
            if(str[j]==a)
            t+=b;
        }
        encoded_message.push(t);
        //cout<<encoded_message.front()<<endl;
      }
    else if(temp_str=="BST")
      { 
        //cout<<"add to bst: "<<encoded_message.front()<<endl;
        //add to bst
        //pop from encoded_message      
        
        root = b.Insert(root, encoded_message.front());
        encoded_message.pop();  

         

        //encoded_message.pop();      
      }
    
    pqueue.dequeue();
    
    
  }
  switch (order)
  {
  case 1:  
    cout<<"Printing INORDER"<<endl;
    b.Inorder(root,out);
    break;
  case 2:
    cout<<"Printing PREORDER"<<endl;
    b.Preorder(root,out);
    break;
  case 3:  
    cout<<"Printing POSTORDER"<<endl;
    b.Postorder(root,out);
    break;
  
  default:
    break;
  }
  

  return 0;
 
}