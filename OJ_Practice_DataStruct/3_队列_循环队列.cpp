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
		return (rear - front+MaxSize) % MaxSize;//��ȡ�ӳ�
	}
	bool isfull() {
		if ((rear+1) % MaxSize == front) return true;//��������
		return false;
	}
	bool isempty() {
		if (rear == front)return true;//�ӿ�����
		return false;
	}
	void push(int e) {
		if (!isfull()) {
			data[rear] = e;
			rear = (rear + 1) % MaxSize;//βָ���һ
			//ע���������Ȳ���Ԫ���ڽ�β�±��һ 
			//Ҳ����˵��֤��rearָ���β����һ��λ�� ����������ʵ�����ݵ� 
			//Ҳ����βָ��ָ����ǿ�洢��Ԫ�������������Ĵ�����Ԫ
		}
		else {
			cout << "��������"<<endl;
		}
	}
	int pop() {
		if (!isempty()) {
			int temp = data[front];
			front = (front + 1) % MaxSize;//��ָ���һ
			return temp;
		}
		else {
			cout << "����Ϊ��"<<endl;
		}
	}
	int top() {
		if (!isempty()) {
			int temp = data[front];
			return temp;
		}
		else {
			cout << "����Ϊ��" << endl;
		}
	}
	void show() {
		if (isempty()) return;
		int count = front;
		while (count != rear) {//���׵�β���
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