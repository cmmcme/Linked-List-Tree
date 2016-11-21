#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

typedef struct Node
{
	Node* parent;   //부모를 가리킴 (이진트리로 변환한 트리에선 진짜 부모x)  
	Node* child;   //첫번째 자식  
	Node* next;       //형제 노드  
	Node* prev;         //전꺼를 저장함  
	int num; //가지고 있는 데이터 번호  
	Node() : parent(NULL), child(NULL), next(NULL), prev(NULL) {};  	//각 값을 초기화 한다. 
}Node;

class Tree  {
public:
	Tree() : Root(NULL), Position(NULL) {}; //초기화  	
	void searchP(int _p, Node* s)   //p라는 값을 가지고 있는 노드를 찾음  	
	{
		if (s->num == _p)
			Position = s;
		else
		{
			if (s->child != NULL)
				searchP(_p, s->child);   //처음자식의 끝까지 내려간다.    		
			if (s->next != NULL)
				searchP(_p, s->next);
		}
	}
	void insert(int n, int p, int o)  //p를 부모로하는 o번째 자식으로 n이 들어가라  
	{
		if (p == -1)   //루트에 노드 삽입  	
		{
			Node* newN = new Node;
			newN->num = n;
			Root = newN;
		}
		else    //루트가 아닐때  		
		{
			searchP(p, Root);   //p라는 값을 가지고 있는 데이터의 위치를 찾음    			
			if (Position == 0)
				cout << p << "라는 데이터를 가진 부모가 없습니다" << endl;
			else
			{
				Node *newN = new Node;
				newN->parent = Position;
				if (o == 1)    //첫번째 자식에 삽입  			
				{
					if (Position->child == NULL)   //첫번째 자식이 비어있을때  		
						Position->child = newN;
					else    //비어있지 않았을때  			
					{
						Position->child->prev = newN;
						newN->next = Position->child;
						Position->child = newN;
					}
					newN->num = n;
				}
				else    //o번째 자식에 삽입  			
				{

					Position = Position->child;
					newN->num = n;
					o--;
					while (o--) {
						if (o == 0 && Position->next == NULL)  // o번째에 자식이 없는 경우  	
						{
							Position->next = newN;
							newN->prev = Position;
						}
						else if (o == 0 && Position->next != NULL) //o번째에 자식이 있는 경우  	
						{
							newN->next = Position->next;
							newN->prev = Position;
							Position->next->prev = newN;
							Position->next = newN;
						}
						Position = Position->next;
					}
				}
			}
		}
	}
	void Preorder(Node *s)
	{
		if (s != NULL)
		{
			cout << s->num << " ";
			if (s->child != NULL)
				Preorder(s->child);

			if (s->next != NULL)
				Preorder(s->next);
		}
	}

	void Postorder(Node *s)
	{
		if (s != NULL)
		{
			if (s->child != NULL)
				Postorder(s->child);

			cout << s->num << " ";

			if (s->next != NULL)
				Postorder(s->next);
		}
	}
	Node* getRoot() { return Root; }
	Node* getPosition() { return Position; }
	void resetPosition() { Position = 0; }

private:
	Node* Root;
	Node* Position;
};

typedef struct BNode
{
	BNode* parent;
	BNode* left;
	BNode* right;
	int num;
	BNode() : parent(NULL), left(NULL), right(NULL), num(0) {};//각 값을 초기화 한다.

}BNode;

class BinaryTree
{
public:
	BinaryTree() :x(1), count(1), Root(NULL), Position(NULL) {};
	void searchP(int _p, BNode* s)
	{
		if (s->num == _p)
			Position = s;
		else
		{
			if (s->left != NULL)
				searchP(_p, s->left);
			if (s->right != NULL)
				searchP(_p, s->right);
		}
	}

	void insert(int n, int p, int o)
	{
		if (p == -1)
		{
			BNode* newN = new BNode;
			newN->num = n;
			Root = newN;
		}
		else
		{
			searchP(p, Root);
			//포지션 = p값을 가지고 있는 트리에서 부모 노드

			if (Position == NULL)
				cout << p << "라는 데이터를 가진 부모가 없습니다" << endl;
			else
			{
				BNode* newN = new BNode;
				newN->num = n;

				if (o == 1)
				{
					if (Position->left == NULL)    //자식이 없는 경우
					{
						Position->left = newN;
						newN->parent = Position;
					}
					else                //여기서 잘못된듯.
					{
						newN->right = Position->left;
						Position->left->parent = newN;
						Position->left = newN;
						newN->parent = Position;
					}
				}


				else    //o번째 노드에 삽입
				{
					//포지션을 트리에서 첫번째 자식이라고 바꿈
					Position = Position->left;
					o--;    //첫번째 자식으론 간거니까 -- 해줌

					while (o--) {

						newN->parent = Position;

						if (o == 0 && Position->right == NULL) //포지션의 형제노드(p라는 부모를 가진 데이터의 o번째 자식)이 없다면
							Position->right = newN;



						else if (o == 0 && Position->right != NULL)
						{
							Position->right->parent = newN;
							newN->right = Position->right;
							Position->right = newN;
						}

						Position = Position->right;   //포지션은 다음 형제 노드로 감

					}
				}
			}
		}
	}

	void Inorder(BNode *s)
	{
		if (s->left != NULL)
			Inorder(s->left);

		if (s == Position)
			x = count;
		else
			count++;

		if (s->right != NULL)
			Inorder(s->right);

	}
	int Depth(BNode *s)
	{
		int depth = 0;
		while (s != Root)
		{
			depth++;
			s = s->parent;
		}
		return depth;
	}
	void resetX() { count = x = 1; }
	int getX() { return x; }
	BNode* getRoot() { return Root; }
	BNode* getPosition() { return Position; }
	void resetPosition() { Position = NULL; }

private:
	BNode* Root;
	BNode* Position;
	int x;
	int count;
};

int main()
{
	char question;
	int n, p, o;
	BinaryTree Sample;
	Tree NomalSample;

	while (1)
	{
		//Input Data
		cin >> question;

		switch (question) {
		case 'I': // 삽입 질의를 나타내는 기호
			cin >> n >> p >> o;
			//n=삽일될 노드의 번호 p=부모노드 번호 o=형제들 사이의 순서
			Sample.insert(n, p, o);
			NomalSample.insert(n, p, o);
			break;

		case 'P': // 전위순회  	
			NomalSample.Preorder(NomalSample.getRoot());
			cout << endl;
			break;
		case 'T': // 후위순회  			
			NomalSample.Postorder(NomalSample.getRoot());
			cout << endl;
			break;

		case 'C': // 좌표출력
			cin >> n; // 출력할 노드의 번호
			Sample.resetPosition();
			Sample.searchP(n, Sample.getRoot());
			if (Sample.getPosition() == 0)
				cout << "노드가 존재하지 않습니다" << endl;

			else //노드가 존재할 때,
			{
				Sample.resetX();
				Sample.Inorder(Sample.getRoot());
				cout << Sample.getX() << " " << Sample.Depth(Sample.getPosition()) << endl;

			}
			break;

		case 'Q':
			return 0;
		}
	}
	return 0;
}