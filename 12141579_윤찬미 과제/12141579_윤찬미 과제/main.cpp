#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

typedef struct Node
{
	Node* parent;   //�θ� ����Ŵ (����Ʈ���� ��ȯ�� Ʈ������ ��¥ �θ�x)  
	Node* child;   //ù��° �ڽ�  
	Node* next;       //���� ���  
	Node* prev;         //������ ������  
	int num; //������ �ִ� ������ ��ȣ  
	Node() : parent(NULL), child(NULL), next(NULL), prev(NULL) {};  	//�� ���� �ʱ�ȭ �Ѵ�. 
}Node;

class Tree  {
public:
	Tree() : Root(NULL), Position(NULL) {}; //�ʱ�ȭ  	
	void searchP(int _p, Node* s)   //p��� ���� ������ �ִ� ��带 ã��  	
	{
		if (s->num == _p)
			Position = s;
		else
		{
			if (s->child != NULL)
				searchP(_p, s->child);   //ó���ڽ��� ������ ��������.    		
			if (s->next != NULL)
				searchP(_p, s->next);
		}
	}
	void insert(int n, int p, int o)  //p�� �θ���ϴ� o��° �ڽ����� n�� ����  
	{
		if (p == -1)   //��Ʈ�� ��� ����  	
		{
			Node* newN = new Node;
			newN->num = n;
			Root = newN;
		}
		else    //��Ʈ�� �ƴҶ�  		
		{
			searchP(p, Root);   //p��� ���� ������ �ִ� �������� ��ġ�� ã��    			
			if (Position == 0)
				cout << p << "��� �����͸� ���� �θ� �����ϴ�" << endl;
			else
			{
				Node *newN = new Node;
				newN->parent = Position;
				if (o == 1)    //ù��° �ڽĿ� ����  			
				{
					if (Position->child == NULL)   //ù��° �ڽ��� ���������  		
						Position->child = newN;
					else    //������� �ʾ�����  			
					{
						Position->child->prev = newN;
						newN->next = Position->child;
						Position->child = newN;
					}
					newN->num = n;
				}
				else    //o��° �ڽĿ� ����  			
				{

					Position = Position->child;
					newN->num = n;
					o--;
					while (o--) {
						if (o == 0 && Position->next == NULL)  // o��°�� �ڽ��� ���� ���  	
						{
							Position->next = newN;
							newN->prev = Position;
						}
						else if (o == 0 && Position->next != NULL) //o��°�� �ڽ��� �ִ� ���  	
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
	BNode() : parent(NULL), left(NULL), right(NULL), num(0) {};//�� ���� �ʱ�ȭ �Ѵ�.

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
			//������ = p���� ������ �ִ� Ʈ������ �θ� ���

			if (Position == NULL)
				cout << p << "��� �����͸� ���� �θ� �����ϴ�" << endl;
			else
			{
				BNode* newN = new BNode;
				newN->num = n;

				if (o == 1)
				{
					if (Position->left == NULL)    //�ڽ��� ���� ���
					{
						Position->left = newN;
						newN->parent = Position;
					}
					else                //���⼭ �߸��ȵ�.
					{
						newN->right = Position->left;
						Position->left->parent = newN;
						Position->left = newN;
						newN->parent = Position;
					}
				}


				else    //o��° ��忡 ����
				{
					//�������� Ʈ������ ù��° �ڽ��̶�� �ٲ�
					Position = Position->left;
					o--;    //ù��° �ڽ����� ���Ŵϱ� -- ����

					while (o--) {

						newN->parent = Position;

						if (o == 0 && Position->right == NULL) //�������� �������(p��� �θ� ���� �������� o��° �ڽ�)�� ���ٸ�
							Position->right = newN;



						else if (o == 0 && Position->right != NULL)
						{
							Position->right->parent = newN;
							newN->right = Position->right;
							Position->right = newN;
						}

						Position = Position->right;   //�������� ���� ���� ���� ��

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
		case 'I': // ���� ���Ǹ� ��Ÿ���� ��ȣ
			cin >> n >> p >> o;
			//n=���ϵ� ����� ��ȣ p=�θ��� ��ȣ o=������ ������ ����
			Sample.insert(n, p, o);
			NomalSample.insert(n, p, o);
			break;

		case 'P': // ������ȸ  	
			NomalSample.Preorder(NomalSample.getRoot());
			cout << endl;
			break;
		case 'T': // ������ȸ  			
			NomalSample.Postorder(NomalSample.getRoot());
			cout << endl;
			break;

		case 'C': // ��ǥ���
			cin >> n; // ����� ����� ��ȣ
			Sample.resetPosition();
			Sample.searchP(n, Sample.getRoot());
			if (Sample.getPosition() == 0)
				cout << "��尡 �������� �ʽ��ϴ�" << endl;

			else //��尡 ������ ��,
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