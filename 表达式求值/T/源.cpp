#include<iostream>
#include<string>
#include<stack>
#include<cmath>
#include <iomanip>//规定输出格式
using namespace std;
bool correct = 1;
double result = 0;//输出结果为双精度浮点数
bool MatchedPairs(string expr)  //检查表达式的括号是否匹配
{
	stack<int>s;
	int length = (int)expr.size();//字符串长度
	for (int i = 0; i < length; i++) {
		if (expr.at(i) == '(')//遇到‘（’就压栈
			s.push(i);
		else
			if (expr.at(i) == ')') {//遇到‘）’就出栈
				if (!s.empty())
					s.pop();
				else//如果栈空，则缺少‘（’，括号匹配错误，返回0
				{
					return 0;
				}
			}
	}
	if (!s.empty())//检查完整个表达式，如果栈非空则有多余的‘（’，括号匹配错误，返回0
	{
		return 0;
	}
	else
		return 1;//括号匹配正确，返回1
}
int judgePrecedence(char operation)//运算符优先级的判断
{
	switch (operation)
	{
	case '+':
	case '-':
		return 1; //定义加、减运算或负号的优先级为1
	case '*':
	case '/':
	case'%':
		return 2; //定义乘、除、取余运算的优先级为2
	case '^':
		return 3;
	case '(':
	case '\0':
		return 0; //定义在栈中的‘（’和栈底字符?的优先级为0
	}
}
void ReversedPolishNotation(char* s1, char* s2)//中缀转后缀（逆波兰式）
{
	stack<char> s;//开一个字符栈存储操作符
	s.push('\0');//栈底字符'\0'  
	int i = 0, j = 0;//i记录s1，j记录s2
	char ch = s1[0];
	while (ch != '\0')  //遇到'\0'结束
	{
		if (ch == '(') //如果遇到‘（’就压栈
		{
			s.push('('); //压栈
			ch = s1[++i];
			if (ch == '-')//如果是负号就先补零
			{
				s2[j++] = '0';
				s2[j++] = ' ';
			}
		}
		else if (ch == ')') //如果遇到')'就把与'('之间的全部出栈依次写入
		{
			while (s.top() != '(') //循环至'('处 
			{
				s2[j++] = s.top();
				s.pop();//出栈
			}
			s.pop(); //最后删除'('
			ch = s1[++i];
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%') //如果是运算符
		{
			char t = s.top();  //栈顶元素
			if ((t == '^') && (ch == '^'))//次方的次方从后往前算(如例子中2^2^3转为后缀应为223^^）
			{
				s.push(ch);
				ch = s1[++i];
			}
			else {
				while (judgePrecedence(t) >= judgePrecedence(ch)) //比较优先级（插入符号必须大于栈顶符号，等于也不可）
				{
					s2[j++] = t;  //如果栈顶的大的话就把栈顶写入
					s.pop(); //栈顶出栈
					t = s.top();
				}
				s.push(ch);  //压入此字符
				ch = s1[++i];

			}
		}
		else
		{
			while ((ch >= '0' && ch <= '9') || ch == '.') //如果是数字或小数点
			{
				s2[j++] = ch;   //写入字符串
				ch = s1[++i];
			}
			s2[j++] = ' ';   //用空格隔开数 用于区分两位数或者小数
		}
	}
	ch = s.top();
	s.pop();
	while (ch != '\0')  //将剩余所有的依次取出写入后缀式  '\0'是栈底字符
	{
		s2[j++] = ch;
		ch = s.top();
		s.pop();
	}
	s2[j++] = '\0';
}
void Calculate(char *s) //运算后缀式
{
	stack<double> operate;
	int i = 0;
	double n1, n2, n3; //同上
	while (s[i] != '\0') //循环至最后
	{

		if (s[i] >= '0' && s[i] <= '9') //计算操作数
		{
			double number = 0;//操作数
			int power = 0;//幂指数
			while (s[i] >= '0' && s[i] <= '9')
			{
				number = number * 10 + (s[i] - '0');
				i++;
			}
			if (s[i] == '.')
			{
				power = 0;//幂指数归0
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
		else if (s[i] == ' ')  //忽略数字间的空格
			i++;
		else if (s[i] == '+')//加法
		{
			n1 = operate.top();  //出栈
			operate.pop();  //删除
			if (operate.empty()) {//便进行计算边检查表达式语法正确
								  //栈空则表达式错误：少操作数
				correct = 0;
				break;
			}
			else {
				n2 = operate.top();
				operate.pop();
				n3 = n2 + n1;
				operate.push(n3); //结果压栈
				i++;
			}
		}
		else if (s[i] == '-') //减法
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
		else if (s[i] == '*')//乘法
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
		else if (s[i] == '/')//除法
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

				n3 = n2 / n1;//注意n1,n2顺序！
				operate.push(n3);
				i++;
			}
		}
		else if (s[i] == '^')  //次方
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
				n3 = pow(n2, n1);//注意n2,n1顺序!
				operate.push(n3);
				i++;
			}
		}
		else if (s[i] == '%')//取余
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
				n3 = ((int)n2) % ((int)n1);//浮点数不能进行取余操作
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
		else {//栈非空，表达式错误
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
	int count = 0;//检查表达式中是否含非法字符
	int b = (int)a.size();
	if (MatchedPairs(a)) {//括号匹配
		char c[100], d[100];//将a一一赋值给c,在最后加'\0'，d是转换后的后缀式
		for (int m = 0; m <= b; m++) {
			if (m != b) {
				c[m] = a[m];
			}
			else
				c[m] = '\0';
		}
		for (int n = 0; n < b; n++) {//检查表达式是否含非法字符
			if ((c[n] == '0') || (c[n] == '1') || (c[n] == '2') || (c[n] == '3') || (c[n] == '4') || (c[n] == '5') || (c[n] == '6') || (c[n] == '7') || (c[n] == '8') || (c[n] == '9') || (c[n] == '+') || (c[n] == '-') || (c[n] == '*') || (c[n] == '/') || (c[n] == '%') || (c[n] == '^') || (c[n] == '.') || (c[n] == '(') || (c[n] == ')'))
				count++;
		}

		if (count == b) {//不含非法字符
			ReversedPolishNotation(c, d);//中缀式转换成后缀式
			if (correct == 1)//表达式正确
				Calculate(d);
		}
		else
			cout << "ERROR IN INFIX NOTATION" << endl;
	}
	else
		cout << "ERROR IN INFIX NOTATION" << endl;

	return 0;
}
