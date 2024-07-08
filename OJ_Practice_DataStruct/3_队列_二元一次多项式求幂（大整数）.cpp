#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
#define MaxSize 100




class LongInt {
public:
	char s[MaxSize];
	LongInt() {
		for (int i = 0; i < MaxSize; i++) { s[i] = '0'; s[0] = '+'; }
	}

	LongInt(const LongInt & x) {
		for (int i = 0; i < MaxSize; i++) { s[i] =x.s[i]; }
	}
	void operator=(LongInt& x) {
		for (int i = 0; i < MaxSize; i++) { s[i] = x.s[i]; }
	}
	LongInt& operator+(LongInt& x) {
		LongInt* result = new LongInt();
		int minwei = (this->weishu() < x.weishu()) ? this->weishu() : x.weishu();
		int jinwei=0;
		int t = 0;
		if (this->iszheng() && x.iszheng()) {
			for (int i = MaxSize - 1; i >= 1; i--) {
				t = this->s[i] - '0' + x.s[i] - '0' + jinwei;
				jinwei = 0;
				if (t >= 10) {
					jinwei += t / 10;
					t %= 10;
				}
				result->s[i] = '0' + t;
			}
		}
		else if (!this->iszheng() && !x.iszheng()) {
			for (int i = MaxSize - 1; i >= 1; i--) {
				t = this->s[i] - '0' + x.s[i] - '0' + jinwei;
				jinwei = 0;
				if (t >= 10) {
					jinwei += t / 10;
					t %= 10;
				}
				result->s[i] = '0' + t;
			}
			result->s[0] = '-';
		}
		else if (this->iszheng() && !x.iszheng()) {
			if (this->AbsLargeThan(x)) {
				for (int i = MaxSize - 1; i >= 1; i--) {
					if (this->s[i] - x.s[i] + jinwei < 0) {						
						t = 10 + this->s[i] - x.s[i] + jinwei;
						jinwei = -1;
					}
					else {
						t = this->s[i] - x.s[i] + jinwei;
						jinwei = 0;
					}
					result->s[i] = '0' + t;
				}
				result->s[0] = '+';
			}
			else {
				for (int i = MaxSize - 1; i >= 1; i--) {
					if (x.s[i] - s[i] + jinwei < 0) {
						t = 10 + x.s[i] - s[i] + jinwei;
						jinwei = -1;
					}
					else {
						t = x.s[i] - s[i] + jinwei;
						jinwei = 0;
					}
					result->s[i] = '0' + t;
				}
				result->s[0] = '-';
			}
		}
		else if (!this->iszheng() && x.iszheng()) {
			if (this->AbsLargeThan(x)) {
				for (int i = MaxSize - 1; i >= 1; i--) {
					if (this->s[i] - x.s[i] + jinwei < 0) {
						t = 10 + this->s[i] - x.s[i] + jinwei;
						jinwei = -1;
					}
					else {
						t = this->s[i] - x.s[i] + jinwei;
						jinwei = 0;
					}
					result->s[i] = '0' + t;
				}
				result->s[0] = '-';
			}
			else {
				for (int i = MaxSize - 1; i >= 1; i--) {
					if (x.s[i] - s[i] + jinwei < 0) {
						t = 10 + x.s[i] - s[i] + jinwei;
						jinwei = -1;
					}
					else {
						t = x.s[i] - s[i] + jinwei;
						jinwei = 0;
					}
					result->s[i] = '0' + t;
				}
				result->s[0] = '+';
			}
		}
		return *result;

	}
	LongInt& operator*(int k) {
		
		int jinwei = 0;
		int t = 0;
		LongInt* result = new LongInt();
		if (k == 0) return *result;
		for (int i = MaxSize - 1; i >= 1; i--) {
			t = (this->s[i] - '0')*k+ jinwei;
			jinwei = 0;
			if (t >= 10) {
				jinwei += t / 10;
				t %= 10;
			}
			result->s[i] = '0' + t;
		}
		return *result;
	}

	LongInt& operator*(LongInt& x) {
		LongInt* result = new LongInt();
		for (int i = MaxSize - 1; i >= 1; i--) {
			LongInt* re = new LongInt(x * (s[i] - '0'));
			int j = MaxSize - 1 - i;
			if (!re->isZero()) {	
				for (int k = 0; k < re->weishu(); k++) {
					re->s[MaxSize - re->weishu() + k - j] = re->s[MaxSize - re->weishu() + k];
				}
				for (int k = 0; k < j; k++) {
					re->s[MaxSize - 1 - k] = '0';
				}
				LongInt temp = (*result + *re);
				*result = temp;
			}
		}
		if ((iszheng() && x.iszheng()) || (!iszheng() && !x.iszheng())) {
			result->s[0] = '+';
		}
		else {
			result->s[0] = '-';
		}	
		return *result;
	}
	friend ostream & operator<<(ostream&cout,LongInt&x) {
		if (x.isZero()) { cout << '0'; return cout; }
		for (int i = 0; i < x.weishu(); i++)
			cout << x.s[MaxSize-x.weishu()+i];
		//cout<<endl;
		return cout;
	}
	friend istream& operator>>(istream&cin, LongInt&x) {
		int ss;
		int count = 0;
		cin >> ss;
		if (ss>0) {
			while (ss != 0) {
				x.s[MaxSize - count - 1] = ss % 10 + '0';
				count++;
				ss /= 10;
			}
		}
		else {
			x.s[0] = '-';
			ss = -ss;
			while (ss != 0) {
				x.s[MaxSize - count - 1] = ss % 10 + '0';
				count++;
				ss /= 10;
			}
		}
		return cin;
	}

	int weishu() {
		for(int i=1;i<MaxSize;i++){
			if (s[i] != '0') {
				return MaxSize - i;
			}
		}
		return 0;
	}

	bool LargeThan(LongInt& x) {
		if (this->s[0] == '+' && this->s[0] == '-') {
			return true;
		}
		else if (this->s[0] == '-' && this->s[0] == '+') {
			return false;
		}
		else if(this->s[0] == '+' && this->s[0] == '+'){
			for (int i = 1; i < MaxSize;i++) {
				if (s[i] > x.s[i]) return true;
				if (s[i] < x.s[i])return false;
			}
		}
	}

	bool AbsLargeThan(LongInt& x) {
		for (int i = 1; i < MaxSize; i++) {
			if (s[i] > x.s[i]) return true;
			if (s[i] < x.s[i])return false;
		}
	}



	bool iszheng() {
		if (s[0] == '+') return true;
		return false;
	}
	bool isZero() {
		if (weishu() == 0&&s[MaxSize-1]=='0') {
			return true;
		}
		return false;
	}

	bool iszhengOne() {
		if (weishu() == 1 && s[MaxSize - 1] == '1'&&s[0]=='+') {
			return true;
		}
		return false;
	}
	bool isfuOne() {
		if (weishu() == 1 && s[MaxSize - 1] == '1' && s[0] == '-') {
			return true;
		}
		return false;
	}

};


struct Node {
	LongInt data;
	Node* next;
	Node():next(NULL) {}
	Node(LongInt& i):data(i),next(NULL) {}
	Node(Node *p):data(p->data),next(NULL){}
};
struct Queue {
	Node* head;
	Node* tail;
	Queue() { head = tail = NULL; }
	void push(Node *p) {
		if (head == NULL) head=tail=p;
		else {
			tail->next = p;
			tail = tail->next;
		}
	}
	Node* pop() {
		if (head == NULL) return NULL;
		Node* p = head;
		head = head->next;
		p->next = NULL;
		return p;
	}
	Node * front() {
		return head;
	}
	bool isempty() {
		if (head == NULL)return true;
		return false;
	}
};

//自定义数据类型大整数



int main() {
	Node* a = new Node(), * b = new Node();
	Node* s = new Node(), * t = new Node();
	int n;
	Queue q;
	//cin >> a >> b>>t>>w;
	//cout << a << endl;
	//cout << b << endl;
	//cout << t << endl;
	//cout << w << endl;
	//cout << a * b << endl;
	//cout << t * w << endl;
	//cout << (a+b)*(a * b + t * w);

	cin >> a->data >> b->data;
	cin >> n;
	//cout << a->data + b->data;
	//cout << n << endl;



	
	q.push(new Node(a));
	q.push(new Node(b));
	s = new Node();
	t = new Node();
	for (int i = 1; i < n; i++){
		q.push(new Node());
		for (int j = 1; j <= i + 2; j++) {
			t = new Node(q.front());
			q.pop();
			//cout <<"a:" << a->data << endl;
			//cout <<"b:" << b->data << endl;
			//cout <<"s:" << s->data << endl;
			//cout <<"t:" << t->data << endl;
			//cout <<"at:" << (a->data * t->data).s[0] << a->data * t->data << endl;
			//cout <<"bs:" << (b->data * s->data).s[0]<<b->data * s->data << endl;
			//cout <<"和:" << a->data * t->data + b->data * s->data << endl;
			q.push(new Node(a->data * t->data + b->data * s->data));
			s = new Node(t);

			if (j != i + 2) {
				//cout << s->data <<" ";//因为输出的是s 所以实际上最后一行并未输出 程序确实执行了10行 但第一行我们已经初始化了 所以最后一行是第11行
			}
		}
		//cout << endl;
	}


	int x = n, y = 0, count = 0;
	Node* p = q.head;
	//while (p != NULL) {
	//	cout << p->data << " ";
	//	p = p->next;
	//}
	//cout << endl;
	//p = q.head;
	while (p!= NULL) {
		if (!p->data.isZero()) {
			if (p->data.s[0] == '+' && count > 0)cout << '+';
			if (p->data.s[0] == '-')cout << '-';
			if(!p->data.isfuOne()&&!p->data.iszhengOne())cout << p->data;
			count++;
			if (x == 1) { cout << "x"; }
			else if (x > 1) { cout << "x^" << x; }
			if (y == 1) { cout << "y"; }
			else if (y > 1) { cout << "y^" << y; }
		}
		x--;
		y++;
		p=p->next;
	}



	system("pause");

	return 0;
}