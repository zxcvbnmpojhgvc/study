#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node * left, * right;
};

struct Node * newNode(int data){
    struct Node * new = (struct Node *)malloc(sizeof(struct Node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

struct Node * createNode(struct Node* root ,int data){
    if(root == NULL){
        root = newNode(data);
        return root;
    }

    if(data > root->data){
        root->right = createNode(root->right, data);
    }
    else if (data < root->data)
    {
        root->left  = createNode(root->left, data);
    }
    else if(data == root->data){
        printf("\n%d already exists in the bst\n",data);
    }
    return root;

}

void iPreOrder(struct Node * root){
    if(root == NULL){
        return;
    }

    struct Node * stack[1000];
    int top = -1;
    stack[++top] = root;
    struct Node * current;
    while(top>=0){
        current = stack[top--];
        printf("%d ",current->data);
        if(current->right != NULL){
            stack[++top] = current->right;
        }
        if(current->left != NULL){
            stack[++top] = current->left;
        }
    }
    printf("\n");
}


void iPostOrder(struct Node * root){
    if(root == NULL){
        return;
    }
    struct Node * stack1[1000], * stack2[1000];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    struct Node * current;
    while (top1 > -1)
    {
        current = stack1[top1];
        stack2[++top2] = stack1[top1--];
        if(current->left != NULL){
            stack1[++top1] = current->left;
        }
        if (current->right != NULL)
        {
            stack1[++top1] = current->right;
        } 
    }
    while(top2>-1){
        printf("%d ",stack2[top2--]->data);
    }
    printf("\n");

    
}


void height(struct Node* root){  

    int depth = 0;  
  
    struct Node * queue[1000];
    int front = 0, rear = 0;
    queue[rear] = root;
    queue[++rear] = NULL;
      

    while(front<=rear){  
        struct Node* temp;  
        temp = queue[front++];

        if(temp == NULL){  
            depth++;  
        }  
          
        if(temp != NULL){  
            if(temp->left){  
                queue[++rear] = temp->left;
            }  
            if(temp->right){  
                queue[++rear] = temp->right; 
            }  
        }  
      
        else if(front<=rear){  
            queue[++rear] = NULL;
        }  
    } 
    printf("Height of the tree is : %d\n",depth); 
    
} 


void countNode(struct Node * root){
    if(root == NULL){
        return;
    }

    struct Node * stack[1000];
    int top = -1;
    stack[++top] = root;
    int count = 0;
    struct Node * current;
    while(top>=0){
        current = stack[top--];
        count++;
        if(current->right != NULL){
            stack[++top] = current->right;
        }
        if(current->left != NULL){
            stack[++top] = current->left;
        }
    }
    printf("Node count is : %d\n",count);
}

int main() {
    struct Node* root = NULL;

    int choice, key;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert element\n");
        printf("2. Iterative Preorder Traversal\n");
        printf("3. Iterative Postorder Traversal\n");
        printf("4. Count nodes\n");
        printf("5. Display height of the tree\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Exiting program.\n");
                return 0;
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &key);
                root = createNode(root, key);
                printf("Element %d inserted successfully.\n", key);
                break;
            case 2:
                printf("Preorder traversal is as follows");
                iPreOrder(root);
                break;
            case 3:
                printf("Postorder traversal is as follows");
                iPostOrder(root);
                break;
            case 4:
                countNode(root);
                break;
            case 5:
                height(root);
                break;   
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}



