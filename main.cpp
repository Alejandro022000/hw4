#include "ArgumentManager.h"
#include "queue.h"
#include "bst.h"
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main(int argc, char *argv[]) {
  
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));
  /*
    ifstream input("input5.txt");
    ofstream out("output1.txt");
*/
  string inStr; // input string
  my_queue pqueue; // priority queue to save commands
  queue<string> encoded_message; //regular queue to save words to decode
  BST my_bst, *root = NULL; //BST
  int order; //to decide the order of the output (pre, post, or inorder)

  //first get all the commands in the priority queue
  while (getline(input, inStr)) {
    //this will be used at the end to determine order of output of bst
    if (inStr == "Inorder"){
      order = 1;
      continue;
    }
    else if (inStr == "Preorder"){
      order = 2;
      continue;
    }
    else if (inStr == "Postorder"){
      order = 3;
      continue;
    }

    if (inStr.size() != 0) {
        int index = 0;
        string temp_str = "";
        string temp_num="";
        //get everything before the parenthesis
        while(inStr[index]!='('){
          temp_str+=inStr[index];
          index++;
        }
        index++;
        //get the priority value
        while(inStr[index]!=')'){
          temp_num+=inStr[index];
          index++;
        }
        pqueue.enqueue(stoi(temp_num), temp_str);//enqueue
    }
  }

  
  //we are going to read every command in the priority queue
  while(!pqueue.empty()){//if not empty 
    int index = 0;
    string temp_str = "";
    string inStr = pqueue.get_top_val();//get the next command

    //getting the command name. Options:(DECODE,REPLACE,SWAP,REMOVE,ADD,BST)
    while(inStr[index]!=':'){
      temp_str+=inStr[index];//holds command name
      index++;
    }
        
    if(temp_str == "DECODE"){
      index+=2;
      string word = "";//holds the string that needs to be decoded
      while(inStr[index]!=']'){
        word+=inStr[index++];
      }
      encoded_message.push(word);//add the string to the normal queue
    }
    else if(temp_str== "REPLACE"){        
      if(!encoded_message.empty()){ 
        char prev_char,new_char;//replace prev_char with new_char
        index+=2;
        prev_char=inStr[index++];

        if(inStr[index+1]==']')
          new_char=' ';
        else
          new_char = inStr[index+1];

        string word = encoded_message.front();//get the next string in the queue
        encoded_message.pop();
        for(int j=0;j<word.length();j++)      {
            if(word[j]==prev_char)//replace prev_char with new_char
              word[j]=new_char;
        }
        encoded_message.push(word);//push back to the queue
      }
    }
    else if(temp_str=="SWAP"){ 
      if(!encoded_message.empty()){    
        char prev_char,new_char;//swap prev_char with new_char
        index++;
        prev_char=inStr[index+=1];

        if(inStr[index+=1]==']')
          new_char=' ';
        else
          new_char=inStr[index+=1];

        string word = encoded_message.front();
        encoded_message.pop();

        for(int j=0;j<word.length();j++){//swap prev_char with new_char   
          if(word[j]==prev_char)
          word[j]=new_char;
          else if(word[j]==new_char)
          word[j]=prev_char;
        }   
        encoded_message.push(word);//push back to the queue
      }
    }
    else if(temp_str=="REMOVE"){
      if(!encoded_message.empty()){  
        index++;
        string str = encoded_message.front();
        encoded_message.pop();
        string word="";    
        char char_to_remove=inStr[index+=1];//character to remove
        for(int j=0;j<str.length();j++){
          if(str[j]!=char_to_remove)
          word+=str[j];//remove
        }
        encoded_message.push(word);//push back to the queue
      }
    }
    else if(temp_str=="ADD"){      
      if(!encoded_message.empty()){           
        index++;
        string str = encoded_message.front();
        encoded_message.pop();
        string word="";               

        char reference_char = inStr[index+=1];//reference character
        char char_to_add = inStr[index+=2];//character to add

        for(int j=0;j<str.length();j++){
            word+=str[j];
            if(str[j]==reference_char)
              word+=char_to_add; //if found the reference, add the other char
        }
        encoded_message.push(word);//push back to the queue
      }
    }
    else if(temp_str=="BST"){ 
      if(!encoded_message.empty()){        
      root = my_bst.Insert(root, encoded_message.front());//insert to the bst
      encoded_message.pop();//get rid of it, bye bye nena
    }    }
    pqueue.dequeue();//we are done with this command, bring the next one!!!! 
  }

  //now, let's figure out how we are going to output this tree
  switch (order){//told you order will be imprtant ;)
  case 1:  
    cout<<"Printing INORDER"<<endl;
    my_bst.Inorder(root,out);
    break;
  case 2:
    cout<<"Printing PREORDER"<<endl;
    my_bst.Preorder(root,out);
    break;
  case 3:  
    cout<<"Printing POSTORDER"<<endl;
    my_bst.Postorder(root,out);
    break;  
  default:
    break;
  }
  
  //WE ARE DONE BABY!!!!!!!!!!!!!!!
  //take a nap, you deserve it
  return 0;
 
}