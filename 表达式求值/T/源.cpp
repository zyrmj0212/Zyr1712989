#include<iostream>
#include<string>
#include<stack>
#include<cmath>
#include <iomanip>//�涨�����ʽ
using namespace std;
bool correct = 1;
double result = 0;//������Ϊ˫���ȸ�����
bool MatchedPairs(string expr)  //�����ʽ�������Ƿ�ƥ��
{
	stack<int>s;
	int length = (int)expr.size();//�ַ�������
	for (int i = 0; i < length; i++) {
		if (expr.at(i) == '(')//������������ѹջ
			s.push(i);
		else
			if (expr.at(i) == ')') {//�����������ͳ�ջ
				if (!s.empty())
					s.pop();
				else//���ջ�գ���ȱ�١�����������ƥ����󣬷���0
				{
					return 0;
				}
			}
	}
	if (!s.empty())//������������ʽ�����ջ�ǿ����ж���ġ�����������ƥ����󣬷���0
	{
		return 0;
	}
	else
		return 1;//����ƥ����ȷ������1
}
int judgePrecedence(char operation)//��������ȼ����ж�
{
	switch (operation)
	{
	case '+':
	case '-':
		return 1; //����ӡ�������򸺺ŵ����ȼ�Ϊ1
	case '*':
	case '/':
	case'%':
		return 2; //����ˡ�����ȡ����������ȼ�Ϊ2
	case '^':
		return 3;
	case '(':
	case '\0':
		return 0; //������ջ�еġ�������ջ���ַ�?�����ȼ�Ϊ0
	}
}
void ReversedPolishNotation(char* s1, char* s2)//��׺ת��׺���沨��ʽ��
{
	stack<char> s;//��һ���ַ�ջ�洢������
	s.push('\0');//ջ���ַ�'\0'  
	int i = 0, j = 0;//i��¼s1��j��¼s2
	char ch = s1[0];
	while (ch != '\0')  //����'\0'����
	{
		if (ch == '(') //���������������ѹջ
		{
			s.push('('); //ѹջ
			ch = s1[++i];
			if (ch == '-')//����Ǹ��ž��Ȳ���
			{
				s2[j++] = '0';
				s2[j++] = ' ';
			}
		}
		else if (ch == ')') //�������')'�Ͱ���'('֮���ȫ����ջ����д��
		{
			while (s.top() != '(') //ѭ����'('�� 
			{
				s2[j++] = s.top();
				s.pop();//��ջ
			}
			s.pop(); //���ɾ��'('
			ch = s1[++i];
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%') //����������
		{
			char t = s.top();  //ջ��Ԫ��
			if ((t == '^') && (ch == '^'))//�η��Ĵη��Ӻ���ǰ��(��������2^2^3תΪ��׺ӦΪ223^^��
			{
				s.push(ch);
				ch = s1[++i];
			}
			else {
				while (judgePrecedence(t) >= judgePrecedence(ch)) //�Ƚ����ȼ���������ű������ջ�����ţ�����Ҳ���ɣ�
				{
					s2[j++] = t;  //���ջ���Ĵ�Ļ��Ͱ�ջ��д��
					s.pop(); //ջ����ջ
					t = s.top();
				}
				s.push(ch);  //ѹ����ַ�
				ch = s1[++i];

			}
		}
		else
		{
			while ((ch >= '0' && ch <= '9') || ch == '.') //��������ֻ�С����
			{
				s2[j++] = ch;   //д���ַ���
				ch = s1[++i];
			}
			s2[j++] = ' ';   //�ÿո������ ����������λ������С��
		}
	}
	ch = s.top();
	s.pop();
	while (ch != '\0')  //��ʣ�����е�����ȡ��д���׺ʽ  '\0'��ջ���ַ�
	{
		s2[j++] = ch;
		ch = s.top();
		s.pop();
	}
	s2[j++] = '\0';
}
void Calculate(char *s) //�����׺ʽ
{
	stack<double> operate;
	int i = 0;
	double n1, n2, n3; //ͬ��
	while (s[i] != '\0') //ѭ�������
	{

		if (s[i] >= '0' && s[i] <= '9') //���������
		{
			double number = 0;//������
			int power = 0;//��ָ��
			while (s[i] >= '0' && s[i] <= '9')
			{
				number = number * 10 + (s[i] - '0');
				i++;
			}
			if (s[i] == '.')
			{
				power = 0;//��ָ����0
				i++;
				while (s[i] >= '0' && s[i] <= '9')
				{
					power--;
					number += pow(10, power) * (s[i] - '0');
					i++;
				}
			}
			operate.push(number);
		}
		else if (s[i] == ' ')  //�������ּ�Ŀո�
			i++;
		else if (s[i] == '+')//�ӷ�
		{
			n1 = operate.top();  //��ջ
			operate.pop();  //ɾ��
			if (operate.empty()) {//����м���߼����ʽ�﷨��ȷ
								  //ջ������ʽ�����ٲ�����
				correct = 0;
				break;
			}
			else {
				n2 = operate.top();
				operate.pop();
				n3 = n2 + n1;
				operate.push(n3); //���ѹջ
				i++;
			}
		}
		else if (s[i] == '-') //����
		{
			n1 = operate.top();
			operate.pop();
			if (operate.empty()) {

				correct = 0;
				break;
			}
			else {
				n2 = operate.top();
				operate.pop();
				n3 = n2 - n1;
				operate.push(n3);
				i++;
			}
		}
		else if (s[i] == '*')//�˷�
		{
			n1 = operate.top();
			operate.pop();
			if (operate.empty()) {

				correct = 0;
				break;
			}
			else {
				n2 = operate.top();
				operate.pop();
				n3 = n2 * n1;
				operate.push(n3);
				i++;
			}
		}
		else if (s[i] == '/')//����
		{
			n1 = operate.top();
			operate.pop();
			if (operate.empty()) {

				correct = 0;
				break;
			}
			else {
				n2 = operate.top();
				operate.pop();

				n3 = n2 / n1;//ע��n1,n2˳��
				operate.push(n3);
				i++;
			}
		}
		else if (s[i] == '^')  //�η�
		{
			n1 = operate.top();
			operate.pop();
			if (operate.empty()) {

				correct = 0;
				break;
			}
			else {
				n2 = operate.top();
				operate.pop();
				n3 = pow(n2, n1);//ע��n2,n1˳��!
				operate.push(n3);
				i++;
			}
		}
		else if (s[i] == '%')//ȡ��
		{
			n1 = operate.top();
			operate.pop();
			if (operate.empty()) {

				correct = 0;
				break;
			}
			else {
				n2 = operate.top();
				operate.pop();
				n3 = ((int)n2) % ((int)n1);//���������ܽ���ȡ�����
				operate.push(n3);
				i++;
			}
		}
	}
	result = operate.top();
	operate.pop();
	if (correct != 0) {
		if ((operate.empty())) {
			cout << setiosflags(ios::fixed) << setprecision(2) << result << endl;
		}
		else {//ջ�ǿգ����ʽ����
			correct = 0;
			cout << "ERROR IN INFIX NOTATION" << endl;
		}
	}
	else {
		cout << "ERROR IN INFIX NOTATION" << endl;
	}
}

int main()
{
	string a;
	cin >> a;
	int count = 0;//�����ʽ���Ƿ񺬷Ƿ��ַ�
	int b = (int)a.size();
	if (MatchedPairs(a)) {//����ƥ��
		char c[100], d[100];//��aһһ��ֵ��c,������'\0'��d��ת����ĺ�׺ʽ
		for (int m = 0; m <= b; m++) {
			if (m != b) {
				c[m] = a[m];
			}
			else
				c[m] = '\0';
		}
		for (int n = 0; n < b; n++) {//�����ʽ�Ƿ񺬷Ƿ��ַ�
			if ((c[n] == '0') || (c[n] == '1') || (c[n] == '2') || (c[n] == '3') || (c[n] == '4') || (c[n] == '5') || (c[n] == '6') || (c[n] == '7') || (c[n] == '8') || (c[n] == '9') || (c[n] == '+') || (c[n] == '-') || (c[n] == '*') || (c[n] == '/') || (c[n] == '%') || (c[n] == '^') || (c[n] == '.') || (c[n] == '(') || (c[n] == ')'))
				count++;
		}

		if (count == b) {//�����Ƿ��ַ�
			ReversedPolishNotation(c, d);//��׺ʽת���ɺ�׺ʽ
			if (correct == 1)//���ʽ��ȷ
				Calculate(d);
		}
		else
			cout << "ERROR IN INFIX NOTATION" << endl;
	}
	else
		cout << "ERROR IN INFIX NOTATION" << endl;

	return 0;
}
