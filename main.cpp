#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

struct node{
float data;
node *left, *right;
int occurance = 1;
};
node *insertData(float x, node* t){
  node *temp;
  if(t){
    if(x == t->data){
      (t->occurance)++;
    }
    else if(x < t->data){
      t->left = insertData(x, t->left);
    }
    else if (x > t->data){
      t->right = insertData(x, t->right);
    }
    return t;
  }
  else{
    temp = new(node);
    temp->data = x;
    temp->left = temp->right = 0;
    return temp;
  }
}  
node *minValueNode(node* t){
  while(t->left != 0){
    t = t->left;
  }
  return t;
}
node *deleteNode(float x, node* t){
  if(t){
    if(x < t->data){
      t->left = deleteNode(x, t->left);
    }
    else if(x > t->data){
      t->right = deleteNode(x, t->right);
    }
    else{
      if(t->occurance > 1){
        (t->occurance)--;
        return t;
      }
      else if(t->left == 0){
        node *temp = t->right;
        delete t;
        return temp;
      }
      else if(t->right == 0){
        node *temp = t->left;
        delete t;
        return temp;
      }
      else{
        node *temp = minValueNode(t->right);
        t->data = temp->data;
        t->occurance = temp->occurance;
        temp->occurance = 0;
        t->right = deleteNode(temp->data, t->right);
      }     
    }
  }
  else{
    cout << "There is no data to delete" << endl;
  }
  return t;
}
string openFile(string fpath){
  string data, x;
  ifstream inFile;
  inFile.open(fpath);
  if(!inFile){
    cout << "File Error or Missing" << endl;
  }
  else{
    while(inFile >> x){
      data += x + " ";
    }
    inFile.close();
    cout << "Data : " << data << endl;
  }
  return data;
}

void inOrder(node* n, int level, int swing){
  int i;
  if(n){
    inOrder(n->left, level-1, 1);
    for(i = 0; i <= level; i++){
      cout << "\t";
    }
    cout << n->data << "(" << n->occurance << ")";
    if(swing == 1){
      cout << "\\\n";
    }
    else if(swing){
      cout << "\/\n";
    }
    inOrder(n->right, level-1, 2);
  }
  else{
    cout << endl;
  }
}
int main() {
  float c;
  char que, retry;
  node *root = 0;
  bool bruh = true;
  string fpath, data, num;
  
  while(bruh){
    cout << "What you want to do?\n1. Input from File\n2. Input\n3. Delete\n4. Print\n5. Exit\nAnswer : ";
    cin >> que;
    switch(que){
      case('1'):
        cout << "Enter the file path" << endl;
        cin >> fpath;
        data = openFile(fpath);
        for(int i = 0; i < data.length(); i++){       
          if(isspace(data[i])){
            c = stof(num);
            num = "";
            root = insertData(c, root);
          }
          else{
            num += data[i]; 
          }
        }
        break;
      case('2'): 
        do{
          cout << "\nPlease input the data (Numerical Value) : \n";
          cin >> c;
          root = insertData(c, root);
          cout << "Want to enter again? (y/n) : ";
          cin >> retry;
        }while(retry == 'y' || retry == 'Y');
        break;
      case('3'): 
        do{
          cout << "What node do you want to delete ?" << endl;
          cin >> c;
          deleteNode(c, root);
          cout << "Want to delete again? (y/n) : ";
          cin >> retry;
        }while(retry == 'y' || retry == 'Y');
        break;
      case('4'): 
        inOrder(root, 7, 0);
        break;
      case('5'):
        cout << "---------------- Thank you ----------------" << endl;
        bruh = false;
        break;
    }
  }
  return 0;
}