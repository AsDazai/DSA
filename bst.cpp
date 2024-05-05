#include <iostream>
using namespace std;
struct node
{
    node *left;
    node *right;
    int data;
};
class tree
{
    public:
    node *root;
    void create();
    void insert(node *root,node *nn);
    void display(node *root);
    int longest(node *root);
    void minimum(node *root);
    void mirror(node *root);
    tree()
    {
        root=NULL;
    }
};
void tree :: create()
{
   char ch;
   {
    do
    {
        node *nn=new node;
        nn->left=NULL;
        nn->right=NULL;
        cout<<"Enter the Data to Node: "<<endl;
        cin>>nn->data;
        if(root==NULL)
        {
            root=nn;
        }
        else
        {
            insert(root,nn);
        }
        cout<<"DO YOU WANT TO CONTINUE: "<<endl;
        cin>>ch;
    } while (ch=='y'||ch=='Y');
    
   }
}
void tree :: insert(node *root,node *nn)
{
    if(nn->data < root->data)
    {
        if(root->left==NULL)
        {
            root->left=nn;
        }
        else
        {
            insert(root->left,nn);
        }
    }
    else
    {
        if(root->right==NULL)
        {
            root->right=nn;
        }
        else
        {
            insert(root->right,nn);
        }
    }
}
void tree :: display(node *root)
{
    if(root!=NULL)
    {
    display(root->left);
    cout<<root->data<<" ";
    display(root->right);
    }
}
int tree :: longest(node *root)
{
    if (root==NULL)
    {
        return 0;
    }
    else{
    
    int LEFT=longest(root->left);
    int RIGHT=longest(root->right);
    return max (LEFT,RIGHT)+1;
    }
}
void tree :: minimum(node *root)
{
    if (root->left==NULL)
    {
        cout<<root->data;
    }
    else{
        return minimum(root->left);
    }
}

void tree :: mirror(node *root)
{
    if (root==NULL)
    {
        return;
    }
    else{
        node *temp;
        mirror(root->left);
        mirror(root->right);
        temp=root->left;
        root->left=root->right;
        root->right=temp;

    }
}

int main()
{
    tree t;
    int b;
    char c;
    int cnt;
    do
    {
        cout<<"Which OPeration You Want to Performed: "<<endl;
        cout<<" 1.Create a BST\n 2.Display(inorder)\n 3.Insert new node to bst\n 4.Minimum node\n 5.Longest Path\n6. mirror "<<endl;
        cin>>b;
        switch(b)
        {
            case 1:
            t.create();
            break;

            case 2:
            cout<<"Inorder: "<<endl;
            t.display(t.root);
            break;

            case 3:
            t.create();
            break;

            case 4:
            cout<<"Minimum: ";
            t.minimum(t.root);
            break;

            case 5:
            cout<<"The Longest Path is of nodes: "<<endl;
            cnt = t.longest(t.root);
            cout<<cnt<<endl;
            break;

            case 6:
            t.mirror(t.root);
            break;
        }
    cout<<"Do YOu Want TO Continue(y||Y): ";
    cin>>c;
    } while (c=='y'||c=='Y');
    return 0;
}
