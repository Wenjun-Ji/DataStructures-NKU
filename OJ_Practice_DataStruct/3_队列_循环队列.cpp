#include<iostream>
using namespace std;
#define MaxSize 10
class SeqQueue {
public:
	int* data;
	int front;
	int rear;
	SeqQueue() {
		data = new int [MaxSize];
		front = rear = 0;
	}
	int getnum(){
		return (rear - front+MaxSize) % MaxSize;//获取队长
	}
	bool isfull() {
		if ((rear+1) % MaxSize == front) return true;//队满条件
		return false;
	}
	bool isempty() {
		if (rear == front)return true;//队空条件
		return false;
	}
	void push(int e) {
		if (!isfull()) {
			data[rear] = e;
			rear = (rear + 1) % MaxSize;//尾指针加一
			//注意这里是先插入元素在将尾下标加一 
			//也就是说保证是rear指向队尾的下一个位置 而队首是有实际数据的 
			//也就是尾指针指向的那块存储单元就是我们牺牲的存贮单元
		}
		else {
			cout << "队列已满"<<endl;
		}
	}
	int pop() {
		if (!isempty()) {
			int temp = data[front];
			front = (front + 1) % MaxSize;//首指针加一
			return temp;
		}
		else {
			cout << "队列为空"<<endl;
		}
	}
	int top() {
		if (!isempty()) {
			int temp = data[front];
			return temp;
		}
		else {
			cout << "队列为空" << endl;
		}
	}
	void show() {
		if (isempty()) return;
		int count = front;
		while (count != rear) {//从首到尾输出
			cout<<data[count++]<<" ";
		}
	}
};







int main(){
	SeqQueue sq;
	sq.push(1);
	sq.push(2);
	sq.push(3);
	sq.push(4);
	sq.show(); cout << endl;
	sq.pop();
	sq.show(); cout << endl;
	system("pause");
	return 0;
}